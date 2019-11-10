#ifndef ZGRAPHICSCENE_H
#define ZGRAPHICSCENE_H

#include <QGraphicsScene>
#include <QPainter>


class ZGraphicsScene: public QGraphicsScene{

    int mGridSize;
    QColor mGridColor;
    bool mGridVisible;

    Q_OBJECT
public:
    ZGraphicsScene(QObject *parent = Q_NULLPTR):QGraphicsScene(parent),
        mGridSize(20),mGridColor(0x0a8affu),mGridVisible(true)
    {

    }
    bool gridVisible() const {
        return mGridVisible;
    }
    void setGridVisible(bool gridVisible){
        if(mGridVisible != gridVisible){
            mGridVisible = gridVisible;
            update();
        }
    }
    void setColor(QColor color){
        mGridColor = color;
        update();
    }

protected:
    void drawBackground(QPainter *painter, const QRectF &rect){
        painter->setPen(mGridColor);

        if(mGridVisible) {
            QRect r = rect.toRect();
            int xmin  =r.left() - r.left()%mGridSize - mGridSize;
            int ymin = r.top() - r.top()%mGridSize - mGridSize;
            int xmax = r.right() - r.right()%mGridSize + mGridSize;
            int ymax = r.bottom() - r.bottom()%mGridSize + mGridSize;
            for(int x=xmin ; x <= xmax; x += mGridSize ){
                painter->drawLine(x, r.top(), x, r.bottom());
            }

            for(int y=ymin ; y <= ymax; y+= mGridSize ){
                painter->drawLine(r.left(), y, r.right(), y);
            }
        }
    }
};

#endif // ZGRAPHICSCENE_H
