#ifndef TIDYWORKER_H
#define TIDYWORKER_H

#include <QObject>
#include <tidy.h>
#include <buffio.h>

class TidyWorker : public QObject {
    Q_OBJECT

public:
    TidyWorker(QString source, bool cleanUp);
    ~TidyWorker();

private:
    QString source_;
    bool cleanUp_;

signals:
    void finishedTidy(QString tidiedSource);
    void finished();

public slots:
    void process();
};

#endif // TIDYWORKER_H
