#pragma once
#include "../Domain/medicament.h"
#include "../Utilities/VectorDinamic.h"
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>


class repo_medicament
{
protected:
    vector<medicament> lista_med;
    vector<medicament> reteta;



    int get_position_of_elem(const medicament &m, vector<medicament> &v)
    {
        auto it=v.begin();
        if(it==v.end())
            return -1;
        int poz=0;
        while((*it)!=m)
        {
            it++;
            poz++;
            if(it==v.end())
                return -1;
        }
        return poz;
    }

public:

    void export_as_CSV()
    {
        ofstream out("reteta.csv");
        medicament m;

        auto it=reteta.begin();
        while(it!=(reteta.end()))
        {

            m=(*it);
            out<<"\""<<m.get_denumire()<<"\","<<m.get_pret()<<",\""<<m.get_producator()<<"\",\""<<m.get_substanta()<<"\""<<endl;
            ++it;
        }
    }

    void export_as_HTML()
    {
        ofstream out("reteta.html");
        medicament m;

        auto it=reteta.begin();
        out<<"<table style=\"width:100%\" border=\"1\">"<<endl;
        while(it!=(reteta.end()))
        {
            out<<"  <tr>"<<endl;
            m=(*it);
            out<<"    <td>"<<m.get_denumire();
            out<<"    </td>\n<td>"<<m.get_pret();
            out<<"    </td>\n<td>"<<m.get_producator();
            out<<"    </td>\n<td>"<<m.get_substanta()<<"</td>\n";
            ++it;
            out<<"  </tr>"<<endl;
        }
        out<<"</table>";
    }

    int adauga_medicament(const char denumire[],const float pret,const char producator[], const char s_activa[])
    {
        medicament nou = medicament(denumire,pret,producator,s_activa);
        if(get_position_of_elem(nou,lista_med)==-1)
        {
            lista_med.push_back(nou);
            return 1;
        }
        return 0;

    }

    int elimina_medicament(const char denumire[],const float pret,const char producator[], const char s_activa[])
    {
        medicament nou = medicament(denumire,pret,producator,s_activa);
        if(get_position_of_elem(nou,lista_med)==-1)
            return 0;
        lista_med.erase(lista_med.begin()+get_position_of_elem(nou,lista_med));
        return 1;
    }

    vector<medicament> get_all()
    {
        return lista_med;
    }

    vector<medicament> get_sorted_vector(bool (*comp)(medicament&, medicament&))
    {
        auto lista_noua=lista_med;
        std::sort(lista_noua.begin(),lista_noua.end(),comp);
        return lista_noua;
    }

    void drop()
    {
        while(!lista_med.empty())
        {
            lista_med.pop_back();
        }
    }

    void adauga_medicament_reteta(const char denumire[],const float pret,const char producator[], const char s_activa[])
    {
        medicament nou = medicament(denumire,pret,producator,s_activa);
        reteta.push_back(nou);
    }

    void elimina_medicament_reteta()
    {
        reteta.erase(reteta.begin());
    }

    vector<medicament> get_reteta()
    {
        return reteta;
    }
};

class file_repo_medicament: public repo_medicament
{

public:

    file_repo_medicament()
    {
        get_lista();
    }
    void get_lista()
    {
        ifstream in("C:\\Users\\Alex\\Desktop\\Programare\\meds.ddb");
        char denum[64],prod[64],subst[64];
        float pret;
        drop();
        while(  in.getline(denum,63)&&
                in>>pret&&
                in.getline(prod,63)&&
                in.getline(prod,63)&&
                in.getline(subst,63))
        {
            adauga_medicament(denum,pret,prod,subst);
        }
    }

    void save_lista()
    {

        ofstream out("C:\\Users\\Alex\\Desktop\\Programare\\meds.ddb");
        medicament m;

        auto it=lista_med.begin();
        while(it!=(lista_med.end()))
        {

            m=(*it);
            out<<m.get_denumire()<<endl<<m.get_pret()<<endl<<m.get_producator()<<endl<<m.get_substanta()<<endl;
            ++it;
        }

    }
};
