#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QString>
#include <QDir>
#include <QtConcurrent>
#include <QFileDialog>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_path->setReadOnly(true);
    ui->lineEdit_threads->setValidator(new QIntValidator());

    connect(ui->chooseButton, &QPushButton::clicked,
            this, &MainWindow::choose_directory);
    connect(ui->searchButton, &QPushButton::clicked,
            this, &MainWindow::start_search);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::choose_directory()
{
    QFileDialog dialog;
    ui->lineEdit_path->setText(dialog.getExistingDirectory(this));
}


void MainWindow::filesToTable()
{
    ui->tableWidget->setRowCount(files.length());
    for(int i = 0; i < files.length(); i++)
    {
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem("Under review"));
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(files[i]));
    }
}


bool MainWindow::areLinesFilled()
{
    bool a = ui->lineEdit_path->text().isEmpty();
    bool b = ui->lineEdit_searchString->text().isEmpty();
    bool c = ui->lineEdit_threads->text().isEmpty();
    return (!a & !b & !c);
}


void MainWindow::disableUI(bool state)
{
    ui->chooseButton->setDisabled(state);
    ui->searchButton->setDisabled(state);
    ui->lineEdit_searchString->setDisabled(state);
    ui->lineEdit_threads->setDisabled(state);
}


void MainWindow::start_search()
{
    if(!areLinesFilled())
        return;

    ui->tableWidget->clearContents();
    files.clear();

    QDir dir(ui->lineEdit_path->text());
    dir.setNameFilters({"*.txt"});
    for(auto &file : dir.entryList())
        files.append(file);

    filesToTable();

    if(files.isEmpty()) {
        ui->label_status->setText("Searching is done!");
        return;
    }

    disableUI(true);

    ui->label_status->setText("Work in progress...");

    job.reset(new Job(dir, ui->lineEdit_searchString->text()));

    connect(job.data(), &Job::counter_ready,
            this, &MainWindow::display_counter);
    connect(job.data(), &Job::all_files_reviewed,
            this, &MainWindow::finish_search);

    job->manageTasks(ui->lineEdit_threads->text().toInt());
}


void MainWindow::display_counter(const QString& file, const int& counter)
{
    int fileRow = files.indexOf(file);
    ui->tableWidget->setItem(fileRow, 1, new QTableWidgetItem(QString::number(counter)));
}


void MainWindow::finish_search()
{
    disableUI(false);
    ui->label_status->setText("Searching is done!");
}
