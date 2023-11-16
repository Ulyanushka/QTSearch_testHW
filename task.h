#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QFutureWatcher>
#include <QDir>

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = nullptr);
    ~Task() = default;

    Task(const QDir& dir, const QString& file);

    void run(const QString& searchString);

signals:
    void fileReviewed(const QString& file, const int& counter);

private slots:
    void handleFinished();

private:
    int reviewFile(const QString& path, const QString& searchString);

    QFutureWatcher<int> watcher;
    QDir dir;
    QString file;
    int counter;
};

#endif // TASK_H
