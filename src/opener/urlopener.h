//
// C++ Interface: opener
//
// Description:
//
//
// Author: Daniel Faust <hessijames@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef URLOPENER_H
#define URLOPENER_H

#include <QDialog>

#include <QUrl>

class Config;
class Options;
class QLabel;
class ConversionOptions;
class QDialog;
class KFileWidget;
class QPushButton;
class KUrlRequester;

/**
    @author Daniel Faust <hessijames@gmail.com>
*/
class UrlOpener : public QDialog
{
    Q_OBJECT
public:
    enum DialogPage { FileOpenPage, ConversionOptionsPage };

    UrlOpener(Config *_config, QWidget *parent, Qt::WindowFlags = {});
    ~UrlOpener();

    DialogPage currentPage()
    {
        return page;
    }

private:
    void readConfig();
    void writeConfig();

    Config *config;

    KUrlRequester *urlRequester;
    Options *options;
    DialogPage page;
    QLabel *lSelector;
    QLabel *lOptions;
    QList<QUrl> urls;
    QPushButton *pProceed;
    QPushButton *pAdd;
    QPushButton *pCancel;

private slots:
    void proceedClickedSlot();
    void okClickedSlot();

Q_SIGNALS:
    void openFiles(const QList<QUrl> &files, ConversionOptions *conversionOptions);
};

#endif
