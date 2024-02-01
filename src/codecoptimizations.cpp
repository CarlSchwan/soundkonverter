
#include "codecoptimizations.h"

#include <KLocalizedString>
#include <QButtonGroup>
#include <QDialogButtonBox>
#include <QIcon>
#include <QLabel>
#include <QLayout>
#include <QLocale>
#include <QRadioButton>
#include <QScrollArea>

CodecOptimizations::CodecOptimizations(const QList<Optimization> &_optimizationList, QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , optimizationList(_optimizationList)
{
    setWindowTitle(i18nc("@title:window", "Solutions for backend problems"));
    setWindowIcon(QIcon::fromTheme("help-about"));

    QVBoxLayout *box = new QVBoxLayout(this);

    QLabel *messageLabel = new QLabel( i18n("You have installed or removed backends and your soundKonverter settings can be optimized."), this );
    box->addWidget( messageLabel );

    QFrame *frame = new QFrame(this);
    frame->setFrameShape( QFrame::StyledPanel );
    frame->setFrameShadow( QFrame::Sunken );
    box->addWidget( frame );

    QGridLayout *grid = new QGridLayout( frame );
    grid->setColumnStretch( 1, 0 );
    grid->setColumnStretch( 2, 0 );

    for( int i=0; i<optimizationList.count(); i++ )
    {
        const QString codecName = optimizationList.at(i).codecName;
        const Optimization::Mode mode = optimizationList.at(i).mode;
        const QString currentBackend = optimizationList.at(i).currentBackend;
        const QString betterBackend = optimizationList.at(i).betterBackend;
        const Optimization::Solution solution = optimizationList.at(i).solution;

        QLabel *solutionLabel = new QLabel( frame );
        grid->addWidget( solutionLabel, i, 0 );
        if( mode == Optimization::Encode )
        {
            solutionLabel->setText( i18n( "For encoding %1 files the backend '%2' can be replaced with '%3'.", codecName, currentBackend, betterBackend ) );
        }
        else if( mode == Optimization::Decode && codecName == "audio cd" )
        {
            solutionLabel->setText( i18n( "For ripping audio CDs the backend '%1' can be replaced with '%2'.", currentBackend, betterBackend ) );
        }
        else if( mode == Optimization::Decode )
        {
            solutionLabel->setText( i18n( "For decoding %1 files the backend '%2' can be replaced with '%3'.", codecName, currentBackend, betterBackend ) );
        }
        else if( mode == Optimization::ReplayGain )
        {
            solutionLabel->setText( i18n( "For applying Replay Gain to %1 files the backend '%2' can be replaced with '%3'.", codecName, currentBackend, betterBackend ) );
        }

        QRadioButton *solutionIgnore = new QRadioButton( i18n("Ignore"), frame );
        if( solution == Optimization::Ignore )
            solutionIgnore->setChecked( true );
        grid->addWidget( solutionIgnore, i, 1 );

        QRadioButton *solutionFix = new QRadioButton( i18n("Fix"), frame );
        solutionFixButtons.append( solutionFix );
        if( solution != Optimization::Ignore )
            solutionFix->setChecked( true );
        grid->addWidget( solutionFix, i, 2 );

        QButtonGroup *solutionButtonGroup = new QButtonGroup( frame );
        solutionButtonGroup->addButton( solutionIgnore );
        solutionButtonGroup->addButton( solutionFix );
    }

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CodecOptimizations::okClicked);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CodecOptimizations::rejected);
}

CodecOptimizations::~CodecOptimizations()
{}

void CodecOptimizations::okClicked()
{
    for( int i=0; i<optimizationList.count(); i++ )
    {
        if( solutionFixButtons.at(i) && solutionFixButtons.at(i)->isChecked() )
            optimizationList[i].solution = Optimization::Fix;
        else
            optimizationList[i].solution = Optimization::Ignore;
    }

    emit solutions( optimizationList );
}

