
#ifndef REPLAYGAINFILELISTITEM_H
#define REPLAYGAINFILELISTITEM_H

#include "core/replaygainplugin.h"
#include "metadata/tagengine.h"

#include <QItemDelegate>
#include <QPointer>
#include <QTreeWidget>
#include <QUrl>

class ReplayGainFileListItem : public QTreeWidgetItem
{
public:
    explicit ReplayGainFileListItem( QTreeWidget *parent );
    ReplayGainFileListItem( QTreeWidget *parent, QTreeWidgetItem *preceding );
    explicit ReplayGainFileListItem( QTreeWidgetItem *parent );

    ~ReplayGainFileListItem();

    enum Type {
        Track,
        Album
    } type;

    enum State {
        Waiting,
        WaitingForReplayGain,
        Processing,
        Stopped
    } state;

    // code values will be displayed in the log files
    enum ReturnCode {
        Succeeded                       = 0,
        SucceededWithProblems           = 1,
        StoppedByUser                   = 2,
        Skipped                         = 3,
        BackendNeedsConfiguration       = 4,
        Failed                          = 5
    } returnCode;

    QUrl url;
    QString albumName;
    QString codecName;
    int samplingRate;
    TagData *tags;

    int length;

    QStringList directories();
    QList<QUrl> urls();
    void setState( State newState );

};

class ReplayGainFileListItemDelegate : public QItemDelegate
{
public:
    explicit ReplayGainFileListItemDelegate( QObject *parent );

    virtual void paint( QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const;
};

#endif // REPLAYGAINFILELISTITEM_H
