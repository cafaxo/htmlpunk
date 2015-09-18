#include "MainWindow.h"
#include "ui_main.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->htmlPreviewDock->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_findButton_clicked() {    
    ui->htmlEdit->find(QRegExp(ui->searchField->text()));
}

void MainWindow::on_replaceButton_clicked() {
    ui->htmlEdit->replace(QRegExp(ui->searchField->text()), ui->replaceField->text());
}

void MainWindow::on_replaceAllButton_clicked() {
    ui->htmlEdit->replaceAll(QRegExp(ui->searchField->text()), ui->replaceField->text());
}

void MainWindow::on_actionOpen_triggered()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",  tr("Files (*.*)"));
    this->setWindowTitle("htmlpunk - " + fileName);
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    ui->htmlEdit->setText(file.readAll());
    file.close();
}

void MainWindow::on_actionTidy_triggered() {
    ui->htmlEdit->tidy(true);
}

void MainWindow::on_actionFormat_triggered() {
    ui->htmlEdit->tidy(false);
}

void MainWindow::on_actionUndo_triggered() {
    ui->htmlEdit->undo();
}

void MainWindow::on_actionRedo_triggered() {
    ui->htmlEdit->redo();
}

void MainWindow::on_actionCut_triggered() {
    ui->htmlEdit->cut();
}

void MainWindow::on_actionCopy_triggered() {
    ui->htmlEdit->copy();
}

void MainWindow::on_actionPaste_triggered() {
    ui->htmlEdit->paste();
}

void MainWindow::on_actionSearch_and_Replace_triggered() {
    ui->findReplaceDock->show();
    ui->searchField->setFocus();
}

void MainWindow::on_actionSave_triggered() {
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    file.write((const char *)ui->htmlEdit->document()->toPlainText().toLatin1().data());
    file.close();
}

void MainWindow::on_actionSave_As_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",  tr("Files (*.*)"));
    this->setWindowTitle("htmlpunk - " + fileName);
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    file.write((const char *)ui->htmlEdit->document()->toPlainText().toLatin1().data());
    file.close();
}

void MainWindow::on_actionWeb_Preview_triggered() {
    ui->htmlPreviewDock->show();
    ui->htmlPreview->setHtml(ui->htmlEdit->document()->toPlainText());
}
