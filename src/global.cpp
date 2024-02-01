//
// C++ Implementation: global
//
// Description:
//
//
// Author: Daniel Faust <hessijames@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "global.h"

#include <KFormat>
#include <KLocalizedString>
#include <QLocale>

Global::Global()
{
}

Global::~Global()
{
}

QString Global::prettyNumber(double num, QString unit, short digits)
{
    QString prettyString;
    if (unit == "%" && digits == 3) {
        if (num < 10)
            prettyString.asprintf("%.2f %%", num);
        else if (num < 100)
            prettyString.asprintf("%.1f %%", num);
        else
            prettyString.asprintf("%.0f %%", num);
    } else if (unit == "%" && digits == 2) {
        if (num < 10)
            prettyString.asprintf("%.1f %%", num);
        else
            prettyString.asprintf("%.0f %%", num);
    } else if (unit == "B") {
        KFormat format;
        prettyString = format.formatValue(num, KFormat::Unit::Bit);
    } else if (unit == "ms") {
        KFormat format;
        prettyString = format.formatDuration(num, KFormat::DurationFormatOption::ShowMilliseconds);
    } else if (unit == "s") {
        KFormat format;
        prettyString = format.formatDuration(num);
    }
    return prettyString;
}
