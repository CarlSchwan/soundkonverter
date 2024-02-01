
#ifndef SOUNDKONVERTER_CODEC_FFMPEG_H
#define SOUNDKONVERTER_CODEC_FFMPEG_H

#include "../../core/codecplugin.h"

#include <QDateTime>
#include <QWeakPointer>

class ConversionOptions;
class QDialog;
class QCheckBox;

class soundkonverter_codec_ffmpeg : public CodecPlugin
{
    Q_OBJECT
public:
    struct FFmpegEncoderData {
        QString name;
        bool experimental = false;
    };

    struct CodecData {
        QString codecName;
        QList<FFmpegEncoderData> ffmpegEnoderList;
        FFmpegEncoderData currentFFmpegEncoder;
    };

    /** Default Constructor */
    soundkonverter_codec_ffmpeg(QObject *parent, const QVariantList &args);

    /** Default Destructor */
    ~soundkonverter_codec_ffmpeg();

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
    QWeakPointer<KProcess> infoProcess;
    QString infoProcessOutputData;

    QWeakPointer<QDialog> configDialog;
    QCheckBox *configDialogExperimantalCodecsEnabledCheckBox;

    int configVersion;
    bool experimentalCodecsEnabled;
    int ffmpegVersionMajor;
    int ffmpegVersionMinor;
    QDateTime ffmpegLastModified;
    QSet<QString> ffmpegCodecList;

private slots:
    /** Get the process' output */
    void processOutput();

    void configDialogSave();
    void configDialogDefault();

    void infoProcessOutput();
    void infoProcessExit(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // _SOUNDKONVERTER_CODEC_FFMPEG_H_
