
#include "diropener.h"
#include "../config.h"
#include "../options.h"
#include "../codecproblems.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KUrlRequester>
#include <KWindowConfig>
#include <QApplication>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QLocale>
#include <QPushButton>

DirOpener::DirOpener(Config *_config, Mode _mode, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , dialogAborted(false)
    , config(_config)
    , mode(_mode)
    , m_buttonBox(new QDialogButtonBox(this))
{
    setWindowTitle(i18n("Add folder"));
    setWindowIcon(QIcon::fromTheme("folder"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    QPushButton *proceedButton = nullptr;
    if (mode == Convert) {
        m_buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
        proceedButton = new QPushButton(m_buttonBox);
        proceedButton->setText(i18nc("@action:button", "Proceed"));
        proceedButton->setIcon(QIcon::fromTheme("go-next"));
        m_buttonBox->addButton(proceedButton, QDialogButtonBox::ActionRole);

        connect(proceedButton, &QPushButton::clicked, this, &DirOpener::proceedClicked);
    } else if (mode == ReplayGain) {
        m_buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    }

    const int fontHeight = QFontMetrics(QApplication::font()).boundingRect("M").size().height();

    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &DirOpener::addClicked);

    page = DirOpenPage;

    QGridLayout *mainGrid = new QGridLayout;
    QGridLayout *topGrid = new QGridLayout;
    mainGrid->addLayout( topGrid, 0, 0 );
    mainLayout->addLayout(mainGrid);
    mainLayout->addWidget(m_buttonBox);

    lSelector = new QLabel(i18n("1. Select directory"), this);
    QFont font;
    font.setBold( true );
    lSelector->setFont( font );
    topGrid->addWidget( lSelector, 0, 0 );
    lOptions = new QLabel(i18n("2. Set conversion options"), this);
    topGrid->addWidget( lOptions, 0, 1 );

    // draw a horizontal line
    QFrame *lineFrame = new QFrame(this);
    lineFrame->setFrameShape( QFrame::HLine );
    lineFrame->setFrameShadow( QFrame::Sunken );
    mainGrid->addWidget( lineFrame, 1, 0 );

    if( mode == ReplayGain )
    {
        lSelector->hide();
        lOptions->hide();
        lineFrame->hide();
    }

    // Dir Opener Widget

    dirOpenerWidget = new QWidget(this);
    mainGrid->addWidget( dirOpenerWidget, 2, 0 );

    QVBoxLayout *box = new QVBoxLayout( dirOpenerWidget );

    QHBoxLayout *directoryBox = new QHBoxLayout();
    box->addLayout( directoryBox );

    QLabel *labelFilter = new QLabel( i18n("Directory:"), dirOpenerWidget );
    directoryBox->addWidget( labelFilter );

    uDirectory = new KUrlRequester(QUrl("kfiledialog:///soundkonverter-add-media"), dirOpenerWidget);
    uDirectory->setMode( KFile::Directory | KFile::ExistingOnly | KFile::LocalOnly );
    directoryBox->addWidget( uDirectory );

    QLabel *labelDirectory = new QLabel( i18n("Only add selected file formats:"), dirOpenerWidget );
    box->addWidget( labelDirectory );

    QHBoxLayout *fileTypesBox = new QHBoxLayout();
    box->addLayout( fileTypesBox );

    QStringList codecList;
    fileTypes = new QListWidget(dirOpenerWidget);
    if( mode == Convert )
    {
        codecList = config->pluginLoader()->formatList( PluginLoader::Decode, PluginLoader::CompressionType(PluginLoader::InferiorQuality|PluginLoader::Lossy|PluginLoader::Lossless|PluginLoader::Hybrid) );
    }
    else if( mode == ReplayGain )
    {
        codecList = config->pluginLoader()->formatList( PluginLoader::ReplayGain, PluginLoader::CompressionType(PluginLoader::InferiorQuality|PluginLoader::Lossy|PluginLoader::Lossless|PluginLoader::Hybrid) );
    }
    for( int i = 0; i < codecList.size(); i++ )
    {
        if( codecList.at(i) == "audio cd" ) continue;
        QListWidgetItem *newItem = new QListWidgetItem( codecList.at(i), fileTypes );
        newItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsUserCheckable );
        newItem->setCheckState( Qt::Checked );
    }

    QVBoxLayout *fileTypesFormatsBox = new QVBoxLayout();
    fileTypesBox->addLayout( fileTypesFormatsBox );

    fileTypesFormatsBox->addWidget( fileTypes );
    QLabel *formatHelp = new QLabel( "<a href=\"format-help\">" + i18n("Are you missing some file formats?") + "</a>", this );
    connect( formatHelp, SIGNAL(linkActivated(const QString&)), this, SLOT(showHelp()) );
    fileTypesFormatsBox->addWidget( formatHelp );

    QVBoxLayout *fileTypesButtonsBox = new QVBoxLayout();
    fileTypesBox->addLayout( fileTypesButtonsBox );
    fileTypesButtonsBox->addStretch();

    pSelectAll = new QPushButton(QIcon::fromTheme("edit-select-all"), i18n("Select all"), dirOpenerWidget);
    fileTypesButtonsBox->addWidget( pSelectAll );
    connect( pSelectAll, SIGNAL(clicked()), this, SLOT(selectAllClicked()) );

    pSelectNone = new QPushButton(QIcon::fromTheme("application-x-zerosize"), i18n("Select none"), dirOpenerWidget);
    fileTypesButtonsBox->addWidget( pSelectNone );
    connect( pSelectNone, SIGNAL(clicked()), this, SLOT(selectNoneClicked()) );

    cRecursive = new QCheckBox( i18n("Recursive"), dirOpenerWidget );
    cRecursive->setChecked( true );
    cRecursive->setToolTip( i18n("If checked, files from subdirectories will be added, too.") );
    fileTypesButtonsBox->addWidget( cRecursive );

    fileTypesButtonsBox->addStretch();


    // Conversion Options Widget

    options = new Options(config, i18n("Select your desired output options and click on \"Ok\"."), this);
    mainGrid->addWidget( options, 2, 0 );
    adjustSize();
    options->hide();

    const QUrl url = QFileDialog::getExistingDirectoryUrl(this, i18nc("@title:window", "Directory"), uDirectory->url().toLocalFile());
    if( !url.isEmpty() )
        uDirectory->setUrl( url );
    else
        dialogAborted = true;

        // Prevent the dialog from beeing too wide because of the directory history
    if( parent && width() > parent->width() )
        resize(QSize(parent->width() - fontHeight, sizeHint().height()));

    readConfig();
}

DirOpener::~DirOpener()
{
    writeConfig();
}

void DirOpener::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "DirOpener");
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void DirOpener::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "DirOpener");
    KWindowConfig::restoreWindowSize(windowHandle(), group);
}

void DirOpener::proceedClicked()
{
    if( page == DirOpenPage )
    {
        dirOpenerWidget->hide();
        options->show();
        page = ConversionOptionsPage;
        QFont font;
        font.setBold( false );
        lSelector->setFont( font );
        font.setBold( true );
        lOptions->setFont( font );
        m_buttonBox->clear();
        m_buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    }
}

void DirOpener::addClicked()
{
    QStringList selectedCodecs;
    for( int i = 0; i < fileTypes->count(); i++ )
    {
        if( fileTypes->item(i)->checkState() == Qt::Checked )
            selectedCodecs += fileTypes->item(i)->text();
    }

    if( mode == Convert )
    {
        ConversionOptions *conversionOptions = options->currentConversionOptions();
        if( conversionOptions )
        {
            hide();

            emit openFiles( uDirectory->url(), cRecursive->checkState() == Qt::Checked, selectedCodecs, conversionOptions );
            accept();
        }
        else
        {
            KMessageBox::error( this, i18n("No conversion options selected.") );
        }
    }
    else if( mode == ReplayGain )
    {
        hide();
        emit openFiles( uDirectory->url(), cRecursive->checkState() == Qt::Checked, selectedCodecs );
        accept();
    }
}

void DirOpener::selectAllClicked()
{
    for( int i = 0; i < fileTypes->count(); i++ )
    {
        fileTypes->item(i)->setCheckState( Qt::Checked );
    }
}

void DirOpener::selectNoneClicked()
{
    for( int i = 0; i < fileTypes->count(); i++ )
    {
        fileTypes->item(i)->setCheckState( Qt::Unchecked );
    }
}

void DirOpener::showHelp()
{
    QList<CodecProblems::Problem> problemList;

    QMap<QString,QStringList> problems = ( mode == Convert ) ? config->pluginLoader()->decodeProblems() : config->pluginLoader()->replaygainProblems();
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


