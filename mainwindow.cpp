#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDebug>
#include <QtMath>
// 02/06/2018
#define MyApp "QFirstGameZAKI"
#define MyOrg "ZAKI PRO"

int sw = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init values
    QSettings sett(MyOrg,MyApp);
    auto state = sett.value("SplitterState").toByteArray();
    ui->splitter->restoreState(state);

    // Create :  Scene
    scene = new ZGraphicsScene(this);

    // Create : Pixmap item
    QImage im("://images/CAT FACE.png");
    im = im.scaledToWidth(25);
    pix = new QGraphicsPixmapItem(QPixmap::fromImage(im));

    // Add items to scene
    scene->addItem(pix);
    pix->setPos(0,0);

    // Items options:
    //pix->setFlag(QGraphicsItem::ItemIsMovable);

    // Create Timer:
    timer = new QTimer(this);

    // Create Animation:
    connect(timer,&QTimer::timeout,[&](){
        // Define the pen :)
        QPen pen(Qt::SolidLine);
        pen.setColor(QColor("#ff0000"));
        pen.setWidth(2);

        // factor = 20.0 : Grid Size of ZGraphicsScene : you can change it :)
        qreal fac = 20.0;

        // Check state (Up/Down ..)
        auto id = ui->buttonGroup->checkedId();
        if(id == -4)// left
            this->state = 180.0;
        else if(id == -5)// right
            this->state = 0.0;
        else if(id == -2)// up
            this->state = 90.0;
        else if(id == -3)// down
            this->state = -90.0;

        // Define the line :)
        QLineF line;
        line.setP1(lastpos);
        line.setAngle(this->state+ui->rotation->value());
        line.setLength(1*fac);

        // Draw Line!
        this->scene->addLine(line,pen);

        // Save last point position
        this->lastpos = line.p2();

        sw++;// just for swap the color!

        // Set position to cat cursor :)
        pix->setPos(lastpos.x(),lastpos.y()-10);

        // Increment Timer, at the END
        this->timerCounter++;
        if(this->timerCounter >= ui->position->value()){
            timer->stop();
            this->timerCounter=0;
        }
    });

    // init the cat cursor position :)
    lastpos = QPointF(500,500);
    pix->setPos(lastpos.x(),lastpos.y()-10);

    // Graphic View
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    this->showMaximized();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// SpinBox : Rotation
void MainWindow::on_rotation_valueChanged(double arg1){

    Q_UNUSED(arg1);
    /* Rotate Item From The Center */
    rorateItem(pix,this->state+(arg1-pix->rotation()));
}

// Button : Clocked : draw

void MainWindow::on_draw_clicked()
{
    // Define the pen :)
//    QPen pen(Qt::SolidLine);
//    sw%2 == 0 ? pen.setColor(QColor("#ff0000")): pen.setColor(QColor("#000000"));
//    pen.setWidth(2);

    // factor = 20.0 : Grid Size of ZGraphicsScene : you can change it :)
//    qreal fac = 20.0;

    // Check state (Up/Down ..)
//    qreal state = 0.0;
//    if(ui->buttonGroup->checkedButton() == (QAbstractButton*)ui->left)
//        state = 180.0;
//    else if(ui->buttonGroup->checkedButton() == (QAbstractButton*)ui->right)
//        state = 0.0;
//    else if(ui->buttonGroup->checkedButton() == (QAbstractButton*)ui->up)
//        state = 90.0;
//    else if(ui->buttonGroup->checkedButton() == (QAbstractButton*)ui->down)
//        state = -90.0;

    // Create Animation:
//    connect(timer,&QTimer::timeout,[&](){

//    // Define the line :)
//    QLineF line;
//    line.setP1(lastpos);
//    line.setAngle(state+ui->rotation->value());
//    line.setLength(1*fac);

//    // Draw Line!
//    this->scene->addLine(line,pen);

//    // Save last point position
//    this->lastpos = line.p2();
//    sw++;

//    // Set position to cat cursor :)
//    pix->setPos(lastpos.x(),lastpos.y()-10);

//    this->timerCounter++;
//    if(this->timerCounter == ui->position->value()){
//        timer->stop();
//        this->timerCounter=0;
//    }

//    });
    timer->start(20);
}

// Event : Resize
void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    auto w = ui->graphicsView->width();
    auto h = ui->graphicsView->height();
    scene->setSceneRect(0,0,w,h);
}

// Event : Close
void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    QSettings sett(MyOrg,MyApp);
    sett.setValue("SplitterState",ui->splitter->saveState());
}

// My Function :) : Rotaion items from the center
void MainWindow::rorateItem(QGraphicsItem *item, qreal angle)
{
    /* Rotate Item From The Center */
    QRectF rect = item->mapToScene(item->boundingRect()).boundingRect();
    QPointF center = rect.center();
    QTransform t;

    t.translate(center.x(), center.y());
    t.rotate(angle);
    t.translate(-center.x(), -center.y());

    item->setPos(t.map(item->pos()));
    item->setRotation(item->rotation() + angle);
}

// Clear Scene : view
void MainWindow::on_clear_clicked()
{
    this->scene->clear();

    QImage im("://images/CAT FACE.png");
    im = im.scaledToWidth(20);
    pix = new QGraphicsPixmapItem(QPixmap::fromImage(im));
    scene->addItem(pix);
    lastpos = QPointF(500,500);
    pix->setPos(lastpos.x(),lastpos.y()-10);
}
