#pragma once
#include "../Repository/Repository.h"
#include "../Domain/medicament.h"

class ActiuneUndo
{
protected:
    medicament med;
    repo_medicament &repo;

public:
    ActiuneUndo(medicament m, repo_medicament &rep) : med{m}, repo{rep} {}
    virtual void doUndo()=0;
    virtual ~ActiuneUndo(){};
};

class UndoADD: public ActiuneUndo
{

public:

    void doUndo() override
    {
        repo.elimina_medicament(med.get_denumire(),med.get_pret(),med.get_producator(),med.get_substanta());
    }

    UndoADD(medicament m,repo_medicament &rep): ActiuneUndo{m,rep} {}


};

class UndoDELETE: public ActiuneUndo
{

public:

    void doUndo() override
    {
        repo.adauga_medicament(med.get_denumire(),med.get_pret(),med.get_producator(),med.get_substanta());
    }

    UndoDELETE(medicament m,repo_medicament &rep): ActiuneUndo{m,rep} {}
};

class UndoMODIFICA: public ActiuneUndo
{
private:
    medicament med2;
public:

    void doUndo() override
    {
        repo.elimina_medicament(med2.get_denumire(),med2.get_pret(),med2.get_producator(),med2.get_substanta());
        repo.adauga_medicament(med.get_denumire(),med.get_pret(),med.get_producator(),med.get_substanta());
    }

    UndoMODIFICA(medicament vechi,medicament nou,repo_medicament &rep): ActiuneUndo{vechi,rep}, med2{nou} {}
};
