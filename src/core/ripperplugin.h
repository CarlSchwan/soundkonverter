
#ifndef RIPPERPLUGIN_H
#define RIPPERPLUGIN_H

#include <QVariantList>
#include <kcoreaddons_export.h>

#include "backendplugin.h"

#include <QUrl>

class RipperPlugin;

class KCOREADDONS_EXPORT RipperPluginItem : public BackendPluginItem
{
    Q_OBJECT
public:
    explicit RipperPluginItem(QObject *parent);
    virtual ~RipperPluginItem();

    struct Data {
        int fromSector; // cd paranoia
        int toSector;

        int fileCount; // icedax
        int processedFiles;
        float lastFileProgress;
    } data;
};

/** @author Daniel Faust <hessijames@gmail.com> */
class KCOREADDONS_EXPORT RipperPlugin : public BackendPlugin
{
    Q_OBJECT
public:
    explicit RipperPlugin(QObject *parent);
    virtual ~RipperPlugin();

    virtual QString type() const;

    virtual QList<ConversionPipeTrunk> codecTable() = 0;

    /** rips a track */
    virtual int rip(const QString &device, int track, int tracks, const QUrl &outputFile) = 0;
    /** returns a command for ripping a track through a pipe; "" if pipes aren't supported */
    virtual QStringList ripCommand(const QString &device, int track, int tracks, const QUrl &outputFile) = 0;
};

#endif // RIPPERPLUGIN_H
