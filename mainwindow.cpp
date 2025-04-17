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
    createActions();

    // Настройка спинбокса для толщины кисти
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(setPenWidth(int)));

    // Инициализация переменных
    instrument = 1;         // По умолчанию выбран карандаш
    color.setRgb(0, 0, 0);  // Черный цвет по умолчанию
    widthOfPen = 3;         // Толщина кисти по умолчанию
    changed = false;        // Флаг изменений

    // Создание нового файла
    newFile();

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
    isPressed = true;

    QPoint p = QPoint(
        ui->scrollArea->horizontalScrollBar()->value(),
        ui->scrollArea->verticalScrollBar()->value());
    QPoint pos = event->pos() + p;

    current = ui->scrollArea->mapFrom(this, pos);
    next = current;

    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    QPoint pos = QPoint(
        ui->scrollArea->horizontalScrollBar()->value(),
        ui->scrollArea->verticalScrollBar()->value());
    next = ui->scrollArea->mapFrom(this, event->pos() + pos);

    ui->statusBar->showMessage(
        (changed ? QString("* ") : QString("")) +
        QString::number(next.x()) + QString(",") + QString::number(next.y()));

    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    isPressed = false;

    QPoint pos = QPoint(
        ui->scrollArea->horizontalScrollBar()->value(),
        ui->scrollArea->verticalScrollBar()->value());
    next = ui->scrollArea->mapFrom(this, event->pos() + pos);

    switch (instrument) {
    case 3: {
        drawLine();
        break;
    }
    case 4: {
        drawEllipse();
        break;
    }
    case 5: {
        drawRectangle();
        break;
    }
    default: {
        break;
    }
    }
}

void MainWindow::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    if (current == next) {
        return;
    }

    switch (instrument) {
    case 1: {
        if (isPressed) {
            painter.begin(&img);
            painter.setPen(QPen(color, widthOfPen, Qt::SolidLine));
            changed = true;
            painter.drawLine(current, next);
            painter.end();
        }
        current = next;
        label->setPixmap(img);
        break;
    }
    case 2: {
        if (isPressed) {
            painter.begin(&img);
            painter.setPen(QPen(Qt::white, widthOfPen + 6, Qt::SolidLine));
            changed = true;
            painter.drawLine(current, next);
            painter.end();
        }
        current = next;
        label->setPixmap(img);
        break;
    }
    case 3: {
        imgTmp = img;
        if (isPressed) {
            painter.begin(&imgTmp);
            painter.setPen(QPen(color, widthOfPen, Qt::SolidLine));
            if (current != next) {
                painter.drawLine(current, next);
            }
            painter.end();
            label->setPixmap(imgTmp);
        }
        break;
    }
    case 4: {
        imgTmp = img;
        if (isPressed) {
            painter.begin(&imgTmp);
            painter.setPen(QPen(color, widthOfPen, Qt::SolidLine));
            painter.drawEllipse(QRectF(current, next));
            painter.end();
            label->setPixmap(imgTmp);
        }
        break;
    }
    case 5: {
        imgTmp = img;
        if (isPressed) {
            painter.begin(&imgTmp);
            painter.setPen(QPen(color, widthOfPen, Qt::SolidLine));
            painter.drawRect(QRectF(current, next));
            painter.end();
            label->setPixmap(imgTmp);
        }
        break;
    }
    default: {
        break;
    }
    }
}


void MainWindow::drawLine() {

}

void MainWindow::drawEllipse() {

}

void MainWindow::drawRectangle() {

}

void MainWindow::newFile() {
    if (changed) {
        save();
    }
    loadFile(":/template.png");
}

void MainWindow::open() {

}

bool MainWindow::save() {

}

void MainWindow::loadFile(const QString& fileName) {

}

void MainWindow::closeEvent(QCloseEvent* event) {

}


void MainWindow::createActions() {
    QMenu* fileMenu = menuBar()->addMenu(tr("&Файл"));

    QAction* newAct = fileMenu->addAction(tr("&Новый файл"));
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, SIGNAL(triggered(bool)), SLOT(newFile()));

    QAction* openAct = fileMenu->addAction(tr("&Открыть файл"));
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered(bool)), SLOT(open()));

    QAction* saveAct = fileMenu->addAction(tr("&Сохранить как"));
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered(bool)), SLOT(save()));

    QAction* quitAct = fileMenu->addAction(tr("&Выход"));
    quitAct->setShortcuts(QKeySequence::Quit);
    connect(quitAct, SIGNAL(triggered(bool)), SLOT(close()));
}

MainWindow::~MainWindow() {
}



