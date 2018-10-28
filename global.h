//
// Created by goldimax on 18-10-28.
//

#pragma once

#include <QTextStream>
#include <cstdlib>
#include <QString>

QTextStream cin(stdin);
QTextStream cout(stdout);
QTextStream cerr(stderr);

QString locale = QString(std::getenv("LANG")).mid(0, 5);
