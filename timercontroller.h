#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QTime>

class TimerController : public QObject
{
    Q_OBJECT
public:
    explicit TimerController(QObject*parent=nullptr);
    void start();
    void stop();
    unsigned totalSeconds() const;
    unsigned elapsedSeconds() const;
    QTime remaining() const;
    void calculateTotalSec(unsigned, unsigned, unsigned);

signals:
    void tick(QTime, unsigned);
    void finished();

private slots:
    void update();

private:
    QTimer*timer;
    QTime remainingTime;
    unsigned totalSec;
};

#endif // TIMERCONTROLLER_H
