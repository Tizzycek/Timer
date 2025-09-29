#include "mytask.h"
#include <QMessageBox>
#include <QDebug>
#include <QProcess>

void MyTask::run() {
    QString program = "cmd.exe";
    QStringList arguments;
    arguments << "/C" << "start" << "cmd" << "/C" << ".\\executable\\test.exe";

    bool success = QProcess::startDetached(program, arguments);

    if (!success){
        //QMessageBox::critical(this, "Errore fatale", "Il timer non può essere avviato");
        abort();
    }

    this->deleteLater();
}
