#include <QString>
#include <QVector>
#include "global.h"
#include "cmd.h"

int main(int argc, char *argv[]) {
    QVector<QString> arg;
    for (int i = 1; i < argc; i++)
        arg.push_back(QString(argv[i]));
    if (arg.empty()) arg.push_back("");
    run(arg);
    return 0;
}
