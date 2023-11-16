#include "job.h"
#include <QThreadPool>
#include <QFutureWatcher>
#include <QFuture>
#include <QtConcurrent>


Job::Job(QObject *parent)
    : QObject{parent}
{

}


Job::Job(const QDir& dir, const QString searchString)
{
    this->dir = dir;
    this->searchString = searchString;
    for (auto &file : dir.entryList())
        this->files.append(file);
}


void Job::manageTasks(const int num_of_threads)
{
    QThreadPool::globalInstance()->setMaxThreadCount(num_of_threads);
    for (auto &file : files)
    {
        tasks.append(QSharedPointer<Task>(new Task(dir, file)));
        connect(tasks.last().data(), &Task::fileReviewed,
                this, &Job::send_counter);

        tasks.last()->run(searchString);
    }
}


void Job::send_counter(const QString& file, const int& counter)
{
    emit counter_ready(file, counter);

    files.removeOne(file);
    if(files.empty())
        emit all_files_reviewed();
}
