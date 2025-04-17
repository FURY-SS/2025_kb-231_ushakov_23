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
    bool isPressed;     // Флаг нажатия кнопки мыши
    QPointF current;    // Текущая позиция курсора (начальная точка)
    QPointF next;       // Следующая позиция курсора (конечная точка)
    int instrument;     // Текущий выбранный инструмент (1-карандаш, 2-ластик и т.д.)
    QColor color;       // Текущий цвет рисования
    QPainter painter;   // Объект для рисования
    int widthOfPen;     // Текущая толщина кисти
    bool changed;       // Флаг изменений (для запроса сохранения)


    // Вспомогательные методы
    void createActions();               // Создание меню и действий
    void loadFile(const QString &fileName); // Загрузка файла
    void repaintButtons();              // Обновление состояния кнопок инструментов


protected:
    // Обработчики событий
    void paintEvent(QPaintEvent *);             // Событие перерисовки
    void mouseMoveEvent(QMouseEvent *ev);       // Движение мыши
    void mousePressEvent(QMouseEvent *ev);      // Нажатие кнопки мыши
    void mouseReleaseEvent(QMouseEvent *ev);    // Отпускание кнопки мыши
    void closeEvent(QCloseEvent *event);        // Закрытие окна


public:
    explicit MainWindow(QWidget *parent = 0); // Конструктор
    ~MainWindow();


public slots:
    // Слоты для обработки действий
    //void newFile();             // Создать новый файл
    void open();                // Открыть файл
    bool save();                // Сохранить файл
    void pen();                 // Выбрать карандаш
    void lastic();              // Выбрать ластик
    void line();                // Выбрать линию
    void drawLine();            // Нарисовать линию
    void ellipse();             // Выбрать эллипс
    void drawEllipse();         // Нарисовать эллипс
    void rectangle();           // Выбрать прямоугольник
    void drawRectangle();       // Нарисовать прямоугольник
    void setColor();            // Выбрать цвет
    void setPenWidth(int width);// Установить толщину кисти
};


#endif // MAINWINDOW_H
