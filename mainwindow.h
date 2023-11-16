#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "job.h"
#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void choose_directory();
    void start_search();

    void display_counter(const QString& file, const int& counter);
    void finish_search();

private:
    bool areLinesFilled();
    void filesToTable();
    void disableUI(bool state);

    Ui::MainWindow *ui;

    QScopedPointer<Job> job;
    QStringList files;
};
#endif // MAINWINDOW_H
