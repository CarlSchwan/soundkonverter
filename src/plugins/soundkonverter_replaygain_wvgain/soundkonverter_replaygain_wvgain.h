
#ifndef SOUNDKONVERTER_REPLAYGAIN_WVGAIN_H
#define SOUNDKONVERTER_REPLAYGAIN_WVGAIN_H

#include "../../core/replaygainplugin.h"

#include <QUrl>

class ConversionOptions;


class soundkonverter_replaygain_wvgain : public ReplayGainPlugin
{
    Q_OBJECT
public:
    /** Default Constructor */
    soundkonverter_replaygain_wvgain( QObject *parent, const QVariantList& args );

    /** Default Destructor */
    ~soundkonverter_replaygain_wvgain();

    QString name() const;

    QList<ReplayGainPipe> codecTable();

    bool isConfigSupported( ActionType action, const QString& codecName );
    void showConfigDialog( ActionType action, const QString& codecName, QWidget *parent );
    bool hasInfo();
    void showInfo( QWidget *parent );

    int apply(const QList<QUrl> &fileList, ApplyMode mode = Add);
    float parseOutput( const QString& output );

};

#endif // _SOUNDKONVERTER_REPLAYGAIN_WVGAIN_H_
