//
// C++ Interface: configpagebase
//
// Description:
//
//
// Author: Daniel Faust <hessijames@gmail.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef CONFIGPAGEBASE_H
#define CONFIGPAGEBASE_H

#include <QWidget>

class Config;

/**
	@author Daniel Faust <hessijames@gmail.com>
*/
class ConfigPageBase : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigPageBase( QWidget *parent );
    virtual ~ConfigPageBase();

    int spacingOffset;
    int spacingSmall;
    int spacingMedium;
    int spacingBig;

public slots:
    virtual void resetDefaults();
    virtual void saveSettings();

Q_SIGNALS:
    void configChanged( bool state = true );

};

#endif
