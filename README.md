# Laborator_POO
Prima clasa se numeste **'ListaDeNumere'** si are doua metode supraincarcate numite 'alocare_num'. Clasa primeste un numar intreg 'nr_elem' la initializare, care reprezinta numarul de elemente pe care lista trebuie sa le contina.

In functia 'alocare_num(float *list)' se aloca dinamic un array de tip float cu numarul de elemente dat la initializare si se cere de la utilizator sa introduca valorile fiecarui element al listei prin intermediul fluxului de intrare 'cin'. Aceasta functie este utilizata pentru alocarea unui array de numere reale.

In functia 'alocare_num(int *list)' se aloca dinamic un array de tip int cu numarul de elemente dat la initializare si se cere de la utilizator sa introduca valorile fiecarui element al listei prin intermediul fluxului de intrare 'cin'. In cazul in care un element este mai mic decat 0, acesta va fi transformat in valoarea sa absoluta prin inmultirea cu -1. Aceasta functie este utilizata pentru alocarea unui array de numere intregi.

Clasa are, de asemenea, un membru privat 'num' care retine numarul de elemente si un membru privat 'index_num' care este folosit pentru a itera prin fiecare element al listei in timpul alocarii.

De asemenea, clasa are un friend class 'ListaDeLitere', dar nu este clar ce rol joaca aceasta clasa sau cum este folosita in relatie cu ListaDeNumere.

Clasa are un destructor implicit, care nu face nimic deoarece clasa nu are membri dinamici.


Clasa numita **'ListaDeLitere'**, este conceputa pentru a aloca dinamic un array de caractere prin intermediul metodei 'alocare_lit'. Clasa are trei variabile membre: 'lit', 'index_lit' si 'index_cuv'. 'lit' este numarul total de litere ce trebuie alocate, 'index_lit' este pozitia curenta din array-ul de caractere, iar 'index_cuv' este indexul cuvantului curent din array.

Constructorul clasei primeste ca parametru numarul de elemente din array-ul de numere aflat in clasa ListaDeNumere si aloca dinamic suficient spatiu pentru a contine numarul specificat de caractere (numarul de elemente * 112, unde 112 este lungimea maxima a unui titlu de produs).

Constructorul cu un singur parametru al clasei este folosit pentru a aloca dinamic suficient spatiu pentru a contine toate caracterele necesare dupa ce array-ul de numere a fost convertit in array-ul de litere.

Metoda 'alocare_lit' aloca fiecare caracter introdus de utilizator pana cand se intalneste 'punctul'. Apoi, ea elimina punctul si muta fiecare caracter cu o pozitie la stanga pentru a elimina spatiul gol inaintea punctului. In cele din urma, adauga un caracter newline si un caracter terminator '\0' la sfarsitul array-ului pentru a il termina corect.

Destructorul clasei este gol, deoarece nu sunt necesare actiuni speciale pentru a elibera memoria alocata dinamic.


Clasa numita **'Magazin'** si reprezinta un magazin care vinde jocuri. Clasa contine variabile membre private, care sunt pointeri la caractere (char*) si pointeri la numere in virgula mobila (float*). Variabilele membre sunt urmatoarele:
*  **'nume_magazin'**: reprezinta numele magazinului si este un pointer la caractere.
*  **'lista_jocuri'**: reprezinta lista jocurilor disponibile in magazin si este un pointer la caractere.
*  **'push_nume'**: este un pointer la caractere folosit pentru a citi numele magazinului de la tastatura.
*  **'balanta_de_plata'**: reprezinta balanta de plata a magazinului si este initializata cu 0.
*  **'index_push'**: este un intreg folosit pentru a retine numarul de jocuri pe care utilizatorul doreste sa le adauge la lista de jocuri a magazinului.
*  **'index_pop'**: este un intreg folosit pentru a parcurge lista de jocuri a magazinului.
*  **'lista_preturi'**: reprezinta lista de preturi a jocurilor din magazin si este un pointer la numere in virgula mobila.
*  **'profit'**: reprezinta profitul total al magazinului si este initializat cu 0.
*  **'tva'**: reprezinta TVA-ul total al magazinului si este initializat cu 0.

Clasa contine si un constructor fara parametri si unul cu un parametru intreg a, dar nu este clar din contextul dat la ce sunt folositi acesti constructori. De asemenea, clasa contine si un destructor, care elibereaza memoria alocata dinamic pentru variabilele membre.

Clasa contine mai multe metode publice, care sunt urmatoarele:
*  **'Magazin()'**: este un constructor fara parametri, care citeste de la tastatura numele magazinului si initializeaza variabilele membre pentru lista de jocuri si preturi cu valori default.
*  **'jocuri()'**: este o metoda care solicita utilizatorului sa introduca numarul de jocuri pe care doreste sa le adauge la lista de jocuri a magazinului si apoi solicita introducerea numelor jocurilor prin intermediul unui obiect **'ListaDeLitere'**.
*  **'preturi()'**: este o metoda care solicita introducerea preturilor jocurilor prin intermediul unui obiect **'ListaDeNumere'**.
*  **'afisare_joc()'**: este o metoda care afiseaza numele jocului de pe pozitia **'joc'** din lista de jocuri a magazinului.
*  **'stock()'**: este o metoda care returneaza lista de jocuri a magazinului si **'lungimea'** acesteia prin intermediul parametrului de referinta lungime.
*  **'pret_fara_tva()'**: este o metoda care returneaza lista de preturi a jocurilor din magazin.
*  **'tranzactie_acceptata()'**: este o metoda care adauga la profitul si TVA-ul magazinului valorile primite ca parametri dupa tranzactie.

Clasa Magazin contine si doua metode de supraincarcare: operatorul >> si operatorul <<. Aceste metode sunt folosite pentru a citi si a afisa informatii despre obiectul de tip Magazin.

Operatorul >> este supraincarcat pentru a citi informatii despre jocurile si preturile acestora dintr-un stream de intrare si pentru a le salva in obiectul Magazin corespunzator. In implementarea sa, acest operator creeaza o instanta a clasei ListaDeNumere, care este utilizata pentru a citi preturile jocurilor, iar apoi creeaza o instanta a clasei ListaDeLitere, care este utilizata pentru a citi numele jocurilor. Acest operator este definit ca o functie friend a clasei Magazin, astfel incat poate avea acces la membrii privati ai clasei.

Operatorul << este supraincarcat pentru a afisa informatii despre obiectul Magazin. In implementarea sa, acest operator afiseaza numele magazinului, numarul de jocuri disponibile in stock, numele si pretul fiecarui joc si profitul magazinului. Acest operator este, de asemenea, definit ca o functie friend a clasei Magazin.

Ambele metode de supraincarcare sunt utile pentru a oferi o modalitate comoda de a citi si de a afisa informatii despre obiectele de tip Magazin. Supraincarcarea operatorului >> permite utilizatorului sa introduca informatiile despre jocurile si preturile acestora folosind un stream de intrare standard, cum ar fi std::cin, in timp ce supraincarcarea operatorului << afiseaza aceste informatii intr-un mod frumos si clar. Aceste doua metode ofera, de asemenea, o mai mare flexibilitate in ceea ce priveste interactiunea cu obiectele de tip Magazin.


Clasa **'Client'** este o clasă care descrie un client al unui magazin de jocuri. Ea conține membrii de date cum ar fi: cos_de_cumparaturi, stock, intrebare, cantitatea, numar_produse, index_joc și balanta_cont.

Constructorul clasei primește o referință la obiectul de tip Magazin, iar acesta este utilizat pentru a inițializa 'stock' și pentru a permite clientului să alimenteze contul său. Dacă utilizatorul dorește să alimenteze contul, acesta este întrebat să introducă suma dorită, iar aceasta este stocată în variabila 'balanta_cont'.

Funcția 'cumpara_jocuri()' permite utilizatorului să cumpere jocuri, iar aceasta utilizează obiecte din clasele **'ListaDeNumere'** și **'ListaDeLitere'** pentru a ajuta la alocarea și citirea jocurilor. Funcția 'verificare_stock()' este utilizată pentru a verifica dacă jocurile sunt disponibile în stoc, iar funcția 'cantitate()' este utilizată pentru a permite utilizatorului să modifice cantitatea de jocuri dorite.

Membrii funcționali ai clasei includ funcția 'cos()' care returnează cosul de cumpărături și funcția 'nr_produse()' care returnează cantitatea de jocuri cumpărate. De asemenea, clasa conține și metode de plată cum ar fi plata() și plata_acceptata() care permit utilizatorului să plătească pentru jocurile achiziționate.

Destructorul clasei Client este folosit pentru a dezaloca memoria alocată dinamic în timpul vieții obiectelor de tip Client.

În general, această clasă are un rol important în procesul de achiziționare a jocurilor și gestionarea contului utilizatorului în cadrul unui magazin de jocuri.


**'Checkout'** este o clasă care gestionează procesul de plată pentru un coș de cumpărături. Are mai mulți membri de date private, inclusiv pointeri către matrice de caractere pentru produsele selectate și informații despre stoc, întregi pentru numărul de produse și informații despre comandă și float-uri pentru prețurile produselor, plata totală și plata TVA.

Constructorul primește două obiecte, un obiect "Magazin" și un obiect "Client", și inițializează membrii de date în consecință. Funcția "plata" calculează plata totală iterând peste produse și cantitățile lor respective și apelând funcția "tva" pentru a calcula plata TVA. De asemenea, solicită utilizatorului să introducă un cod de reducere și îl aplică dacă este introdus codul corect. Plata finală este apoi afișată, iar funcția "finalizare_plata" este apelată pentru a finaliza procesul de plată.

Funcția "tva" calculează plata TVA pentru un anumit preț al produsului prin adăugarea a 19% din preț la plata TVA și returnarea noului preț cu TVA adăugată.

Funcția "cod_reducere" solicită utilizatorului să introducă un cod de reducere și verifică dacă se potrivește cu un cod predefinit. Dacă se potrivește, se aplică o reducere de 25% la plata totală.

Funcția "finalizare_plata" verifică dacă soldul clientului este suficient pentru a acoperi plata și actualizează soldul clientului și înregistrările de tranzacții ale magazinului în consecință.

Funcția "get_ordine" extrage informațiile despre comandă din produsele selectate și informațiile despre stoc iterând peste matrice și comparând caracterele. Returnează o matrice de întregi care reprezintă ordinea produselor selectate.

Destructorul clasei Checkout este folosit pentru a dezaloca memoria alocată dinamic în timpul vieții obiectelor de tip Checkout.
