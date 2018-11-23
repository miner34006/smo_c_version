#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <core/src/functional/FunctionalModule.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_applyButton_clicked();

    void on_startButton_clicked();

    void on_goButton_clicked();

private:
    Ui::MainWindow *ui;
    FunctionalModule *fm;
    void onPoelokEvent();
};

#endif // MAINWINDOW_H
