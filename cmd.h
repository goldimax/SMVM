//
// Created by goldimax on 18-10-28.
//

#pragma once

#include <QHash>
#include <QVector>
#include <QString>
#include <global.h>
#include "i18n/i18n.h"
#include "code.h"
#include "mem.h"

typedef void(*cmdFun)(QVector<QString> &arg);

void help(QVector<QString> &arg) {
    static QVector<QString> info = {
            "SMVM - self modifiable virtual machine",
            "\trun <FILE>\trun from <FILE>",
            "\thelp\t\tprint this info"
    };
    for (const auto &s:info) {
        cout << i18n::get(s) << endl;
    }
}

QString format(QString s) {
    if (s.size() < 2) return "0" + s;
    if (s.size() > 2) return s.right(2);
    return s;
}

void runFile(QVector<QString> &arg) {
    QFile execFile(arg.back());
    if (!execFile.exists()) {
        cerr << i18n::get(arg.back() + i18n::get(" not find"));
        return;
    }
    execFile.open(QIODevice::ReadOnly);
    QVector<QString> ins;
    QTextStream ein(&execFile);
    while (!ein.atEnd()) {
        QString s;
        ein >> s;
        ins.push_back(s);
    }
    auto mem = (char *) getMen(4096);
    runFun f = genCode(mem, ins);
    f();
    munmap(mem, 4096);
}

QHash<QString, cmdFun> cmd = {
        {"",     help},
        {"help", help},
        {"run",  runFile}
};

void run(QVector<QString> &arg) {
    QString command = arg[0];
    arg.removeFirst();
    if (cmd.find(command) != cmd.end()) {
        if (arg.empty()) arg.push_back("");
        cmd[command](arg);
    } else {
        cerr << i18n::get("Cannot find command ") << command << endl;
        QVector<QString> nil;
        help(nil);
    }
}