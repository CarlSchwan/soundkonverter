

#include "soundkonverter.h"
#include "global.h"

#include <KAboutData>
#include <KLocalizedString>
#include <KMainWindow>
#include <QApplication>
#include <QCommandLineParser>
#include <QLocale>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    KLocalizedString::setApplicationDomain("soundkonverter");

    KAboutData about(QStringLiteral("soundkonverter"),
                     i18n("soundKonverter"),
                     QStringLiteral(SOUNDKONVERTER_VERSION_STRING),
                     i18n("soundKonverter is a frontend to various audio converters, Replay Gain tools and CD rippers.\n\nPlease file bug reports at "
                          "https://github.com/dfaust/soundkonverter/issues"),
                     KAboutLicense::GPL_V3,
                     i18n("(C) 2005-2017 Daniel Faust, 2024 KDE Community"));

    about.addAuthor(i18n("Daniel Faust"), i18n("Author"), "hessijames@gmail.com");
    about.addCredit(i18n("David Vignoni"), i18n("Nuvola icon theme"), {}, "http://www.icon-king.com");
    about.addCredit(i18n("Scott Wheeler"), i18n("TagLib"), "wheeler@kde.org", "http://ktown.kde.org/~wheeler");
    about.addCredit(i18n("Marco Nelles"), i18n("Audex"), 0, "http://opensource.maniatek.de/audex");
    about.addCredit(i18n("Amarok developers"), i18n("Amarok"), 0, "http://amarok.kde.org");
    about.addCredit(i18n("All programmers of audio converters"), i18n("Backends"));
    about.addCredit(i18n("Patrick Auernig"), i18n("Inital Port to KDE Frameworks 5"), "patrick.auernig@gmail.com");

    QCommandLineParser parser;
    parser.addOption(QCommandLineOption("replaygain", i18n("Open the Replay Gain tool and add all given files")));
    parser.addOption(QCommandLineOption("rip <device>", i18n("List all tracks on the cd drive <device>, 'auto' will search for a cd")));
    parser.addOption(QCommandLineOption("profile <profile>", i18n("Add all files using the given profile")));
    parser.addOption(QCommandLineOption("format <format>", i18n("Add all files using the given format")));
    parser.addOption(QCommandLineOption("output <directory>", i18n("Output all files to <directory>")));
    parser.addOption(QCommandLineOption("invisible", i18n("Start soundKonverter invisible")));
    parser.addOption(QCommandLineOption("autostart", i18n("Start the conversion immediately (enabled when using '--invisible')")));
    parser.addOption(QCommandLineOption("autoclose", i18n("Close soundKonverter after all files are converted (enabled when using '--invisible')")));
    parser.addOption(QCommandLineOption("command <command>", i18n("Execute <command> after each file has been converted (%i=input file, %o=output file)")));
    parser.addOption(QCommandLineOption("file-list <path>", i18n("Load the file list at <path> after starting soundKonverter")));
    parser.addOption(QCommandLineOption("+[files]", i18n("Audio file(s) to append to the file list")));

    about.setupCommandLine(&parser);
    parser.process(app);

    // if( !soundKonverterApp::start() )
    //{
    //     return 0;
    // }

    // soundKonverterApp app;
    auto mainWindow = new soundKonverter();

    /*
    static bool first = true;
    bool visible = true;
    bool autoclose = false;
    bool autostart = false;
    bool activateMainWindow = true;

    if( ( first || !mainWindow->isVisible() ) && args->isSet("replaygain") && args->count() > 0 )
        visible = false;

    autoclose = args->isSet( "autoclose" );
    autostart = args->isSet( "autostart" );

    const QString profile = args->getOption( "profile" );
    const QString format = args->getOption( "format" );
    const QString directory = args->getOption( "output" );
    const QString notifyCommand = args->getOption( "command" );
    const QString fileListPath = args->getOption( "file-list" );

    if( args->isSet( "invisible" ) )
    {
        autoclose = true;
        autostart = true;
        visible = false;
        mainWindow->showSystemTray();
    }

    if( first && fileListPath.isEmpty() && QFile::exists(KStandardDirs::locateLocal("data","soundkonverter/filelist_autosave.xml")) )
    {
        if( !visible )
        {
            visible = true;
            autoclose = false;
            autostart = false;
            mainWindow->show();
        }
        mainWindow->show();
        qApp->processEvents();
        mainWindow->loadAutosaveFileList();
    }
    else if( !fileListPath.isEmpty() && QFile::exists(fileListPath) )
    {
        mainWindow->loadFileList(fileListPath);
    }

    const QString device = args->getOption( "rip" );
    if( !device.isEmpty() )
    {
        const bool success = mainWindow->ripCd( device, profile, format, directory, notifyCommand );
        if( !success && first )
        {
            qApp->quit();
            return 0;
        }
    }

    if( visible )
        mainWindow->show();

    mainWindow->setAutoClose( autoclose );

    if( args->isSet( "replaygain" ) )
    {
        QList<QUrl> urls;
        for( int i=0; i<args->count(); i++ )
        {
            urls.append( args->arg(i) );
        }
        if( !urls.isEmpty() )
        {
            mainWindow->addReplayGainFiles( urls );
            activateMainWindow = false;
        }
    }
    else
    {
        QList<QUrl> urls;
        for( int i=0; i<args->count(); i++ )
        {
            urls.append( args->arg(i) );
        }
        if( !urls.isEmpty() )
            mainWindow->addConvertFiles( urls, profile, format, directory, notifyCommand );
    }
    args->clear();

    if( activateMainWindow )
        mainWindow->activateWindow();

    if( autostart )
        mainWindow->startConversion();

    if( first )
        mainWindow->startupChecks();

    first = false;
    */

    // mainWin has WDestructiveClose flag by default, so it will delete itself.
    return app.exec();
}
