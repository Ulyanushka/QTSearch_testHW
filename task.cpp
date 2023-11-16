#include "task.h"
#include <QtConcurrent>
#include <QFuture>


Task::Task(QObject *parent)
    : QObject{parent}
{

}


Task::Task(const QDir& dir, const QString& file)
{
    this->dir = dir;
    this->file = file;

    connect(&watcher, &QFutureWatcher<int>::finished,
            this, &Task::handleFinished);
}


int Task::reviewFile(const QString& path, const QString& searchString)
{
    QFile curFile(path);
    curFile.open(QIODevice::ReadOnly);
    QTextStream in(&curFile);
    QString line;
    int counter = 0;
    do{
        line = in.readLine();
        int index = 0;
        while ((index = line.indexOf(searchString, index)) != -1)
        {
            index++;
            counter++;
        }
    }while(!line.isNull());
    return counter;
}


void Task::run(const QString& searchString)
{
    QFuture<int> future = QtConcurrent::run(this, &Task::reviewFile,
                                            dir.path() + "\\" + file, searchString);
    watcher.setFuture(future);
}


void Task::handleFinished()
{
    counter = watcher.result();
    emit fileReviewed(file, counter);
}
