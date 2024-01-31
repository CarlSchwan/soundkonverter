
#ifndef SOUNDKONVERTER_CODEC_MUSEPACK_H
#define SOUNDKONVERTER_CODEC_MUSEPACK_H

#include "../../core/codecplugin.h"

class ConversionOptions;


class soundkonverter_codec_musepack : public CodecPlugin
{
    Q_OBJECT
public:
    /** Default Constructor */
    soundkonverter_codec_musepack( QObject *parent, const QVariantList& args );

    /** Default Destructor */
    ~soundkonverter_codec_musepack();

    QString name() const;

    /** search for the backend binaries in the given directories */
    virtual void scanForBackends( const QStringList& directoryList = QStringList() );

    QList<ConversionPipeTrunk> codecTable();

    bool isConfigSupported( ActionType action, const QString& codecName );
    void showConfigDialog( ActionType action, const QString& codecName, QWidget *parent );
    bool hasInfo();
    void showInfo( QWidget *parent );
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
    float parseOutput( const QString& output );

    ConversionOptions *conversionOptionsFromXml( QDomElement conversionOptions, QList<QDomElement> *filterOptionsElements = 0 );
};

#endif // SOUNDKONVERTER_CODEC_MUSEPACK_H
