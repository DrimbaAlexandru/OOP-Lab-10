#ifndef GUI_W_H
#define GUI_W_H

#include <QEvent>
#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include <QListWidget>
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include "Controller/controller.h"
#include <windows.h>
#include "gui_cos.h"
#include "gui_graphic.h"
#include "observer.h"

#include <iostream>

class GUI_W: public QWidget
{
private:

    observable obs;
    QListWidget* Lista= new QListWidget;
    QHBoxLayout* Lay1 = new QHBoxLayout;
    QHBoxLayout* lay_st_under = new QHBoxLayout;
    QVBoxLayout* lay_st = new QVBoxLayout;
    QVBoxLayout* lay_dr = new QVBoxLayout;
    QHBoxLayout* lay_dr_under=new QHBoxLayout;
    QVBoxLayout* lay_dr_under_st=new QVBoxLayout;
    QVBoxLayout* lay_dr_under_dr=new QVBoxLayout;

    QPushButton* btn_new_cos_list = new QPushButton("Deschide cos cumparaturi (lista)");
    QPushButton* btn_new_cos_draw = new QPushButton("Deschide cos cumparaturi (desen)");
    QPushButton* btn_sort_denumire = new QPushButton("Sortare dupa denumire",nullptr);
    QPushButton* btn_unsort = new QPushButton("Reload",nullptr);
    QPushButton* btn_undo = new QPushButton("Undo",nullptr);
    QPushButton* btn_add = new QPushButton("Add",nullptr);
    QPushButton* btn_mod = new QPushButton("Modifica",nullptr);
    QPushButton* btn_del = new QPushButton("Delete",nullptr);
    QPushButton* btn_f_den=new QPushButton("Filtrare dupa denumire");
    QPushButton* btn_f_prod=new QPushButton("Filtrare dupa producator");
    QPushButton* btn_f_subs=new QPushButton("Filtrare dupa substanta");
    QPushButton* btn_reset=new QPushButton("Clear fields");

    QLineEdit* ln_denum = new QLineEdit;
    QDoubleSpinBox* ln_pret  = new QDoubleSpinBox ;
    QLineEdit* ln_prod  = new QLineEdit;
    QLineEdit* ln_subst = new QLineEdit;

    QLabel* lb_denum = new QLabel("  Denumire:",nullptr);
    QLabel* lb_pret  = new QLabel("      Pret:",nullptr);
    QLabel* lb_prod  = new QLabel("Producator:",nullptr);
    QLabel* lb_subst = new QLabel(" S. activa:",nullptr);

    QHBoxLayout* box_denum = new QHBoxLayout;
    QHBoxLayout* box_pret  = new QHBoxLayout;
    QHBoxLayout* box_prod = new QHBoxLayout;
    QHBoxLayout* box_subst = new QHBoxLayout;

    controller &ctr;
    vector<medicament> lista_m;

    void populate_list(const vector<medicament> & l)
    {
        obs.notify();
        Lista->clear();
        unsigned i;
        medicament m;
        for(i=0;i<l.size();i++)
        {
            m=l[i];
            Lista->addItem(m.get_denumire());
        }
    }

    void conectare()
    {
        QObject::connect(btn_sort_denumire, &QPushButton::clicked,[&]()
        {
            lista_m=ctr.get_sorted_vector([](medicament &m1, medicament &m2){return  strcmp(m1.get_denumire(), m2.get_denumire()) <0;   });
            populate_list(lista_m);
        });
        QObject::connect(btn_unsort, &QPushButton::clicked,[&]()
        {
            lista_m=ctr.getall();
            populate_list(lista_m);
        });
        QObject::connect(btn_f_den, &QPushButton::clicked,[&]()
        {
            auto l=ctr.getall();
            lista_m=vector<medicament>();
            QString str;
            Lista->clear();
            unsigned i;
            medicament m;
            for(i=0;i<l.size();i++)
            {
                m=l[i];
                str=QString(m.get_denumire());
                if(str.toUpper().contains(ln_denum->text().toUpper()))
                {
                    Lista->addItem(m.get_denumire());
                    lista_m.push_back(m);
                }
            }
        });
        QObject::connect(btn_f_subs, &QPushButton::clicked,[&]()
        {
            auto l=ctr.getall();
            lista_m=vector<medicament>();
            QString str;
            Lista->clear();
            unsigned i;
            medicament m;
            for(i=0;i<l.size();i++)
            {
                m=l[i];
                str=QString(m.get_substanta());
                if(str.toUpper().contains(ln_subst->text().toUpper()))
                {
                    Lista->addItem(m.get_denumire());
                    lista_m.push_back(m);
                }
            }
        });
        QObject::connect(btn_f_prod, &QPushButton::clicked,[&]()
        {
            auto l=ctr.getall();
            lista_m=vector<medicament>();
            QString str;
            Lista->clear();
            unsigned i;
            medicament m;
            for(i=0;i<l.size();i++)
            {
                m=l[i];
                str=QString(m.get_producator());
                if(str.toUpper().contains(ln_prod->text().toUpper()))
                {
                    Lista->addItem(m.get_denumire());
                    lista_m.push_back(m);
                }
            }
        });
        QObject::connect(btn_new_cos_list,&QPushButton::clicked,[&](){
            cos_cumparaturi* cos=new cos_cumparaturi(ctr,obs);
            cos->show();

        });

        QObject::connect(btn_new_cos_draw,&QPushButton::clicked,[&](){
            cos_draw* cos=new cos_draw(ctr,obs);
            cos->show();
        });
        QObject::connect(btn_undo,&QPushButton::clicked,[&]()
        {
            ctr.do_UNDO();
            lista_m=ctr.getall();
            populate_list(lista_m);
        });
        QObject::connect(btn_add,&QPushButton::clicked,[&]()
        {
            char denum[64],prod[64],subst[64];
            float pret;
            strcpy(denum,ln_denum->text().toStdString().c_str());
            strcpy(prod,ln_prod->text().toStdString().c_str());
            strcpy(subst,ln_subst->text().toStdString().c_str());
            pret=ln_pret->value();
            if(strlen(denum)==0)
            {
                QMessageBox msg;
                msg.setText("Denumirea nu poate fi vida!");
                msg.addButton(QMessageBox::Ok);
                msg.exec();
                return;
            }
            if(!ctr.adauga_medicament(denum,pret,prod,subst))
            {
                QMessageBox msg;
                msg.setText("Medicamentul exista deja!");
                msg.addButton(QMessageBox::Ok);
                msg.exec();
                return;
            }
            lista_m=ctr.getall();
            populate_list(lista_m);
        });
        QObject::connect(btn_mod,&QPushButton::clicked,[&]()
        {
            QList<QListWidgetItem*> l_sel=Lista->selectedItems();
            if(l_sel.size()!=1)
                return;
            unsigned row=Lista->row(Lista->currentItem());
            if(row>lista_m.size()) return;
            medicament old=lista_m[row];

            char denum[64],prod[64],subst[64];
            float pret;
            strcpy(denum,ln_denum->text().toStdString().c_str());
            strcpy(prod,ln_prod->text().toStdString().c_str());
            strcpy(subst,ln_subst->text().toStdString().c_str());
            pret=ln_pret->value();

            if(!ctr.modifica_medicament(old,medicament(denum,pret,prod,subst)))
            {
                QMessageBox msg;
                msg.setText("Datele nu au fost modificate!");
                msg.addButton(QMessageBox::Ok);
                msg.exec();
                return;
            }
            lista_m=ctr.getall();
            populate_list(lista_m);
        });
        QObject::connect(btn_del,&QPushButton::clicked,[&]()
        {
            QList<QListWidgetItem*> l_sel=Lista->selectedItems();
            if(l_sel.size()!=1)
            {
                QMessageBox msg;
                msg.setText("Niciun element selectat");
                msg.addButton(QMessageBox::Ok);
                msg.exec();
                return;
            }
            int row=Lista->row(Lista->currentItem());

            ctr.elimina_medicament(lista_m[row].get_denumire(),
                                   lista_m[row].get_pret(),
                                   lista_m[row].get_producator(),
                                   lista_m[row].get_substanta());
            lista_m=ctr.getall();
            populate_list(lista_m);
            Lista->setCurrentRow(row);
        });
        QObject::connect(btn_reset,&QPushButton::clicked,[&]()
        {
            ln_denum->setText("");
            ln_pret->setValue(0);
            ln_prod->setText("");
            ln_subst->setText("");
        });
        QObject::connect(Lista,&QListWidget::itemSelectionChanged,[&]()
        {
            QList<QListWidgetItem*> l_sel=Lista->selectedItems();
            if(l_sel.size()!=1)
                return;
            unsigned row=Lista->row(Lista->currentItem());
            if(row>lista_m.size()) return;
            ln_denum->setText(QString(lista_m[row].get_denumire()));
            ln_pret->setValue(lista_m[row].get_pret());
            ln_prod->setText(QString(lista_m[row].get_producator()));
            ln_subst->setText(QString(lista_m[row].get_substanta()));
        });

    }
public:
    GUI_W(controller &ctr):ctr{ctr}
    {

        conectare();
        ln_pret->setMaximum(10000.0);
        this->setWindowTitle("LAB OOP");

        this->setLayout(Lay1);
        Lay1->addLayout(lay_st);
        Lay1->addLayout(lay_dr);

        box_denum->addWidget(lb_denum);
        box_pret ->addWidget(lb_pret );
        box_prod ->addWidget(lb_prod );
        box_subst->addWidget(lb_subst);
        box_denum->addWidget(ln_denum);
        box_pret ->addWidget(ln_pret );
        box_prod ->addWidget(ln_prod );
        box_subst->addWidget(ln_subst);

        lay_st->addWidget(Lista);
        lay_st->addLayout(lay_st_under);
        lista_m=ctr.getall();
        populate_list(lista_m);

        lay_dr->addLayout(box_denum);
        lay_dr->addLayout(box_pret);
        lay_dr->addLayout(box_prod);
        lay_dr->addLayout(box_subst);
        lay_st_under->addWidget(btn_sort_denumire);
        lay_st_under->addWidget(btn_unsort);
        lay_dr->addLayout(lay_dr_under);
        lay_dr_under->addLayout(lay_dr_under_st);
        lay_dr_under->addLayout(lay_dr_under_dr);

        lay_dr_under_st->addWidget(btn_add);
        lay_dr_under_st->addWidget(btn_mod);
        lay_dr_under_st->addWidget(btn_del);
        lay_dr_under_st->addWidget(btn_undo);
        lay_dr_under_st->addWidget(btn_reset);

        lay_dr_under_dr->addWidget(btn_new_cos_list);
        lay_dr_under_dr->addWidget(btn_new_cos_draw);

        lay_st->addWidget(btn_f_den);
        lay_st->addWidget(btn_f_prod);
        lay_st->addWidget(btn_f_subs);
    }

};

#endif // GUI_W_H
