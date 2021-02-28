#include<iostream>
//#include<typeinfo>

using namespace std;

class Polinom{
    private:
        int grad;
        float* coeficienti;
        Polinom* urmator;

    public:
        // Constructori

        Polinom(int grad_Polinom, float* v){
            grad = grad_Polinom;
            coeficienti = new float[grad+1];
            for(int i = 0; i < grad_Polinom + 1 ;i++)
                coeficienti[i] = v[i];
        }
        Polinom(int grad_polinom){
            grad = grad_polinom;
        }
        // Settere

        void set_grad(int x){
            grad = x;
        }
        void set_urmator(Polinom* x){
            urmator = x;
        }
        void set_coeficienti(int grad_polinom){
            coeficienti = new float[grad_polinom+1];
        }


        // Gettere

        int get_grad(){
            return grad;
        }

        Polinom* get_urmator(){
            return urmator;
        }
        float *get_coeficienti(){
            return coeficienti;
        }
        float get_coeficient_i(int pozitie){
            return coeficienti[pozitie];
        }



        // Metodele din cerinta(valoare,suma,diferenta,produs)


        float value(float n){
            float s = 0,exponent=1;
            for(int i=0;i<grad+1;i++)
            {
                for(int j = 1; j <= i ; j++)
                    exponent = exponent*n;
                s = s + coeficienti[i] * exponent;
                exponent = 1;
            }
            return s;
        }

        Polinom* sum(Polinom* x){
            int* grad_maxim = new int;
            int* grad_minim = new int;

            int* i = new int(0);

            // Stabilim gradul maxim si gradul minim dintre cele doua polinoame

            if(grad == x->get_grad()){
                *grad_maxim = grad;
                *grad_minim = grad;
            }
            else if(grad > x->get_grad()){
                *grad_maxim = grad;
                *grad_minim = x->get_grad();
            }
            else{
                *grad_maxim = x->get_grad();
                *grad_minim = grad;
            }
            // Acum ca am stabilit gradul maxim si gradul minim putem aloca dinamic coeficientilor sumei un spatiu de grad_maxim + 1 elemente
            // si facem suma la primele grad_minim + 1 elemente, dupa care adaugam restul de grad_maxim - grad_minim + 1 elemente

            float* vector_suma_coeficienti = new float[*grad_maxim + 1];

            //cout<<"Grad Maxim: "<<*grad_maxim<<" Grad Minim: "<< *grad_minim<<"\n\n";

            for(*i = 0; *i<*grad_minim + 1; *i=*i+1)

                vector_suma_coeficienti[*i] = coeficienti[*i] + x->get_coeficient_i(*i);
            if(*grad_maxim == grad) // daca gradul maxim este cel al polinomului din care apelam functia atunci folosim coeficienti[i] pentru a accesa coeficientii ramasi
                while(*i < *grad_maxim + 1){
                    vector_suma_coeficienti[*i] = coeficienti[*i];
                    *i = *i+1;
                }
            else
                while(*i < *grad_maxim + 1){
                    vector_suma_coeficienti[*i] = x->get_coeficient_i(*i);
                    *i = *i + 1;
                }
            // avem suma coeficientilor in *vector_suma_coeficienti si ne ramane doar sa creem obiectul de gradul *grad_maxim si coeficientii din vector_suma_coeficienti

            Polinom* suma_polinoamelor = new Polinom(*grad_maxim,vector_suma_coeficienti);
            delete i;
            //delete grad_maxim;
            delete grad_minim;
            //delete vector_suma_coeficienti;

            return suma_polinoamelor;

        }

        Polinom* sub(Polinom* x){
            int* grad_maxim = new int;
            int* grad_minim = new int;

            int* i = new int(0);

            // Stabilim gradul maxim si gradul minim dintre cele doua polinoame

            if(grad == x->get_grad()){
                *grad_maxim = grad;
                *grad_minim = grad;
            }
            else if(grad > x->get_grad()){
                *grad_maxim = grad;
                *grad_minim = x->get_grad();
            }
            else{
                *grad_maxim = x->get_grad();
                *grad_minim = grad;
            }
            // Acum ca am stabilit gradul maxim si gradul minim putem aloca dinamic coeficientilor diferentei un spatiu de grad_maxim + 1 elemente
            // si facem diferenta la primele grad_minim + 1 elemente, dupa care adaugam restul de grad_maxim - grad_minim + 1 elemente
            // in functie de pozitionarea lor in functie de operatorul de scadere. Ex: 2x - 4x^2. Polinomul 1 este 2x iar polinomul 2 este 4x^2
            // dar polinomul rezultant al diferentei va fi -4x^2 + 2x deci trebuie sa fim atenti la semne

            float* vector_diferenta_coeficienti = new float[*grad_maxim + 1];

            //cout<<"Grad Maxim: "<<*grad_maxim<<" Grad Minim: "<< *grad_minim<<"\n\n";

            for(*i = 0; *i < *grad_minim + 1; *i=*i+1)

                vector_diferenta_coeficienti[*i] = coeficienti[*i] - x->get_coeficient_i(*i);

            if(*grad_maxim == grad) // daca gradul maxim este cel al polinomului din care apelam functia atunci folosim coeficienti[i] pentru a accesa coeficientii ramasi
                while(*i < *grad_maxim + 1){
                    vector_diferenta_coeficienti[*i] = coeficienti[*i];
                    *i = *i+1;
                }
            else
                while(*i < *grad_maxim + 1){
                    vector_diferenta_coeficienti[*i] = (-1)*x->get_coeficient_i(*i);
                    *i = *i + 1;
                }
            // avem suma coeficientilor in *vector_suma_coeficienti si ne ramane doar sa creem obiectul de gradul *grad_maxim si coeficientii din vector_suma_coeficienti

            Polinom* diferenta_polinoamelor = new Polinom(*grad_maxim,vector_diferenta_coeficienti);
            delete i;
            //delete grad_maxim;
            delete grad_minim;
            //delete vector_diferenta_coeficienti;

            return diferenta_polinoamelor;

        }

        Polinom* prod(Polinom* x){
            float* vector_produs_coeficienti = new float[grad + x->get_grad() + 1];
            int i,j;
            for(i = 0; i < grad + x->get_grad()+1; i++)
                vector_produs_coeficienti[i] = 0;      // initializam toti coeficientii cu 0

            for(i = 0; i<grad+1; i++)
                for(j = 0; j < x->get_grad() + 1; j++)
                    vector_produs_coeficienti[i+j] = vector_produs_coeficienti[i+j] + (coeficienti[i] * x->get_coeficient_i(j));

            Polinom* produsul_polinoamelor = new Polinom((grad + x->get_grad()),vector_produs_coeficienti);
            delete vector_produs_coeficienti;
            return produsul_polinoamelor;
        }

        // Metode ce nu fac parte din cerinta insa sunt folositoare pentru testarea codului

        void afisare_polinom(){
            int i=grad;
            while(coeficienti[i] == 0 && i>=0){
                i--;
                grad--;
            }
            if(i == -1)
                cout<<"0";  // cazul in care toti coeficientii sunt egali cu 0 => polinomul este 0
            else if(i == 0)
                cout<<coeficienti[0];  // cazul in care polinomul este de grad 0 singurul termen este termenul liber
            else{
                if(coeficienti[i] == 1)
                    cout<<"X^"<<i;
                else if(coeficienti[i] == -1)
                    cout<<"-X^"<<i;
                else
                    cout<<coeficienti[i]<<"X^"<<i;
                i--;

                for(; i>=1; i--)
                {
                    if(coeficienti[i]){
                        if(coeficienti[i]>0)
                            cout<<" + ";
                        if(coeficienti[i]!= 1 && coeficienti[i]!= -1)
                            cout<<coeficienti[i]<<"X^"<<i;
                        else if(coeficienti[i] == 1)
                            cout<<"X^"<<i;
                        else if(coeficienti[i] == -1)
                            cout<<"- X^"<<i;
                    }
                }
                if(coeficienti[0]>0)
                    cout<<" + "<<coeficienti[0];
                else if(coeficienti[0]<0)
                    cout<<" "<<coeficienti[0];
            }
            //cout<<"\n";
        }


};

Polinom* cap = NULL;

void adaugareLista(Polinom *x){

    Polinom* i = cap;
    x->set_urmator(NULL);

    if(i == NULL)
        cap = x;
    else{
        while(i->get_urmator() != NULL)
            i = i->get_urmator();

        i->set_urmator(x);
    }

}

void afisareLista(){
    Polinom *i = cap;
    int *j = new int(1);
    while(i!=NULL){
        //cout<<i->get_grad()<<" ";
        cout<<*j<<". ";
        i->afisare_polinom();
        cout<<"\n";
        i = i->get_urmator();
        *j = *j+1;
    }
    delete j;
    cout<<"\n";
}
int lungimeLista(){
    Polinom *i=cap;
    int lungime = 0;
    while(i!=NULL){
        lungime = lungime + 1;
        i=i->get_urmator();
    }
    return lungime;
}

void stergereNod(Polinom* x){
    if(cap == x){
        cap = x->get_urmator();
        delete x;
    }
    else{
        Polinom* i = cap;
        Polinom* anterior = i;

        while(i!= x && i!=NULL){
            anterior = i;
            i = i->get_urmator();
        }
        anterior->set_urmator(i->get_urmator());
        delete i;
        //delete x; // Practic x a fost sters atunci cand am sters i
    }
}

Polinom* cautareNod(int indice){
    Polinom* i = cap;
    int j=1;

    while(i!=NULL && j<indice){
        i = i->get_urmator();
        j++;
    }
    return i;
}

int selectareIndice(){
    if(cap == NULL){
        cout<<"Nu ati adaugat niciun polinom pana acum. Folositi comanda ADD pentru a adauga polinoame.\n";
        return -1;
    }
    else{
        afisareLista();
        cout<<"Selectati unul dintre polinoamele de mai sus folosind indicele indicat: ";
        int* indice = new int;
        cin>>*indice;
        int* lungime = new int(lungimeLista());
        while(*indice<1 || *indice> *lungime){
            if(*indice < 1)
                cout<<"Indicele tastat este prea mic.\n";
            else if(*indice > *lungime)
                cout<<"Indicele tastat este prea mare.\n";
            cout<<"Tastati alt indice: ";
            cin>>*indice;
        }
    return *indice;
    }
}

void rulare_program(){
    string* instructiune = new string;
    cout<<"\nTastati comanda: ";
    cin>>*instructiune;

    if(*instructiune == "ADD"){
        cout<<"Scrieti gradul polinomului: ";
        int* grad = new int;
        cin>>*grad;

        cout<<"Scrieti coeficientii polinomului incepand cu termenul liber si pana la termenul de gradul "<<*grad<<": ";
        float* v = new float[*grad+1];
        for(int i = 0; i<*grad+1; i++)
            cin>>v[i];

        Polinom* obiect = new Polinom(*grad,v);

        adaugareLista(obiect);
        //cout<<typeid(*obiect).name()<<" "<<typeid(nou).name()<<" "<<typeid(obiect).name()<<"\n";

        cout<<"Felicitari! Polinomul a fost adaugat cu succes.\n";

    }

    else if(*instructiune == "DELETE"){
        int* indice = new int(selectareIndice());
        if(*indice!=-1){
            stergereNod(cautareNod(*indice));
            cout<<"Polinomul a fost sters cu succes!\n";
        }
        delete indice;
    }

    else if(*instructiune == "SUM"){
        if(lungimeLista()<2)
            cout<<"Nu ati adaugat suficiente polinoame astfel incat sa realizati o suma. Daca doriti sa adaugati un polinom folositi comanda ADD\n";
        else{
            afisareLista();
            cout<<"Selectati doua polinoame dintre cele de mai sus folosind indicii: ";
            int *indice_1 = new int, *indice_2 = new int;

            cin>>*indice_1>>*indice_2;

            int* lungime = new int(lungimeLista());

            while(*indice_1 > *lungime || *indice_2 > *lungime || *indice_1 < 1 || *indice_2 < 1){
                cout<<"Perechea de indici tastata nu apartine intervalului de indici [1, "<<*lungime<<"].\n";
                cout<<"Mai tastati odata indicii: ";
                cin>>*indice_1>>*indice_2;
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


            Polinom* obiect_nou = cautareNod(*indice_1)->sum(cautareNod(*indice_2)); // apeleaza metoda sum al celui de-al indice_1 nod al listei si transmite ca parametru al sumei cel de-al indice_2 nod al listei.

            cout<<"Suma polinomului ";
            cautareNod(*indice_1)->afisare_polinom();
            cout<<" cu polinomul ";
            cautareNod(*indice_2)->afisare_polinom();
            cout<<" este:\n";
            obiect_nou->afisare_polinom();
            cout<<"\n\n";

            cout<<"Doriti sa adaugati aceasta suma ca fiind un nou polinom?(Tastati \"DA\" sau \"NU\")\n";

            string* raspuns = new string;

            cin>>*raspuns;
            cout<<"\n";
            while(*raspuns != "DA" && *raspuns != "NU"){
                cout<<"Raspunsul dumneavoastra este invalid. Mai incercati odata: ";
                cin>>*raspuns;
            }
            if(*raspuns == "DA"){
                adaugareLista(obiect_nou);
                cout<<"Felicitari! Polinomul a fost adaugat cu succes.\n";
            }
            else{
                delete obiect_nou;
                cout<<"Polinomul a fost sters cu succes!\n";
            }
            delete raspuns;
            delete indice_1;
            delete indice_2;
            delete lungime;
        }
    }

    else if(*instructiune == "SUB"){
        if(lungimeLista()<2)
            cout<<"Nu ati adaugat suficiente polinoame astfel incat sa realizati o diferenta. Daca doriti sa adaugati un polinom folositi comanda ADD\n";
        else{
            afisareLista();
            cout<<"Selectati doua polinoame dintre cele de mai sus folosind indicii: ";
            int *indice_1 = new int, *indice_2 = new int;

            cin>>*indice_1>>*indice_2;

            int* lungime = new int(lungimeLista());

            while(*indice_1 > *lungime || *indice_2 > *lungime || *indice_1 < 1 || *indice_2 < 1){
                cout<<"Perechea de indici tastata nu apartine intervalului de indici [1, "<<*lungime<<"].\n";
                cout<<"Mai tastati odata indicii: ";
                cin>>*indice_1>>*indice_2;
            }


            Polinom* obiect_nou = cautareNod(*indice_1)->sub(cautareNod(*indice_2)); // apeleaza metoda sub al celui de-al indice_1 nod al listei si transmite ca parametru al diferentei cel de-al indice_2 nod al listei.

            cout<<"Scaderea polinomului ";
            cautareNod(*indice_2)->afisare_polinom();
            cout<<" din polinomul ";
            cautareNod(*indice_1)->afisare_polinom();
            cout<<" va avea ca rezultat polinomul:\n";
            obiect_nou->afisare_polinom();
            cout<<"\n\n";

            cout<<"Doriti sa adaugati aceasta diferenta ca fiind un nou polinom?(Tastati \"DA\" sau \"NU\")\n";

            string* raspuns = new string;

            cin>>*raspuns;
            cout<<"\n";
            while(*raspuns != "DA" && *raspuns != "NU"){
                cout<<"Raspunsul dumneavoastra este invalid. Mai incercati odata: ";
                cin>>*raspuns;
            }
            if(*raspuns == "DA"){
                adaugareLista(obiect_nou);
                cout<<"Felicitari! Polinomul a fost adaugat cu succes.\n";
            }
            else{
                delete obiect_nou;
                cout<<"Polinomul a fost sters cu succes!\n";
            }
            delete raspuns;
            delete indice_1;
            delete indice_2;
            delete lungime;
        }
    }
    else if(*instructiune == "PROD"){
        if(lungimeLista()<2)
            cout<<"Nu ati adaugat suficiente polinoame astfel incat sa realizati un produs de polinoame. Daca doriti sa adaugati un polinom folositi comanda ADD\n";
        else{
            afisareLista();
            cout<<"Selectati doua polinoame dintre cele de mai sus folosind indicii: ";
            int *indice_1 = new int, *indice_2 = new int;

            cin>>*indice_1>>*indice_2;

            int* lungime = new int(lungimeLista());

            while(*indice_1 > *lungime || *indice_2 > *lungime || *indice_1 < 1 || *indice_2 < 1){
                cout<<"Perechea de indici tastata nu apartine intervalului de indici [1, "<<*lungime<<"].\n";
                cout<<"Mai tastati odata indicii: ";
                cin>>*indice_1>>*indice_2;
            }


            Polinom* obiect_nou = cautareNod(*indice_1)->prod(cautareNod(*indice_2)); // apeleaza metoda sub al celui de-al indice_1 nod al listei si transmite ca parametru al diferentei cel de-al indice_2 nod al listei.

            cout<<"Produsul dintre polinomului ";
            cautareNod(*indice_1)->afisare_polinom();
            cout<<" si polinomul ";
            cautareNod(*indice_2)->afisare_polinom();
            cout<<" este:\n";
            obiect_nou->afisare_polinom();
            cout<<"\n\n";

            cout<<"Doriti sa adaugati acest produs de polinoame ca fiind un nou polinom?(Tastati \"DA\" sau \"NU\")\n";

            string* raspuns = new string;

            cin>>*raspuns;
            cout<<"\n";
            while(*raspuns != "DA" && *raspuns != "NU"){
                cout<<"Raspunsul dumneavoastra este invalid. Mai incercati odata: ";
                cin>>*raspuns;
            }
            if(*raspuns == "DA"){
                adaugareLista(obiect_nou);
                cout<<"Felicitari! Polinomul a fost adaugat cu succes.\n";
            }
            else{
                delete obiect_nou;
                cout<<"Polinomul a fost sters cu succes!\n";
            }
            delete raspuns;
            delete indice_1;
            delete indice_2;
            delete lungime;
        }
    }

    else if(*instructiune == "VALUE"){
        int* indice = new int(selectareIndice());
        if(*indice!=-1){
            float* punct = new float;
            cout<<"Tastati punctul dorit: ";
            cin>>*punct;
            Polinom *obiect = cautareNod(*indice);
            cout<<"\nValoarea polinomului "<<*indice<<" pentru punctul "<<*punct<<" este: "<<obiect->value(*punct)<<"\n";
            delete indice;
            delete punct;
        }
        delete indice;
    }

    else if(*instructiune == "TOTAL"){
        if(cap == NULL)
            cout<<"Nu ati adaugat niciun polinom pana acum. Folositi comanda ADD pentru a adauga polinoame.\n";
        else
            afisareLista();
    }

    else if(*instructiune == "STOP")
    {
        delete instructiune;
        return;
    }
    else{
        cout<<"\nComanda gresita! Va rog sa mai incercati odata:\n";
    }
    delete instructiune;
    rulare_program();
}



int main(){
    /*
    Polinom a(2),b(3),c(15),d(122),e(100),f(-23);

    cap = &a;
    a.set_urmator(&b);
    b.set_urmator(&c);
    c.set_urmator(NULL);

    adaugareLista(&d);
    Polinom *obiect = new Polinom(1002);

    adaugareLista(obiect);

    afisareLista();

    */


    cout<<"\t\t\tBINE ATI VENIT!\n\n";
    cout<<"\t\tComenzile acestui program sunt:\n\n";
    cout<<"\t-ADD pentru a adauga un polinom\n";
    cout<<"\t-DELETE pentru a sterge un polinom\n";
    cout<<"\t-SUM pentru a insuma doua polinoame\n";
    cout<<"\t-SUB pentru a scadea doua polinoame\n";
    cout<<"\t-PROD pentru a inmulti doua polinoame\n";
    cout<<"\t-VALUE pentru a calcula valoarea polinomului intr-un punct\n";
    cout<<"\t-TOTAL pentru a afisa toate polinoamele introduse pana acum\n";
    cout<<"\t-STOP pentru a opri programul";
    cout<<"\n\n";

    rulare_program();

    return 0;
}
