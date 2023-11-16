#ifndef JOB_H
#define JOB_H


#include "task.h"
#include <QObject>
#include <QDir>
#include <QString>
#include <QList>


class Job : public QObject
{
    Q_OBJECT
public:
    explicit Job(QObject *parent = nullptr);
    ~Job() = default;

    Job(const QDir& dir, const QString searchString);

    void manageTasks(const int num_of_threads);

signals:
    void counter_ready(const QString& file, const int& counter);
    void all_files_reviewed();

private slots:
    void send_counter(const QString& file, const int& counter);

private:
    QList<QSharedPointer<Task>> tasks;

    QString searchString;
    QDir dir;
    QStringList files;
};

#endif // JOB_H
