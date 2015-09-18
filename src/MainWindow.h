#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QFileDialog>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_findButton_clicked();
    void on_replaceButton_clicked();
    void on_replaceAllButton_clicked();
    void on_actionTidy_triggered();
    void on_actionOpen_triggered();
    void on_actionFormat_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionSearch_and_Replace_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionWeb_Preview_triggered();

private:
    Ui::MainWindow *ui;
    QString fileName;
};

#endif // MAINWINDOW_H
