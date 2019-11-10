#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>
#include <QResizeEvent>
#include "zgraphicscene.h"
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
    void rorateItem(QGraphicsItem *item, qreal angle);

private slots:

    void on_rotation_valueChanged(double arg1);
    void on_draw_clicked();

    void on_clear_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsPixmapItem *pix;
    ZGraphicsScene *scene;
    QTimer *timer;
    int timerCounter = 0;
    qreal state = 0.0; // Up/Down/Left/Right
    QPointF lastpos; // last position of point - line :)

};

#endif // MAINWINDOW_H
