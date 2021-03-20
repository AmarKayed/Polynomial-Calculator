/*

Pentru documentatia codului de mai jos am comentat fiecare sectiune cu un punct specific care se regaseste in documentul "README.txt".
Ca sa vedeti detalii despre o anumita parte a codului de mai jos, folositi punctul asociat pentru a citi detaliile in documentia din "README.txt"
Programul a fost scris si rulat in CodeBlocks.

Detalii autor:

Nume: Kayed Amar
Grupa: 143
Facultatea de Matematica si Informatica, anul universitar 2020 - 2021.

*/


#include<iostream>      // Punctul 1
#include<cstring>

using namespace std;

class Polinom{          // Punctul 2

    // Clasele au implicit specificatorul private, dar am ales sa-l scriu pentru usurinta citirii codului.

    private:

    /// Atributele clasei           => Punctul 2.1

        int grad;
        float* coeficienti;
        Polinom* urmator;

    /// Metodele clasei

        /// Settere:                                                                                => Punctul 2.2

        void set_grad(int grad);                                                                    // Punctul 2.2.1

        void set_coeficienti(int grad, float* coeficienti);                                         // Punctul 2.2.2

        inline void set_urmator(Polinom* nodul_urmator){this->urmator = nodul_urmator;}             // Punctul 2.2.3

        void set_polinom(int grad, float* coeficienti, Polinom* urmator);                           // Punctul 2.2.4


    public:

        /// Constructori:                                                         => Punctul 2.3

        Polinom();                                                                // Punctul 2.3.1

        Polinom(int grad);                                                        // Punctul 2.3.2

        Polinom(int grad, float* coeficienti);                                    // Punctul 2.3.3

        Polinom(int grad, float* coeficienti, Polinom* nodul_urmator);            // Punctul 2.3.4

        Polinom(Polinom p, Polinom* nodul_urmator);                               // Punctul 2.3.5

        /// Destructor:         => Punctul 2.4

        ~Polinom();             // Punctul 2.4.1

        /// Gettere:            => Punctul 2.5

        inline int get_grad(){return this->grad;}                                   // Punctul 2.5.1

        inline float* get_coeficienti(){return this->coeficienti;}                  // Punctul 2.5.2

        inline float get_coeficient_k(int k){return (this->coeficienti)[k];}        // Punctul 2.5.3

        inline Polinom* get_urmator(){return this->urmator;}                        // Punctul 2.5.4

        /// Metodele cerute in cerinta:(DECLARAREA ACESTORA)    => Punctul 3

        float valoare(float punct);             // Punctul 3.1

        Polinom operator +(Polinom &p);         // Punctul 3.2

        Polinom operator -(Polinom &p);         // Punctul 3.3

        Polinom operator *(Polinom &p);         // Punctul 3.4

        /// CERINTE BONUS                   => Punctul 4

        bool operator ==(Polinom &p);       // Punctul 4.1

        void operator +=(Polinom &p);       // Punctul 4.2

        /// Metode utile pentru testarea codului:(Nu fac parte din cerinta. DECLARAREA ACESTORA)    => Punctul 5

        friend istream& operator >>(istream& in, Polinom& nod);     // Punctul 5.1

        friend ostream& operator <<(ostream& out, Polinom& nod);    // Punctul 5.2

        Polinom& operator =(Polinom &p);        // Punctul 5.3

        void validare_atribute();               // Punctul 5.4
};

/// Settere:                => Punctul 2.2

void Polinom::set_grad(int grad){                   // Punctul 2.2.1
    this->grad = grad;
}

void Polinom::set_coeficienti(int grad, float* coeficienti){            // Punctul 2.2.2
    this->grad = grad;
    if(this->coeficienti != NULL)
        delete [] this->coeficienti;
    this->coeficienti = new float[grad + 1];
    for(int i = 0; i < grad + 1 ;i++)
        (this->coeficienti)[i] = coeficienti[i];
}

void Polinom::set_polinom(int grad, float* coeficienti, Polinom* urmator){          // Punctul 2.2.4
    this->grad = grad;
    if(this->coeficienti != NULL)
        delete [] this->coeficienti;
    this->coeficienti = new float[grad + 1];
    for(int i = 0; i < grad + 1 ;i++)
        (this->coeficienti)[i] = coeficienti[i];
    this->urmator = urmator;
}

/// DEFINIREA CONSTRUCTORILOR DECLARATI IN CLASA        => Punctul 2.3

Polinom::Polinom(){                                     // Punctul 2.3.1
    this->coeficienti = NULL;
    this->urmator = NULL;
}

Polinom::Polinom(int grad){                             // Punctul 2.3.2
    this->grad = grad;
    this->urmator = NULL;
}

Polinom::Polinom(int grad, float* coeficienti){         // Punctul 2.3.3
    this->grad = grad;
    this->coeficienti = new float[grad+1];
    for(int i=0; i < grad+1; i++)
        (this->coeficienti)[i] = coeficienti[i];
    this->urmator = NULL;
}

Polinom::Polinom(int grad, float* coeficienti, Polinom* nodul_urmator){     // Punctul 2.3.4
    this->grad = grad;
    this->coeficienti = new float[grad+1];
    for(int i = 0;i < grad+1; i++)
        (this->coeficienti)[i] = coeficienti[i];
    this->urmator = nodul_urmator;
}

Polinom::Polinom(Polinom p, Polinom* nodul_urmator){    // Punctul 2.3.5
    this->grad = p.get_grad();
    this->coeficienti = new float[this->get_grad()+1];
    for(int i = 0;i < this->get_grad()+1; i++)
        (this->coeficienti)[i] = p.get_coeficient_k(i);
    this->urmator = nodul_urmator;
}

/// DESTRUCTOR:             => Punctul 2.4

Polinom::~Polinom(){        // Punctul 2.4.1

    //cout<<"\nS-a sters Polinomul \n"<<*this<<"\n\n";

    if(this->coeficienti != NULL){
        delete [] this->coeficienti;
        this->coeficienti = NULL;       // Ne asiguram ca nu se mai sterge odata din greseala
    }
    /*
    if(this->urmator != NULL){
        delete this->urmator;
        this->urmator = NULL;
    }
    */
}

/// Metodele cerute in cerinta:(DEFINIREA ACESTORA)             => Punctul 3

float Polinom:: valoare(float punct){                           // Punctul 3.1
    float suma = 0;
    float exponent = 1;
    for(int i = 0; i < this->get_grad() + 1; i++)
    {
        for(int j = 0; j < i ; j++)
            exponent = exponent * punct;
        suma = suma + this->get_coeficient_k(i)*exponent;
        exponent = 1;
    }
    return suma;
}

Polinom Polinom::operator +(Polinom &p){                        // Punctul 3.2

    // Se returneaza prin valoare si nu prin referinta, intrucat obiectul referentiat ar fi fost pe stiva si s-ar fi sters dupa oprirea subprogramului

    int grad_maxim = max(this->get_grad(), p.get_grad());

    float* suma_coeficienti = new float[grad_maxim + 1];

    int i=0;

    while(i < this->get_grad() + 1  &&  i < p.get_grad() + 1)       // <=> i < min(this->get_grad() + 1, p.get_grad() + 1)
    {
        suma_coeficienti[i] = this->get_coeficient_k(i) + p.get_coeficient_k(i);
        i++;
    }

    while(i < this->get_grad() + 1){
        suma_coeficienti[i] = this->get_coeficient_k(i);
        i++;
    }

    while(i < p.get_grad() + 1){
        suma_coeficienti[i] = p.get_coeficient_k(i);
        i++;
    }
    Polinom Obiect_Nou(grad_maxim, suma_coeficienti);
    Obiect_Nou.validare_atribute();
    delete [] suma_coeficienti;
    return Obiect_Nou;

}

Polinom Polinom:: operator -(Polinom &p){                       // Punctul 3.3

    int grad_maxim = max(this->get_grad(), p.get_grad());

    float* diferenta_coeficienti = new float[grad_maxim + 1];

    int i=0;

    while(i < this->get_grad() + 1  &&  i < p.get_grad() + 1)
    {
        diferenta_coeficienti[i] = this->get_coeficient_k(i) - p.get_coeficient_k(i);
        i++;
    }

    while(i < this->get_grad() + 1){
        diferenta_coeficienti[i] = this->get_coeficient_k(i);
        i++;
    }

    while(i < p.get_grad() + 1){
        diferenta_coeficienti[i] = (-1)*p.get_coeficient_k(i);
        i++;
    }
    Polinom Obiect_Nou(grad_maxim, diferenta_coeficienti);
    Obiect_Nou.validare_atribute();
    delete [] diferenta_coeficienti;
    return Obiect_Nou;

}

Polinom Polinom:: operator *(Polinom &p){                       // Punctul 3.4

    int grad_produs = this->get_grad() + p.get_grad();

    float* coeficienti_produs = new float[grad_produs + 1];

    int i,j;

    for(i = 0; i < grad_produs + 1; i++)     // initializam vectorul de coeficienti cu 0;
        coeficienti_produs[i] = 0;

    for(i=0;i < this->get_grad() + 1; i++)
        for(j=0; j < p.get_grad() + 1; j++)
            coeficienti_produs[i+j] = coeficienti_produs[i+j] + this->get_coeficient_k(i) * p.get_coeficient_k(j);

    Polinom Obiect_Nou(grad_produs, coeficienti_produs);

    Obiect_Nou.validare_atribute();

    delete [] coeficienti_produs;

    return Obiect_Nou;
}


/// Metoda BONUS                                                => Punctul 4

bool Polinom::operator==(Polinom &p){                           // Punctul 4.1
    if(this->get_grad() != p.get_grad())
        return false;
    for(int i = 0; i < this->get_grad() + 1; i++)
        if(this->get_coeficient_k(i) != p.get_coeficient_k(i))
            return false;
    return true;
}

void Polinom::operator +=(Polinom& p){                          // Punctul 4.2
    Polinom suma(*this + p,this->get_urmator());
    *this = suma;
}

/// Metode utile pentru testarea codului:(Nu fac parte din cerinta. DEFINIREA ACESTORA)     => Punctul 5

istream& operator >>(istream& in, Polinom& nod){            // Punctul 5.1
    cout<<"Scrieti gradul polinomului: ";
    float grad;
    in>>grad;

    while(grad<0 || int(grad) - grad != 0){
        if(grad<0)
            cout<<"Din definitia de pe Wikipedia, polinomii nu pot avea grad negativ, tastati un grad pozitiv va rog: ";
        else cout<<"Gradul polinomului trebuie sa fie un numar natural, mai tastati odata gradul: ";
        in>>grad;
    }

    cout<<"Scrieti coeficientii polinomului incepand cu termenul liber si pana la termenul de gradul "<<grad<<": ";

    float* coeficienti = new float[int(grad)+1];

    for(int i = 0; i<grad+1; i++)
        in>>coeficienti[i];

    cin.get();          // Eliberam Buffer-ul

    Polinom Obiect_Intermediar(int(grad),coeficienti,nod.get_urmator());
    Obiect_Intermediar.validare_atribute();
    nod = Obiect_Intermediar;

    delete [] coeficienti;

    return in;
}

ostream& operator <<(ostream& out, Polinom& nod){           // Punctul 5.2

    if(nod.get_grad() <= 0 && nod.get_coeficient_k(0) == 0)     // tratam cazul polinomului nul
        out<<nod.get_coeficient_k(0);
    else {
        int i;
        for(i=nod.get_grad(); i>=0; i--)
            if(i == nod.get_grad() && i != 0 && i != 1){
                if(nod.get_coeficient_k(i) == 1)
                    out<<"X^"<<i<<" ";
                else if(nod.get_coeficient_k(i) == -1)
                    out<<"- X^"<<i<<" ";
                else if(nod.get_coeficient_k(i)>0)
                    out<<nod.get_coeficient_k(i)<<"X^"<<i<<" ";
                else if(nod.get_coeficient_k(i)<0)
                    out<<"- "<<(-1)*nod.get_coeficient_k(i)<<"X^"<<i<<" ";
                // cazul in care nod.get_coeficient_k(i) == 0 este deja tratat de la primul while
            }
            else if(i == 1){
                if(nod.get_coeficient_k(i)<0){
                    if(nod.get_coeficient_k(i) == -1)
                        out<<"- X ";
                    else out<<"- "<<(-1)*nod.get_coeficient_k(i)<<"X ";
                }
                else if(nod.get_coeficient_k(i)>0){// am tratat toate cele 4 cazuri
                    if(nod.get_coeficient_k(i) == 1 && i!=nod.get_grad())
                        out<<"+ X ";
                    else if(nod.get_coeficient_k(i) != 1 && i != nod.get_grad())
                        out<<"+ "<<nod.get_coeficient_k(i)<<"X ";
                    else if(nod.get_coeficient_k(i) == 1 && i == nod.get_grad())
                        out<<"X ";
                    else if(nod.get_coeficient_k(i) != 1 && i == nod.get_grad())
                        out<<nod.get_coeficient_k(i)<<"X ";
                }
            }
            else if(i == 0 && i != nod.get_grad()){
                if(nod.get_coeficient_k(0)>0)
                    out<<"+ "<<nod.get_coeficient_k(0);
                else if(nod.get_coeficient_k(0)<0)
                    out<<"- "<<(-1)*nod.get_coeficient_k(0);
            }
            else if(i == 0 && i == nod.get_grad())
                out<<nod.get_coeficient_k(0);
            else if(nod.get_coeficient_k(i) == -1)
                out<<"- X^"<<i<<" ";
            else if(nod.get_coeficient_k(i) == 1)
                out<<"+ X^"<<i<<" ";
            else if(nod.get_coeficient_k(i)>0)
                out<<"+ "<<nod.get_coeficient_k(i)<<"X^"<<i<<" ";
            else if(nod.get_coeficient_k(i)<0)
                out<<"- "<<(-1)*nod.get_coeficient_k(i)<<"X^"<<i<<" ";
    }

    return out;
}

Polinom& Polinom::operator =(Polinom& p){                   // Punctul 5.3
    this->grad = p.get_grad();
    if(this->coeficienti!=NULL)
        delete [] coeficienti;
    this->coeficienti = new float[p.get_grad() + 1];
    for(int i=0;i < p.get_grad() + 1; i++)
        (this->coeficienti)[i] = p.get_coeficient_k(i);
    this->urmator = p.get_urmator();
    return *this;
}

void Polinom::validare_atribute(){                          // Punctul 5.4                                             // Punctul 5.4
    int ok=0;
    while(this->get_grad() > 0 && this->get_coeficient_k(this->get_grad()) == 0){
        this->grad = this->grad - 1;
        ok++;
    }
    if(ok){
        float *coeficienti_noi = new float[this->grad + 1];
        int i;
        for(i=0; i < this->grad + 1; i++)
            coeficienti_noi[i] = this->get_coeficient_k(i);
        delete [] this->coeficienti;
        this->coeficienti = new float[this->grad + 1];
        for(i=0; i < this->grad + 1;i++)
            (this->coeficienti)[i] = coeficienti_noi[i];
        delete [] coeficienti_noi;
    }
}

/// Functii pentru prelucrarea listelor:    => Punctul 6


void adaugare_nod_in_lista(Polinom* (&cap), Polinom &nod){                  // Punctul 6.1
    // "nod" pointeaza deja la NULL (l-am initializat in declaratie)
    if(cap == NULL)
        cap = &nod;
    else{
        Polinom* i = cap;

        while(i->get_urmator() != NULL)
            i = i->get_urmator();

        // in pointerul i avem ultimul nod al listei. Dorim sa facem ca acest nod sa pointeze catre nodul pe care vrem sa-l adaugam
        Polinom Obiect_Intermediar(i->get_grad(), i->get_coeficienti(), &nod);
        // Obiect_Intermediar a copiat tot ce era in i cu exceptia ca Obiect_Intermediar pointeaza catre nodul pe care vrem sa-l adaugam
        *i = Obiect_Intermediar;
    }
}

void afisare_noduri_lista(Polinom* (&cap)){                    // Punctul 6.2

    if(cap == NULL)
        cout<<"Lista vida.\n";
    else{
        int indice = 1;
        Polinom* i = cap;
        while(i != NULL){
            cout << indice << ". " << *i << "\n";
            indice++;
            i = i->get_urmator();
        }
    }
}

int lungime_lista(Polinom* (&cap)){                 // Punctul 6.3
    int lungime = 0;
    Polinom* i = cap;
    while(i != NULL){
        lungime++;
        i = i->get_urmator();
    }
    return lungime;
}

void stergere_nod_din_lista(Polinom* (&cap), int indice){            // Punctul 6.4
    if(lungime_lista(cap) == 1){
        cap = NULL;
    }
    else if(indice == 1)
        cap = cap->get_urmator();
    else{
        Polinom* nod_curent = cap;
        Polinom* nod_anterior = nod_curent;
        int j = 1;

        while(nod_curent != NULL){
            if(j == indice)
                break;
            j++;
            nod_anterior = nod_curent;
            nod_curent = nod_curent->get_urmator();

        }

        Polinom Obiect_Nou(nod_anterior->get_grad(),nod_anterior->get_coeficienti(),nod_curent->get_urmator()); // Cream un obiect nou care sa pointeze catre nodul imediat urmator celui pe care vrem sa-l stergem
        // initializam acest obiect nou astfel incat sa aibe toate proprietatile nodului anterior celui pe care vrem sa-l stergem

        *nod_anterior = Obiect_Nou;

        //acum nodul anterior are exact aceleasi proprietati ca inainte, cu exceptia ca pointeaza direct la nodul de dupa cel pe care l-am sters

    }
    /// Obiectele pe care le "stergem" ataunci cand nu mai pointam catre ele vor fi sterse automat cand se elibereaza stiva din primul apel al functiei rulare_program(a fost apelata in main), fiind sterse de destructor.
}

void stergere_duplicate_din_lista(Polinom* (&cap),int &caz){            // Punctul 6.5
    if(lungime_lista(cap)<=1)
        cout<<"Nu exista destule noduri in lista astfel incat sa existe duplicate.\n";
    else{

        Polinom* i = cap;
        int indice_i = 1,indice_j = 2, ok = 0, lungime = lungime_lista(cap);
        while(i != NULL && indice_i<=lungime){
            indice_j = indice_i + 1;
            Polinom* j = i->get_urmator();
            while(j != NULL && indice_j<=lungime){
                if(*i == *j && indice_j<=lungime){
                    stergere_nod_din_lista(cap, indice_j);
                    indice_j--;
                    lungime--;
                    ok++;
                }
                j = j->get_urmator();
                indice_j++;
            }
            if(caz == 2 && ok != 0){
                stergere_nod_din_lista(cap, indice_i);
                indice_i--;
                lungime--;
            }
            i = i->get_urmator();
            indice_i++;
            ok = 0;
        }
    }
}

void selectare_indici_polinoame(int numar_indici_de_selectat, float* (&vector_de_indici), Polinom* (&cap)){         // Punctul 6.6
    int lungimea_listei = lungime_lista(cap);
    if(lungimea_listei == 0 || (lungimea_listei == 1 && numar_indici_de_selectat == 2)){
        cout<<"Nu aveti destule polinoame pentru a efectua aceasta operatie. Pentru a adauga polinoame folositi comanda ADD.\n";
        vector_de_indici[0] = -1; // folosim -1 ca sa indicam ca aceasta operatie nu este disponibila inca.
    }
    else {
        if(numar_indici_de_selectat == 1){
            cout<<"Selectati polinomul dorit folosind indicele asociat:\n\n";
            afisare_noduri_lista(cap);
            cout<<"\n(Pentru a selecta unul dintre polinoamele de mai sus, tastati unul dintre indicii asociati polinoamelor)\n\n";
            cout<<"Indicele tastat de dumneavoastra este: ";
        }
        else{
            cout<<"Selectati doua polinoame dintre cele de mai jos folosind indicii asociati:\n\n";
            afisare_noduri_lista(cap);
            cout<<"\n(Pentru a selecta polinoamele de mai sus, tastati indicii asociati polinoamelor pe rand, in ordinea in care doriti sa efectuati operatia aleasa)\n\n";
            cout<<"Indicii tastati de catre dumneavoastra sunt: ";
        }

        int ok = 0;

        for(int i = 0; i < numar_indici_de_selectat; i++)
            {
                cin>>vector_de_indici[i];
                if(vector_de_indici[i] < 1 || vector_de_indici[i] > lungimea_listei || int(vector_de_indici[i]) - vector_de_indici[i] != 0)
                    ok++;
            }
        cout<<"\n";
        while(ok != 0){
            ok = 0;
            cout<<"Multimea de indici pe care ati tastat-o nu apartine intervalului de indici INTREGI din intervalul [1, " << lungimea_listei<<"]. Va rog sa mai tastati odata: ";
            for(int i = 0; i < numar_indici_de_selectat; i++)
                {
                    cin>>vector_de_indici[i];
                    if(vector_de_indici[i] < 1 || vector_de_indici[i] > lungimea_listei || int(vector_de_indici[i]) - vector_de_indici[i] != 0)
                        ok++;
                }
        }
    }
    return ;
}

Polinom& cautare_nod_in_lista(Polinom* (&cap),int indice){      // Punctul 6.7
    Polinom* i = cap;
    int j = 1;
    while(i != NULL && j<indice){
        j++;
        i = i->get_urmator();
    }
    return *i;
}

void intrebare_adaugare_polinom(int indice,Polinom &obiect_de_adaugat,Polinom* (&cap)){     // Punctul 6.8
    char raspuns[1000];
    char caz_de_afisat[100];
    if(indice == 1)
        strcpy(caz_de_afisat, "aceasta suma");
    else if(indice == 2)
        strcpy(caz_de_afisat, "aceasta diferenta");
    else if(indice == 3)
        strcpy(caz_de_afisat, "acest produs");

    cout<<"Doriti sa adaugati "<<caz_de_afisat<<" ca fiind un nou polinom?(Tastati \"DA\" sau \"NU\") ";
    cin.getline(raspuns, 1000);
    cout<<"\n";
    while(strcmp(raspuns,"DA") !=0 && strcmp(raspuns, "NU") !=0){
        cout<<"Raspunsul dumneavoastra este invalid, mai incercati odata:(Tastati \"DA\" sau \"NU\") ";
        cin.getline(raspuns, 1000);
        cout<<"\n";
    }
    if(strcmp(raspuns, "DA") == 0){
        adaugare_nod_in_lista(cap, obiect_de_adaugat);
        cout<<"Felicitari! Ati adaugat "<< caz_de_afisat<<" cu succes!\n\n";
    }
    else if(strcmp(raspuns, "NU") == 0)
        cout<<"Polinomul a fost sters cu succes\n\n";

}

/// Functie pentru rularea programului:     => Punctul 7

void rulare_program(Polinom* cap){  // Punctul 7.1

    char comanda[1000];

    cout<<"\nTastati Comanda: ";

    cin.getline(comanda, 1000);

    cout<<"\n";

    if(strcmp(comanda,"ADD") == 0){                     // Punctul 7.2
        Polinom Obiect_Nou;         // Constructorul implicit initializeaza pointerii "coeficienti" si "urmator" cu NULL
        cin>>Obiect_Nou;
        adaugare_nod_in_lista(cap, Obiect_Nou);
        cout<<"Felicitari! Polinomul a fost adaugat cu succes.\n";
        rulare_program(cap);
    }
    else if(strcmp(comanda,"DELETE") == 0){             // Punctul 7.3
        float* indicii_de_tastat = new float[1];                // NU SE POATE FARA ALOCARE DINAMICA, DA EROARE ATUNCI CAND TRANSMIT CA PARAMETRU
        selectare_indici_polinoame(1,indicii_de_tastat,cap);
        if(indicii_de_tastat[0] != -1){
            stergere_nod_din_lista(cap,int(indicii_de_tastat[0]));
            cout<<"Felicitari! Polinomul a fost sters cu succes.\n";
            cin.get(); // Eliberam buffer-ul
        }
        delete [] indicii_de_tastat;
        rulare_program(cap);
    }
    else if(strcmp(comanda,"SUM") == 0){                // Punctul 7.4
        float* indicii_de_tastat = new float[2];
        selectare_indici_polinoame(2,indicii_de_tastat,cap);
        if(indicii_de_tastat[0] != -1){
            Polinom &p1 = cautare_nod_in_lista(cap, int(indicii_de_tastat[0]));
            Polinom &p2 = cautare_nod_in_lista(cap, int(indicii_de_tastat[1]));
            Polinom p3 = p1 + p2;
            cout<<"Suma dintre polinomul "<<p1<<" si polinomul "<<p2<<" este: "<< p3 << "\n\n";
            cin.get(); // Pentru a elibera buffer-ul
            intrebare_adaugare_polinom(1,p3,cap);
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
        else{
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
    }
    else if(strcmp(comanda, "SUM REPLACE") == 0){               // Punctul 7.5
        float* indicii_de_tastat = new float[2];
        selectare_indici_polinoame(2,indicii_de_tastat,cap);
        if(indicii_de_tastat[0] != -1){
            Polinom &p1 = cautare_nod_in_lista(cap, int(indicii_de_tastat[0]));
            Polinom &p2 = cautare_nod_in_lista(cap, int(indicii_de_tastat[1]));
            cout<<"Suma dintre polinomul "<<p1<<" si polinomul "<<p2<<" este: ";
            p1+=p2;
            cout<< p1 << "\n\n";
            cin.get(); // Pentru a elibera buffer-ul
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
        else{
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
    }
    else if(strcmp(comanda,"SUB") == 0){                        // Punctul 7.6
        float* indicii_de_tastat = new float[2];
        selectare_indici_polinoame(2,indicii_de_tastat,cap);
        if(indicii_de_tastat[0] != -1){
            Polinom &p1 = cautare_nod_in_lista(cap, int(indicii_de_tastat[0]));
            Polinom &p2 = cautare_nod_in_lista(cap, int(indicii_de_tastat[1]));
            Polinom p3 = p1 - p2;
            cout<<"Scazand din polinomul "<<p1<<" polinomul "<<p2<<" obtinem "<< p3 << "\n\n";
            cin.get(); // Pentru a elibera buffer-ul
            intrebare_adaugare_polinom(2,p3,cap);
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
        else{
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
    }
    else if(strcmp(comanda,"PROD") == 0){                       // Punctul 7.7
        float* indicii_de_tastat = new float[2];
        selectare_indici_polinoame(2,indicii_de_tastat,cap);
        if(indicii_de_tastat[0] != -1){
            Polinom &p1 = cautare_nod_in_lista(cap, int(indicii_de_tastat[0]));
            Polinom &p2 = cautare_nod_in_lista(cap, int(indicii_de_tastat[1]));
            Polinom p3 = p1 * p2;
            cout<<"Produsul dintre polinomul "<<p1<<" si polinomul "<<p2<<" este egal cu polinomul "<< p3 << "\n\n";
            cin.get(); // Pentru a elibera buffer-ul
            intrebare_adaugare_polinom(3,p3,cap);
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
        else{
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
    }
    else if(strcmp(comanda,"VALUE") == 0){                      // Punctul 7.8
        float* indicii_de_tastat = new float[1];
        selectare_indici_polinoame(1,indicii_de_tastat,cap);
        if(indicii_de_tastat[0] != -1){
            cout<<"Tastati punctul dorit: ";
            float punct;
            cin >> punct;
            Polinom &Obiectul_Selectat = cautare_nod_in_lista(cap,int(indicii_de_tastat[0]));
            cout << "Valoarea polinomului " << Obiectul_Selectat << " in punctul X = " << punct << " este: ";
            cout<< Obiectul_Selectat.valoare(punct)<<"\n";
            cin.get(); // Pentru a elibera buffer-ul
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
        else{
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
    }
    else if(strcmp(comanda, "DUPLICATE") == 0){                 // Punctul 7.9
        cout<<"\nDoriti sa pastrati polinoamele care au duplicate si doar sa stergeti restul copiilor sau doriti sa le stergeti si pe ele inclusiv? (Tastati \"DA\" sau \"NU\") ";
        char raspuns[100];
        cin.getline(raspuns,100);
        cout<<"\n";
        while(strcmp(raspuns,"DA") !=0 && strcmp(raspuns, "NU") !=0){
            cout<<"Raspunsul dumneavoastra este invalid, mai incercati odata:(Tastati \"DA\" sau \"NU\") ";
            cin.getline(raspuns, 100);
            cout<<"\n";
        }
        int caz;
        if(strcmp(raspuns, "DA") == 0)
            caz = 1;
        else if (strcmp(raspuns, "NU") == 0)
            caz = 2;
        stergere_duplicate_din_lista(cap,caz);
        cout<<"\n\nToate duplicatele din lista au fost sterse. Lista dumneavoastra acum arata asa:\n\n";
        afisare_noduri_lista(cap);
        rulare_program(cap);
    }
    else if(strcmp(comanda,"TOTAL") == 0){              // Punctul 7.10
        afisare_noduri_lista(cap);
        rulare_program(cap);
    }
    else if(strcmp(comanda,"NUMAR") == 0){              // Punctul 7.11
        cout<<"In total ati adaugat "<<lungime_lista(cap)<<" polinoame.\n";
        rulare_program(cap);
    }
    else if(strcmp(comanda, "GRAD") == 0){              // Punctul 7.12
        float* indicii_de_tastat = new float[1];
        selectare_indici_polinoame(1,indicii_de_tastat,cap);
        if(indicii_de_tastat[0] != -1){
            Polinom &Obiectul_Ales = cautare_nod_in_lista(cap, int(indicii_de_tastat[0]));
            cout<<"Gradul polinomului " << Obiectul_Ales<<" este: "<< Obiectul_Ales.get_grad()<<"\n";
            cin.get(); // Pentru a elibera buffer-ul
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
        else{
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
    }
    else if(strcmp(comanda, "EGALE") == 0){                     // Punctul 7.13
        float* indicii_de_tastat = new float[2];
        selectare_indici_polinoame(2,indicii_de_tastat,cap);
        if(indicii_de_tastat[0] != -1){
            Polinom &p1 = cautare_nod_in_lista(cap, int(indicii_de_tastat[0]));
            Polinom &p2 = cautare_nod_in_lista(cap, int(indicii_de_tastat[1]));
            cout<<"Polinomul " << p1;
            if(!(p1 == p2))
                cout<<" NU";
            cout<<" este egal cu polinomul " << p2<<"\n\n";
            cin.get(); // Pentru a elibera buffer-ul
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
        else{
            delete [] indicii_de_tastat;
            rulare_program(cap);
        }
    }
    else if(strcmp(comanda,"STOP") == 0){               // Punctul 7.14
        return;
    }
    else{
        cout<<"\nComanda tastata nu reprezinta una dintre comenzile prezentate in antetul consolei.\n";
        cout<<"Mai incercati odata, va rog.\n";
        rulare_program(cap);
    }
}

/// main-ul:                => Punctul 8

int main(){

    cout<<"\t\t\tBINE ATI VENIT!\n\n";
    cout<<"\t\tComenzile acestui program sunt:\n\n";
    cout<<"\t-ADD pentru a adauga un polinom\n";
    cout<<"\t-DELETE pentru a sterge un polinom\n";
    cout<<"\t-SUM pentru a insuma doua polinoame\n";
    cout<<"\t-SUM REPLACE pentru a insuma doua polinoame si a memora rezultatul in primul polinom\n";
    cout<<"\t-SUB pentru a scadea doua polinoame\n";
    cout<<"\t-PROD pentru a inmulti doua polinoame\n";
    cout<<"\t-VALUE pentru a calcula valoarea polinomului intr-un punct\n";
    cout<<"\t-DUPLICATE pentru a sterge toate polinoamele care sunt duplicate in cadrul listei de polinoame\n";
    cout<<"\t-TOTAL pentru a afisa toate polinoamele introduse pana acum\n";
    cout<<"\t-NUMAR pentru a afisa doar numarul de polinoame introduse pana acum\n";
    cout<<"\t-GRAD pentru a afisa gradul unui polinom adaugat\n";
    cout<<"\t-EGALE pentru a afisa daca doua polinoame adaugate sunt egale sau nu\n";
    cout<<"\t-STOP pentru a opri programul";
    cout<<"\n\n";

    Polinom *cap = NULL;

    rulare_program(cap);

    if(cap != NULL)
        delete cap;

    return 0;
}
