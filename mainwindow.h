#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    unsigned totalSeconds = 0;
    ~MainWindow();

private slots:
    void startCountdown();     // quando si clicca "Avvia"
    void updateCountdown();    // ogni secondo
    void startMyTask();        // quando il tempo scade
    void info();
    void modificaConfig();
    //void chiudi();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTime remainingTime;
    inline QString randomSentence();
    void stopTimer(QString stopPath);
};

#endif // MAINWINDOW_H
