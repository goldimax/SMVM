//
// Created by goldimax on 18-10-28.
//

#pragma once

#include <QString>
#include <QLocale>
#include "zh_CN.h"

namespace i18n {
    const QString &get(const QString &s) {
        QLocale locale;
        if (locale.language() == QLocale::Chinese) return zh_CN::get(s);
        return s;
    }
}
