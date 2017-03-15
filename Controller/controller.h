#include "../Repository/Repository.h"
#include "../Undo/Undo.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#pragma once

class controller
{
private:
    file_repo_medicament &repo;
    vector<ActiuneUndo*> act_undo;

public:

    ~controller()
    {
        while(!act_undo.empty())
        {
            delete act_undo.back();
            act_undo.pop_back();
        }
    }

    controller(file_repo_medicament &repo):repo{repo}
    {

    }

    int adauga_medicament(const char denumire[],const float pret,const char producator[], const char s_activa[])
    {
        if(repo.adauga_medicament(denumire,pret,producator,s_activa))
        {
            act_undo.push_back(new UndoADD{medicament(denumire,pret,producator,s_activa),repo});
            repo.save_lista();
            return 1;
        }
        return 0;
    }

    int elimina_medicament(const char denumire[],const float pret,const char producator[], const char s_activa[])
    {
        if(repo.elimina_medicament(denumire,pret,producator,s_activa))
        {
            act_undo.push_back(new UndoDELETE{medicament(denumire,pret,producator,s_activa),repo});
            repo.save_lista();
            return 1;
        }
        return 0;
    }

    int modifica_medicament(medicament vechi, medicament nou)
    {
        if(vechi==nou)
            return 0;
        if(repo.elimina_medicament(vechi.get_denumire(),
                                vechi.get_pret(),
                                vechi.get_producator(),
                                vechi.get_substanta()))
        {
        repo.adauga_medicament(nou.get_denumire(),
                               nou.get_pret(),
                               nou.get_producator(),
                               nou.get_substanta());

        act_undo.push_back(new UndoMODIFICA{vechi,nou,repo});

        repo.save_lista();
        return 1;
        }
        return 0;
    }
    void do_UNDO()
    {
        if(act_undo.empty())
            return;

        (act_undo.back())->doUndo();
        delete act_undo.back();
        act_undo.pop_back();
        repo.save_lista();

    }
    vector<medicament> getall()
    {
        return repo.get_all();
    }

    vector<medicament> get_sorted_vector(bool (*comp)(medicament&, medicament&))
    {
        return repo.get_sorted_vector(comp);
    }

    void adauga_medicament_reteta(const char denumire[],const float pret,const char producator[], const char s_activa[])
    {
        repo.adauga_medicament_reteta(denumire,pret,producator,s_activa);
    }

    vector<medicament> get_reteta()
    {
        return repo.get_reteta();
    }
    int get_reteta_size()
    {
        return get_reteta().size();
    }

    void export_CSV()
    {
        repo.export_as_CSV();
    }

    void export_HTML()
    {
        repo.export_as_HTML();
    }
    void generare_reteta(int n)
    {
        vector<medicament> v=getall();
        int a[n],i,unic,len=0,med,dim=v.size();
        medicament q;

        srand (time(NULL));

        if(n>dim)
            n=dim;

        while(len<n)
        {
            med=rand();
            med=med%dim;
            unic=1;
            for(i=0;i<len;i++)
                if(a[i]==med)
                {
                    unic=0;
                    break;
                }
            if(unic)
                {a[len]=med;
                len++;}
        }
        dim=get_reteta().size();

        for(i=0;i<dim;i++)
        {
            repo.elimina_medicament_reteta();
        }

        for(i=0;i<n;i++)
        {
            q=*(v.begin()+a[i]);
            adauga_medicament_reteta(q.get_denumire(),q.get_pret(),q.get_producator(),q.get_substanta());
        }

    }

};
