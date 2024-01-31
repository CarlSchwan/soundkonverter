

#ifndef CODECOPTIMIZATIONS_H
#define CODECOPTIMIZATIONS_H

#include <QDialog>

class QRadioButton;


/**
 * @short Shows a message box with suggestions for optimizing the backend order
 * @author Daniel Faust <hessijames@gmail.com>
 * @version 1.0
 */
class CodecOptimizations : public QDialog
{
    Q_OBJECT
public:
    struct Optimization {
        QString codecName;
        enum Mode {
            Encode,
            Decode,
            ReplayGain
        } mode;
        QString currentBackend;
        QString betterBackend;
        enum Solution {
            Fix,
            Ignore,
            Undecided
        } solution;
    };

    /** Default Constructor */
    CodecOptimizations(const QList<Optimization> &optimizationList, QWidget *parent, Qt::WindowFlags = {});

    /** Default Destructor */
    ~CodecOptimizations();

private:
    QList<Optimization> optimizationList;
    QList<QRadioButton*> solutionFixButtons;

private slots:
    void okClicked();

Q_SIGNALS:
    void solutions( const QList<CodecOptimizations::Optimization>& solutions );
};

#endif // CODECOPTIMIZATIONS_H
