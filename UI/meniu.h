#pragma once
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "../Controller/controller.h"
#include <algorithm>

using namespace std;

void afiseaza_medicament(medicament q);


#define nr_optiuni 15


class meniu
{
private:

    controller ctr;


    ///  move console cursor to given position
    void gotoxy(int x, int y);

    ///citeste un sir de caractere nevid in *char-ul dat
    void citeste_denum(char denum[]);

    ///citeste un float strict pozitiv
    void citeste_pret(float &pret);


    ///citeste un sir de caractere nevid in *char-ul dat
    void citeste_prod(char prod[]);


    ///citeste un sir de caractere nevid in *char-ul dat
    void citeste_subst(char subst[]);

    ///Functia de adaugare a unui medicament in memorie
    void adaugare();


    ///Functia de modificare in lista a unui medicament
    void modifica();

    ///Functia de stergere din lista
    int stergere();

    ///Cautare medicament in lista
    void cautare();

    ///Afiseaza toate medicamentele care corespund unor criterii
    void filtrare();

    ///Sortare dupa criteriu si afisare
    void sortare();

    ///Adaugare medicament la reteta
    int adaugare_reteta();

    ///Afiseaza toate medicamentele din lista
    void afisare_toate(vector<medicament> v)
    {
        cout<<setw(30)<<"Denumire"<<setw(8)<<"Pret"<<setw(18)<<"Producator"<<setw(23)<<"Substanta activa"<<endl;
        for_each(v.begin(),v.end(),afiseaza_medicament);
    }

    void generare_reteta()
    {
        int t;
        system("cls");
        cout<<"Nr de medicamente: ";
        while (!(scanf("%d",&t))||(t<0))
            {cout<<"\nNu e bun!\n";
            fflush(stdin);}

        ctr.generare_reteta(t);
    }

public:
    void afiseaza_meniu()
    {
        /*ctr.adauga_medicament("Paracetamol 500mg", 3.15, "SanoSan", "Paracetamol");
        ctr.adauga_medicament("Ciplox 5ml", 8.53, "Imedica", "Ciprofloxacina 0.3%");
        ctr.adauga_medicament("Antibacterial Hand Gel 29ml", 6.99, "Bath&Body Works", "Ethanol 68%");
        ctr.adauga_medicament("Faringo Hot Drink", 1.20, "Terapia Ranbaxi", "Paracetamol");
        ctr.adauga_medicament("Seringa sterila cu ac 20ml", 0.99, "Plastor Oradea", "  -  ");*/
        af_meniu:

        system("cls");
        int sel=1;
        char r;
        cout<<"> 1. Adaugare\n  2. Stergere\n  3. Modificare\n  4. Afisare"<<endl;
        cout<<"  5. Cautare\n  6. Filtrare\n  7. Sortare\n  8. Stergere reteta\n";
        cout<<"  9. Generare reteta \n  10. Adaugare la reteta\n  11. Afisare reteta\n";
        cout<<"  12. Undo\n  13. Export reteta CSV\n  14. Export reteta HTML\n  15. Iesire"<<endl;
        cout<<endl<<"  Numar medicamente in reteta: "<<ctr.get_reteta_size();

        muta_cursor:
        r=getch();
        switch(r)
        {
            case 'w':
                {
                gotoxy(0,sel-1);
                putch(' ');
                if(sel==1)
                    sel=nr_optiuni;
                else sel--;
                gotoxy(0,sel-1);
                putch('>');
                goto muta_cursor;
                }
            case 's':
                {
                gotoxy(0,sel-1);
                putch(' ');
                if(sel==nr_optiuni)
                    sel=1;
                else sel++;
                gotoxy(0,sel-1);
                putch('>');
                goto muta_cursor;
                }
            case 13 :
                switch(sel)
                    {
                        case 1: adaugare(); break;
                        case 2: stergere(); break;
                        case 3: modifica(); break;
                        case 4: system("cls"); afisare_toate(ctr.getall());getch(); break;
                        case 5: cautare(); break;
                        case 6: filtrare(); break;
                        case 7: sortare();break;
                        case 8: ctr.generare_reteta(0);break;
                        case 9:  generare_reteta(); break;
                        case 10: adaugare_reteta(); break;
                        case 11: system("cls"); afisare_toate(ctr.get_reteta());getch(); break;
                        case 12: ctr.do_UNDO(); break;
                        case 13: ctr.export_CSV();break;
                        case 14: ctr.export_HTML();break;
                        case 15: return;
                    }
                goto af_meniu;
            }
            goto muta_cursor;
    }
};
