

#ifndef ABOUTPLUGINS_H
#define ABOUTPLUGINS_H

#include <KDialog>

class Config;


/**
 * @short Shows the logs that are collected by the logger
 * @author Daniel Faust <hessijames@gmail.com>
 * @version 1.0
 */
class AboutPlugins : public KDialog
{
    Q_OBJECT
public:
    /** Default Constructor */
    AboutPlugins( Config *_config, QWidget *parent=0, Qt::WFlags f=0 );

    /** Default Destructor */
    virtual ~AboutPlugins();

private:
    Config *config;

};

#endif // ABOUTPLUGINS_H