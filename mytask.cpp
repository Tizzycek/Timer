#include "mytask.h"
#include <QMessageBox>
#include <QDebug>
#include <QProcess>

#ifdef _WIN32
void MyTask::run() {
    QString program = "cmd.exe";
    QStringList arguments;
    arguments << "/C" << "start" << "cmd" << "/C" << ".\\ASCIIVideoPlayer\\ASCIIVideoPlayer.exe";
    qDebug() << arguments;

    bool success = QProcess::startDetached(program, arguments);

    if (!success){
        //QMessageBox::critical(this, "Errore fatale", "Il timer non può essere avviato");
        abort();
    }

    this->deleteLater();   
}
#else
void MyTask::run(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Error");
    msgBox.setText("To be implemented!");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
}
#endif
