#include "meniu.h"
void afiseaza_medicament(medicament q)
{
    cout<<setw(30)<<q.get_denumire()<<setw(8)<<q.get_pret()<<setw(18)<<q.get_producator()<<setw(23)<<q.get_substanta()<<endl;
}

void meniu::gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void meniu::citeste_denum(char denum[])
    {
    cout<<"Denumire: ";
    cin.get(denum,63);

    while(strlen(denum)==0)
    {
        cout<<"Numele nu poate fi vid!\n";
        cout<<"Denumire: ";
        cin.clear();cin.get();
        cin.get(denum,63);
    }
    cin.clear();cin.get();
}

void meniu::citeste_pret(float &pret)
{
    cout<<"\nPret: ";
    while(!scanf("%f",&pret)||(pret<=0))
    {
        cout<<"Pretul nu poate fi negativ, nul sau un non-numar!\n";
        cout<<"Pret: ";
        fflush(stdin);
    }
    cin.clear();cin.get();
}

void meniu::citeste_prod(char prod[])
{
    cout<<"\nProducator: ";
    cin.get(prod,63);

    while(strlen(prod)==0)
    {
        cout<<"Numele producatorului nu poate fi vid!";
        cout<<"\nProducator: ";
        cin.clear();cin.get();
        cin.get(prod,63);
    }
    cin.clear();cin.get();
}

void meniu::citeste_subst(char subst[])
{
    cout<<"\nSubstanta activa: ";
    cin.get(subst,63);

    while(strlen(subst)==0)
    {
        cout<<"Acest camp nu poate fi vid!\n";
        cout<<"Substanta activa: ";
        cin.clear();cin.get();
        cin.get(subst,63);
    }
    cin.clear();cin.get();
}

void meniu::adaugare()
{
    system("cls");
    char denum[64];
    float pret=0;
    char prod[64];
    char subst[64];

    citeste_denum(denum);
    citeste_pret(pret);
    citeste_prod(prod);
    citeste_subst(subst);

    ctr.adauga_medicament(denum, pret, prod, subst);
}

int meniu::stergere()
{
    vector<medicament> v=ctr.getall();
    int l=v.size();
    int sel=0;
    char r;
    medicament q;
    system("cls");

    cout<<"> Inapoi\n";
    afisare_toate(v);

    afisare:
    r=getch();
    switch(r)
    {
    case 'w':
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch(' ');
        if(sel==0)
            sel=l;
        else
            sel--;
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch('>');
        goto afisare;
    case 's':
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch(' ');
        if(sel==l)
            sel=0;
        else
            sel++;
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch('>');
        goto afisare;
    case 13:
        if(sel==0)
            return 0;
        q=*(v.begin()+(sel-1));
        ctr.elimina_medicament(q.get_denumire(),q.get_pret(),q.get_producator(),q.get_substanta());
        return 1;
    default: goto afisare;
    }


}
void meniu::modifica()
{
    vector<medicament> v=ctr.getall();
    int l=v.size();
    int sel=0;
    char r;
    medicament vechi,nou;
    system("cls");

    cout<<"> Inapoi\n";
    afisare_toate(v);

    afisare:
    r=getch();
    switch(r)
    {
    case 'w':
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch(' ');
        if(sel==0)
            sel=l;
        else
            sel--;
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch('>');
        goto afisare;
    case 's':
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch(' ');
        if(sel==l)
            sel=0;
        else
            sel++;
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch('>');
        goto afisare;
    case 13:
        if(sel==0)
            return;
        vechi=*(v.begin()+(sel-1));
        goto inlocuire;
    default: goto afisare;
    }

    inlocuire:
    system("cls");
    char denum[64];
    float pret=0;
    char prod[64];
    char subst[64];

    citeste_denum(denum);
    citeste_pret(pret);
    citeste_prod(prod);
    citeste_subst(subst);

    nou=medicament(denum,pret,prod,subst);
    ctr.modifica_medicament(vechi,nou);
}
void meniu::cautare()
{
    system("cls");
    vector<medicament> v=ctr.getall();

    medicament q;
    int sel=0;
    char r;

    cout<<"> Inapoi\n  dupa denumire\n  dupa producator\n  dupa substanta activa";
    cere_dupa_ce:
    r=getch();
    switch(r)
    {
        case 'w':
            gotoxy(0,sel);
            putch(' ');
            if(sel==0)
                sel=3;
            else sel--;
            gotoxy(0,sel);
            putch('>');
            break;
        case 's':
            gotoxy(0,sel);
            putch(' ');
            if(sel==3)
                sel=0;
            else sel++;
            gotoxy(0,sel);
            putch('>');
            break;
        case 13:
            switch(sel)
            {
                case 0: return;
                case 1: goto cauta_dupa_denum;
                case 2: goto cauta_dupa_prod;
                case 3: goto cauta_dupa_subst;
            }
    }
    goto cere_dupa_ce;

    cauta_dupa_denum:
        system("cls");
        char denum[64];
        citeste_denum(denum);
        system("cls");

        cout<<setw(30)<<"Denumire"<<setw(8)<<"Pret"<<setw(18)<<"Producator"<<setw(23)<<"Substanta activa"<<endl;
        for_each(v.begin(),v.end(),[denum](medicament q){if (strstr(q.get_denumire(),denum)!=0) afiseaza_medicament(q);});

        getch();
        return;

    cauta_dupa_prod:
        system("cls");
        char prod[64];
        citeste_prod(prod);
        system("cls");

        cout<<setw(30)<<"Denumire"<<setw(8)<<"Pret"<<setw(18)<<"Producator"<<setw(23)<<"Substanta activa"<<endl;
        for_each(v.begin(),v.end(),[prod](medicament q){if (strstr(q.get_producator(),prod)!=0) afiseaza_medicament(q);});

        getch();
        return;

    cauta_dupa_subst:
        system("cls");
        char subst[64];
        citeste_subst(subst);
        system("cls");

        cout<<setw(30)<<"Denumire"<<setw(8)<<"Pret"<<setw(18)<<"Producator"<<setw(23)<<"Substanta activa"<<endl;
        for_each(v.begin(),v.end(),[subst](medicament q){if (strstr(q.get_substanta(),subst)!=0) afiseaza_medicament(q);});

        getch();
        return;
}

void meniu::sortare()
{
    system("cls");
    medicament q;
    VectorDinamic<medicament> v;
    int sel=0;
    char r;

    cout<<"> Inapoi\n  Cresc. dupa denumire\n  Cresc. dupa pret\n  Cresc. dupa producator\n  Cresc. dupa substanta activa\n";
    cout<<"  Descresc. dupa denumire\n  Descresc. dupa pret\n  Descresc. dupa producator\n  Descresc. dupa substanta activa";

    cere_dupa_ce:
    r=getch();
    switch(r)
    {
        case 'w':
            gotoxy(0,sel);
            putch(' ');
            if(sel==0)
                sel=8;
            else sel--;
            gotoxy(0,sel);
            putch('>');
            break;
        case 's':
            gotoxy(0,sel);
            putch(' ');
            if(sel==8)
                sel=0;
            else sel++;
            gotoxy(0,sel);
            putch('>');
            break;
        case 13:
            system("cls");
            switch(sel)
            {
                case 0: return;
                case 1: afisare_toate(ctr.get_sorted_vector([](medicament &m1, medicament &m2){return  strcmp(m1.get_denumire(),  m2.get_denumire())  <0;   }));getch();return;
                case 5: afisare_toate(ctr.get_sorted_vector([](medicament &m1, medicament &m2){return -strcmp(m1.get_denumire(),  m2.get_denumire())  <0;   }));getch();return;
                case 2: afisare_toate(ctr.get_sorted_vector([](medicament &m1, medicament &m2){float s1=m1.get_pret(); float s2=m2.get_pret(); return s1<s2;}));getch();return;
                case 6: afisare_toate(ctr.get_sorted_vector([](medicament &m1, medicament &m2){float s1=m1.get_pret(); float s2=m2.get_pret(); return s2<s1;}));getch();return;
                case 3: afisare_toate(ctr.get_sorted_vector([](medicament &m1, medicament &m2){return  strcmp(m1.get_producator(),m2.get_producator())<0;   }));getch();return;
                case 7: afisare_toate(ctr.get_sorted_vector([](medicament &m1, medicament &m2){return -strcmp(m1.get_producator(),m2.get_producator())<0;   }));getch();return;
                case 4: afisare_toate(ctr.get_sorted_vector([](medicament &m1, medicament &m2){return  strcmp(m1.get_substanta(), m2.get_substanta()) <0;   }));getch();return;
                case 8: afisare_toate(ctr.get_sorted_vector([](medicament &m1, medicament &m2){return -strcmp(m1.get_substanta(), m2.get_substanta()) <0;   }));getch();return;
            }
    }
    goto cere_dupa_ce;


}

void meniu::filtrare()
{
    system("cls");
    vector<medicament> v=ctr.getall();
    medicament q;
    float pret;
    int sel=0;
    char r;

    cout<<"> Inapoi\n  dupa pret minim\n  dupa pret maxim";
    cere_dupa_ce:
    r=getch();
    switch(r)
    {
        case 'w':
            gotoxy(0,sel);
            putch(' ');
            if(sel==0)
                sel=2;
            else sel--;
            gotoxy(0,sel);
            putch('>');
            break;
        case 's':
            gotoxy(0,sel);
            putch(' ');
            if(sel==2)
                sel=0;
            else sel++;
            gotoxy(0,sel);
            putch('>');
            break;
        case 13:
            switch(sel)
            {
                case 0: return;
                case 1: goto pmin;
                case 2: goto pmax;
            }
    }
    goto cere_dupa_ce;

    pmin:
        system("cls");
        citeste_pret(pret);
        system("cls");

        cout<<setw(30)<<"Denumire"<<setw(8)<<"Pret"<<setw(18)<<"Producator"<<setw(23)<<"Substanta activa"<<endl;
        for_each(v.begin(),v.end(),[pret](medicament q){if (q.get_pret()>=pret) afiseaza_medicament(q);});

        getch();
        return;

    pmax:
        system("cls");
        citeste_pret(pret);
        system("cls");

        cout<<setw(30)<<"Denumire"<<setw(8)<<"Pret"<<setw(18)<<"Producator"<<setw(23)<<"Substanta activa"<<endl;
        for_each(v.begin(),v.end(),[pret](medicament q){if (q.get_pret()<=pret) afiseaza_medicament(q);});

        getch();
        return;
}

int meniu::adaugare_reteta()
{
    vector<medicament> v=ctr.getall();
    int l=v.size();
    int sel=0;
    char r;
    medicament q;
    system("cls");

    cout<<"> Inapoi\n";
    afisare_toate(v);

    afisare:
    r=getch();
    switch(r)
    {
    case 'w':
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch(' ');
        if(sel==0)
            sel=l;
        else
            sel--;
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch('>');
        goto afisare;
    case 's':
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch(' ');
        if(sel==l)
            sel=0;
        else
            sel++;
        if(sel!=0)
            gotoxy(0,sel+1);
        else gotoxy(0,0);
        putch('>');
        goto afisare;
    case 13:
        if(sel==0)
            return 0;
        q=*(v.begin()+(sel-1));
        ctr.adauga_medicament_reteta(q.get_denumire(),q.get_pret(),q.get_producator(),q.get_substanta());
        return 1;
    default: goto afisare;
    }
}
