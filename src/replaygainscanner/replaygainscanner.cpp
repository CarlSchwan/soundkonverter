
#include "replaygainscanner.h"

#include "replaygainfilelist.h"
#include "replaygainprocessor.h"
#include "config.h"
#include "logger.h"
#include "combobutton.h"
#include "opener/diropener.h"
#include "codecproblems.h"
#include "progressindicator.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QApplication>
#include <QBoxLayout>
#include <QCheckBox>
#include <QFileDialog>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QLocale>
#include <QPushButton>
#include <QStringList>

ReplayGainScanner::ReplayGainScanner(Config *_config, Logger *_logger, bool showMainWindowButton, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , config(_config)
    , logger(_logger)
{
    auto layout = new QVBoxLayout(this);

    setWindowTitle(i18n("Replay Gain tool"));
    setWindowIcon(QIcon::fromTheme("soundkonverter-replaygain"));

    const int fontHeight = QFontMetrics(QApplication::font()).boundingRect("M").size().height();

    QWidget *widget = new QWidget( this );
    layout->addWidget(widget);

    QGridLayout* grid = new QGridLayout( widget );

    QHBoxLayout* filterBox = new QHBoxLayout();
    grid->addLayout( filterBox, 0, 0 );

    cAdd = new ComboButton( widget );
    cAdd->insertItem(QIcon::fromTheme("folder"), i18n("Add folder..."));
    cAdd->insertItem(QIcon::fromTheme("audio-x-generic"), i18n("Add files..."));
    filterBox->addWidget( cAdd );
    connect( cAdd, SIGNAL(clicked(int)), this, SLOT(addClicked(int)) );

    filterBox->addStretch();

    pShowMainWindow = new QPushButton(QIcon::fromTheme("soundkonverter"), i18n("Show soundKonverter main window"), widget);
    pShowMainWindow->setVisible( showMainWindowButton );
    filterBox->addWidget( pShowMainWindow );
    connect( pShowMainWindow, SIGNAL(clicked()), this, SLOT(showMainWindowClicked()) );
    
    fileList = new ReplayGainFileList( config, logger, widget );
    grid->addWidget( fileList, 1, 0 );
    connect( fileList, SIGNAL(processStarted()), this, SLOT(processStarted()) );
    connect( fileList, SIGNAL(processStopped()), this, SLOT(processStopped()) );

    QHBoxLayout* progressBox = new QHBoxLayout();
    grid->addLayout( progressBox, 2, 0 );

    progressIndicator = new ProgressIndicator( this );
    progressBox->addWidget( progressIndicator );
    connect( fileList, SIGNAL(timeChanged(float)), progressIndicator, SLOT(timeChanged(float)) );
    connect( fileList, SIGNAL(finished(bool)), progressIndicator, SLOT(finished(bool)) );
    connect( progressIndicator, SIGNAL(progressChanged(const QString&)), this, SLOT(progressChanged(const QString&)) );


    QHBoxLayout* buttonBox = new QHBoxLayout();
    grid->addLayout( buttonBox, 3, 0 );

    pTagVisible = new QPushButton(QIcon::fromTheme("list-add"), i18n("Tag untagged"), widget);
    pTagVisible->setToolTip( i18n("Calculate Replay Gain tags for all files in the file list without Replay Gain tags.") );
    buttonBox->addWidget( pTagVisible );
    connect( pTagVisible, SIGNAL(clicked()), this, SLOT(calcReplayGainClicked()) );

    pRemoveTag = new QPushButton(QIcon::fromTheme("list-remove"), i18n("Untag tagged"), widget);
    pRemoveTag->setToolTip( i18n("Remove the Replay Gain tags from all files in the file list.") );
    buttonBox->addWidget( pRemoveTag );
    connect( pRemoveTag, SIGNAL(clicked()), this, SLOT(removeReplayGainClicked()) );

    pCancel = new QPushButton(QIcon::fromTheme("dialog-cancel"), i18n("Cancel"), widget);
    pCancel->hide();
    buttonBox->addWidget( pCancel );
    connect( pCancel, SIGNAL(clicked()), this, SLOT(cancelClicked()) );

    cForce = new QCheckBox( i18n("Force recalculation"), this );
    cForce->setToolTip( i18n("Recalculate Replay Gain tags for files that already have Replay Gain tags set.") );
    buttonBox->addWidget( cForce );
    
    buttonBox->addStretch();

    pClose = new QPushButton(QIcon::fromTheme("dialog-close"), i18n("Close"), widget);
    pClose->setFocus();
    buttonBox->addWidget( pClose );
    connect( pClose, SIGNAL(clicked()), this, SLOT(closeClicked()) );

    ReplayGainProcessor *replayGainProcessor = new ReplayGainProcessor( config, fileList, logger );
    connect( fileList, SIGNAL(processItem(ReplayGainFileListItem*,ReplayGainPlugin::ApplyMode)), replayGainProcessor, SLOT(add(ReplayGainFileListItem*,ReplayGainPlugin::ApplyMode)) );
    connect( fileList, SIGNAL(killItem(ReplayGainFileListItem*)), replayGainProcessor, SLOT(kill(ReplayGainFileListItem*)) );
    connect( replayGainProcessor, SIGNAL(finished(ReplayGainFileListItem*,ReplayGainFileListItem::ReturnCode)), fileList, SLOT(itemFinished(ReplayGainFileListItem*,ReplayGainFileListItem::ReturnCode)) );
    connect( replayGainProcessor, SIGNAL(updateItem(ReplayGainFileListItem*,bool)), fileList, SLOT(updateItem(ReplayGainFileListItem*,bool)) );

    connect( replayGainProcessor, SIGNAL(finishedProcess(int,bool)), logger, SLOT(processCompleted(int,bool)) );

    connect( replayGainProcessor, SIGNAL(updateTime(float)), progressIndicator, SLOT(update(float)) );
    connect( replayGainProcessor, SIGNAL(timeFinished(float)), progressIndicator, SLOT(timeFinished(float)) );

    resize(QSize(60 * fontHeight, 40 * fontHeight));
    readConfig();
}

ReplayGainScanner::~ReplayGainScanner()
{
    writeConfig();
}

void ReplayGainScanner::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), u"ReplayGainTool"_s);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
}

void ReplayGainScanner::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), u"ReplayGainTool"_s);
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void ReplayGainScanner::addClicked( int index )
{
    if( index == 1 )
    {
        showFileDialog();
    }
    else
    {
        showDirDialog();
    }
}

void ReplayGainScanner::showFileDialog()
{
    QStringList filterList;
    QStringList allFilter;
    const QStringList formats = config->pluginLoader()->formatList( PluginLoader::ReplayGain, PluginLoader::CompressionType(PluginLoader::InferiorQuality|PluginLoader::Lossy|PluginLoader::Lossless|PluginLoader::Hybrid) );
    foreach( QString format, formats )
    {
        QString extensionFilter = config->pluginLoader()->codecExtensions(format).join(" *.");
        if( extensionFilter.length() == 0 )
            continue;
        extensionFilter = "*." + extensionFilter;
        allFilter += extensionFilter;
        filterList += extensionFilter + "|" + i18n("%1 files",format.replace("/","\\/"));
    }
    filterList.prepend( allFilter.join(" ") + "|" + i18n("All supported files") );
    filterList += "*.*|" + i18n("All files");

    // add the control elements
    auto urls = QFileDialog::getOpenFileUrls(this, i18n("Add Files"), QUrl("kfiledialog:///soundkonverter-add-media"), filterList.join("\n"));

    QStringList errorList;
    //    codec    @0 files @1 solutions
    QMap< QString, QList<QStringList> > problems;
    QString fileName;

    const bool canDecodeAac = config->pluginLoader()->canDecode( "m4a/aac" );
    const bool canDecodeAlac = config->pluginLoader()->canDecode( "m4a/alac" );
    const bool checkM4a = ( !canDecodeAac || !canDecodeAlac ) && canDecodeAac != canDecodeAlac;

    for( int i=0; i<urls.count(); i++ )
    {
        QString mimeType;
        QString codecName = config->pluginLoader()->getCodecFromFile( urls.at(i), &mimeType, checkM4a );

        if( !config->pluginLoader()->canReplayGain(codecName,0,&errorList) )
        {
            fileName = urls.at(i).toDisplayString(QUrl::PreferLocalFile);

            if( codecName.isEmpty() )
                codecName = mimeType;
            if( codecName.isEmpty() )
                codecName = fileName.right(fileName.length()-fileName.lastIndexOf(".")-1);

            if( problems.value(codecName).count() < 2 )
            {
                problems[codecName] += QStringList();
                problems[codecName] += QStringList();
            }
            problems[codecName][0] += fileName;
            if( !errorList.isEmpty() )
            {
                problems[codecName][1] += errorList;
            }
            else
            {
                problems[codecName][1] += i18n("This file type is unknown to soundKonverter.\nMaybe you need to install an additional soundKonverter plugin.\nYou should have a look at your distribution's package manager for this.");
            }
            urls.removeAt(i);
            i--;
        }
    }

    QList<CodecProblems::Problem> problemList;
    for( int i=0; i<problems.count(); i++ )
    {
        CodecProblems::Problem problem;
        problem.codecName = problems.keys().at(i);
        if( problem.codecName != "wav" )
        {
            #if QT_VERSION >= 0x040500
            problems[problem.codecName][1].removeDuplicates();
            #else
            QStringList found;
            for( int j=0; j<problems.value(problem.codecName).at(1).count(); j++ )
            {
                if( found.contains(problems.value(problem.codecName).at(1).at(j)) )
                {
                    problems[problem.codecName][1].removeAt(j);
                    j--;
                }
                else
                {
                    found += problems.value(problem.codecName).at(1).at(j);
                }
            }
            #endif
            problem.solutions = problems.value(problem.codecName).at(1);
            if( problems.value(problem.codecName).at(0).count() <= 3 )
            {
                problem.affectedFiles = problems.value(problem.codecName).at(0);
            }
            else
            {
                problem.affectedFiles += problems.value(problem.codecName).at(0).at(0);
                problem.affectedFiles += problems.value(problem.codecName).at(0).at(1);
                problem.affectedFiles += i18n("... and %1 more files",problems.value(problem.codecName).at(0).count()-2);
            }
            problemList += problem;
        }
    }

    if( problemList.count() > 0 )
    {
        CodecProblems *problemsDialog = new CodecProblems( CodecProblems::ReplayGain, problemList, this );
        problemsDialog->exec();
    }

    if( urls.count() > 0 )
        fileList->addFiles( urls );
}

void ReplayGainScanner::showHelp()
{
    QList<CodecProblems::Problem> problemList;
    const QMap<QString,QStringList> problems = config->pluginLoader()->replaygainProblems();
    for( int i=0; i<problems.count(); i++ )
    {
        CodecProblems::Problem problem;
        problem.codecName = problems.keys().at(i);
        if( problem.codecName != "wav" )
        {
            problem.solutions = problems.value(problem.codecName);
            problemList += problem;
        }
    }

    CodecProblems *problemsDialog = new CodecProblems( CodecProblems::Debug, problemList, this );
    problemsDialog->exec();
}

void ReplayGainScanner::showDirDialog()
{
    DirOpener *dialog = new DirOpener( config, DirOpener::ReplayGain, this );

    if( !dialog->dialogAborted )
    {
        connect( dialog, SIGNAL(openFiles(const QUrl&,bool,const QStringList&)), fileList, SLOT(addDir(const QUrl&,bool,const QStringList&)) );

        dialog->exec();

        disconnect( dialog, SIGNAL(openFiles(const QUrl&,bool,const QStringList&)), 0, 0 );
    }

    delete dialog;
}

void ReplayGainScanner::showMainWindowClicked()
{
    pShowMainWindow->hide();
    emit showMainWindow();
}

void ReplayGainScanner::addFiles( QList<QUrl> urls )
{
    fileList->addFiles( urls );
}

void ReplayGainScanner::calcReplayGainClicked()
{
    fileList->startProcessing( cForce->isChecked() ? ReplayGainPlugin::Force : ReplayGainPlugin::Add );
}

void ReplayGainScanner::removeReplayGainClicked()
{
    fileList->startProcessing( ReplayGainPlugin::Remove );
}

void ReplayGainScanner::cancelClicked()
{
    fileList->cancelProcess();
}

void ReplayGainScanner::closeClicked()
{
    if( pCancel->isVisible() )
    {
        const int ret = KMessageBox::questionTwoActions(this,
                                                        i18n("There are still Replay Gain jobs running."),
                                                        i18n("Do you really want to stop them?"),
                                                        KStandardGuiItem::stop(),
                                                        KStandardGuiItem::cancel());
        if (ret == KMessageBox::PrimaryAction) {
            fileList->cancelProcess();
        } else {
            return;
        }
    }

    accept();
}

void ReplayGainScanner::processStarted()
{
    pTagVisible->hide();
    pRemoveTag->hide();
    pCancel->show();
}

void ReplayGainScanner::processStopped()
{
    pTagVisible->show();
    pRemoveTag->show();
    pCancel->hide();
}

void ReplayGainScanner::progressChanged( const QString& progress )
{
    setWindowTitle(progress + " - " + i18n("Replay Gain tool"));
}
