#include "mytask.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QProcess>
#include <QDir>

void MyTask::run() {
#ifdef _WIN32
    QString program = "cmd.exe";
    QString exePath = QDir::toNativeSeparators(
        QCoreApplication::applicationDirPath() + "\\ASCIIVideoPlayer\\ASCIIVideoPlayer.exe"
        );

    QStringList arguments;
    arguments << "/C" << "start" << "" << exePath;

#elif defined(__linux__)
    QString program;
    QStringList arguments;

    QString exePath = QDir::cleanPath(QCoreApplication::applicationDirPath() + "/ASCIIVideoPlayer/ASCIIVideoPlayer");

    // Prova di diversi terminali (gnome, konsole e xterm)
    if (QFile::exists("/usr/bin/gnome-terminal")) {
        program = "gnome-terminal";
        arguments << "--" << exePath;
    } else if (QFile::exists("/usr/bin/konsole")) {
        program = "konsole";
        arguments << "-e" << exePath;
    } else if (QFile::exists("/usr/bin/xterm")) {
        program = "xterm";
        arguments << "-e" << exePath;
    } else {
        QMessageBox::critical(nullptr, "Errore", "Nessun terminale trovato per eseguire il programma CLI.");
        return;
    }

#else
    QMessageBox::critical(nullptr, "Errore", "Sistema operativo non supportato.");
    return;
#endif

    bool success = QProcess::startDetached(program, arguments);

    if (!success) {
        qCritical() << "Errore nell'avvio di" << program << arguments;
        QMessageBox::critical(nullptr, "Errore", "Impossibile avviare il programma CLI.");
    } else {
        qDebug() << "Processo CLI avviato con successo:" << program << arguments;
    }

    this->deleteLater();
}
