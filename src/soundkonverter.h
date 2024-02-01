/*
 * soundkonverter.h
 *
 * Copyright (C) 2007 Daniel Faust <hessijames@gmail.com>
 */
#ifndef SOUNDKONVERTER_H
#define SOUNDKONVERTER_H

#include <KXmlGuiWindow>
#include <QPointer>
#include <QUrl>

class soundKonverterView;
class KToggleAction;
class QUrl;
class Config;
class Logger;
class LogViewer;
class CDManager;
class ReplayGainScanner;

class KStatusNotifierItem;


/**
 * This class serves as the main window for soundKonverter.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Daniel Faust <hessijames@gmail.com>
 * @version 1.0
 */
class soundKonverter : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /** Default Constructor */
    soundKonverter();

    /** Default Destructor */
    ~soundKonverter();

    virtual void saveProperties( KConfigGroup& configGroup );

    void showSystemTray();
    void addConvertFiles(const QList<QUrl> &urls, const QString &profile, const QString &format, const QString &directory, const QString &notifyCommand);
    void addReplayGainFiles(const QList<QUrl> &urls);
    bool ripCd( const QString& device, const QString& profile, const QString& format, const QString& directory, const QString& notifyCommand );
    void setAutoClose( bool enabled ) { autoclose = enabled; }
    void startConversion();
    void loadAutosaveFileList();
    void loadFileList(const QString& fileListPath);
    void startupChecks();

private slots:
    void showConfigDialog();
    void showLogViewer( const int logId = 0 );
    void showReplayGainScanner();
    void replayGainScannerClosed();
    void showMainWindow();
    void showAboutPlugins();
    void progressChanged( const QString& progress );

    /** The conversion has started */
    void conversionStarted();
    /** The conversion has stopped */
    void conversionStopped( bool failed );

private:
    Config *config;
    Logger *logger;
    CDManager *cdManager;
    QPointer<ReplayGainScanner> replayGainScanner;

    soundKonverterView *m_view;
    LogViewer *logViewer;

    KStatusNotifierItem *systemTray;

    /// exit soundkonverter after all files have been converted
    bool autoclose;

    void setupActions();

};

#endif // _SOUNDKONVERTER_H_
