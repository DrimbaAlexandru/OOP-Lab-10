#define INIT_CAP 8
#pragma once

using namespace std;

template <typename elem>
class IteratorVector;

template <typename elem>
class VectorDinamic
{
friend class IteratorVector<elem>;
private:
    elem* sir;
    int cp;
    int len;

    void asigura_capacitate()
    {
        if(len==cp)
        {
            cp=cp*2;
            elem* new_sir=new elem[cp];
            for(int i=0;i<len;i++)
                new_sir[i]=sir[i];

            delete[] sir;
            sir=new_sir;
        }
    }

public:
    VectorDinamic()
    {
        this->cp=INIT_CAP;
        this->len=0;
        this->sir=new elem[INIT_CAP];
    }

    ~VectorDinamic()
    {
        delete[] sir;
    }

    VectorDinamic operator+(const elem &el)
    {
        asigura_capacitate();
        sir[len]=el;
        len++;
        return *this;
    }
    VectorDinamic operator=(const VectorDinamic &v)
    {
        delete[] this->sir;
        len=v.len;
        cp=v.cp;
        sir=new elem[cp];
        int i;
        for(i=0;i<len;i++)
        {
            sir[i]=v.sir[i];
        }
        return *this;

    }

    ///Sorteaza dupa functia comp. Functia comp trebuie sa returneaze 1 daca elem1 si elem2 NU sunt in ordinea corespunzatoare.
    void sortare(int(*comp)(elem&, elem&))
    {
        int i,j;
        elem aux;
        for(i=0;i<len-1;i++)
            for(j=i+1;j<len;j++)
                if(((*comp)(sir[i],sir[j]))>0)
                {
                    aux=sir[j];
                    sir[j]=sir[i];
                    sir[i]=aux;
                }
    }


    VectorDinamic(const VectorDinamic &v)
    {
        cp=v.cp;
        len=v.len;
        sir=new elem[cp];
        int i;
        for(i=0;i<len;i++)
            sir[i]=v.sir[i];
    }

    VectorDinamic operator-(const elem &el)
    {
        int i;
        int found=0;
        for(i=0;i<len;i++)
        {
            if(found)
                sir[i]=sir[i+1];
            if(!found)
                if(sir[i]==el)
                {
                    found=1;
                    len--;
                    i--;
                }
        }
        return *this;
    }
    int getLength()
    {
        return this->len;
    }

    elem& get_on_poz(int i)
    {
        return sir[i];
    }

	IteratorVector<elem> begin()
	{
	    return IteratorVector<elem>(*this,0);
	}
	IteratorVector<elem> end()
    {
	    return IteratorVector<elem>(*this,len);
	}
};


template <typename elem>
class IteratorVector
{
private:
	const VectorDinamic<elem>& v;
	int poz = 0;

public:
	IteratorVector(const VectorDinamic<elem>& v) :v{v} {}
	IteratorVector(const VectorDinamic<elem>& v, int poz) :v{ v }, poz{poz} {}

	bool valid()const {
		return poz < v.lg;
	}

	elem& element() const {
		return v.sir[poz];
	}

	void next() {
		poz++;
	}

	elem& operator*() {
		return element();
	}

	IteratorVector& operator++() {
		next();
		return *this;
	}

	bool operator==(const IteratorVector& ot) {
		return poz == ot.poz;
	}

	bool operator!=(const IteratorVector& ot) {
		return !(*this == ot);
	}
};

