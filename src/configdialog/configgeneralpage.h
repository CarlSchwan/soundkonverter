//
// C++ Interface: configgeneralpage
//
// Description:
//
//
// Author: Daniel Faust <hessijames@gmail.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef CONFIGGENERALPAGE_H
#define CONFIGGENERALPAGE_H

#include "configpagebase.h"

class Config;
class QCheckBox;
class KComboBox;
class QSpinBox;
class KLineEdit;
class QPushButton;

/**
	@author Daniel Faust <hessijames@gmail.com>
*/
class ConfigGeneralPage : public ConfigPageBase
{
    Q_OBJECT
public:
    /** Default Constructor */
    ConfigGeneralPage( Config *_config, QWidget *parent );

    /** Default Destructor */
    ~ConfigGeneralPage();

private:
    KComboBox *cStartTab;
    KComboBox *cDefaultProfile;
    KComboBox *cDefaultFormat;
//     KComboBox *cPriority;
//     QStringList sPriority;
    KComboBox *cConflictHandling;
    QSpinBox *iNumFiles;
    QCheckBox *cWaitForAlbumGain;
    QCheckBox *cCopyIfSameCodec;
    KComboBox *cReplayGainGrouping;
    QSpinBox *iNumReplayGainFiles;

    Config *config;

//     int profileIndex( const QString& string );
//     int formatIndex( const QString& string );

public slots:
    void resetDefaults();
    void saveSettings();

private slots:
    void somethingChanged();
//     void selectDir();
    void profileChanged();


};

#endif
