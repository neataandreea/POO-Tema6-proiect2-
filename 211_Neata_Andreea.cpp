#include <iostream>
#include<string>
#include<stdlib.h>
#include<string.h>
#include<list>
#include<stdio.h>
using namespace std;

//----------------------------------------------------------
class persoana {
protected:
int id;
string nume;
string cnp;

public:
    persoana (int , string, string);
    virtual ~persoana();
    persoana (const persoana &);
    virtual void afisare(ostream &out);
    virtual void citire (istream &in);
    friend istream & operator>>(istream &,persoana & );
    friend ostream &operator<<(ostream &, persoana &);
    persoana &operator=(const persoana &);


};

persoana :: persoana(int cod=0, string num="", string CNP="")
{   id=cod;
    nume=num;
    try
    {
        for (unsigned int i=0;i<CNP.length();i++)
            if (CNP[i]<'0'||CNP[i]>'9')
                throw 1;
    }
    catch(int i)
    {
        cout<<"CNP-ul persoanei poate contine doar cifre.\n";
        exit(EXIT_FAILURE);
    }
    cnp=CNP;


}
persoana :: ~persoana(){}


persoana :: persoana ( const persoana &p)
{
this->nume=p.nume;
this->cnp=p.cnp;
this->id=p.id;

}


void persoana :: citire(istream & in)
{
    int x;
    cout<<"id: ";
    in>>x;
    id=x;
    cout<<"nume: ";
    in.get();
    string y;
    getline(in,y);
    nume=y;
    string z;

    cout<<"cnp: ";
    in.get();
    in>>z;
     try
    {
        for (unsigned int i=0;i<z.length();i++)
            if (z[i]<'0'||z[i]>'9')
                throw 1;
    }
    catch(int i)
    {
        cout<<"CNP-ul persoanei poate contine doar cifre.\n";
        exit(EXIT_FAILURE);
    }
    cnp=z;
}
void persoana :: afisare(ostream &out)
{
    out<<"id: "<<id<<endl;
    out<<"nume: "<<nume<<endl;
    out<<"cnp: "<<cnp<<endl;
}
istream & operator >>(istream &in , persoana & p)
{
    p.citire(in);
    return in;
}
ostream &operator <<(ostream &out, persoana &p)
{
    p.afisare(out);
    return out;
}
persoana & persoana :: operator =(const persoana &p)
{if (this !=&p){
    this->nume=p.nume;
    this->cnp=p.cnp;
    this->id=p.id;
    return *this;}
}


///-------------------------------------------------------------


class abonament
{
    protected:
        string nume_abonament;
        float pret;
        int perioada;
    public:
        abonament(string,float, int);
        abonament (const abonament&);
        abonament & operator=(const abonament&);
        virtual ~abonament();
        virtual void afisare(ostream & out);
        virtual void citire(istream &in);
        friend istream & operator>>(istream &,abonament & );
        friend ostream &operator<<(ostream &, abonament &);

};

abonament::~abonament(){}

void abonament:: afisare(ostream & out)
{
    out<<"nume abonament: "<<nume_abonament<<endl;
    out<<"pret :"<<pret<<endl;
    out<<"perioada :"<<perioada<<endl;
}
void abonament:: citire(istream & in)
{cout<<"nume abonament :";
in >> nume_abonament;
cout<<"pret :";
in>>pret;
cout<<"perioada: ";
in>>perioada;

}
istream &operator>>(istream &in, abonament&ab)
{
    ab.citire(in);
    return in;
}
ostream &operator<<(ostream &out, abonament &ab)
{
    ab.afisare(out);
    return out;
}

abonament::abonament(string num="", float price=0, int per=0)
{
    nume_abonament=num;
    pret=price;
    perioada=per;
}
abonament::abonament(const abonament&ob)
{
    this->nume_abonament=ob.nume_abonament;
    this->pret=ob.pret;
    this->perioada=ob.perioada;
}
abonament & abonament::operator=(const abonament &ob)
{if (this!=&ob){
    this->nume_abonament=ob.nume_abonament;
    this->pret=ob.pret;
    this->perioada=ob.perioada;
    return *this;}
}


///----------------------------------------------------------------------------------


class abonament_premium: public abonament{
protected:int reducere;
static int n;

public:
     void citire(istream & in);
     void afisare (ostream &out);
    abonament_premium(string, float, int ,int );
    ~abonament_premium();
    friend istream & operator>>(istream &, abonament_premium &);
    friend ostream & operator <<(ostream &, abonament_premium&);
    abonament_premium(const abonament_premium&);
    abonament_premium &operator=(const abonament_premium &);
    static void nr_pers(){cout<<n;}
    friend class clienti;

};
int abonament_premium::n;
abonament_premium::abonament_premium(string num="", float price=0, int per=0, int red=0):abonament(num, price, per)
{
reducere=red;

if(reducere!=0)
    n++;
}
abonament_premium::~abonament_premium (){}
void abonament_premium::citire(istream &in)
{
    abonament::citire(in);
    cout<<"reducere: ";
    in>>reducere;
    if(reducere!=0)
        n++;
}
void abonament_premium::afisare(ostream&out)
{
    abonament::afisare(out);
    out<<"reducere: "<<reducere<<endl;
}
istream &operator>>(istream&in, abonament_premium&ob)
{
    ob.citire(in);
    return in;
}
ostream &operator <<(ostream & out, abonament_premium&ob)
{
    ob.afisare(out);
    return out;
}
abonament_premium::abonament_premium(const abonament_premium&ob):abonament(ob)
{
this->reducere=ob.reducere;
    if(ob.reducere!=0)
        n++;

}
abonament_premium & abonament_premium::operator=(const abonament_premium&ob)
{if (this!=&ob)

    {this->abonament::operator=(ob);
    this->reducere=ob.reducere;
    return *this;}
}


///-------------------------------------------------------------


class abonat : public persoana
{
    protected:string nr_telefon;
    abonament_premium *ab;

    public :abonat (int, string, string,string,abonament_premium* );
            abonat ();
            ~abonat();
            void afisare_abonat( ostream &out);
            void citire_abonat (istream &in);
            friend istream & operator >>(istream &, abonat &);
            friend ostream & operator <<(ostream &, abonat &);
            abonat (const abonat &);
            abonat &operator=(const abonat&);
            friend class clienti;

}k;


abonat & abonat :: operator =(const abonat &ob)
{   if (this !=&ob){
    this->persoana::operator=(ob);
    this->nr_telefon=ob.nr_telefon;
    this->ab=ob.ab;


    return *this;}
}
abonat:: abonat(const abonat&a):persoana(a)
{
    this->nr_telefon=a.nr_telefon;
    this->ab=a.ab;

}

void abonat :: citire_abonat(istream & in)
{
    persoana::citire(in);
    cout<<"numar telefon: ";
    string z;
    in>>z;
     try
    {
        for (unsigned int i=0;i<z.length();i++)
            if (z[i]<'0'||z[i]>'9')
                throw 1;
    }
    catch(int i)
    {
        cout<<"Numarul de telefon poate contine doar cifre.\n";
        exit(EXIT_FAILURE);
    }
    nr_telefon=z;
    in>>(*ab);

}
void abonat :: afisare_abonat(ostream & out)
{
    persoana :: afisare(out);
    out<<"numar telefon: "<<nr_telefon<<endl;
    out<<(*ab);
}
abonat::abonat():persoana()
{
    nr_telefon="";
    abonament_premium *a=new abonament_premium;
    ab=a;
}
abonat::abonat(int cod, string num, string CNP,string tlf, abonament_premium *a=new abonament_premium):persoana(cod,num, CNP)
{
    ab=a;
    nr_telefon=tlf;


}
abonat::~abonat(){}
istream &operator >>(istream & in , abonat & a)
{
    a.citire_abonat(in);
    return in;
}

ostream &operator<<(ostream &out, abonat&a)
{
    a.afisare_abonat(out);
    return out;
}


///--------------------------------------------


class clienti
{
    list <abonat*> lista_abonati;

public:
   ~clienti();
    clienti();
    clienti(abonat, int);
    clienti(const clienti&);
    clienti & operator=(const clienti &);
    void afisare_clienti(ostream &out);
    void citire_clienti(istream &in);
    friend ostream & operator <<(ostream &, clienti &);
    friend istream & operator >>(istream &, clienti&);
    float suma_incasata();

}lista;
float clienti::suma_incasata()
{
    float suma=0;
list<abonat*>::iterator i;
for (i=lista_abonati.begin();i!=lista_abonati.end();++i)
{int per=0;
float p=0;
int red=0;
        if ((**i).ab->reducere==0)
        {per=(**i).ab->perioada;
        p=(**i).ab->pret;
         suma =suma + (p*per);

        }
        else
        {
            p=(**i).ab->pret;
            red=(**i).ab->reducere;
            per=(**i).ab->perioada;
            p=p-red*0.01*p;
            suma=suma+(p*per);

        }

}
return suma;
}


clienti &clienti:: operator=(const clienti & ob)
{
    if (this!=&ob)
    {
        this->lista_abonati=ob.lista_abonati;
        return *this;
    }
}
clienti ::clienti(const clienti &ob)
{
    this->lista_abonati=ob.lista_abonati;
}
ostream &operator <<(ostream &out,clienti&c)
{
    c.afisare_clienti(out);
    return out;
}
istream & operator >>(istream &in , clienti &c)
{
    c.citire_clienti(in);
    return in;
}
void clienti::citire_clienti(istream &in)
{   lista_abonati.clear();
    abonat *a;
    int nr;
    cout<<"Introduceti numarul de clienti:";
    in>>nr;
    a=new abonat[nr];
    int i;
    for (i=0;i<nr;i++)
    {
        cout<<endl<<"clientul "<<i+1<<":"<<endl;
        in>>a[i];
        lista_abonati.push_back(&a[i]);
    }
}
void clienti::afisare_clienti(ostream &out)
{
    list<abonat*>::iterator i;

for (i=lista_abonati.begin();i!=lista_abonati.end();++i)
    (**i).afisare_abonat(out);

}
clienti::~clienti(){}


clienti::clienti()
{
lista_abonati.push_back (&k);
}
clienti::clienti(abonat a, int nr)
{
for (int i=0;i<nr;i++)
        lista_abonati.push_back(&a);
}


///---------------------------------------------------


void menu_output()
{
    printf("\n Neata Andreea 211 - Tema 6 : \n");
    printf("\n\t MENIU:");
    printf("\n===========================================\n");
    printf("\n");
    printf("1. Citire lista de abonati"); printf("\n");
    printf("2. Afisare lista de abonati"); printf("\n");
    printf("3. Suma incasata de la toti abonatii"); printf("\n");
    printf("4. Numarul de abonati premium"); printf("\n");
    printf("5. Copiaza lista"); printf("\n");
    printf("0. Iesire."); printf("\n");
}
void menu()
{
    int option;
    option=0;

    do
    {
        menu_output();

        printf("\nIntroduceti numarul actiunii: ");
        scanf("%d", &option);

        if (option==1)
        {

            lista.citire_clienti(cin);
        }
        if (option==2)
        {
            lista.afisare_clienti(cout);
        }

        if (option==3)
        {
           cout<<lista.suma_incasata()<<endl;
        }
        if (option==4)
        {
           abonament_premium::nr_pers();
        }
        if (option==0)
        {
            printf("\nEXIT!\n");
        }
        if (option<0||option>5)
        {
            printf("\nSelectie invalida\n");
        }
        if (option==5)
        {
           clienti l;
           l=lista;
           cout<<endl<<"copia listei este: "<<l;
        }

        printf("\n");
        system("pause");
        system("cls");
    }
    while(option!=0);
}

int main()
{
menu();
cout<<endl;
cout<<"exemplu upcasting: abonament->abonament_premium "<<endl;
abonament *a=new abonament_premium;
cin>>*a;
cout<<*a;
cout<<endl<<"exemplu downcasting: abonament_premium->abonament "<<endl;
abonament_premium *ab=(abonament_premium*) new abonament;
cin>>*ab;
cout<<*ab;
    return 0;
}

