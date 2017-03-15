#include <string.h>
#pragma once


class medicament
{
private:
    char* denumire;
    char* producator;
    char* substanta;
    float pret;

public:
    medicament()
    {
        this->denumire=nullptr;
        this->pret=0;
        this->producator=nullptr;
        this->substanta=nullptr;
    }
    medicament(const char denum[],const float pr,const char prod[],const char subst[])
    {

        this->denumire=new char[strlen(denum)+1];
        strcpy(this->denumire,denum);
        this->producator=new char[strlen(prod)+1];
        strcpy(this->producator,prod);
        this->substanta=new char[strlen(subst)+1];
        strcpy(this->substanta,subst);
        this->pret=pr;

    }

    ~medicament()
    {
        delete[] this->denumire;
        delete[] this->producator;
        delete[] this->substanta;
    }

    medicament(const medicament &other)
    {
        this->denumire = new char[strlen(other.denumire)+1];
        strcpy(this->denumire,other.denumire);
        this->pret=other.pret;
        this->producator = new char[strlen(other.producator)+1];
        strcpy(this->producator,other.producator);
        this->substanta = new char[strlen(other.substanta)+1];
        strcpy(this->substanta,other.substanta);


    }

    medicament operator=(const medicament &other)
    {

        delete[] this->denumire;
        delete[] this->producator;
        delete[] this->substanta;
        this->denumire = new char[strlen(other.denumire)+1];
        strcpy(this->denumire,other.denumire);
        this->pret=other.pret;
        this->producator = new char[strlen(other.producator)+1];
        strcpy(this->producator,other.producator);
        this->substanta = new char[strlen(other.substanta)+1];
        strcpy(this->substanta,other.substanta);

        return *this;

    }

    bool operator==(const medicament &other)
    {
        if(strcmp(this->denumire,other.denumire)!=0)
            return false;
        if(this->pret!=other.pret)
            return false;
        if(strcmp(this->producator,other.producator)!=0)
            return false;
        if(strcmp(this->substanta,other.substanta)!=0)
            return false;
        return true;
    }

    bool operator!=(const medicament &other)
    {
        return !(*this==other);
    }

    float get_pret()
    {
        return this->pret;
    }

    char* get_denumire()
    {

        return this->denumire;
    }

    char* get_producator()
    {
        return this->producator;
    }

    char* get_substanta()
    {
        return this->substanta;
    }
};
