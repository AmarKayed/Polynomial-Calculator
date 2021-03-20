Nume: Kayed Amar
Grupa:143
Programul a fost scris si rulat in CodeBlocks


Fisierul "input.txt" contine un exemplu de input pentru programul din fisierul cu extensia .cpp
ATENTIE: a se copia continutul din fisierul "input.txt" in intregime folosind CTRL + A si CTRL + C, urmand a fi lipite in consola folosind CTRL + V
Afisarile pentru inputul respectiv se regasesc in fisierul "output.txt"


Cerinta Proiectului:
	12.Polinoame reprezentate ca tablouri unidimensionale cu coeficienți numere reale
		○ Are drept parametrii:
			■ Gradul polinomului
			■ vectorul coeficienților, de dimensiune egală cu gradul plus 1, de la cel al termenului liber la cel de grad maxim
		○ Metode ce se doresc a fi implementate
			■ calculul valorii unui polinom într-un punct;
			■ suma a două polinoame;
			■ diferența a două polinoame;
			■ produsul a două polinoame.



Documentatia programului:


1. Pentru antetul programului am inclus 2 librarii: 

	- iostream pentru citirea si afisarea de la tastatura
	- cstring pentru accesarea functiilor de prelucrare a sirurilor de caractere(strlen, strcmp, etc), care vor fi folosite pentru prelucrarea comenzilor citite din consola.
	
   De asemenea, am folosit "using namespace std;" pentru usurarea scrierii fluxurilor cin si cout, precum si pentru accesarea functiilor min(), max() pe care le voi folosi de-a lungul programului.


2. Am declarat clasa "Polinom".

	- Clasele au implicit specificatorul private, dar am ales sa-l scriu pentru usurinta citirii codului.
	- Clasa "Polinom" reprezinta o schita a obiectelor care sunt de fapt polinoame, reprezentate ca vectori de coeficienti.
	- Fiind doar o schita, clasa "Polinom" are numai declarari de metode si metode inline, tocmai pentru a usura citirea proprietatilor obiectelor acesteia.


	# Atributele instantelor clasei:

		- 2.1	Atributele clasei:
			
			- o variabila de tip int numita "grad" ce reprezinta gradul polinomului(obiectului clasei)
			- un pointer catre un vector de float-uri numit "coeficienti" ce reprezinta coeficientii polinomului(scrisi sub forma unui tablou unidimensional, asa cum este specificat in cerinta)
			- un pointer catre un alt obiect al clasei, acest pointer este numit "urmator" si are rolul de a facilita crearea unei liste simplu inlantuite folosind obiectele clasei(o lista de polinoame)

	    		Toate aceste atribute au specificatorul private pentru a encapsula informatia.
			Fiind o clasa, specificatorul private nu este necesar de mentionat, insa am ales sa-l scriu pentru a usura citirea codului.


	# Metodele clasei:

		- 2.2	Settere:

			- 2.2.1	set_grad() are rolul de a seta atributul "grad" al clasei.

			- 2.2.2	set_coeficienti() are rolul de a seta atributul "grad" al clasei si de a aloca dinamic un vector de float-uri de lungime grad + 1(+1 reprezinta termenul liber al polinomului), care este pointat de catre "coeficienti".
						  In cazul in care pointerul "coeficienti" deja pointeaza catre un vector alocat dinamic inainte de a apela acest setter, o sa stergem acel vector pentru a evita un memory leak.
						  De asemenea, acest setter copiaza toate elementele din parametrul "coeficienti" in vectorul alocat dinamic in pointerul atribut "coeficienti" al clasei.

			- 2.2.3	set_urmator() este o functie inline tocmai pentru ca are o executie rapida, acest setter seteaza pointerul "urmator" cu o adresa de memorie, mai exact, cu adresa unui obiect care reprezinta urmatorul nod al listei simplu inlantuite pe care o vom crea.
					      Spre deosebire de pointerul coeficienti, aici nu ne facem griji ca o sa avem memory leaks, intrucat obiectele se vor sterge automat de destructorul definit mai jos in program.
					      De asemenea, obiectele se vor sterge in ordinea inversa in care acestea apar in lista simplu inlantuita, intrucat adaugarea obiectelor in lista se face prin a le adauga la sfarsitul listei, acestea devenind ultimul nod al listei(la momentul adaugarii).

			- 2.2.4	set_polinom() practic combina set_coeficienti() cu set_urmator(), astfel setand toate atributele clasei "Polinom".
			
			Toate setterele clasei au specificatorul private tocmai pentru a asigura protejarea informatiei.
			Toate obiectele clasei sunt initializate folosind constructorul de initializare, constructorul de copiere si prin supradefinirea operatorului de atribuire.



		- 2.3	Constructori:

			- 2.3.1	Polinom() este constructorul "default" care se apeleaza oricand un obiect nou este creat fara ca acesta sa fie initializat cu oricare alt constructor/operator.
					  Acest constructor initializeaza pointerii "coeficienti" si "urmator" cu valoarea NULL.
					  Initializarea celor doi pointeri este utila in primul rand pentru ca ne asigura ca nu se vor produce erori atunci cand se apeleaza destructorul pentru obiectele create, dar neutilizate,
					  iar in al doilea rand ne ajuta sa initializam pointerul "urmator" astfel incat sa pointeze la sfarsitul listei simplu inlantuite, acest lucru este util, intrucat toate obiectele pe care le vom adauga vor fi plasate la sfarsitul listei mereu.

			- 2.3.2 Polinom(int grad) initializeaza atributul "grad" al obiectelor si initializeaza pointerul "urmator" astfel incat sa pointeze catre NULL(util pentru implementarea listei simplu inlantuite).

			- 2.3.3 Polinom(int grad, float* coeficienti) face tot ce face Polinom(int grad) si aloca dinamic un vector de float-uri, care este pointat de pointerul "coeficienti".
								      De asemenea, copiaza fiecare element din vectorul transmis ca parametru "coeficienti" in vectorul nou alocat in pointerul atribut "coeficienti".

			- 2.3.4 Polinom(int grad, float* coeficienti, Polinom* nodul_urmator) face tot ce face Polinom(int grad, float* coeficienti) cu exceptia faptului ca initializeaza pointerul "urmator" cu adresa din "nodul_urmator" in loc de a il initializa cu NULL.

			- 2.3.5 Polinom(Polinom p, Polinom* nodul_urmator) functioneaza similar unui constructor de copiere, in sensul in care copiaza toate atributele din obiectul p in obiectul pentru care este apelat acest constructor cu exceptia atributului "urmator",
									   acestuia fiindu-i atribuit in schimb adresa din pointerul "nodul_urmator".
			
			Nu am mai implementat un copy-constructor, intrucat avem unul dat implicit de compilator. In schimb, am ales sa implementez o alta versiune asemanatoare unui copy-constructor, care sa fie mai mult folosit pentru initializare.


		- 2.4	Destructor:
			
			- 2.4.1	~Polinom()
 
				- Am pastrat o afisare comentata, in cazul in care doriti sa vizualizati in ce ordine sunt distruse obiectele create.
				- Avand 2 pointeri ca atribute ale clasei, destructorul clasei va dezaloca memoria alocata in cei doi pointeri doar daca acestia sunt diferiti de NULL(daca au fost folositi/pointeaza catre ceva concret).
				- In teorie asa ar trebui sa functioneze un destructor.
				- In practica cazului nostru, putem dezaloca doar pointerul "coeficienti", intrucat doar acesta trebuie sters manual, fiindu-i alocat un vector in memoria heap si nu pe stiva.
				- In schimb, cei doi pointeri in sine, precum si restul atributelor vor fi sterse oricum odata cu stergerea obiectelor declarate pe stiva(in program avem doar declarari pe stiva, nu avem variabile/obiecte globale)
				- De asemenea, nu avem ce sterge din pointerul "urmator", intrucat acesta nu va avea niciun vector dinamic alocat. In schimb, pointerul pointeaza doar la obiecte care reprezinta nodurile din lista simplu inlantuita.
				- Prin urmare, acele noduri se vor sterge automat odata ce se iese din scope, altfel spus, se vor sterge in ordine inversa fata de cum au fost adaugate.
				- Daca avem doua noduri consecutive i si j, cu i pointand catre j, nu trebuie sa stergem ce este in pointerul din i, intrucat destructorul se va apela in ordine inversa fata de cum apar i si j in lista deci j se va sterge inainte ca destructorul din i sa fie apelat.
				- Din aceste motive am lasat comentat instructiunile care sterg informatia din pointerul "urmator".
				- La sfarsit, ca o precautie, atribuim valoarea NULL pointerilor, astfel incat sa fim siguri ca nu s-ar sterge inca odata din greseala.


		- 2.5	Gettere:

			- 2.5.1	get_grad() returneaza valoarea din atributul "grad".
			- 2.5.2	get_coeficienti() returneaza adresa de inceput a vectorului de coeficienti.
			- 2.5.3	get_coeficient_k(int k) returneaza al k-lea element din acel vector de coeficienti.
			- 2.5.4	Polinom* get_urmator() returneaza adresa la care pointeaza "urmator".

			


3. Metodele cerute in cerinta:(valoare, suma, diferenta, produs)


		# Valoarea intr-un punct al polinomului:
		
			- 3.1   float valoare(float punct)
				

				- Aceasta este metoda care calculeaza valoarea unui polinom intr-un punct transmis ca parametru al functiei.
				- Aceasta metoda declara 2 variabile: "suma" si "exponent":
					"suma" este initializata cu 0 pentru ca o vom folosi pentru a realiza o suma de valori
					"exponent" este initializata cu 1 pentru ca o vom folosi pentru a realiza un produs de valori
				- Parcurgem vectorul de coeficienti cu un for in care i merge de la 0 la gradul polinomului
				- Calculam la fiecare pas valoarea punctului la puterea i, rezultatul il memoram in variabila "exponent"
				- Adunam in variabila "suma" produsul dintre al i-lea coeficient si valoarea din variabila "exponent"
				- Reinitializam "exponent" cu 1 pentru a putea calcula ridicarea punctului la puterea i in urmatorul pas
				- La sfarsit avem suma produselor dintre al i-lea coeficient si punct^i in variabila "suma"
				- Prin urmare, "suma" reprezinta valoarea polinomului in punctul transmis ca parametru asa ca returnam "suma"


		# Suma a doua Polinoame

			- 3.2	Polinom operator +(Polinom p)
				
				- Aceasta metoda supradefineste operatorul "+" si realizeaza suma a doua polinoame pe care o returneaza prin valoare.
				- Se declara variabila "grad_maxim" care determina gradul maxim dintre obiectul din care apelam metoda si polinomul "p"
				- Se declara vectorul de coeficienti "suma_coeficienti" care va memora suma coeficientilor dintre cele doua polinoame, acesta este declarat dinamic cu lungimea grad_maxim + 1
				- Se parcurg simultan ambele polinoame(ambii vectori de coeficienti) pana cand se termina cel de lungime minima
				- La fiecare pas i, al i-lea element din vectorul "suma_coeficienti" va prelua valoarea sumei dintre al i-lea element din cele doua polinoame(din vectorii lor de coeficienti)
				- Dupa ce se iese din primul while exista 3 cazuri: cel in care gradele polinoamelor erau egale, cel in care primul are grad mai mare, cel in care al doilea are grad mai mare
				- In cazul in care gradele polinoamelor erau egale atunci suma s-a efectuat cu succes, pentru celalalte doua cazuri mai avem nevoie de 2 while-uri care sa atribuie restul elementelor ce nu au fost abordate
				- Intr-un final, avem in variabila "grad_maxim" lungimea vectorului "suma_coeficienti" - 1, iar in acest vector avem suma coeficientilor
				- Declaram si instantiem un nou obiect. Il initializam cu gradul "grad_maxim" si cu coeficientii din "suma_coeficienti"
				- Efectuam o validare a atributelor folosind metoda "validare_atribute()" astfel incat sa ne asiguram ca gradul polinomului si coeficientii sunt corecti
				- Eliberam zona de memorie alocata in pointerul "suma_coeficienti" folosind delete []
				- Returnam obiectul nou creat care reprezinta suma polinoamelor. Aceasta reprezinta doar o copie care va fi memorata in alt obiect pe care il vom pastra sau nu in lista. Obiectul din functie va fi sters de destructor odata cu iesire din scope.

		
		# Diferenta a doua Polinoame


			- 3.3	Polinom operator -(Polinom p)
				
				- Aceasta metoda supradefineste operatoru "-". Are pasii asemanatori cu metoda sumei polinoamelor(+). Aceasta metoda realizeaza scadearea a doua polinoame si returneaza aceasta scadere prin valoare.
				- Se declara variabila "grad_maxim" care determina gradul maxim dintre obiectul din care apelam metoda si polinomul "p"
				- Se declara vectorul de coeficienti "diferenta_coeficienti" care va memora diferenta coeficientilor dintre cele doua polinoame, acesta este declarat dinamic cu lungimea grad_maxim + 1
				- Se parcurg simultan ambele polinoame(ambii vectori de coeficienti) pana cand se termina cel de lungime minima
				- La fiecare pas i, al i-lea element din vectorul "diferenta_coeficienti" va prelua valoarea diferentei dintre al i-lea element din cele doua polinoame
				- Dupa ce se iese din primul while exista 3 cazuri: cel in care gradele polinoamelor erau egale, cel in care primul are grad mai mare, cel in care al doilea are grad mai mare
				- In cazul in care gradele polinoamelor erau egale atunci diferenta s-a efectuat cu succes
				- In cazul in care primul polinom are gradul mai mare atunci atribuim restul elementelor sale pastrand semnul
				- In cazul in care al doilea polinom are gradul mai mare atunci atribuim restul elementelor sale cu semn schimbat, intrucat acest polinom se afla in dreapta operatiei de scadere(p1 - p2)
				- Intr-un final, avem in variabila "grad_maxim" lungimea vectorului "diferenta_coeficienti" - 1, iar in acest vector avem diferenta coeficientilor
				- Declaram si instantiem un nou obiect. Il initializam cu gradul "grad_maxim" si cu coeficientii din "suma_coeficienti"
				- Efectuam o validare a atributelor folosind metoda "validare_atribute()" astfel incat sa ne asiguram ca gradul polinomului si coeficientii sunt corecti
				- Eliberam zona de memorie alocata in pointerul "suma_coeficienti" folosind delete []
				- Returnam obiectul nou creat care reprezinta diferenta polinoamelor. Aceasta reprezinta doar o copie care va fi memorata in alt obiect pe care il vom pastra sau nu in lista. Obiectul din functie va fi sters de destructor odata cu iesire din scope.					


		# Produsul a doua Polinoame


			- 3.4	Polinom operator *(Polinom p)
					
				- Aceasta metoda supradefineste operatorul "*" si realizeaza produsul a doua polinoame, returnand acest produs prin valoare.
				- Se declara variabila "grad_produs" care memoreaza suma gradelor celor 2 polinoame(daca inmultim un polinom de grad n cu unul cu grad m rezultatul o sa aibe gradul n+m)
				- Se declara un pointer "coeficienti_produs" care aloca dinamic un vector de float-uri de lungime grad_produs + 1(+1 reprezinta termenul liber al polinomului)
				- Initializam fiecare element al acestui vector cu 0, acest lucru o sa ne ajute sa calculam produsul coeficientilor
				- Parcurgem coeficientii primului polinom cu un for care foloseste contorul i. 
				- Pentru fiecare al i-lea coeficient al primului polinom parcurgem al doilea polinomul cu un for care foloseste contorul j
				- Practic inmultim fiecare al i-lea coeficient din primul polinom cu toti coeficientii din al doilea polinom, rezultatul acestei inmultiri o vom pune pe pozitia i+j din vectorul "coeficienti_produs"
				- Pasul anterior este corect, intrucat al i-lea coeficient reprezinta un numar care inmulteste X^i, al j-lea coeficient reprezinta alt numar care inmulteste X^j, inmultind acesti doi coeficienti obtinem ceva* X^(i+j), deci acel ceva trebuie memorat pe pozitia i+j din vectorul rezultat
				- In final cream un nou obiect si il initializam cu gradul = grad_produs si cu coeficientii din "coeficienti_produs"  
				- Efectuam o validare a atributelor folosind metoda "validare_atribute()" astfel incat sa ne asiguram ca gradul polinomului si coeficientii sunt corecti
				- Acest nou obiect reprezinta produsul celor doua polinoame, deci putem sa dezalocam pointerul "coeficienti_produs" si sa returnam obiectul nou creat


4. Cerintele pentru BONUS


		# Operatorul de egalitate ==


			- 4.1	bool operator ==(Polinom &p)
			
				- Aceasta metoda supradefineste operatorul "==" astfel incat sa poata fi aplicat si pe obiecte de tip "Polinom"
				- Aceasta metoda verifica egalitatea dintre doua polinoame si returneaza true daca sunt egale sau fals in caz contrar
				- In primul rand, aceasta metoda verifica daca gradele celor doua polinoame sunt diferite.
				- Avem garantat faptul ca gradele acestor polinoame sunt valide, datorita functiei "validare_atribute()" pe care o apelam oricand adaugam un polinom in lista simplu inlantuita si oricand cream un obiect.
				- In cazul in care gradele sunt egale, parcurgem cu un for coeficientii fiecarui polinom simultan incercand sa gasim primul element care difera si se afla pe aceeasi pozitie in ambii vectori
				- Daca acel element este gasit atunci se returneaza fals, intrucat este suficient sa avem cel putin un coeficient care difera intre cele doua polinoame astfel incat cele doua polinoame sa fie diferite cu totul
				- In schimb, daca atat gradele celor doua polinoame cat si coeficientii lor sunt egale, inseamna ca cele doua polinoame sunt egale si returnam true




		# Operatorul de atribuire a sumei +=

			
			- 4.2	void operator +=(Polinom &p)

				- Aceasta metoda supradefineste operatorul "+=" astfel incat sa poata fi aplicat si pe obiecte de tip "Polinom"
				- Aceasta metoda se foloseste de metoda de adunare a doua polinoame(Punctul 3.2), de constructorul de initializare(Punctul 2.3.5) si de operatorul de atribuire = (Punctul 5.3)
				- Initial declara un obiect local pe care il initializeaza cu toate atributele obiectului care rezulta din suma celor doua polinoame si cu pointerul "urmator" din primul polinom al sumei
				- Acest obiect local nu trebuie validat, intrucat functia de validare a fost apelata in cadrul metodei de suma
				- La sfarsit atribuie primului polinom toate atributele din acest obiect local
				- Practic Obiectul local reprezenta suma celor doua polinoame si pointa catre orice pointa primul polinom, iar la sfarsit am salvat toate aceste atribute in primul polinom



5. Metode ce nu fac parte din cerinta:(utile pentru testarea codului)


		# Operatorul de citire >>


			- 5.1	friend istream& operator >>(istream& in, Polinom& nod)

				- Aceasta functie suprascrie operatorul >> din istream, este o metoda friend pentru ca foloseste obiecte din clasa Polinom si din clasa std
				- La inceput se citeste gradul polinomului. Daca acest grad este negativ sau daca este un numar real atunci nu este unul valid si se incearca citirea sa din nou pana cand se citeste un grad corect(conform definitiei de pe Wikipedia)
				- Dupa care se incearca citirea coeficientiilor incepand cu termenul liber si pana la termenul de gradul citit de la tastatura
				- Pentru citirea coeficientilor se aloca un vector dinamic de coeficienti
				- Dupa citirea coeficientilor se apeleaza functia cin.get() pentru a elibera Buffer-ul in caz ca este necesar
				- Se creaza un obiect intermediar care sa fie initializat cu gradul si coeficientii cititi de la tastatura
				- Se apeleaza metoda "validare_atribute()"(Punctul 5.4) pentru a efectua o validare a gradului si a coeficientilor citit de la tastatura
				- La sfarsit se copiaza acest obiect intermediar in obiectul din care noi am apelat aceasta citire.
				- Dupa iesirea din functie obiectul intermediar va fi sters de destructor, insa atributele copiate raman salvate in polinomul pentru care am apelat aceasta functie, acesta fiind transmis prin referinta
				- Se dezaloca vectorul alocat dinamic prin folosirea lui delete []
				- Metoda returneaza un alt flux istream care sa faciliteze citirea a mai multor tipuri de date folosind >>


	
		# Operatorul de afisare <<


			- 5.2	friend ostream& operator <<(ostream& out, Polinom& nod)
			
				- Aceasta metoda suprascrie operatorul de afisare << din ostream, este o metoda friend pentru ca foloseste obiecte din clasa Polinom si din clasa std
				- Aceasta metoda este putin cam complexa de explicat, intrucat foloseste multe "if-else"-uri tocmai pentru a scrie coeficientii sub forma unui Polinom matematic
				- Prin scriere sub forma de polinom matematic intelegem faptul ca atunci cand un coeficient este egal cu 1 sau -1, acesta nu se scrie, X^1 se scrie X, etc. 
				- Aceste reguli nu merita explicate in README, intrucat complixatatea afisarii ramane O(n), unde n reprezinta lungimea vectorului de coeficienti.
				- Merita insa mentionat faptul ca exista o optimizare la inceput, anume faptul ca daca un polinom are gradul n, dar cel putin ultimul sau coeficient(cel de grad n) este egal cu 0, atunci polinomul are gradul <=n
				- Aceasta optimizare practic foloseste un while care se mentine atat timp cand ultimii coeficienti sunt egali cu 0, de indata ce se intalneste primul coeficient(numarand de la sfarsitul vectorului de coeficienti) care sa fie nenul, atunci Polinomul va fi de grad egal cu pozitia acelui coeficient in vectorului de coeficienti
					Ex: 0*X^3 + 0*X^2 + X nu este un polinom de grad 3, ci de grad 1
				- Optimizarea descrisa mai sus nu apare in corpul acestei functii, ci este deja implementata in functia "validare_atribute()" (Punctul 5.4)
				- Exista cazul in care toti coeficientii sunt nuli(daca asa a fost tastat vectorului la citire), caz in care se va afisa 0
				- Pentru restul cazurilor am fost atent sa omit scrierea inutila a coeficientilor egali cu 1 sau -1 si a puterilor 1 si 0 


		# Operatorul de atribuire =


			- 5.3	Polinom& operator =(Polinom &p)

				- Aceasta metoda suprascrie operatorul de atribuire = astfel incat sa aibe efect si asupra obiectelor de tip "Polinom"
				- La inceput copiaza in atributul "grad" valoarea gradului din "p", folosind un getter scris in definitia clasei
				- Dupa care aloca in "coeficienti" un vector dinamic de lungime grad+1, stergand, daca este cazul, vectorul vechi astfel incat sa nu existe un memory leak in heap
				- Dupa care copiaza toate elementele din vectorul de coeficienti din p in vectorul alocat anterior, element cu element folosind getterul "get_coeficient_k()"
				- La sfasrsit atribuie pointerului "urmator" adresa din pointerul din p folosind getterul "get_urmator()"
				- Se returneaza obiectul folosind pointerul "this" astfel incat sa se poata realiza atribuire multiple(inlantuite)

			- 5.4	void validare_atribute()
				
				- Aceasta metoda are rolul de a verifica daca gradul tastat este adevarat pentru coeficientii dati
				- Mai exact, pentru a evita cazurile in care spre exemplu ni se zice ca gradul unui polinom este 2 iar acesta arata de forma 0*X^2 + X + 1(nu este de gradul 2, este de gradul 1)
				- La inceput, se face o verificare generala in care se verifca daca coeficientul de grad maxim este nul, in caz ca este atunci se va scadea gradul pana cand se intalneste un coeficient nenul luand coeficientii in ordinea descrescatoare a gradului
				- In cazul in care verificarea generala a detectat faptul ca intr-adevar polinomul nu este de gradul specificat, se inlocuiesc coeficientii cu unii mai adecvati.
				- Daca in schimb gradul era corect din prima functia se incheia, nu mai este nimic de facut
				- In schimb, pentru a inlocui coeficientii initiali se aloca dinamic un alt vector de data asta de gradul corect + 1
				- Se realizeaza copierea element cu element din vectorul initial in noul vector incepand de la termenul liber si pana la coeficientul de grad maxim care este si nenul 
				- Se sterge vechiul vector, intrucat nu mai avem nevoie de el si nu ne dorim sa avem un memory leak
				- Se aloca un nou vector dinamic pentru atributul "coeficienti" de aceeasi lungime ca cel alocat anterior si se realizeaza din nou copierea element cu element
				- Practic, am modificat atat gradul cat si coeficientii polinomului pe care doream sa-l verificam si deci putem sa dezalocam vectorul alocat in cadrul functiei
				- Verificarea se incheie, nemai fiind nevoie sa returnam ceva specific


6. Functii pentru prelucrarea listelor simplu inlantuite:

	

		# Functie pentru adaugarea unui nod la sfarsitul listei:


			- 6.1	void adaugare_nod_in_lista(Polinom* (&cap), Polinom &nod)

				- Aceasta functie are ca parametri capul listei simplu inlantuite si polinomul/obiectul pe care dorim sa-l adaugam, amandoi transmisi prin referinta, intrucat dorm sa salvam modificarile si nu dorim sa copiem valorile lor pe stiva
				- Polinomul pe care dorim sa-l adaugam deja are un pointer catre NULL, deci locul acestuia o sa fie la sfarsitul listei
				- Intai se face o verificare, daca lista este vida atunci facem ca, capul sa pointeze direct la polinomul nostru
				- Daca in schimb lista are cel putin un element, se vor parcurge toate nodurile pana la ultimul nod al listei folosindu-ne de un pointer "i"
				- Cream un obiect intermediar pe care il initializam cu exact aceleasi atribute ca cele ale ultimului nod, cu exceptia ca acest obiect intermediar va pointa catre polinomul pe care dorim sa-l adaugam(in loc de NULL, cum facea nodul la care pointa i)
				- Atribuim acest obiect intermediar inapoi nodului catre care pointeaza i
				- La sfarsit toate nodurile raman neschimbate cu exceptia celui la care pointeaza i, acesta acum pointand catre polinomul nou adaugat, iar acest polinom nou adaugat pointeaza catre NULL(sfarsitul listei).
				- De asemenea, obiectul intermediar se va sterge dupa iesire din scope. Nu returnam nimic deci functia va fi de tip void.
 
				

 		# Functie pentru afisarea tuturor nodurilor din lista:


			- 6.2	void afisare_noduri_lista(Polinom* (&cap))

				- Aceasta functie primeste ca parametru capul listei
				- Initial se verifica daca lista este vida, in caz afirmativ se afiseaza un mesaj corespunzator si se iese din functie
				- In caz contrar, se declara un pointer care sa pointeze catre primul nod al listei si un indice pe care il initializam cu 1
				- Se parcurge cu un while prin fiecare nod al listei, la fiecare pas se afiseaza indicele curent care reprezinta pozitia nodului curent in lista, precum si nodul efectiv, incrementandu-se indicele si traversand catre urmatorul nod cu fiecare iteratie


		# Lungimea listei simplu inlantuite

	
			- 6.3	int lungime_lista(Polinom* (&cap))

				- Aceasta functie calculeaza lungimea listei simplu inlantuite care are drept noduri obiecte ale clasei Polinom
				- Ca parametru unic aceasta functie are capul listei
				- Se declara o variabila "lungime" pe care o initializam cu valoarea 0 si in care vom calcula lungimea listei
				- Se declara un pointer "i" care pointeaza catre inceputul listei(primul nod)
				- Folosind o structura while se parcurge lista din nod in nod folosind contorul i, la fiecare iteratie se incrementeaza "lungime" pana cand i pointeaza catre sfarsitul listei(NULL)
				- La sfarsit se returneaza "lungime" care reprezinta lungimea efectiva a listei(numarul de noduri)



		# Stergerea unui nod din lista

			- 6.4	void stergere_nod_din_lista(Polinom* (&cap), int indice)

				- Aceasta functie sterge nodul de pe pozitia "indice" din lista care are capul listei in pointerul "cap"
				- Din moment ce avem garantat faptul ca indicele nostru este din range-ul [1, lungime_lista(cap)], aceasta garantie fiind data de functia selectare_indici_polinoame() (Punctul 6.6)
				- Putem sa presupunem ca daca lungimea listei este 1, atunci singurul nod pe care putem sa-l stergem este chiar primul, deci cap va pointa catre NULL
				- Exista si cazul in care nodul pe care vrem sa-l stergem este chiar primul dintr-o lista de lungime >=2. In acest caz, tot ce facem este sa modificam capul listei astfel incat sa pointeze direct la al doilea nod al listei.
				- In schimb, daca lungimea listei este >=2, mergem pe cazul din "else", anume cel in care ne declaram 2 pointeri "nod_curent" si "nod_anterior" si o variabila contor pe care o numim "j"
				- O sa folosim "nod_curent" pentru a itera printre nodurile listei si facem ca "nod_anterior" sa pointeze catre nodul imediat anterior celui catre care pointeaza "nod_curent" in lista
				- Folosind structura while, o sa iteram printre toate nodurile listei pana cand ajungem la indicele dorit indicat in parametrul "indice"
				- Avem garantat faptul ca indicele din "indice" este cel mult egal cu lungimea listei, datorita functiei "selectare_indici_polinoame()" (Punctul 6.6)
				- Dupa ce se iese din lista, avem in "nod_curent" nodul pe care vrem sa-l stergem, in "nod_anterior" nodul imediat anterior nodului din "nod_curent" in lista
				- Cream un nou obiect numit "Obiect_Nou", care sa aibe toate atributele din "nod_anterior", cu modificarea ca atributul "urmator" va pointa catre ce pointeaza obiectul din "nod_curent"
				- Practic facem ca nodul anterior celui pe care vrem sa-l stergem sa nu mai pointeze catre cel pe care vrem sa-l stergem ci sa pointeze direct la nodul urmator celui pe care vrem sa-l stergem
				- Ca sa salvam aceasta modificare, facem ca Obiectul din "nod_anteriror" sa preia toate atributele din "Obiect_Nou"
				- Dupa iesirea din functie Obiect_Nou se va sterge cu ajutorul destructorului, iar obiectul din "nod_curent" nu mai este accesibil de noi(intrucat nu mai avem niciun pointer care pointeaza catre el)
				- Nodul din "nod_curent" nu ramane pierdut in memorie(nu avem un memory leak), intrucat acesta in sine a fost declarat tot intr-o functie la un moment dat, deci se afla tot pe stiva.
				- Odata ce comanda "STOP" se va apela, toate obiectele declarate pe stiva se vor sterge cu ajutorul destructorului scris la Punctul 2.4.1
				- Bineinteles, puteam sa apelam si noi pe moment destructorul manual, insa acest lucru nu reprezinta un "good practice".
				
			
		# Stergerea duplicatelor din lista
	
			- 6.5	void stergere_duplicate_din_lista(Polinom* (&cap),int &caz)


				- Aceasta functie sterge toate duplicatele dintr-o lista de polinoame, polinoamele egale fiind considerate duplicate 
				- Ca parametrii aceasta functie primeste capul listei si o variabila de tip int numita "caz" care indica cazul abordat
				- In cazul in care caz == 1 inseamna ca se vor sterge toate duplicatele in afara de cel initial(se pastreaza originalul si se elimina duplicatele)
				- In cazul in care caz == 2 inseamna ca stergem si polinomul original cu tot cu duplicatele
				- La inceput se verifica daca lungimea listei(numarul de noduri/polinoame din lista) este de cel putin 2, daca nu este inseamna ca nu avem cum sa avem duplicate
				- Daca in schimb avem minim 2 noduri atunci trecem in "else"
				- Ne declaram un pointer catre un polinom numit "i" si 2 variabile contor, o variabila de tip flag(semafor) si o variabila care sa retina lungimea curenta a listei
				- Planul este sa iteram prin lista folosind 2 pointeri si pentru fiecare al i-lea nod al listei sa cautam prin toate nodurile incepand cu i+1 si pana la sfarsitul listei daca exista duplicate si sa le stergem
				- Se declara alt pointer j si facem ca j sa fie nodul care vine imediat dupa i.
				- In cazul in care am gasit 2 noduri egale stergem nodul pointat de j, decrementam al doilea contor si lungimea listei si incrementam variabila semafor
				- Dupa ce am sters toate duplicatele lui i incepand de pe pozitia i+1 si pana la sfarsitul listei, daca suntem in cazul al doilea(caz == 2) atunci trebuie sa stergem si nodul pointat de i, asta daca s-au gasit duplicate pentru i(daca ok!=0)
				- Dupa caz se pastreaza/se sterge nodul pointat de i si se incrementeaza/decrementeaza indice_i dupa caz, pastrandu-se ordinea in functie de stergeri
				- Cum functia nu returneaza nimic, tipul acesteia este void

		
		# Selectarea indicilor din lista de polinoame		
	
			- 6.6	void selectare_indici_polinoame(int numar_indici_de_selectat, float* (&vector_de_indici), Polinom* (&cap))


				- Aceasta functie este mai mult folosita pentru evitarea scrierii acelorasi linii de cod de mai multe ori
				- Aceasta functie citeste de la tastatura doi indici care reprezinta pozitiile polinoamelor in lista				- 
				- Necesitatea acestei functii este datorata interactivitatii dintre utilizator si consola
				- Ca parametrii functia are o variabila care indica numarul de indici ce trebuie trastati.
				- Acest numar poate fi egal cu 1 sau cu 2, intrucat avem situatii in care necesitam un singur indice(comenzile VALUE, GRAD),iar alte situatii in care avem nevoie de 2(comenzile SUM, SUB, PROD)
				- In functie de caz se afiseaza mesajele corespunzatoare si pentru ambele cazuri se afiseaza lista polinoamelor pentru a facilita vizualizarea optiunilor din care utilizatorul poate alege
				- Se citesc cei doi indici de la tastatura si se declara o variabila de tip flag(semafor)
				- Bineinteles, trebuie tratat si cazul in care utilizatorul tasteaza indici gresiti(care depasesc numarul de polinoame adaugati pana in momentul respectiv in lista)
				- In acest caz se intra intr-un while care nu se opreste decat pana cand se tasteaza o pereche de indici corecta
				- Astfel, am evitat un caz in care am fi avut indici gresiti care duceau la noduri care nu exista in lista
				- La sfarsit nu returnam nimic, intrucat modificarile au fost salvate in vectorul de indici transmis ca parametru


		# Cautarea unui nod in lista simplu inlantuita

			- 6.7	Polinom& cautare_nod_in_lista(Polinom* (&cap),int indice)


				- Aceasta functie cauta si returneaza al indice-lea nod din lista simplu inlantuita
				- Se declara un pointer catre capul listei si variabila contor care reprezinta pozitia nodului curent al listei
				- Cat timp variabila nu am ajuns la al indice-lea nod din lista iteram prin fiecare nod
				- Odata ce am ajuns la al indice-lea nod din lista, avand garantia ca acel indice este cel mult egal cu lungimea listei, aceasta garantie fiind data de functia "selectare_indici_polinoame()" (Punctul 6.6)
				- Putem sa returnam nodul de pe acea pozitie

		# Functie de intrabare pentru adaugarea unui polinom in lista

			- 6.8	void intrebare_adaugare_polinom(int indice,Polinom &obiect_de_adaugat,Polinom* (&cap))

				
				- Aceasta functie este in special folositoare pentru metodele de adunare, scadere si inmultire a polinoamelor
				- Aceasta functie practic are rolul de a intreba utilizatorul daca doreste sa salveze rezultatul operatiilor anterior mentionate ca fiind noi obiecte/noduri ale listei
				- Ca parametrii are un indicator care indica in ce caz ne aflam(cazul sumei, diferentei sau a produsului),
				- obiectul in sine pe care dorim sa-l adaugam, transmis prin referinta si nu prin valoare si capul listei
				- La inceput ne declaram doua siruri de caractere, unul in care memoram raspunsul utilizatorului, iar altul in care determinam un vector de cuvinte care difera in functie de cazul in care ne aflam
				- Se citeste raspunsul utilizatorului
				- In cazul in care raspunsul utilizatorului nu este unul valid se intra in structura while si se insista sa ni se ofere un raspuns valid
				- Odata ce s-a dat un raspuns valid se iese din while
				- In cazul in care raspunsul a fost "DA" atunci se adauga polinomul ca fiind ultimul nod din lista
				- Se afiseaza mesajele corespunzatoare si se iese din functie fara sa se returneze nimic(void)


7. Functie pentru rularea programului

		

		# Descriere generala

			- 7.1	void rulare_program(Polinom* cap)
			
				- Aceasta functie este utilizata pentru a rula efectiv toate functiile de pana acum
				- Ca parametru unic are capul listei, intrucat orice am vrea sa facem avem nevoie sa putem accesa lista noastra de polinoame
				- Principul acestei functii recursive este de a citi o comanda si in functie de aceasta comanda sa intram intr-un caz specific
				- Dupa ce efectuam instrcuctiunile din acel caz functia se apeleaza recursiv si se repeta tot procedeul pana cand comanda tasta este "STOP"
				- Pentru citirea comenzii se foloseste un sir de caractere declarat static si local
				- Pentru determinarea cazului se foloseste functia strcmp din cadrul librariei cstring incluse in Punctul 1


		# Comanda pentru citirea si adaugarea unui polinom in lista


			-  7.2	Cazul "ADD"

				- Se declara un obiect local
				- Se citeste acest obiect local folosind operatorul >>(Punctul 5.1)
				- Se adauga acest polinom citit in lista si se afiseaza un mesaj de confirmare
				- Se apeleaza recursiv functia
				- Cum functia este apelata din nou, obiectul citit ramane pe stiva pana cand se incheie recurenta functiei
			
		# Comanda pentru stergerea unui polinom din lista
		
		
			- 7.3	Cazul "DELETE"


				- Intrucat dorim sa stergem un polinom, avem nevoie sa alegem unul folosind indicele(pozitia in lista)asociat fiecarui polinom
				- Pentru a face ca utilizatorul sa tasteze polinomul dorit folosim functia "selectare_indici_polinoame()"(Punctul 6.6)
				- Intrucat avem un singur indice de ales ne declaram un vector de un singur element, acesta trebuie insa alocat dinamic pentru a putea fi transmis ca parametru functiei
				- In cazul in care am gasit un indice valid, stergem polinomul de pe acea pozitie
				- Afisam un mesaj de confirmare si eliberma buffer-ul daca este cazul folosind cin.get()
				- In ambele cazuri stergem vectorul alocat dinamic si apelam functia recursiv
		

		# Comanda pentru determinarea sumei dintre doua polinoame


			- 7.4	Cazul "SUM"

				- Se determina indicii folosind un vector alocat dinamic cu 2 elemente si functia "selectare_indici_polinoame()" (Punctul 6.6)
				- In cazul in care s-au gasit 2 indici valizi se declara 2 obiecte de tip polinom care reprezinta de fapt referinte la obiectele de indicii respectivi
				- Aceste 2 referinte reprezinta cele 2 obiecte selectate
				- Se declara un al treilea obiect care sa memoreze suma celor 2 referinte folosind operatorul + de insumare(Punctul 3.2)
				- Se afiseaza suma, se elibereaza bufferul si se apeleaza functia de interogare pentru adaugarea polinomului in lista, anume functia "intrebare_adaugare_polinom()"(Punctul 6.8)
				- Se dezaloca vectorul de indici alocat dinamic si se apeleaza functia recursiv



		# Comanda pentru determinarea sumei dintre doua polinoame si atribuirea acesteia primului polinom


			- 7.4	Cazul "SUM REPLACE"

				- Se determina indicii folosind un vector alocat dinamic cu 2 elemente si functia "selectare_indici_polinoame()" (Punctul 6.6)
				- In cazul in care s-au gasit 2 indici valizi se declara 2 obiecte de tip polinom care reprezinta de fapt referinte la obiectele de indicii respectivi
				- Aceste 2 referinte reprezinta cele 2 obiecte selectate
				- Se afiseaza un mesaj corespunzator si se foloseste operatorul += pentru calcularea si atribuirea sumei dintre cele doua polinoame(Punctul 4.2)			
				- Se afiseaza suma si se elibereaza bufferul 
				- Se dezaloca vectorul de indici alocat dinamic si se apeleaza functia recursiv






		# Comanda pentru determinarea diferentei dintre doua polinoame


			- 7.6	Cazul "SUB"

				- Se determina indicii folosind un vector alocat dinamic cu 2 elemente si functia "selectare_indici_polinoame()" (Punctul 6.6)
				- In cazul in care s-au gasit 2 indici valizi se declara 2 obiecte de tip polinom care reprezinta de fapt referinte la obiectele de indicii respectivi
				- Aceste 2 referinte reprezinta cele 2 obiecte selectate
				- Se declara un al treilea obiect care sa memoreze diferenta celor 2 referinte folosind operatorul - de insumare(Punctul 3.3)
				- Se afiseaza diferenta, se elibereaza bufferul si se apeleaza functia de interogare pentru adaugarea polinomului in lista, anume functia "intrebare_adaugare_polinom()"(Punctul 6.8)
				- Se dezaloca vectorul de indici alocat dinamic si se apeleaza functia recursiv



		# Comanda pentru determinarea produsului dintre doua polinoame


			- 7.7	Cazul "PROD"

				- Se determina indicii folosind un vector alocat dinamic cu 2 elemente si functia "selectare_indici_polinoame()" (Punctul 6.6)
				- In cazul in care s-au gasit 2 indici valizi se declara 2 obiecte de tip polinom care reprezinta de fapt referinte la obiectele de indicii respectivi
				- Aceste 2 referinte reprezinta cele 2 obiecte selectate
				- Se declara un al treilea obiect care sa memoreze produsul celor 2 referinte folosind operatorul * de insumare(Punctul 3.4)
				- Se afiseaza produsul, se elibereaza bufferul si se apeleaza functia de interogare pentru adaugarea polinomului in lista, anume functia "intrebare_adaugare_polinom()"(Punctul 6.8)
				- Se dezaloca vectorul de indici alocat dinamic si se apeleaza functia recursiv


		# Comanda pentru calcului valorii unui polinom intr-un punct citit de la tastatura

			
			- 7.8	Cazul "VALUE"

				- Se citeste indicele dorit folosind un vector alocat dinamic si functia "selectare_indici_polinoame()" (Punctul 6.6)
				- Se citeste punctul dorit si se declara o referinta catre obiectul de indicele respectiv 
				- Se afiseaza valoarea polinomului selectat in punctul citit, se elibereaza buffer-ul si se dezaloca vectorul alocat dinamic
				- Se apeleaza recursiv functia

		
		# Comanda pentru stergerea duplicatelor din lista de polinoame


			- 7.9	Cazul "DUPLICATE"


				- Se interogheaza utilizatorul pentru a afla daca doreste sa pastreze sau nu polinoamele originale(care au in acelasi timp duplicate)
				- Se memoreaza raspunsul intr-un sir de caractere si se verifica daca acest raspuns este valid, daca nu este se insista pana ce se tasteaza unul valid
				- Se declara o variabila "caz"
				- In cazul in care raspunsul este "DA", caz ia valoarea 1
				- In cazul in care raspunsul este "NU", caz ia valoarea 2 
				- Se apeleaza functia "stergere_duplicate_din_lista()" (Punctul 6.5) avand ca parametrii capul listei si variabila "caz"
				- Se afiseaza un mesaj de confirmare precum si nodurile ramase dupa stergere si se apeleaza functia recursiv
	

		# Comanda pentru afisarea polinoamelor din lista

	
			- 7.10	Cazul "TOTAL"

			
				- Se apeleaza functia "afisare_noduri_lista()" (Punctul 6.2) avand ca parametru transmis capul listei
				- Se apleaza functia recursiv


		# Comanda pentru afisarea numarului total de polinoame din lista


			- 7.11	Cazul "NUMAR"

				- Se afiseaza un mesaj corespunzator si se afiseaza lungimea listei prin apelarea functiei "lungime_lista()" (Punctul 6.3) avand ca parametru transmis capul listei
				- Se apeleaza functia recursiv


		# Comanda pentru afisarea gradului unui polinom

			
			- 7.12	Cazul "GRAD"

				- Se selecteaza indicii doriti folosind functia "selectare_indici_polinoame()" (Punctul 6.6)
				- Se declara o referinta catre obiectul de indicele tastat, se acceseaza obiectul respectiv prin intermediul functiei "cautare_nod_in_lista()" (Punctul 6.7)
				- Se afiseaza un mesaj corespunzator si se afiseaza gradul polinomului referentiat folosind get_grad()
				- Se elibereaza buffer-ul, se dezaloca vectorul alocat dinamic pentru functia de selectare a indicilor si se apeleaza functia recursiv
				

		# Comanda pentru verificarea si afisarea egalitatii intre doua polinoame

			
			- 7.13	Cazul "EGALE"

				- Se selecteaza indicii tastati si obiectele de indicii respectivi
				- Se verifica si se afiseaza daca sunt egali, determinand aceasta afirmatie prin utilizarea operatorului == (Punctul 4.1)
				- Se elibereaza buffer-ul, se dezaloca vectorul dinamic folosit pentru selectarea indicilor si se apeleaza functia recursiv 
				

		# Comanda pentru oprirea programului

			- 7.14	Cazul "STOP"
				

				- Se apeleaza instructiunea return
				- Odata cu aceasta instructiune se porneste un lant de inchidere a tuturor apelurilor recursive pe care le-am facut de-a lungul utilizarii programului
				- Cu fiecare inchidere de apel se apeleaza destructorul pentru fiecare obiect delcarat pe stiva
				- Se elibereaza tot ce se afla pe stiva, in heap se elibereaza memoria pe parcurs ce se apeleaza destructorii
				- Se intoarce in main unde ne ramane o singura variabila pe stiva, anume pointerul catre capul listei care acum este vida
	
8. Functia main()
	

		# Instructiunile de utilizare a programului

			- Sunt afisate printr-o insiruire de cout-uri toate instructiunile/comenzile pentru utilizarea acestui program in consola

		# Pregatirea rularii programului

			- Se declara un pointer "cap" care pointeaza catre NULL si poate pointa catre obiecte din clasa "Polinom"
			- Aceasta variabila pointer va fi folosita pentru a crea lista simplu inlantuita pentru obiectele clasei "Polinom"
			- Se apeleaza functia de rulare a programului si se incepe rularea efectiva a programului care se va termina odata ce se tasteaza comanda "STOP"
			- Odata ce s-a iesit din functia "rulare_program()", se sterge orice ar fi ramas in pointerul cap(daca este diferit de NULL) si se iese din main, odata cu asta se incheie tot programul

