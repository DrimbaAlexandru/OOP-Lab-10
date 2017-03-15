#include "widget.h"
#include <QApplication>
#include <iostream>
#include "UI/meniu.h"
#include "Teste/tests.h"
#include <assert.h>
#include <algorithm>
#include "gui_w.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    file_repo_medicament repo;
    controller ctr(repo);
    GUI_W GUI(ctr);

    try
    {
        teste();
        //meniu main_meniu;
        //main_meniu.afiseaza_meniu();
        GUI.resize(640,320);
        GUI.show();
    }
    catch (int e)
    {
        cout<<"Eroare la testare! (cod "<<e<<")";
        getch();
    }

    return a.exec();
}
