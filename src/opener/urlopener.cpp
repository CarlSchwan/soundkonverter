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

#include "urlopener.h"
#include "../config.h"
#include "../options.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KUrlRequester>
#include <KWindowConfig>
#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QLocale>
#include <QPushButton>

// TODO enable proceed button only if at least one file got selected // copy'n'paste error ???

// TODO message box if url can't be added -> maybe in file list

UrlOpener::UrlOpener(Config *_config, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , config(_config)
{
    setWindowTitle(i18nc("@title:window", "Add url"));
    setWindowIcon(QIcon::fromTheme("network-workgroup"));

    page = FileOpenPage;

    const int fontHeight = QFontMetrics(QApplication::font()).boundingRect("M").size().height();

    QGridLayout *mainGrid = new QGridLayout(this);
    QGridLayout *topGrid = new QGridLayout;
    mainGrid->addLayout(topGrid, 0, 0);

    lSelector = new QLabel(i18n("1. Enter url"), this);
    QFont font;
    font.setBold(true);
    lSelector->setFont(font);
    topGrid->addWidget(lSelector, 0, 0);
    lOptions = new QLabel(i18n("2. Set conversion options"), this);
    topGrid->addWidget(lOptions, 0, 1);

    // draw a horizontal line
    QFrame *lineFrame = new QFrame(this);
    lineFrame->setFrameShape(QFrame::HLine);
    lineFrame->setFrameShadow(QFrame::Sunken);
    mainGrid->addWidget(lineFrame, 1, 0);

    QVBoxLayout *urlBox = new QVBoxLayout();
    mainGrid->addLayout(urlBox, 2, 0);
    urlBox->addSpacing(6 * fontHeight);
    urlRequester = new KUrlRequester(this);
    urlRequester->setMode(KFile::File | KFile::ExistingOnly);
    urlBox->addWidget(urlRequester);
    urlBox->addStretch();

    options = new Options(config, i18n("Select your desired output options and click on \"Ok\"."), this);
    mainGrid->addWidget(options, 2, 0);
    adjustSize();
    options->hide();

    // add a horizontal box layout for the control elements
    QHBoxLayout *controlBox = new QHBoxLayout();
    mainGrid->addLayout(controlBox, 5, 0);
    controlBox->addStretch();

    pProceed = new QPushButton(QIcon::fromTheme("go-next"), i18n("Proceed"), this);
    controlBox->addWidget(pProceed);
    connect(pProceed, SIGNAL(clicked()), this, SLOT(proceedClickedSlot()));
    pAdd = new QPushButton(QIcon::fromTheme("dialog-ok"), i18n("Ok"), this);
    controlBox->addWidget(pAdd);
    pAdd->hide();
    connect(pAdd, SIGNAL(clicked()), this, SLOT(okClickedSlot()));
    pCancel = new QPushButton(QIcon::fromTheme("dialog-cancel"), i18n("Cancel"), this);
    controlBox->addWidget(pCancel);
    connect(pCancel, SIGNAL(clicked()), this, SLOT(reject()));

    // Prevent the dialog from beeing too wide because of the directory history
    if (parent && width() > parent->width())
        resize(QSize(parent->width() - fontHeight, sizeHint().height()));
    readConfig();
}

UrlOpener::~UrlOpener()
{
    writeConfig();
}

void UrlOpener::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "UrlOpener");
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void UrlOpener::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "UrlOpener");
    KWindowConfig::restoreWindowSize(windowHandle(), group);
}

void UrlOpener::proceedClickedSlot()
{
    if (page == FileOpenPage) {
        if (!urlRequester->url().isValid()) {
            KMessageBox::information(this, i18n("The Url you entered is invalid. Please try again."));
            return;
        }

        urls += urlRequester->url();

        urlRequester->hide();
        options->show();
        page = ConversionOptionsPage;
        QFont font;
        font.setBold(false);
        lSelector->setFont(font);
        font.setBold(true);
        lOptions->setFont(font);
        pProceed->hide();
        pAdd->show();
    }
}

void UrlOpener::okClickedSlot()
{
    if (page == ConversionOptionsPage) {
        ConversionOptions *conversionOptions = options->currentConversionOptions();
        if (conversionOptions) {
            options->accepted();
            emit openFiles(urls, conversionOptions);
            accept();
        } else {
            KMessageBox::error(this, i18n("No conversion options selected."));
        }
    }
}
