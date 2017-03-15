#ifndef GUI_COS_H
#define GUI_COS_H

#include <QWidget>
#include <QLayout>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include "observer.h"
#include "Controller/controller.h"



class cos_cumparaturi:public QWidget,public observer
{
 private:
    controller& ctr;
    observable& obs;

    QHBoxLayout* main_layout=new QHBoxLayout;
    QVBoxLayout* lay_st=new QVBoxLayout;
    QVBoxLayout* lay_dr=new QVBoxLayout;
    QListWidget* lista=new QListWidget;
    QPushButton* btn_random=new QPushButton("Adauga elemente random");
    QPushButton* btn_goleste=new QPushButton("Goleste");
    QSpinBox* socotitoare=new QSpinBox();

    void conectare()
    {
        QObject::connect(btn_random,&QPushButton::clicked,[&](){

            ctr.generare_reteta(socotitoare->value());
            obs.notify();
        });
        QObject::connect(btn_goleste,&QPushButton::clicked,[&](){

            ctr.generare_reteta(0);
            obs.notify();
        });
    }
public:
    void update() override
    {
        socotitoare->setMaximum(ctr.getall().size());
        lista->clear();
        auto l=ctr.get_reteta();
        auto it=l.begin();
        medicament m;
        while(it!=l.end())
        {
            m=*it;
            lista->addItem(QString(m.get_denumire()));
            it++;
        }
    }
    cos_cumparaturi(controller &ctr,observable &obs): ctr{ctr},obs{obs}
    {
        conectare();
        update();
        obs.subscribe(this);
        main_layout->addLayout(lay_st);
        main_layout->addLayout(lay_dr);
        this->setLayout(main_layout);
        lay_st->addWidget(lista);
        lay_dr->addWidget(btn_random);
        lay_dr->addWidget(socotitoare);
        socotitoare->setMinimum(0);
        socotitoare->setMaximum(ctr.getall().size());
        lay_dr->addWidget(btn_goleste);
    }

    ~cos_cumparaturi()
    {
        obs.unsubscribe(this);
    }
};
#endif // GUI_COS_H
