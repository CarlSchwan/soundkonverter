
#ifndef BACKENDPLUGIN_H
#define BACKENDPLUGIN_H

#include <kcoreaddons_export.h>

#include <KProcess>
#include <QList>
#include <QMap>
#include <QObject>
#include <QUrl>

class BackendPlugin;

using namespace Qt::Literals::StringLiterals;

struct ConversionPipeTrunk {
    QString codecFrom, codecTo;

    BackendPlugin *plugin;
    bool enabled; // can we use this conversion pipe? (all needed backends installed?)
    int rating;
    QString problemInfo; // howto message, if a backend is missing

    struct Data // additional data
    {
        bool hasInternalReplayGain;
        bool canRipEntireCd;
    } data;

    bool operator==(const ConversionPipeTrunk &other)
    {
        return plugin == other.plugin;
    }
};

class BackendPluginItem : public QObject
{
    Q_OBJECT
public:
    explicit BackendPluginItem(QObject *parent);
    virtual ~BackendPluginItem();

    KProcess *process;
    int id;
    float progress; // hold the current progress, -1 is the initial value and shows that the progress can't be determined
};

/**
    @author Daniel Faust <hessijames@gmail.com>
*/
class KCOREADDONS_EXPORT BackendPlugin : public QObject
{
    Q_OBJECT
public:
    enum ActionType { Decoder, Encoder, Filter, ReplayGain, Ripper, General };

    enum ErrorCode { UnknownError, BackendNeedsConfiguration, FeatureNotSupported };

    struct FormatInfo {
        QString codecName; // the internal name of this codec
        short priority; // atm. we have to guess the codec when handling of a container file
        bool lossless; // for calculating a possible conversion pipe
        bool inferiorQuality; // e.g. 8 bit file types
        QString description; // description for the simple tab
        QStringList mimeTypes; // TODO this might be obsolete - what's with dolphin's actions context menu?
        QStringList extensions;
    };

    explicit BackendPlugin(QObject *parent);
    virtual ~BackendPlugin();

    virtual QString name() const = 0;
    virtual QString type() const = 0;

    virtual FormatInfo formatInfo(const QString &codecName);
    virtual QString getCodecFromFile(const QUrl &filename, const QString &mimeType = u"application/octet-stream"_s, short *rating = 0);
    virtual bool isConfigSupported(ActionType action, const QString &codecName) = 0;
    virtual void showConfigDialog(ActionType action, const QString &codecName, QWidget *parent) = 0;
    virtual bool hasInfo() = 0;
    virtual void showInfo(QWidget *parent) = 0;
    virtual bool pause(int id);
    virtual bool resume(int id);
    virtual bool kill(int id);
    //     virtual void setPriority( int _priority );
    virtual float progress(int id);
    virtual float parseOutput(const QString &output) = 0;
    //     virtual float parseOutput( const QString& output, BackendPluginItem *backendItem = 0 ) = 0; TODO ogg replaygain fix

    /** search for the backend binaries in the given directories */
    virtual void scanForBackends(const QStringList &directoryList = QStringList());
    /** holds all backend binaries and their location if they were found */
    QMap<QString, QString> binaries;

    QString standardMessage(const QString &type, const QStringList &arguments) const;
    QString standardMessage(const QString &type) const;
    QString standardMessage(const QString &type, const QString &arguments1) const;
    QString standardMessage(const QString &type, const QString &arguments1, const QString &arguments2) const;
    QString standardMessage(const QString &type, const QString &arguments1, const QString &arguments2, const QString &arguments3) const;

    /** returns the url as a string with all special characters escaped so the bash can find the files */
    QString escapeUrl(const QUrl &url);

    void logCommand(int id, const QString &message);
    void logOutput(int id, const QString &message);

protected:
    QList<BackendPluginItem *> backendItems;
    int lastId;
    QStringList allCodecs;
    //     int priority;

Q_SIGNALS:
    void log(int id, const QString &message);
    void jobFinished(int id, int exitCode);

private Q_SLOTS:
    /** Get the process' output */
    virtual void processOutput();

    /** The process has exited */
    virtual void processExit(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // BACKENDPLUGIN_H
