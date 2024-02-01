
#include "logviewer.h"
#include "logger.h"

#include <QApplication>
#include <QLabel>
#include <QLayout>

#include <KComboBox>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QIcon>
#include <QLocale>
#include <QPushButton>
#include <QTextEdit>

using namespace Qt::Literals::StringLiterals;

LogViewer::LogViewer(Logger *_logger, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , logger(_logger)
{
    const int fontHeight = QFontMetrics(QApplication::font()).boundingRect("M").size().height();

    connect(logger, SIGNAL(removedProcess(int)), this, SLOT(processRemoved(int)));
    connect(logger, SIGNAL(updateProcess(int)), this, SLOT(updateProcess(int)));

    setWindowTitle(i18nc("@title:window", "Log Viewer"));
    setWindowIcon(QIcon::fromTheme("view-list-text"));

    QVBoxLayout *box = new QVBoxLayout(this);

    QHBoxLayout *topBox = new QHBoxLayout;
    box->addLayout(topBox);
    QLabel *lItem = new QLabel(i18n("Log file:"));
    topBox->addWidget(lItem);
    topBox->setStretchFactor(lItem, 0);
    cItem = new KComboBox(this);
    topBox->addWidget(cItem);
    topBox->setStretchFactor(cItem, 1);
    connect(cItem, SIGNAL(activated(int)), this, SLOT(itemChanged()));

    kLog = new QTextEdit(this);
    box->addWidget(kLog);
    kLog->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);

    refillLogs();

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close | QDialogButtonBox::Save, this);
    box->addWidget(buttonBox);

    auto updateButton = new QPushButton(i18nc("@action:button", "Update"), buttonBox);
    updateButton->setIcon(QIcon::fromTheme(u"view-refresh-symbolic"_s));
    connect(updateButton, &QPushButton::clicked, this, &LogViewer::refillLogs);
    buttonBox->addButton(updateButton, QDialogButtonBox::ActionRole);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &LogViewer::save);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &LogViewer::reject);

    resize(QSize(60 * fontHeight, 40 * fontHeight));
    readConfig();
}

LogViewer::~LogViewer()
{
    writeConfig();
}

void LogViewer::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "LogViewer");
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void LogViewer::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "LogViewer");
    KWindowConfig::restoreWindowSize(windowHandle(), group);
}

void LogViewer::refillLogs()
{
    const int currentProcess = cItem->itemData(cItem->currentIndex()).toInt();

    cItem->clear();

    QPair<int, QString> log;
    foreach (log, logger->getLogs()) {
        const int id = log.first;
        QString name = log.second;
        // TODO make the string width dependend on the window width
        if (name.length() > 73)
            name = name.left(35) + "..." + name.right(35);

        if (id == 1000)
            cItem->addItem(i18n("soundKonverter application log"), QVariant(id));
        else
            cItem->addItem(name, QVariant(id));
    }

    if (cItem->findData(currentProcess) != -1)
        cItem->setCurrentIndex(cItem->findData(currentProcess));
    else
        cItem->setCurrentIndex(0);

    itemChanged();
}

void LogViewer::itemChanged()
{
    // HACK avoid Qt bug? changing the color of 'uncolored' text when switching the log file
    QTextCursor cursor = kLog->textCursor();
    cursor.setPosition(0);
    kLog->setTextCursor(cursor);

    kLog->clear();
    const LoggerItem *const item = logger->getLog(cItem->itemData(cItem->currentIndex()).toInt());

    if (!item)
        return;

    for (const QString &line : std::as_const(item->data)) {
        kLog->append(line);
    }

    QPalette currentPalette = kLog->palette();
    if (item->completed) {
        currentPalette.setColor(QPalette::Base, QApplication::palette().base().color());
    } else {
        currentPalette.setColor(QPalette::Base, QColor(255, 234, 234));
    }
    kLog->setPalette(currentPalette);
}

void LogViewer::save()
{
    const QString fileName = QFileDialog::getSaveFileName(this, i18n("Save log file"), {}, "*.txt\n*.log");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (file.exists()) {
        if (KMessageBox::questionTwoActions(this,
                                            i18n("File already exists."),
                                            i18n("Do you really want to overwrite it?"),
                                            KStandardGuiItem::overwrite(),
                                            KStandardGuiItem::cancel())
            == KMessageBox::SecondaryAction)
            return;
    }
    if (!file.open(QIODevice::WriteOnly)) {
        KMessageBox::error(this, i18n("Writing to file failed.\nMaybe you haven't got write permission."));
        return;
    }
    QTextStream textStream;
    textStream.setDevice(&file);
    textStream << kLog->toPlainText();
    file.close();
}

void LogViewer::processRemoved(int id)
{
    Q_UNUSED(id)

    refillLogs();
}

void LogViewer::updateProcess(int id)
{
    Q_UNUSED(id)

    refillLogs();
}

void LogViewer::showLog(int id)
{
    if (cItem->findData(QVariant(id)) != -1)
        cItem->setCurrentIndex(cItem->findData(QVariant(id)));
    else
        cItem->setCurrentIndex(0);

    itemChanged();
}
