#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "smart_ptr.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

    SmartPointer<Ui::MainWindow> ui;
    SmartPointer<QLabel> label;

    // Основные переменные класса
    QPixmap img;        // Основное изображение для рисования
    QPixmap imgTmp;     // Временное изображение для предпросмотра фигур

public:
    explicit MainWindow(QWidget *parent = 0); // Конструктор
    ~MainWindow();


public slots:
    // Слоты для обработки действий
    //void newFile();             // Создать новый файл


};

#endif // MAINWINDOW_H
