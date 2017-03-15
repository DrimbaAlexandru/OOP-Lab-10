#ifndef GUI_GRAPHIC_H
#define GUI_GRAPHIC_H

#include <QWidget>
#include <QLayout>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include "observer.h"
#include <stdlib.h>
#include "Controller/controller.h"
#include <QPainter>
#include <QImage>



class cos_draw:public QWidget,public observer
{
 private:
    controller& ctr;
    observable& obs;

    QHBoxLayout* main_layout=new QHBoxLayout;

    void paintEvent(QPaintEvent* ev) override
    {
        QPainter p{ this };
        int n=ctr.get_reteta_size();
        int i;
        QImage img=QImage("C:\\Users\\Alex\\Desktop\\Programare\\Faculta\\OOP Lab 10-11\\OOP_L10\\images.jpg");
        img=img.scaled(180,120);
        for(i=0;i<n;i++)
            p.drawImage(rand()%(width()-180),rand()%(height()-120),img);

    }
public:
    void update() override
    {
        this->repaint();
    }
    cos_draw(controller &ctr,observable &obs): ctr{ctr},obs{obs}
    {
        update();
        this->resize(480,360);
        obs.subscribe(this);
        this->setLayout(main_layout);


    }

    ~cos_draw()
    {
        obs.unsubscribe(this);
    }
};

#endif // GUI_GRAPHIC_H
