
#ifndef SOUNDKONVERTER_RIPPER_CDPARANOIA_H
#define SOUNDKONVERTER_RIPPER_CDPARANOIA_H

#include "../../core/ripperplugin.h"

#include <KProcess>
#include <QList>
#include <QUrl>
#include <QWeakPointer>

class QDialog;
class QCheckBox;
class QComboBox;
class QSpinBox;


class soundkonverter_ripper_cdparanoia : public RipperPlugin
{
    Q_OBJECT
public:
    /** Default Constructor */
    soundkonverter_ripper_cdparanoia( QObject *parent, const QVariantList& args );

    /** Default Destructor */
    ~soundkonverter_ripper_cdparanoia();

    QString name() const;

    QList<ConversionPipeTrunk> codecTable();

    bool isConfigSupported( ActionType action, const QString& codecName );
    void showConfigDialog( ActionType action, const QString& codecName, QWidget *parent );
    bool hasInfo();
    void showInfo( QWidget *parent );

    int rip(const QString &device, int track, int tracks, const QUrl &outputFile);
    QStringList ripCommand(const QString &device, int track, int tracks, const QUrl &outputFile);
    float parseOutput( const QString& output, int *fromSector, int *toSector );
    float parseOutput( const QString& output );

private slots:
    /** Get the process' output */
    void processOutput();

private:
    QWeakPointer<QDialog> configDialog;
    QCheckBox *configDialogForceReadSpeedCheckBox;
    QSpinBox *configDialogForceReadSpeedSpinBox;
    QComboBox *configDialogForceEndiannessComboBox;
    QSpinBox *configDialogMaximumRetriesSpinBox;
    QCheckBox *configDialogEnableParanoiaCheckBox;
    QCheckBox *configDialogEnableExtraParanoiaCheckBox;

    int forceReadSpeed;
    int forceEndianness;
    int maximumRetries;
    bool enableParanoia;
    bool enableExtraParanoia;

private slots:
    void configDialogForceReadSpeedChanged( int state );
    void configDialogSave();
    void configDialogDefault();
};

#endif // SOUNDKONVERTER_RIPPER_CDPARANOIA_H
