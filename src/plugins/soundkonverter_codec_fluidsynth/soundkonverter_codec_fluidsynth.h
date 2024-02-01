
#ifndef SOUNDKONVERTER_CODEC_FLUIDSYNTH_H
#define SOUNDKONVERTER_CODEC_FLUIDSYNTH_H

#include "../../core/codecplugin.h"

#include <KPluginFactory>
#include <QPointer>
#include <QUrl>

class ConversionOptions;
class KPageDialog;
class KUrlRequester;

class soundkonverter_codec_fluidsynth : public CodecPlugin
{
    Q_OBJECT
public:
    /** Default Constructor */
    soundkonverter_codec_fluidsynth(QObject *parent, const KPluginMetaData &metaData, const QVariantList &args);

    /** Default Destructor */
    ~soundkonverter_codec_fluidsynth();

    QString name() const;

    QList<ConversionPipeTrunk> codecTable();
    bool isConfigSupported(ActionType action, const QString &format);
    void showConfigDialog(ActionType action, const QString &format, QWidget *parent);
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

private:
    QPointer<KPageDialog> configDialog;
    KUrlRequester *configDialogSoundFontUrlRequester;

    QUrl soundFontFile;

private slots:
    void configDialogSave();
};

#endif // SOUNDKONVERTER_CODEC_FLUIDSYNTH_H
