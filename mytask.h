#ifndef MYTASK_H
#define MYTASK_H

#include <QObject>

class MyTask : public QObject {
    Q_OBJECT
public slots:
    void run();  // sarà chiamata nel thread
};

#endif // MYTASK_H
