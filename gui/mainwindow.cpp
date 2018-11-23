#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fm;
}

void MainWindow::on_applyButton_clicked()
{
    onPoelokEvent();
}

void MainWindow::on_startButton_clicked()
{
    onPoelokEvent();
}

void MainWindow::onPoelokEvent()
{
    QMessageBox msgBox;
    msgBox.setText("ХУЛЕ ТЫ СМО НЕ ДЕЛАЕШ ПОЕЛОК");
    msgBox.exec();
}

void MainWindow::on_goButton_clicked()
{
    onPoelokEvent();
}
