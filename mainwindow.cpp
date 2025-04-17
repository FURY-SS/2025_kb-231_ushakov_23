#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),  // используем SmartPointer
    label(new QLabel())
{
    ui->setupUi(this);


    label->setAlignment(Qt::AlignTop);
    ui->scrollArea->setWidget(label.get());



}


MainWindow::~MainWindow() {
}
