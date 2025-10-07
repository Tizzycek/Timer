#include "timercontroller.h"

TimerController::TimerController(QObject*parent) : QObject(parent), timer(new QTimer(this)), totalSec(0) {
    connect(timer, &QTimer::timeout, this, &TimerController::update);
}

void TimerController::calculateTotalSec(unsigned hours, unsigned minutes, unsigned seconds){
    remainingTime = QTime(hours, minutes, seconds);
    totalSec = hours * 3600 + minutes * 60 + seconds;
}

void TimerController::start(){
    timer->start(1000);
    emit tick(remainingTime, 0);
}

void TimerController::stop(){
    timer->stop();
}

void TimerController::update(){
    remainingTime = remainingTime.addSecs(-1);
    unsigned elapsed = totalSec - (remainingTime.hour() * 3600 + remainingTime.minute() * 60 + remainingTime.second());
    emit tick(remainingTime, elapsed);

    if (remainingTime == QTime(0, 0, 0)){
        timer->stop();
        emit finished();
    }
}

unsigned TimerController::totalSeconds() const{
    return totalSec;
}

unsigned TimerController::elapsedSeconds() const {
    return totalSec - (remainingTime.hour() * 3600 + remainingTime.minute() * 60 + remainingTime.second());
}

QTime TimerController::remaining() const {
    return remainingTime;
}
