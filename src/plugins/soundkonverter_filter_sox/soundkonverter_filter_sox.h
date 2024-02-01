
#ifndef SOUNDKONVERTER_FILTER_SOX_H
#define SOUNDKONVERTER_FILTER_SOX_H

#include "../../core/filterplugin.h"

#include <QDateTime>
#include <QPointer>

class FilterOptions;
class QDialog;
class KComboBox;

class soundkonverter_filter_sox : public FilterPlugin
{
    Q_OBJECT
public:
    struct SoxCodecData {
        QString codecName;
        QString soxCodecName;
        bool external;
        bool experimental;
        bool enabled;
    };

    /** Default Constructor */
    soundkonverter_filter_sox(QObject *parent, const QVariantList &args);

    /** Default Destructor */
    ~soundkonverter_filter_sox();

    QString name() const;
    int version();

    QList<ConversionPipeTrunk> codecTable();

    bool isConfigSupported(ActionType action, const QString &codecName);
    void showConfigDialog(ActionType action, const QString &codecName, QWidget *parent);
    bool hasInfo();
    void showInfo(QWidget *parent);

    CodecWidget *newCodecWidget();
    FilterWidget *newFilterWidget();

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

    FilterOptions *filterOptionsFromXml(QDomElement filterOptions);

private:
    QList<SoxCodecData> codecList;
    QPointer<KProcess> infoProcess;
    QString infoProcessOutputData;

    QPointer<QDialog> configDialog;
    KComboBox *configDialogSamplingRateQualityComboBox;

    int configVersion;
    QString samplingRateQuality;
    bool experimentalEffectsEnabled;
    QDateTime soxLastModified;
    QSet<QString> soxCodecList;

    QString soxCodecName(const QString &codecName);

private slots:
    void configDialogSave();
    void configDialogDefault();

    void infoProcessOutput();
    void infoProcessExit(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif // SOUNDKONVERTER_FILTER_SOX_H
