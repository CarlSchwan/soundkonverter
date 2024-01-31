//
// C++ Interface: optionseditor
//
// Description:
//
//
// Author: Daniel Faust <hessijames@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef OPTIONSEDITOR_H
#define OPTIONSEDITOR_H

// #include <KPageWidget>
#include <KPageDialog>
#include <QLayout>

class Options;
class Config;
class TagEngine;
// class ConversionOptions;

class KLineEdit;
class KComboBox;
class QSpinBox;
class QTextEdit;
class QPushButton;
class QLabel;
class FileListItem;

/**
	@author Daniel Faust <hessijames@gmail.com>
*/
class OptionsEditor : public KPageDialog
{
    Q_OBJECT
public:
    OptionsEditor( Config *_config, QWidget *parent );
    ~OptionsEditor();

private:
    void setTagInputEnabled( bool enabled );

    /** The widget, where we can set our output options */
    Options *options;

    /** A list of all covers */
    QLabel* lCoversLabel;
    QHBoxLayout *bCovers;
    QList<QLabel*> lCovers;
    /** A lineedit for entering the title of track */
    QLabel* lTitleLabel;
    KLineEdit* lTitle;
    QPushButton *pTitleEdit;
    /** A spinbox for entering or selecting the track number */
    QLabel* lTrackLabel;
    QSpinBox *iTrack;
    QPushButton *pTrackEdit;
    /** A spinbox for entering or selecting the total track number */
    QLabel* lTrackTotalLabel;
    QSpinBox *iTrackTotal;
    QPushButton *pTrackTotalEdit;
    /** A lineedit for entering the artist of a track */
    QLabel* lArtistLabel;
    KLineEdit* lArtist;
    QPushButton *pArtistEdit;
    /** A lineedit for entering the composer of a track */
    QLabel* lComposerLabel;
    KLineEdit* lComposer;
    QPushButton *pComposerEdit;
    /** A lineedit for entering the album artist */
    QLabel* lAlbumArtistLabel;
    KLineEdit* lAlbumArtist;
    QPushButton *pAlbumArtistEdit;
    /** A lineedit for entering the album name */
    QLabel* lAlbumLabel;
    KLineEdit* lAlbum;
    QPushButton *pAlbumEdit;
    /** A spinbox for entering or selecting the disc number */
    QLabel* lDiscLabel;
    QSpinBox *iDisc;
    QPushButton *pDiscEdit;
    /** A spinbox for entering or selecting the total disc number */
    QLabel* lDiscTotalLabel;
    QSpinBox *iDiscTotal;
    QPushButton *pDiscTotalEdit;
    /** A spinbox for entering or selecting the year of the album */
    QLabel* lYearLabel;
    QSpinBox *iYear;
    QPushButton *pYearEdit;
    /** A combobox for entering or selecting the genre of the album */
    QLabel* lGenreLabel;
    KComboBox* cGenre;
    QPushButton *pGenreEdit;
    /** A textedit for entering a comment for a track */
    QLabel* lCommentLabel;
    QTextEdit *tComment;
    QPushButton *pCommentEdit;

    /** When hitting this button, the options lock (when multiple files are selected) will be deactivated */
    QLabel* lEditOptions;
    QPushButton *pEditOptions;

    /** When hitting this button, the tag lock (when reading tags failed) will be deactivated */
    QLabel* lEditTags;
    QPushButton *pEditTags;

    QList<FileListItem*> selectedItems;

    Config *config;
    TagEngine *tagEngine;

    QPushButton *nextButton;
    QPushButton *prevButton;

public slots:
    // connected to FileList
    void itemsSelected( QList<FileListItem*> );
    void setPreviousEnabled( bool );
    void setNextEnabled( bool );

private slots:
    void applyChanges();

    void editOptionsClicked();
    void editTagsClicked();

    void editTitleClicked();
    void editTrackClicked();
    void editTrackTotalClicked();
    void editArtistClicked();
    void editComposerClicked();
    void editAlbumArtistClicked();
    void editAlbumClicked();
    void editDiscClicked();
    void editDiscTotalClicked();
    void editYearClicked();
    void editGenreClicked();
    void editCommentClicked();

Q_SIGNALS:
    // connected to FileList
    void updateFileListItems( QList<FileListItem*> items );

};

#endif
