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

    // Создание меню и действий
    //createActions();

    // Настройка спинбокса для толщины кисти
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(setPenWidth(int)));

    // Инициализация переменных
    instrument = 1;         // По умолчанию выбран карандаш
    color.setRgb(0, 0, 0);  // Черный цвет по умолчанию
    widthOfPen = 3;         // Толщина кисти по умолчанию
    changed = false;        // Флаг изменений

    // Создание нового файла
    //newFile();

    // Обновление состояния кнопок инструментов
    repaintButtons();
}

void MainWindow::pen() {
    instrument = 1;
    repaintButtons();
}

void MainWindow::lastic() {
    instrument = 2;
    repaintButtons();
}

void MainWindow::line() {
    instrument = 3;
    repaintButtons();
}

void MainWindow::ellipse() {
    instrument = 4;
    repaintButtons();
}

void MainWindow::rectangle() {
    instrument = 5;
    repaintButtons();
}


void MainWindow::setPenWidth(int width) {
    widthOfPen = width;
}

void MainWindow::setColor() {

}

void MainWindow::repaintButtons() {
    QColor selectedColor(153, 153, 153);
    QColor defaultColor(255, 255, 255);

    QList<QPushButton*> butts = this->findChildren<QPushButton*>();

    for (int b = 0; b < butts.size(); b++) {
        if (butts[b]->objectName().contains("_")) {
            if (butts[b]->objectName() == QString("pushButton_%1").arg(instrument)) {
                butts[b]->setStyleSheet(
                    QString("background-color: rgb(%1, %2, %3);")
                        .arg(selectedColor.red())
                        .arg(selectedColor.green())
                        .arg(selectedColor.blue()));
            }
            else {
                butts[b]->setStyleSheet(
                    QString("background-color: rgb(%1, %2, %3);")
                        .arg(defaultColor.red())
                        .arg(defaultColor.green())
                        .arg(defaultColor.blue()));
            }
        }
    }
}


void MainWindow::mousePressEvent(QMouseEvent* event) {

}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {

}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {

}

void MainWindow::paintEvent(QPaintEvent* event) {

}

void MainWindow::drawLine() {

}

void MainWindow::drawEllipse() {

}

void MainWindow::drawRectangle() {

}

void MainWindow::open() {

}

bool MainWindow::save() {

}

void MainWindow::loadFile(const QString& fileName) {

}

void MainWindow::closeEvent(QCloseEvent* event) {

}


MainWindow::~MainWindow() {
}
