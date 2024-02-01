//
// C++ Implementation: opener
//
// Description:
//
//
// Author: Daniel Faust <hessijames@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "playlistopener.h"
#include "../codecproblems.h"
#include "../config.h"
#include "../options.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QLocale>
#include <QPushButton>

PlaylistOpener::PlaylistOpener(Config *_config, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , dialogAborted(false)
    , config(_config)
{
    setWindowTitle(i18n("Add playlist"));
    setWindowIcon(QIcon::fromTheme("view-media-playlist"));

    const int fontHeight = QFontMetrics(QApplication::font()).boundingRect("M").size().height();

    QGridLayout *mainGrid = new QGridLayout(this);

    options = new Options(config, i18n("Select your desired output options and click on \"Ok\"."), this);
    mainGrid->addWidget(options, 1, 0);

    // add a horizontal box layout for the control elements
    QHBoxLayout *controlBox = new QHBoxLayout();
    mainGrid->addLayout(controlBox, 2, 0);
    controlBox->addStretch();

    pAdd = new QPushButton(QIcon::fromTheme("dialog-ok"), i18n("Ok"), this);
    controlBox->addWidget(pAdd);
    connect(pAdd, SIGNAL(clicked()), this, SLOT(okClickedSlot()));
    pCancel = new QPushButton(QIcon::fromTheme("dialog-cancel"), i18n("Cancel"), this);
    controlBox->addWidget(pCancel);
    connect(pCancel, SIGNAL(clicked()), this, SLOT(reject()));

    // Prevent the dialog from beeing too wide because of the directory history
    if (parent && width() > parent->width())
        resize(QSize(parent->width() - fontHeight, sizeHint().height()));
    readConfig();

    fileDialog = new QFileDialog(this, i18n("Add Files"), QStringLiteral("kfiledialog:///soundkonverter-add-media"), "*.m3u");
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    connect(fileDialog, &QFileDialog::accepted, this, &PlaylistOpener::fileDialogAccepted);
    connect(fileDialog, &QFileDialog::rejected, this, &PlaylistOpener::reject);
    const int dialogReturnCode = fileDialog->exec();
    if (dialogReturnCode == QDialog::Rejected) {
        dialogAborted = true;
    }
}

void PlaylistOpener::fileDialogAccepted()
{
    QStringList errorList;
    //    codec    @0 files @1 solutions
    QMap<QString, QList<QStringList>> problems;
    //     QStringList messageList;
    QString fileName;
    QStringList filesNotFound;

    urls.clear();
    QUrl playlistUrl = fileDialog->selectedUrls().first();
    QFile playlistFile(playlistUrl.toLocalFile());
    if (playlistFile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&playlistFile);
        QString line;
        do {
            line = stream.readLine();
            if (!line.startsWith("#EXTM3U") && !line.startsWith("#EXTINF") && !line.isEmpty()) {
                QUrl url(line);
                if (url.isRelative())
                    url = QUrl(playlistUrl.path() + "/" + line);
                url = url.adjusted(QUrl::NormalizePathSegments);

                if (!url.isLocalFile() || QFile::exists(url.toLocalFile()))
                    urls += url;
                else
                    filesNotFound += url.url(QUrl::PreferLocalFile);
            }
        } while (!line.isNull());
        playlistFile.close();
    }

    const bool canDecodeAac = config->pluginLoader()->canDecode("m4a/aac");
    const bool canDecodeAlac = config->pluginLoader()->canDecode("m4a/alac");
    const bool checkM4a = (!canDecodeAac || !canDecodeAlac) && canDecodeAac != canDecodeAlac;

    for (int i = 0; i < urls.count(); i++) {
        QString mimeType;
        QString codecName = config->pluginLoader()->getCodecFromFile(urls.at(i), &mimeType, checkM4a);

        if (!config->pluginLoader()->canDecode(codecName, &errorList)) {
            fileName = urls.at(i).url(QUrl::PreferLocalFile);

            if (codecName.isEmpty())
                codecName = mimeType;
            if (codecName.isEmpty())
                codecName = fileName.right(fileName.length() - fileName.lastIndexOf(".") - 1);

            if (problems.value(codecName).count() < 2) {
                problems[codecName] += QStringList();
                problems[codecName] += QStringList();
            }
            problems[codecName][0] += fileName;
            if (!errorList.isEmpty()) {
                problems[codecName][1] += errorList;
            } else {
                problems[codecName][1] += i18n(
                    "This file type is unknown to soundKonverter.\nMaybe you need to install an additional soundKonverter plugin.\nYou should have a look at "
                    "your distribution's package manager for this.");
            }
            urls.removeAt(i);
            i--;
        }
    }

    QList<CodecProblems::Problem> problemList;
    for (int i = 0; i < problems.count(); i++) {
        CodecProblems::Problem problem;
        problem.codecName = problems.keys().at(i);
        if (problem.codecName != "wav") {
#if QT_VERSION >= 0x040500
            problems[problem.codecName][1].removeDuplicates();
#else
            QStringList found;
            for (int j = 0; j < problems.value(problem.codecName).at(1).count(); j++) {
                if (found.contains(problems.value(problem.codecName).at(1).at(j))) {
                    problems[problem.codecName][1].removeAt(j);
                    j--;
                } else {
                    found += problems.value(problem.codecName).at(1).at(j);
                }
            }
#endif
            problem.solutions = problems.value(problem.codecName).at(1);
            if (problems.value(problem.codecName).at(0).count() <= 3) {
                problem.affectedFiles = problems.value(problem.codecName).at(0);
            } else {
                problem.affectedFiles += problems.value(problem.codecName).at(0).at(0);
                problem.affectedFiles += problems.value(problem.codecName).at(0).at(1);
                problem.affectedFiles += i18n("... and %1 more files", problems.value(problem.codecName).at(0).count() - 2);
            }
            problemList += problem;
            //             messageList += "<b>Possible solutions for " + codecName + "</b>:\n" + problems.value(codecName).at(1).join("\n<b>or</b>\n") +
            //             i18n("\n\nAffected files:\n") + affectedFiles.join("\n");
        }
    }

    if (problemList.count() > 0) {
        CodecProblems *problemsDialog = new CodecProblems(CodecProblems::Decode, problemList, this);
        problemsDialog->exec();
    }

    //     if( !messageList.isEmpty() )
    //     {
    //         messageList.prepend( i18n("Some files can't be decoded.\nPossible solutions are listed below.") );
    //         QMessageBox *messageBox = new QMessageBox( this );
    //         messageBox->setIcon( QMessageBox::Information );
    //         messageBox->setWindowTitle( i18n("Missing backends") );
    //         messageBox->setText( messageList.join("\n\n").replace("\n","<br>") );
    //         messageBox->setTextFormat( Qt::RichText );
    //         messageBox->exec();
    //     }

    if (!filesNotFound.isEmpty()) {
        int filesNotFoundCount = filesNotFound.count();
        if (filesNotFoundCount > 5) {
            do {
                filesNotFound.removeLast();
            } while (filesNotFound.count() >= 5);
            filesNotFound += i18n("... and %1 more files", filesNotFoundCount - 4);
        }
        filesNotFound.prepend(i18n("The following files couldn't be found:\n"));
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Information);
        messageBox->setWindowTitle(i18n("Files not found"));
        messageBox->setText(filesNotFound.join("\n").replace("\n", "<br>"));
        messageBox->setTextFormat(Qt::RichText);
        messageBox->exec();
    }

    if (urls.count() <= 0)
        reject();
}

PlaylistOpener::~PlaylistOpener()
{
    writeConfig();
}

void PlaylistOpener::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "PlaylistOpener");
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void PlaylistOpener::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "PlaylistOpener");
    KWindowConfig::restoreWindowSize(windowHandle(), group);
}

void PlaylistOpener::okClickedSlot()
{
    ConversionOptions *conversionOptions = options->currentConversionOptions();
    if (conversionOptions) {
        options->accepted();
        Q_EMIT openFiles(urls, conversionOptions);
        accept();
    } else {
        KMessageBox::error(this, i18n("No conversion options selected."));
    }
}
