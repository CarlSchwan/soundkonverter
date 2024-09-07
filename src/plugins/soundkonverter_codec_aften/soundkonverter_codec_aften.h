
#ifndef SOUNDKONVERTER_CODEC_AFTEN_H
#define SOUNDKONVERTER_CODEC_AFTEN_H

#include "../../core/codecplugin.h"

#include <KPluginFactory>

class ConversionOptions;

class soundkonverter_codec_aften : public CodecPlugin
{
    Q_OBJECT
public:
    /** Default Constructor */
    soundkonverter_codec_aften(QObject *parent, const KPluginMetaData &metadata, const QVariantList &args);

    /** Default Destructor */
    ~soundkonverter_codec_aften();

    QString name() const;

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
    float parseOutput(const QString &output);
};

#endif // _SOUNDKONVERTER_CODEC_AFTEN_H_
