#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath> // pentru rotunjiri
#include <random> // pentru cerinta bonus: "Folosirea unei biblioteci utilitare"

using namespace std;

// Clasa Template
template<typename T>
class Magazin {
private:
    vector<T> produse;
    static Magazin<T>* instance;

    // Constructor privat pentru a preveni instanțierea din afara clasei
    Magazin() {}

public:
    // Metodă statică pentru a obține o singură instanță a clasei
    static Magazin<T>* getInstance() {
        if (instance == nullptr) {
            instance = new Magazin<T>();
        }
        return instance;
    }

    void adaugaProdus(const T& produs) {
        produse.push_back(produs);
    }

    void afisareProduse() {
        for (const auto& produs : produse) {
            afisareDescriere(produs); // Apelăm funcţia template creată mai jos
            cout << endl;
        }
    }
};

template<typename T>
Magazin<T>* Magazin<T>::instance = nullptr;

// Funcţia Template
template<typename T>
void afisareDescriere(const T& obiect) {
    obiect.descriere();
}

class Joc {
protected:
    static int numarJocuri; // variabila membru statica
    string nume;
    float pret;
public:
    Joc(const string& nume, float pret): nume(nume), pret(pret) {
        numarJocuri++; // incrementam numarul total de jocuri
    }
    virtual ~Joc() {numarJocuri--;}

    virtual void descriere() const {
        cout << "Acesta este un joc generic.\n";
        cout << "Se numeste: "<<nume<<endl;
        cout << "Si costa: "<<pret<<" euro!\n";
    }
    string getNume() const {
        return nume;
    }

    static int getNumarJocuri() { // metoda statica
        return numarJocuri;
    }
};

int Joc::numarJocuri = 0; // initializam variabila statica cu valoarea 0

class JocSingleplayer : public Joc {
protected:
    string descriere_singleplayer;
public:
    JocSingleplayer(const string& nume, float pret, const string& descriere): Joc(nume, pret), descriere_singleplayer(descriere) {}
    virtual ~JocSingleplayer() {}

    virtual void descriere() const override {
        cout << "Acesta este un joc singleplayer.\n";
        cout << "Se numeste: "<<nume<<endl;
        cout<<"Descrierea: "<<descriere_singleplayer<<endl;
        cout << "Si costa: "<<pret<<" euro!\n";
    }
};

class JocMultiplayer : public Joc {
protected:
    vector<string> platforme;
public:
    JocMultiplayer(const string& nume, float pret, const vector<string>& platforme): Joc(nume, pret), platforme(platforme) {}
    virtual ~JocMultiplayer() {}

    virtual void descriere() const override {
        cout << "Acesta este un joc multiplayer.\n";
        cout << "Se numeste: "<<nume<<endl;
        cout << "Este disponibil pe urmatoarele platforme: ";
        int max = platforme.size();
        for(int index = 0; index < max; index++)
            if(index != max - 1)
                cout << platforme[index] << ", ";
            else cout << platforme[index];
        cout << endl << "Si costa: "<<pret<<" euro!\n";
    }
};

class JocFps : public Joc {
protected:
    string descriere_fps;
    vector<string> platforme;
public:
    JocFps(const string& nume, float pret, const string& descriere, const vector<string>& platforme): Joc(nume, pret), descriere_fps(descriere), platforme(platforme) {
        if (platforme.empty()) {
            throw invalid_argument("Lista de platforme nu poate fi goală!");
        }
    }
    virtual ~JocFps() {}

    void descriere() const override {
        cout << "Acesta este un joc FPS.\n";
        cout << "Se numeste: "<<nume<<endl;
        cout<<"Descrierea: "<<descriere_fps<<endl;
        cout << "Este disponibil pe urmatoarele platforme: ";
        int max = platforme.size();
        for(int index = 0; index < max; index++)
            if(index != max - 1)
                cout << platforme[index] << ", ";
            else cout << platforme[index];
        cout << endl << "Si costa: "<<pret<<" euro!\n";
    }
};

class Interfata {
public:
    virtual void descriere() = 0;
    virtual void afisare() = 0;
    virtual ~Interfata() {}
};

class InterfataPremium {
public:
    virtual float calculeazaDiscount() = 0;
    virtual void afisareDiscount() = 0;
    virtual ~InterfataPremium() {}
};

class Client {
protected:
    string nume;
    string adresaEmail;
public:
    Client(const string& nume, const string& adresaEmail): nume(nume), adresaEmail(adresaEmail) {}
    virtual ~Client() {}

    virtual void afisare() {
        cout << "Nume client: " << nume << "\nAdresa email: " << adresaEmail << "\n";
    }
};

class ClientPremium : public Client, public InterfataPremium {
protected:
    float discount;
    static int numarClienti; // variabila membru statica
public:
    ClientPremium(const string& nume, const string& adresaEmail, float discount): Client(nume, adresaEmail), discount(discount) {
        numarClienti++; // incrementam numarul total de clienti premium
    }
    virtual ~ClientPremium() {}

    float calculeazaDiscount() override {
        if (discount < 0) {
            throw out_of_range("Discountul nu poate fi negativ.");
        }
        return discount * 0.9;
}

void afisareDiscount() override {
try {
cout << "Discount client premium: " << calculeazaDiscount() << "\n";
}
catch(out_of_range& e) {
cout << "Eroare: " << e.what() << "\n";
}
}

void afisare() override {
Client::afisare();
afisareDiscount();
}

static int getNumarClienti() { // metoda statica
return numarClienti;
}

static void resetNumarClienti() { // metoda statica
numarClienti = 0;
}
};

int ClientPremium::numarClienti = 0; // initializam variabila statica cu valoarea 0

class ExceptieJoc : public exception
{
    string msg;
public:
    ExceptieJoc(const string& numeJoc) : msg("Jocul " + numeJoc + " nu a fost gasit în baza de date.") {}
    const char* what() const noexcept override {
        return msg.c_str();
    }

    Joc gasesteJoc(const string& numeJoc, const vector<Joc*>& jocuri)
    {
        for(auto joc : jocuri)
            if (joc->getNume() == numeJoc)
                return *joc;
        throw ExceptieJoc(numeJoc);
    }

    // Exemplu de downcasting:
    JocFps& gasesteJocu(const string& numeJoc, const vector<Joc*>& jocuri) {
        for(auto joc : jocuri)
            if (joc->getNume() == numeJoc) {
                JocFps* jocFps = dynamic_cast<JocFps*>(joc);
                if (jocFps == nullptr)
                    throw ExceptieJoc(numeJoc);
                else
                    return *jocFps;
            }
        throw ExceptieJoc(numeJoc);
    }
};

int main()
{
    cout << "Testare cod (cerinte):\n\n";

    // Acest bloc try...catch încearcă să creeze un obiect JocFps și să apeleze metoda descriere().
    // Dacă apare o excepție de tipul std::exception (sau orice alt tip specificat), aceasta va fi prinsă în blocul catch și se va afișa un mesaj corespunzător.
    try {
        JocFps joc("Call of Duty", 59.99, "Un joc de actiune si shooter FPS", {"PC", "Xbox", "PlayStation"});
        joc.descriere();
    }
    catch (const exception& e) {
    cout << "A aparut o exceptie: " << e.what() << "\n";
    }

    // Acest bloc try...catch încearcă să creeze un obiect ClientPremium și să apeleze metoda afisare().
    // Dacă apare o excepție de tipul std::exception (sau orice alt tip specificat), aceasta va fi prinsă în blocul catch și se va arunca o altă excepție de tipul std::runtime_error.
    // Această excepție poate fi prinsă într-un alt bloc try...catch sau poate fi lăsată să fie prinsă de sistemul de operare.
    try {
        ClientPremium client("John Doe", "johndoe@gmail.com", 0.2);
        client.afisare();
    }
    catch (const exception& e) {
        cout << "A aparut o exceptie: " << e.what() << "\n";
        throw runtime_error("Exceptie re-aruncata din blocul catch.");
    }

    // Testare cerintă static
    Joc joc7("Joc 1", 59.99);
    Joc joc8("Joc 2", 39.99);
    Joc joc9("Joc 3", 49.99);
    cout << "Numarul total de jocuri: " << Joc::getNumarJocuri() << endl;
    ClientPremium client5("Client 5", "client5@example.com", 0.15);
    ClientPremium client6("Client 6", "client6@example.com", 0.2);
    cout << "Numarul total de clienti premium: " << ClientPremium::getNumarClienti() << endl;
    ClientPremium::resetNumarClienti();
    cout << "Numarul total de clienti premium dupa resetare: " << ClientPremium::getNumarClienti() << endl;

    cout << "\nCreare obiecte (baza de date):\n\n";
    //Initializare obiect Magazin
    Magazin<Joc>* magazin = Magazin<Joc>::getInstance();
    magazin->adaugaProdus(joc7);
    magazin->afisareProduse();

    // Cerinţa Random
    default_random_engine generator;
    uniform_real_distribution<float> repartitie(10.0, 69.99);

    //Initializare obiect Joc
    string numeJoc;
    float pretJoc = repartitie(generator); // setăm pretul jocului ca un nr. random
    pretJoc = floor(pretJoc * 100) / 100; // rotunjim nr. obţinut
    cout << "Introduceti numele jocului: ";
    cin.ignore(0);
    getline(cin, numeJoc);
    cin.ignore(0, '\n');
    unique_ptr<Joc> jocPtr = make_unique<Joc>(numeJoc, pretJoc); // smart pointer

    //Initializare obiect JocSingleplayer
    string numeJocSingleplayer, descriereSingleplayer;
    float pretJocSingleplayer = repartitie(generator); // setăm pretul jocului singleplayer ca un nr. random
    pretJocSingleplayer = floor(pretJocSingleplayer * 100) / 100; // rotunjim nr. obţinut
    cout << "Introduceti numele jocului singleplayer: ";
    cin.ignore(0);
    getline(cin, numeJocSingleplayer);
    cin.ignore(0, '\n');
    cout << "Introduceti descrierea jocului singleplayer: ";
    cin.ignore(0);
    getline(cin, descriereSingleplayer);
    cin.ignore(0, '\n');
    unique_ptr<JocSingleplayer> jocSingleplayerPtr = make_unique<JocSingleplayer>(numeJocSingleplayer, pretJocSingleplayer, descriereSingleplayer); // smart pointer

    //Initializare obiect JocMultiplayer
    string numeJocMultiplayer, platforma;
    float pretJocMultiplayer = repartitie(generator); // setăm pretul jocului multiplayer ca un nr. random
    pretJocMultiplayer = floor(pretJocMultiplayer * 100) / 100; // rotunjim nr. obţinut
    vector<string> platforme;
    int numarPlatforme;
    cout << "Introduceti numele jocului multiplayer: ";
    cin.ignore(0);
    getline(cin, numeJocMultiplayer);
    cin.ignore(0, '\n');
    cout << "Introduceti numarul de platforme suportate de joc: ";
    cin >> numarPlatforme;
    cin.ignore();
    for(int i = 0; i < numarPlatforme; i++) {
        cout << "Introduceti platforma " << i+1 << ": ";
        getline(cin, platforma);
        platforme.push_back(platforma);
    }
    cin.ignore(0, '\n');
    unique_ptr<JocMultiplayer> jocMultiplayerPtr = make_unique<JocMultiplayer>(numeJocMultiplayer, pretJocMultiplayer, platforme); // smart pointer

    //Initializare obiect JocFps
    unique_ptr<JocFps> joc_fps; // smart pointer
    try {
    string numeJocFps;
    float pret_joc = repartitie(generator); // setăm pretul jocului fps ca un nr. random
    pret_joc = floor(pret_joc * 100) / 100; // rotunjim nr. obţinut
    string descriere_joc;
    vector<string> platforme_joc;
    cout << "Introduceti numele jocului FPS: ";
    cin.ignore(0);
    getline(cin, numeJocFps);
    cin.ignore(0, '\n');
    cout << "Introduceti descrierea jocului FPS: ";
    getline(cin, descriere_joc);
    cout << "Introduceti platformele pe care ruleaza jocul FPS (separate prin virgula): ";
    string platforme_input;
    getline(cin, platforme_input);
    cin.ignore(0, '\n');
    size_t poz = 0;
    while ((poz = platforme_input.find(',')) != string::npos) {
        platforme_joc.push_back(platforme_input.substr(0, poz));
        platforme_input.erase(0, poz + 1);
    }
    platforme_joc.push_back(platforme_input); // ultima platforma

    joc_fps = make_unique<JocFps>(numeJocFps, pret_joc, descriere_joc, platforme_joc); // smart pointer
    }
    catch (invalid_argument& e) {
        cout << "Eroare: " << e.what() << "\n";
        return 1;
    }

    //Initializare obiect Client
    unique_ptr<Client> client11; // smart pointer
    string nume_client;
    string adresa_email;
    cout << "Introduceti numele clientului: ";
    cin.ignore(0);
    getline(cin, nume_client);
    cout << "Introduceti adresa de email a clientului: ";
    getline(cin, adresa_email);
    cin.ignore(0, '\n');
    client11 = make_unique<Client>(nume_client, adresa_email); // smart pointer

    //Initializare obiect ClientPremium
    unique_ptr<ClientPremium> client_premium; // smart pointer
    try {
        string nume_client_premium;
        string adresa_email_premium;
        float discount_premium = repartitie(generator); // setăm discountul ca un nr. random
        discount_premium = floor(discount_premium * 10) / 10; // rotunjim nr. obţinut
        cout << "Introduceti numele clientului premium: ";
        cin.ignore(0);
        getline(cin, nume_client_premium);
        cout << "Introduceti adresa de email a clientului premium: ";
        getline(cin, adresa_email_premium);
        cin.ignore(0, '\n');
        client_premium = make_unique<ClientPremium>(nume_client_premium, adresa_email_premium, discount_premium); // smart pointer
    }
    catch (out_of_range& e) {
        cout << "Eroare: " << e.what() << "\n";
        return 1;
    }

    cout << "Afisare obiecte:\n\n";
    // Afisare obiecte create:
    cout<<endl;
    jocPtr->descriere();
    cout<<endl;
    jocSingleplayerPtr->descriere();
    cout<<endl;
    jocMultiplayerPtr->descriere();
    cout<<endl;
    joc_fps->descriere();
    cout<<endl;
    client11->afisare();
    cout<<endl;
    client_premium->afisare();
    cout<<endl;
    return 0;
}
