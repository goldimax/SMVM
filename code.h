//
// Created by goldimax on 18-10-28.
//

#pragma once

#include <QString>
#include <QVector>
#include <QHash>
#include <QJsonObject>
#include <qglobal.h>
#include "global.h"

typedef void(*runFun)();

void printInt(int i) { cout << i << endl; }

QHash<QString, char*> funs = {
        {"printInt", (char*)printInt}
};

void writeAddr(char *&m, char *p) {
    for (auto ip = (unsigned long long)p, i = 0ull; i < 8; i++) {
        *m = ip % 256;
        ip /= 256;
        m++;
    }
}

runFun genCode(char *mem, QVector<QString> &ins) {
    char *p = mem;
    for (auto s:ins) {
        if (s.front() == '@') {
            s.replace("@", "");
            auto x = s.split(':');
            funs[x[0]] = p;
            p += x[1].toULongLong();
        }
    }
    p = nullptr;
    for (auto s:ins) {
        if (s.size() == 2) {
            bool ok;
            *p = (char)s.toInt(&ok, 16);
            p++;
        } else if (s.front() == '<' && s.back() == '>') {
            s.replace("<", "");
            s.replace(">", "");
            auto x = s.split('+');
            if (x.size() == 1) x.push_back("0");
            writeAddr(p, funs[x[0]] + x[1].toULongLong());
        } else if (s.front() == '@') {
            s.replace("@", "");
            p = funs[s.split(':')[0]];
        }
    }
    return (runFun) funs["main"];
}
