
#ifndef SOUNDKONVERTER_CODEC_FFMPEG_H
#define SOUNDKONVERTER_CODEC_FFMPEG_H

#include "../../core/codecplugin.h"

#include <KPluginFactory>
#include <QDateTime>
#include <QPointer>

class ConversionOptions;
class KPageDialog;
class QCheckBox;

class soundkonverter_codec_libav : public CodecPlugin
{
    Q_OBJECT
public:
    struct LibavCodecData {
        QString name;
        bool external;
        bool experimental;
    };

    struct CodecData {
        QString codecName;
        QList<LibavCodecData> libavCodecList;
        LibavCodecData currentLibavCodec;
    };

    /** Default Constructor */
    soundkonverter_codec_libav(QObject *parent, const KPluginMetaData &metadata, const QVariantList &args);

    /** Default Destructor */
    ~soundkonverter_codec_libav();

    QString name() const;
    int version();

    QList<ConversionPipeTrunk> codecTable();

    bool isConfigSupported(ActionType action, const QString &codecName);
    void showConfigDialog(ActionType action, const QString &codecName, QWidget *parent);
    bool hasInfo();
    void showInfo(QWidget *parent);

    CodecWidget *newCodecWidget();

    int convert(const QUrl &inputFile,
                const QUrl &outputFile,
                const QString &inputCodec,
                const QString &outputCodec,
                const ConversionOptions *_conversionOptions,
                TagData *tags = 0,
                bool replayGain = false);
    QStringList convertCommand(const QUrl &inputFile,
                               const QUrl &outputFile,
                               const QString &inputCodec,
                               const QString &outputCodec,
                               const ConversionOptions *_conversionOptions,
                               TagData *tags = 0,
                               bool replayGain = false);
    float parseOutput(const QString &output, int *length);
    float parseOutput(const QString &output);

private:
    QList<CodecData> codecList;
    QPointer<KProcess> infoProcess;
    QString infoProcessOutputData;

    QPointer<KPageDialog> configDialog;
    QCheckBox *configDialogExperimantalCodecsEnabledCheckBox;

    int configVersion;
    bool experimentalCodecsEnabled;
    int libavVersionMajor;
    int libavVersionMinor;
    QDateTime libavLastModified;
    QList<QString> libavCodecList;

public Q_SLOTS:
    void configDialogSave();
    void configDialogDefault();

private Q_SLOTS:
    /** Get the process' output */
    void processOutput();

    void infoProcessOutput();
    void infoProcessExit(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // _SOUNDKONVERTER_CODEC_FFMPEG_H_
