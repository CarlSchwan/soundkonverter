
#ifndef SOUNDKONVERTER_RIPPER_ICEDAX_H
#define SOUNDKONVERTER_RIPPER_ICEDAX_H

#include "../../core/ripperplugin.h"

#include <KProcess>
#include <QList>
#include <QUrl>

class soundkonverter_ripper_icedax : public RipperPlugin
{
    Q_OBJECT
public:
    /** Default Constructor */
    soundkonverter_ripper_icedax(QObject *parent, const QVariantList &args);

    /** Default Destructor */
    ~soundkonverter_ripper_icedax();

    QString name() const;

    QList<ConversionPipeTrunk> codecTable();

    bool isConfigSupported(ActionType action, const QString &codecName);
    void showConfigDialog(ActionType action, const QString &codecName, QWidget *parent);
    bool hasInfo();
    void showInfo(QWidget *parent);

    int rip(const QString &device, int track, int tracks, const QUrl &outputFile);
    QStringList ripCommand(const QString &device, int track, int tracks, const QUrl &outputFile);
    float parseOutput(const QString &output, RipperPluginItem *ripperItem);
    float parseOutput(const QString &output);

private slots:
    /** Get the process' output */
    void processOutput();
};

#endif // SOUNDKONVERTER_RIPPER_ICEDAX_H
