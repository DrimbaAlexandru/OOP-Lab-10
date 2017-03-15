#include "../Controller/controller.h"
#include <string.h>
#include <iostream>

void teste()
{
    repo_medicament repo;
    int ok;

    repo.adauga_medicament("MED1",1,"MED1","MED1");
    repo.adauga_medicament("MED2",2,"MED2","MED2");
    ok=(repo.get_all().size()==2);
    if(!ok)
        throw 1;

    auto v=repo.get_all();
    auto it=v.begin();

    if(strcmp((*it).get_denumire(),"MED1")!=0)
        throw 2;

    repo.elimina_medicament("MED3",3,"MED3","MED3");
    ok=(repo.get_all().size()==2);
    if(!ok)
        throw 3;

    if((*((repo.get_sorted_vector([](medicament &m1, medicament &m2){return (m1.get_pret()>m2.get_pret());})).begin())).get_pret()!=2)
        throw 4;

    repo.elimina_medicament("MED2",2,"MED2","MED2");
    ok=(repo.get_all().size()==1);
    if(!ok)
        throw 5;

}
