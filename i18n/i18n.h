//
// Created by goldimax on 18-10-28.
//

#pragma once

#include <QString>
#include <QLocale>
#include <cstdlib>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include "../global.h"

namespace i18n {
    bool exists = true;
    QHash<QString, QString> dict;

    const QString &get(const QString &s) {
        if (dict.size() == 0 && exists) {
            QFile langFile("i18n/" + locale + ".json");
            if (!langFile.exists()) {
                exists = false;
                return s;
            }
            langFile.open(QIODevice::ReadOnly);
            QTextStream lang(&langFile);
            QString json = lang.readAll();
            auto tmp = QJsonDocument::fromJson(json.toUtf8()).object().toVariantHash();
            for (auto i = tmp.constKeyValueBegin(); i != tmp.constKeyValueEnd(); i++) {
                dict[i.base().key()] = i.base().value().toString();
            }
        }
        if (dict.contains(s)) return dict[s];
        else return s;
    }
}
