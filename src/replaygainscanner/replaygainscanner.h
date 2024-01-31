
#ifndef REPLAYGAINSCANNER_H
#define REPLAYGAINSCANNER_H

#include <QDialog>
#include <QUrl>

class Config;
class Logger;
class ComboButton;
class ReplayGainFileList;
class ProgressIndicator;

class QCheckBox;
class QPushButton;
class QTreeWidget;
class QFileDialog;

/**
 * @short The Replay Gain Tool
 * @author Daniel Faust <hessijames@gmail.com>
 */
class ReplayGainScanner : public QDialog
{
    Q_OBJECT
public:
    ReplayGainScanner(Config *, Logger *, bool showMainWindowButton, QWidget *parent, Qt::WindowFlags f = {});
    ~ReplayGainScanner();

    void addFiles( QList<QUrl> urls );

private slots:
    void addClicked( int );
    void showDirDialog();
    void showFileDialog();
    void showMainWindowClicked();
    void showHelp();
    void calcReplayGainClicked();
    void removeReplayGainClicked();
    void cancelClicked();
    void closeClicked();
    void processStarted();
    void processStopped();
    void progressChanged( const QString& progress );

private:
    void readConfig();
    void writeConfig();

    ComboButton *cAdd;
    QPushButton *pShowMainWindow;
    QCheckBox *cForce;
    ReplayGainFileList *fileList;
    ProgressIndicator *progressIndicator;
    QPushButton *pTagVisible;
    QPushButton *pRemoveTag;
    QPushButton *pCancel;
    QPushButton *pClose;

    Config *config;
    Logger *logger;

Q_SIGNALS:
    void addFile( const QString& );
    void addDir( const QString&, const QStringList& filter = QStringList(), bool recursive = true );
    void calcAllReplayGain( bool force );
    void removeAllReplayGain();
    void cancelProcess();
    void showMainWindow();
};

#endif // REPLAYGAINSCANNER_H
