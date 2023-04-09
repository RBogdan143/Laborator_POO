#include <iostream>

using namespace std;

// In aceasta clasa aloc dinamic un array de int-uri sau float-uri in functie de array-ul primit ca input in metoda 'alocare_num'.
class ListaDeNumere
{
    int num, index_num;
public:
    ListaDeNumere(int nr_elem)
    {
        num = nr_elem;
    }
    void alocare_num(float *list)
    {
        for(index_num=0;index_num<num;index_num++)
            cin>>list[index_num];
    }
    void alocare_num(int *list)
    {
        for(index_num=0;index_num<num;index_num++)
            {cin>>list[index_num];
             if(list[index_num]<0)
                list[index_num] *= -1;}
    }
    friend class ListaDeLitere;
    ~ListaDeNumere(){}
};

// In aceasta clasa aloc dinamic un array de char-uri prin metoda 'alocare_lit'.
class ListaDeLitere
{
    int lit, index_lit, index_cuv=0;
public:
    ListaDeLitere(int nr_elem)
    {
        lit = nr_elem*112;
    }
    ListaDeLitere(ListaDeNumere& t)
    {
        lit = 112*t.num;
    }
    void alocare_lit(char *list)
    {
        index_lit=0;
        while(cin>>noskipws>>list[index_lit])
        {
            if(list[index_lit]=='.')
                break;
            else index_lit++;
        }
        for(index_cuv=0;index_cuv<index_lit;index_cuv++)
            list[index_cuv] = list[index_cuv+1];
        cin>>skipws;
        list[index_lit]='\0';
        list[index_lit+1]='\n';
    }
    ~ListaDeLitere(){}
};

// In aceasta clasa definesc obiectul 'Magazin' prin a aloca dinamic un array de char-uri reprezentând 'numele magazinului' prin constructor.
// Apoi, aloc dinamic un alt array de char-uri reprezentând 'stock-ul magazinului' prin clasa 'ListaDeLitere'.
// Si, in cele din urma, aloc dinamic un array de float-uri reprezentând 'pretul produselor din stock' prin clasa 'ListaDeNumere'.
class Magazin
{
    char *nume_magazin, *lista_jocuri, *push_nume;
    int balanta_de_plata = 0, index_push, index_pop;
    float *lista_preturi, profit=0.0, tva=0.0;
public:
    Magazin(int a)
    {
        nume_magazin = new char[3];
        nume_magazin[0] = 'a';
        nume_magazin[1] = '\0';
        nume_magazin[2] = '\n';
        lista_jocuri = new char[3];
        lista_jocuri[0] = 'b';
        lista_jocuri[1] = '\0';
        lista_jocuri[2] = '\n';
        lista_preturi = new float[3];
        lista_preturi[0] = 1.1;
        lista_preturi[1] = 2.1;
        lista_preturi[2] = 3.1;
    }
    Magazin()
    {
        cout<<"Adaugati un nume magazinului: ";
        push_nume = new char[1];
        nume_magazin = new char[1];
        index_push = 0;
        while(cin>>noskipws>>push_nume[index_push])
        {
            if(push_nume[index_push]!='.')
            {
                delete[] nume_magazin;
                nume_magazin = new char[index_push+1];
                for(index_pop=0;index_pop<=index_push;index_pop++)
                    nume_magazin[index_pop] = push_nume[index_pop];
                delete[] push_nume;
                index_push ++;
                push_nume = new char[index_push+1];
                for(index_pop=0;index_pop<=index_push;index_pop++)
                    push_nume[index_pop] = nume_magazin[index_pop];
                nume_magazin[index_push] = '\0';
                nume_magazin[index_push+1] = '\n';
            }
            else break;
        }
        cin>>skipws;
        delete[] push_nume;
    }
    void jocuri()
    {
        cout<<"Inserati numarul de jocuri pe care vreti sa-l adaugati: ";
        cin>>index_push;
        lista_jocuri = new char[index_push*112];
        ListaDeNumere t(index_push);
        ListaDeLitere r(t);
        cout<<"Adaugati jocurile disponibile in colectia "<<nume_magazin<<": \n";
        r.alocare_lit(lista_jocuri);
    }
    void preturi()
    {
        lista_preturi = new float[index_push];
        ListaDeNumere t(index_push);
        cout<<"Adaugati preturile jocurilor "<<nume_magazin<<": \n";
        t.alocare_num(lista_preturi);
    }
    void afisare_joc(char *lista, int joc, int index_cuv=0, int index_lit=0)
    {
        while(lista[index_lit]!='\0')
            {if(lista[index_lit]!='.')
                if(lista[index_lit]!=',')
                    {if(index_cuv == joc)
                        cout<<lista[index_lit];}
                else{ if(index_cuv==joc)
                            break;
                      index_cuv++;
                      index_lit++;
                    }
            else
                break;
            index_lit ++;}
    }
    char *stock(int& lungime)
    {
        lungime = 0;
        while(lista_jocuri[lungime]!='\n')
        {
            if(lista_jocuri[lungime]=='\n')
                    break;
            else lungime++;
        }
        lungime+=2;
        return lista_jocuri;
    }
    float *pret_fara_tva()
    {
        return lista_preturi;
    }
    void tranzactie_acceptata(float profit_nou, float tva_nou)
    {
        profit += profit_nou;
        tva += tva_nou;
    }
    friend void operator>>(istream& is, Magazin& obj)
    {
        obj.jocuri();
        obj.preturi();
    }
    friend void operator<<(ostream& os, Magazin& obj)
    {
        cout<<endl;
        cout<<"Magazinul se numeste: "<<obj.nume_magazin<<", si are "<<obj.index_push<<" jocuri in stock:\n";
        for(obj.index_pop=0;obj.index_pop<obj.index_push;obj.index_pop++)
        {
            obj.afisare_joc(obj.lista_jocuri, obj.index_pop);
            cout<<" (Si costa: "<<obj.lista_preturi[obj.index_pop]<<" euro 'fara tva')\n";
        }
        cout<<"Avand un profit de: "<<obj.profit<<" euro!\n";
        cout<<endl;
    }
    ~Magazin()
    {
        delete[] nume_magazin;
        delete[] lista_jocuri;
        delete[] lista_preturi;
    }
};

// In aceasta clasa preluam stock-ul din clasa 'Magazin' si introducem balanta clientului prin constructor.
// Apoi, alocam dinamic un array de char-uri reprezentând 'produsele pe care vrem sa le adaugam in cos' prin clasa 'ListaDeLitere'.
// Si, verificam daca toate produsele din cos se afla in stock-ul magazinului prin metoda 'verificare_stock'.
// Daca nu este un produs in stock, atunci se afiseaza pe ecran produsul care nu este in stock prin metoda 'afisare_joc' din clasa 'Magazin' si,
// Apoi se reseteaza metoda 'cumpara_jocuri' pentru a ne lasa sa incercam din nou.
// Daca totul este ok, atunci se initializeaza un array de int-uri reprezentand 'cantitate de produse identice pe care o vrem',
// Cu toate elementele egale cu 1 si, in functie de input-ul primit, ori o sa se aloce dinamic din nou array-ul cu input-urile noastre,
// Ori o sa ramana asa cum a fost initializat.
class Client
{
    char *cos_de_cumparaturi, *stock, intrebare;
    int *cantitatea, numar_produse, index_joc;
    float balanta_cont = 0.0;
public:
    Client(Magazin& p)
    {
        p.stock(index_joc);
        stock = new char[index_joc];
        stock = p.stock(index_joc);
        cout<<"Dorinti sa alimentati contul?\n";
        cout<<"Daca da, atunci tastati litera 'y', altfel 'n': ";
        cin>>intrebare;
        if(intrebare=='y')
        {
            cout<<"Adaugati suma dorita pentru a alimenta contul (in euro): ";
            cin>>balanta_cont;
        }
    }
    void cumpara_jocuri()
    {
        cout<<"Inserati numarul de jocuri pe care vreti sa-l cumparati: ";
        cin>>numar_produse;
        cos_de_cumparaturi = new char[numar_produse*112];
        ListaDeNumere t(numar_produse);
        ListaDeLitere r(t);
        cout<<"Adaugati jocurile in cos: \n";
        r.alocare_lit(cos_de_cumparaturi);
        index_joc = 0;
        if(verificare_stock(index_joc)==-1)
        {
            Magazin p(1);
            p.afisare_joc(cos_de_cumparaturi, index_joc);
            cout<<" nu este in stoc!\n";
            cout<<"Incercati din nou cu alt produs!\n";
            delete[] cos_de_cumparaturi;
            cumpara_jocuri();
        }
        else
        {
            cantitatea = new int[numar_produse];
            for(index_joc=0;index_joc<numar_produse;index_joc++)
                    cantitatea[index_joc] = 1;
            cout<<"Cantitateam jocurilor este automat setata ca 1!\n";
            cout<<"Daca doriti sa o modificati, atunci tastati litera 'y', altfel 'n': ";
            cin>>intrebare;
            if(intrebare=='y')
            {
                delete[] cantitatea;
                cantitate();
            }
        }
    }
    void cantitate()
    {
        ListaDeNumere t(numar_produse);
        cantitatea = new int[numar_produse];
        cout<<"Adaugati cate jocuri de acelasi fel vreti (in ordinea lor din cos):\n";
        t.alocare_num(cantitatea);
    }
    int verificare_stock(int& out_of_stuck, int copy_index = 0, int index_stock = 0, int index_cos = 0, int verificator=0)
    {
        while(cos_de_cumparaturi[index_cos]!='\0')
        {
            copy_index = index_cos;
            while(stock[index_stock]!='\0')
            {
                if(stock[index_stock]!='.')
                    if(stock[index_stock]!=',')
                        if(stock[index_stock]!=cos_de_cumparaturi[index_cos])
                                {verificator = 1;
                                 index_cos++;
                                 index_stock++;}
                        else
                        {
                            index_cos++;
                            index_stock++;
                        }
                    else
                    {
                        if(verificator == 0)
                                break;
                        index_cos = copy_index;
                        index_stock+=2;
                        verificator = 0;
                    }
                else {if(verificator == 0)
                            break;
                      return -1;}
            }
            while(cos_de_cumparaturi[index_cos]!=' ')
                    if(cos_de_cumparaturi[index_cos]!='.')
                        index_cos++;
                    else break;
            index_cos++;
            out_of_stuck++;
            index_stock=0;
        }
        return 0;
    }
    char *cos(int& lungime)
    {
        lungime = 0;
        while(cos_de_cumparaturi[lungime]!='\n')
        {
            if(cos_de_cumparaturi[lungime]=='\n')
                    break;
            else lungime++;
        }
        lungime+=2;
        return cos_de_cumparaturi;
    }
    int *nr_produse(int& index)
    {
        index = numar_produse;
        return cantitatea;
    }
    float plata()
    {
        return balanta_cont;
    }
    void plata_acceptata(float balanta_noua)
    {
        balanta_cont = balanta_noua;
    }
    ~Client()
    {
        delete[] cos_de_cumparaturi;
        delete[] cantitatea;
        delete[] stock;
    }
};

// In aceasta clasa preluam stock-ul si preturile din clasa 'Magazin', iar din clasa 'Client', cosul si cantitatea produselor prin constructor.
// Apoi creiem un array de index-i prin metoda 'get_ordine' pentru a putea calcula corect totalul de plata,
// In continuare parcurgem array-urile de pret si cantitate apeland metoda 'tva' pentru a adauga tva-ul corect al produselor ca apoi sa inmultim cu cantitatea dorita.
// Dupa ce avem totalul gata calculat, in functie de input-ul primit se apeleaza metoda 'cod_reducere' sau nu.
// In metoda 'cod_reducere' se verifica daca inputul primit se potriveste cu codul initializat si, daca da, atunci se scade 25% din totalul de plata.
// Apoi se apeleaza metoda 'finalizare_plata', unde se face tranzactia de bunuri daca clientul are destui bani in cont.
// In final se actualizeaza balanta clientului si a magazinului.
class Checkout
{
    char *jocuri_alese, *get_index_stock, intrebare;
    int *numar_produse, *ordine, index_get, max_array;
    float *pret_produse, total_plata = 0.0, tva_plata = 0.0;
public:
    Checkout(Magazin& p, Client& o)
    {
        p.stock(index_get);
        get_index_stock = new char[index_get];
        get_index_stock = p.stock(index_get);
        o.cos(index_get);
        jocuri_alese = new char[index_get];
        jocuri_alese = o.cos(index_get);
        pret_produse = p.pret_fara_tva();
        numar_produse = o.nr_produse(index_get);
    }
    void plata(Magazin& p, Client& o)
    {
        ordine = get_ordine(index_get);
        max_array = index_get;
        for(index_get=0;index_get<max_array;index_get++)
            total_plata += tva(pret_produse[ordine[index_get]], tva_plata) * numar_produse[index_get];
        cout<<"Daca vreti sa adaugati un cod de reducere, atunci tastati litera 'y', altfel 'n': ";
        cin>>intrebare;
        if(intrebare=='y')
            {cod_reducere(total_plata);
             int rounded_total_plata = static_cast<int>(total_plata * 100);
             total_plata = static_cast<float>(rounded_total_plata) / 100;
             cout<<"Aveti total de plata: "<<total_plata<<" euro"<<endl;}
        else
        {
            int rounded_total_plata = static_cast<int>(total_plata * 100);
            total_plata = static_cast<float>(rounded_total_plata) / 100;
            cout<<"Aveti total de plata: "<<total_plata<<" euro"<<endl;
        }
        finalizare_plata(p, o);
    }
    float tva(float pret, float& total_tva)
    {
        total_tva += pret * (19.0/100.0);
        pret += pret * (19.0/100.0);
        return pret;
    }
    void cod_reducere(float& pret, const char cod[17] = "5283Q-Q8L9K-E4R6H", int index_verificare=0, int verificator=0)
    {
        char input[17];
        cout<<"Introduceti codul: ";
        while(cin>>input[index_verificare])
                if(index_verificare==16)
                    break;
                else index_verificare ++;
        for(index_verificare=0;index_verificare<17;index_verificare++)
                if(input[index_verificare] != cod[index_verificare])
                        {verificator = 1;
                         break;}
        if(verificator == 0)
            pret -= pret * (25.0/100.0);
        else cout<<"Cod invalid!\n";
    }
    void finalizare_plata(Magazin& p, Client& o)
    {
        float balanta_client = o.plata();
        if(balanta_client>=total_plata)
        {
            balanta_client -= total_plata;
            int rounded_total_client = static_cast<int>(balanta_client * 100);
            balanta_client = static_cast<float>(rounded_total_client) / 100;
            balanta_client += 0.01;
            o.plata_acceptata(balanta_client);
            int rounded_total_tva = static_cast<int>(tva_plata * 100);
            tva_plata = static_cast<float>(rounded_total_tva) / 100;
            tva_plata += 0.01;
            total_plata -= tva_plata;
            p.tranzactie_acceptata(total_plata, tva_plata);
        }
        else cout<<endl<<"Tranzactie esuata: fonduri insuficiente!\n";
    }
    int *get_ordine(int max, int index_array=0, int index_ordine = 0, int copy_index = 0, int index_stock = 0, int index_cos = 0, int verificator=0)
    {   int *return_array;
        return_array = new int(max+1);
        while(jocuri_alese[index_cos]!='\0')
        {
            copy_index = index_cos;
            while(get_index_stock[index_stock]!='\0')
            {
                if(get_index_stock[index_stock]!='.')
                    if(get_index_stock[index_stock]!=',')
                        if(get_index_stock[index_stock]!=jocuri_alese[index_cos])
                                {verificator = 1;
                                 index_cos++;
                                 index_stock++;}
                        else
                        {
                            index_cos++;
                            index_stock++;
                        }
                    else
                    {
                        if(verificator == 0)
                                break;
                        index_ordine ++;
                        index_cos = copy_index;
                        index_stock+=2;
                        verificator = 0;
                    }
                else if(verificator == 0)
                            break;
            }
            return_array[index_array] = index_ordine;
            index_array ++;
            index_ordine = 0;
            while(jocuri_alese[index_cos]!=' ')
                    if(jocuri_alese[index_cos]!='.')
                        index_cos++;
                    else break;
            index_cos++;
            index_stock=0;
        }
        return return_array;
    }
    ~Checkout()
    {
        delete[] jocuri_alese;
        delete[] get_index_stock;
        delete[] numar_produse;
        delete[] pret_produse;
        delete[] ordine;
    }
};

int main()
{
    Magazin v;
    cin>>v;
    cout<<v;
    Client c(v);
    c.cumpara_jocuri();
    Checkout x(v, c);
    x.plata(v, c);
    cout<<v;
    return 0;
}
