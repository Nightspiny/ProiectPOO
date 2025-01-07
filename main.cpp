#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <set>
using namespace std;

void initializeFiles() {
    ofstream carti("carti.txt", ios::app);
    ofstream utilizatori("utilizatori.txt", ios::app);
    carti.close();
    utilizatori.close();
}

class Publicatie {
public:
    virtual void citire(istream& in) = 0;
    virtual void afisare(ostream& out) const = 0;
    virtual ~Publicatie() {}
};

class Carte: public Publicatie {
protected:
    string titlu, autor, dataReturnare;
    static int contorCarti;
    bool imprumutata;

public:
    Carte(const string& titlu = "", const string& autor = "", bool imprumutata = false, const string& dataReturnare = "")
        : titlu(titlu), autor(autor), imprumutata(imprumutata), dataReturnare(dataReturnare) {
        contorCarti++;
    }

    virtual ~Carte() {
        contorCarti--;
    }

    virtual void citire(istream& in){
        cout<< "Introduceti titlul cartii: ";
        getline(in, titlu);
        cout<< "Introduceti autorul cartii: ";
        getline(in, autor);
        imprumutata = false;
        dataReturnare = "";
    }
    virtual void afisare(ostream& out) const {
        out<< "Titlu: " << titlu << endl;
        out<< "Autor: " << autor << endl;
        out << "Imprumutata: " << (imprumutata ? "Da" : "Nu") << endl;
        if (imprumutata) {
            out << "Data returnare: " << dataReturnare << endl;
        }
    }

    virtual void salvare(ofstream& fout) const {
        fout << titlu << ";" << autor << ";" << imprumutata << ";" << dataReturnare << ";";
    }

    virtual void incarcare(ifstream& fin) {
        getline(fin, titlu, ';');
        getline(fin, autor, ';');
        string imprumutataStr;
        getline(fin, imprumutataStr, ';');
        imprumutata = (imprumutataStr == "1");
        getline(fin, dataReturnare, ';');
    }

    static int getNumarCarti(){
        return  contorCarti;
    }

    const string& getTitlu() const {
        return titlu;
    }

    string getAutor() const {
        return autor;
    }

    bool esteImprumutata() const {
        return imprumutata;
    }

    string getDatareturnare() const {
        return dataReturnare;
    }

    void modificaImprumut(bool status, const string& data = "") {
        imprumutata = status;
        if (status) {
            if (data.empty()) {
                throw invalid_argument("Data returnarii trebuie specificata pentru o carte imprumutata.");
            }
            dataReturnare = data;
        } else {
            dataReturnare = "";
        }
    }

    static bool valideazaData(const std::string& data) {
        if (data.size() != 10 || data[2] != '/' || data[5] != '/') return false;

        for (size_t i = 0; i < data.size(); i++) {
            if ((i != 2 && i != 5) && !isdigit(data[i])) return false;
        }

        int zi = stoi(data.substr(0, 2));
        int luna = stoi(data.substr(3, 2));
        int an = stoi(data.substr(6, 4));

        if (zi <= 0 || zi > 31) return false;
        if (luna <= 0 || luna > 12) return false;
        if (an < 2024) return false;

        return true;
    }

    friend istream& operator>>(istream& in, Carte& carte) {
        carte.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const Carte& carte) {
        carte.afisare(out);
        return out;
    }
};

int Carte::contorCarti = 0;

class CarteFizica: public Carte {
    int stoc;

public:
    CarteFizica(const string& titlu = "", const string& autor = "", bool imprumutata = false, const string& dataReturnare = "", int stoc = 0)
        :Carte(titlu, autor, imprumutata, dataReturnare), stoc(stoc){}

    void citire(istream& in) override {
        Carte::citire(in);
        cout << "Introduceti numarul de exemplare disponibile: ";
        in >> stoc;
        in.ignore();
        if (stoc < 0)
        {
            throw invalid_argument("Stocul nu poate fi negativ!");
        }
    }

    void salvare(ofstream& fout) const override {
        fout << "CarteFizica;";
        Carte::salvare(fout);
        fout << stoc << endl;
    }

    void incarcare(ifstream& fin) override {
        Carte::incarcare(fin);
        string stocStr;
        getline(fin, stocStr);
        stoc = stoi(stocStr);
    }

    int getStoc() const {
        return stoc;
    }

    void modificaStoc(int schimbare) {
        stoc += schimbare;
        if (stoc < 0) {
            stoc = 0;
        }
    }

    void afisare(ostream& out) const override{
        Carte::afisare(out);
        out << ", Stoc: " << stoc << endl;
    }

    friend istream& operator>>(istream& in, CarteFizica& carte) {
        carte.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const CarteFizica& carte) {
        carte.afisare(out);
        return out;
    }
};


class CarteElectronica: public Carte{
    string format;

public:
    CarteElectronica(const string& titlu = "", const string& autor = "", bool imprumutata = false, const string& dataReturnare = "", const string& format = "")
        : Carte(titlu, autor, imprumutata, dataReturnare), format(format) {}

    void citire(istream& in) override {
        Carte::citire(in);
        cout<< "Introduceti formatul cartii (PDF/EPUB): ";
        in >> format;
        in.ignore();
        if (format != "PDF" && format!= "EPUB") {
            throw invalid_argument("Formatul trebuie sa fie PDF sau EPUB!");
        }
    }

    string getFormat() const {
        return format;
    }

    void afisare(ostream& out) const override {
        Carte::afisare(out);
        out<<", Format: "<< format << endl;
    }

    void salvare(ofstream& fout) const override {
        fout << "CarteElectronica;";
        Carte::salvare(fout);
        fout << format << endl;
    }

    void incarcare(ifstream& fin) override {
        Carte::incarcare(fin);
        getline(fin, format);
    }

    friend istream& operator>>(istream& in, CarteElectronica& carte) {
        carte.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const CarteElectronica& carte) {
        carte.afisare(out);
        return out;
    }

};

template <typename T>
class Biblioteca {
private:
    vector<T> colectie;

public:
    void adauga(const T& item) {
        colectie.push_back(item);
    }

    void afiseaza() const {
        for (const auto& item : colectie) {
            cout << *item << endl;
        }
    }

    size_t dimensiune() const {
        return colectie.size();
    }
};

class Utilizator {
protected:
    string nume;
    int varsta;
    static int contorUtilizatori;

public:
    Utilizator(const string& nume="", int varsta = 0) : nume(nume), varsta(varsta) {
        contorUtilizatori++;
    }

    virtual ~Utilizator() {
        contorUtilizatori--;
        std::cout<<"Destructor Utilizator\n";
    }

    string getNume() const {
        return nume;
    }

    int getVarsta() const {
        return varsta;
    }

    static int getNumarUtilizatori() {
        return contorUtilizatori;
    }


    virtual void citire(std::istream& in) {
        cout<< "Nume: "; std::getline(in, nume);
        cout<< "Varsta: "; in>>varsta; in.ignore();
        if (varsta <= 0) {
            throw invalid_argument("Varsta trebuie sa fie un numar pozitiv!");
        }
    }

    virtual void afisare(std::ostream& out) const{
        out<<"Nume: " << nume << ", Varsta: " << varsta;
    }

    friend istream& operator>>(std::istream& in, Utilizator& utilizator) {
        utilizator.citire(in);
        return in;
    }

    friend ostream& operator<<(std::ostream& out, const Utilizator& utilizator) {
        utilizator.afisare(out);
        return out;
    }
};

int Utilizator::contorUtilizatori = 0;

class Elev : public Utilizator {
    string clasaElev;

public:
    Elev(const std::string& nume = "", int varsta = 0, const string& clasaElev = "")
        : Utilizator(nume, varsta), clasaElev(clasaElev) {}

    void citire(istream& in) override {
        Utilizator::citire(in);
        cout << "Clasa: ";
        getline(in, clasaElev);
        if (clasaElev.empty()) {
            throw invalid_argument("Clasa nu poate fi vida!");
        }
    }

    string getClasa() const  {
        return clasaElev;
    }

    void afisare(ostream& out) const override {
        Utilizator::afisare(out);
        out<<", Clasa: " << clasaElev;
    }

    friend istream& operator>>(istream& in, Elev& elev) {
        elev.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const Elev& elev) {
        elev.afisare(out);
        return out;
    }
};

class Profesor: public Utilizator {
    string materie;

public:
    Profesor(const string& nume = "", int varsta = 0, const string& materie = "")
        : Utilizator(nume, varsta), materie(materie) {}

    void citire(istream& in) override {
        Utilizator::citire(in);
        cout<<"Materie: ";
        getline(in, materie);
        if (materie.empty()) {
            throw invalid_argument("Materie nu poate fi vida!");
        }
    }

    string getMaterie() const  {
        return materie;
    }

    void afisare(ostream& out) const override {
        Utilizator::afisare(out);
        out<<", Materie: "<< materie;
    }

    friend istream& operator>>(istream& in, Profesor& prof) {
        prof.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const Profesor& prof) {
        prof.afisare(out);
        return out;
    }
};

class ManagerUtilizatori {
private:
    vector<std::shared_ptr<Utilizator>> utilizatori;
    static ManagerUtilizatori* instance;

    ManagerUtilizatori() {}

public:
    ManagerUtilizatori(const ManagerUtilizatori&) = delete;
    ManagerUtilizatori& operator=(const ManagerUtilizatori&) = delete;

    static ManagerUtilizatori* getInstance() {
        if (!instance) {
            instance = new ManagerUtilizatori();
        }
        return instance;
    }

    void adaugaUtilizator(shared_ptr<Utilizator> utilizator) {
        utilizatori.push_back(utilizator);
    }

    void afiseazaUtilizatori() const {
        if (utilizatori.empty()) {
            cout << "Nu exista utilizatori.\n";
            return;
        }

        for (const auto& utilizator : utilizatori) {
            cout << *utilizator << "\n";
        }
    }

    void scrieUtilizatoriInFisier(const string& numeFisier) const {
        ifstream fisierExistente(numeFisier);
        set<string> utilizatoriExistenti;

        // Citim utilizatorii existenți
        if (fisierExistente.is_open()) {
            string linie;
            while (getline(fisierExistente, linie)) {
                if (!linie.empty()) {
                    stringstream ss(linie);
                    string tip, nume;
                    getline(ss, tip, ';');
                    getline(ss, nume, ';');
                    utilizatoriExistenti.insert(nume); // Adăugăm numele în set
                }
            }
            fisierExistente.close();
        }

        // mod de append
        ofstream fisier(numeFisier, ios::app);
        if (!fisier.is_open()) {
            cerr << "Eroare la deschiderea fișierului " << numeFisier << endl;
            return;
        }

        // Scriem doar utilizatorii noi
        for (const auto& utilizator : utilizatori) {
            if (utilizatoriExistenti.find(utilizator->getNume()) == utilizatoriExistenti.end()) {
                if (dynamic_pointer_cast<Elev>(utilizator)) {
                    auto elev = dynamic_pointer_cast<Elev>(utilizator);
                    fisier << "Elev;" << elev->getNume() << ";"
                           << elev->getVarsta() << ";"
                           << elev->getClasa() << endl;
                } else if (dynamic_pointer_cast<Profesor>(utilizator)) {
                    auto profesor = dynamic_pointer_cast<Profesor>(utilizator);
                    fisier << "Profesor;" << profesor->getNume() << ";"
                           << profesor->getVarsta() << ";"
                           << profesor->getMaterie() << endl;
                }
            }
        }
        fisier.close();
    }

    void citesteUtilizatoriDinFisier(const string& numeFisier) {
        ifstream fisier(numeFisier); // Deschid fișierul pentru citire
        if (!fisier.is_open()) {
            cerr << "Eroare la deschiderea fișierului: " << numeFisier << endl;
            return;
        }

        string linie;
        while (getline(fisier, linie)) {
            if (linie.empty()) continue; // Sar peste liniile goale

            istringstream ss(linie); // Construiesc un stream pentru a procesa linia
            string tip, nume, clasaSauMaterie;
            int varsta;

            getline(ss, tip, ';');
            getline(ss, nume, ';');
            ss >> varsta;
            ss.ignore(); // Ignor separatorul ';'

            if (tip == "Elev") {
                getline(ss, clasaSauMaterie, ';');
                utilizatori.push_back(make_shared<Elev>(nume, varsta, clasaSauMaterie));
            } else if (tip == "Profesor") {
                getline(ss, clasaSauMaterie, ';');
                utilizatori.push_back(make_shared<Profesor>(nume, varsta, clasaSauMaterie));
            } else {
                cerr << "Tip necunoscut: " << tip << endl;
            }
        }
        fisier.close(); // Închid fișierul
    }

};

ManagerUtilizatori* ManagerUtilizatori::instance = nullptr;

class LibraryManagement {
private:
    vector<shared_ptr<Carte>> carti;

public:
    void citesteCartiDinFisier(const string& numeFisier) {
        ifstream fisier(numeFisier);
        if (!fisier.is_open()) return;

        string linie;
        while (getline(fisier, linie)) {
            if (linie.empty()) continue;

            stringstream ss(linie);
            string tip;
            getline(ss, tip, ';');

            string titlu, autor, dataRetur;
            getline(ss, titlu, ';');
            getline(ss, autor, ';');

            string imprumutataStr;
            getline(ss, imprumutataStr, ';');
            bool imprumutata = (imprumutataStr == "1");

            getline(ss, dataRetur, ';');

            if (tip == "CarteFizica") {
                string stocStr;
                getline(ss, stocStr);
                int stoc = !stocStr.empty() ? stoi(stocStr) : 0;
                carti.push_back(make_shared<CarteFizica>(titlu, autor, imprumutata, dataRetur, stoc));
            } else if (tip == "CarteElectronica") {
                string format;
                getline(ss, format);
                carti.push_back(make_shared<CarteElectronica>(titlu, autor, imprumutata, dataRetur, format));
            }
        }
    }

    void scrieCartiInFisier(const string& numeFisier) const {
        ifstream fisierExistente(numeFisier);
        set<string> cartiExistente;

        // Citim cărțile existente din fișier
        if (fisierExistente.is_open()) {
            string linie;
            while (getline(fisierExistente, linie)) {
                if (!linie.empty()) {
                    stringstream ss(linie);
                    string tip, titlu;
                    getline(ss, tip, ';');
                    getline(ss, titlu, ';');
                    cartiExistente.insert(titlu); // Adăugăm titlul în set
                }
            }
            fisierExistente.close();
        }

        // Deschidem fișierul în mod de append
        ofstream fisier(numeFisier, ios::app);
        if (!fisier.is_open()) return;

        // Scriem doar cărțile noi
        for (const auto& carte : carti) {
            if (cartiExistente.find(carte->getTitlu()) == cartiExistente.end()) {
                if (auto carteFizica = dynamic_pointer_cast<CarteFizica>(carte)) {
                    fisier << "CarteFizica;"
                           << carteFizica->getTitlu() << ";"
                           << carteFizica->getAutor() << ";"
                           << carteFizica->esteImprumutata() << ";"
                           << carteFizica->getDatareturnare() << ";"
                           << carteFizica->getStoc() << endl;
                } else if (auto carteElectronica = dynamic_pointer_cast<CarteElectronica>(carte)) {
                    fisier << "CarteElectronica;"
                           << carteElectronica->getTitlu() << ";"
                           << carteElectronica->getAutor() << ";"
                           << carteElectronica->esteImprumutata() << ";"
                           << carteElectronica->getDatareturnare() << ";"
                           << carteElectronica->getFormat() << endl;
                }
            }
        }
        fisier.close();
    }

    void adaugaCarte(shared_ptr<Carte> carte) {
        carti.push_back(carte);
    }

    void imprumutaCarte(const string& titlu, const string& data) {
        for (auto& carte : carti) {
            if (carte->getTitlu() == titlu) {
                if (carte->esteImprumutata()) {
                    throw runtime_error("Cartea este deja imprumutata!");
                }
                if (!Carte::valideazaData(data)) {
                    throw invalid_argument("Data introdusa nu este valida!");
                }
                carte->modificaImprumut(true, data);
                cout << "Cartea a fost imprumutata cu succes!\n";
                return;
            }
        }
        cout << "Cartea cu titlul \"" << titlu << "\" nu a fost gasita.\n";
    }

    void returneazaCarte(const string& titlu) {
        for (auto& carte : carti) {
            if (carte->getTitlu() == titlu) {
                if (!carte->esteImprumutata()) {
                    throw runtime_error("Cartea nu este imprumutata!");
                }
                carte->modificaImprumut(false);
                cout << "Cartea a fost returnata cu succes!\n";
                return;
            }
        }
        cout << "Cartea cu titlul \"" << titlu << "\" nu a fost gasita.\n";
    }

    const vector<shared_ptr<Carte>>& getCarti() const {
        return carti;
    }
};
int main() {
    initializeFiles();
    ManagerUtilizatori* managerUtilizatori = ManagerUtilizatori::getInstance();
    LibraryManagement biblioteca;

    biblioteca.citesteCartiDinFisier("carti.txt");
    managerUtilizatori->citesteUtilizatoriDinFisier("utilizatori.txt");

    Biblioteca<shared_ptr<Carte>> bibliotecaCarti;
    Biblioteca<shared_ptr<Utilizator>> bibliotecaUtilizatori;

    bool ruleaza = true;

    while (ruleaza) {
        cout << "\n--- Meniu Interactiv ---\n";
        cout << "1. Adauga utilizator\n";
        cout << "2. Afiseaza toti utilizatorii\n";
        cout << "3. Adauga carte\n";
        cout << "4. Afiseaza toate cartile\n";
        cout << "5. Imprumuta o carte\n";
        cout << "6. Returneaza o carte\n";
        cout << "7. Afiseaza cartile imprumutate\n";
        cout << "8. Afiseaza biblioteca sortata dupa titlu\n";
        cout << "9. Afiseaza numar total utilizatori\n";
        cout << "10. Afiseaza numar total carti\n";
        cout << "11. Salveaza datele!\n";
        cout << "0. Iesire\n";
        cout << "Alegerea ta: ";

        int optiune;
        cin >> optiune;
        cin.ignore();

        try {
            switch (optiune) {
                case 1: {
                    cout << "Adauga utilizator (Elev sau Profesor)\n";
                    cout << "1. Elev\n2. Profesor\n";
                    int tipUtilizator;
                    cin >> tipUtilizator;
                    cin.ignore();

                    shared_ptr<Utilizator> utilizator;
                    if (tipUtilizator == 1) {
                        utilizator = make_shared<Elev>();
                    } else if (tipUtilizator == 2) {
                        utilizator = make_shared<Profesor>();
                    } else {
                        cout << "Optiune invalida.\n";
                        break;
                    }

                    cin >> *utilizator;
                    managerUtilizatori->adaugaUtilizator(utilizator);
                    bibliotecaUtilizatori.adauga(utilizator);
                    break;
                }

                case 2: {
                    cout << "Utilizatori inregistrati:\n";
                    managerUtilizatori->afiseazaUtilizatori();
                    break;
                }

                case 3: {
                    cout << "Adauga carte (CarteFizica sau CarteElectronica)\n";
                    cout << "1. CarteFizica\n2. CarteElectronica\n";
                    int tipCarte;
                    cin >> tipCarte;
                    cin.ignore();

                    shared_ptr<Carte> carte;
                    if (tipCarte == 1) {
                        carte = make_shared<CarteFizica>();
                    } else if (tipCarte == 2) {
                        carte = make_shared<CarteElectronica>();
                    } else {
                        cout << "Optiune invalida.\n";
                        break;
                    }

                    cin >> *carte;
                    biblioteca.adaugaCarte(carte);
                    bibliotecaCarti.adauga(carte);
                    break;
                }

                case 4: {
                    cout << "Carti inregistrate:\n";
                    for (const auto& carte : biblioteca.getCarti()) {
                        cout << *carte << "\n";
                    }
                    break;
                }

                case 5: {
                    string titlu, data;
                    cout << "Titlul cartii de imprumutat: ";
                    getline(cin, titlu);
                    cout << "Data returnarii (format DD/MM/YYYY): ";
                    getline(cin, data);

                    biblioteca.imprumutaCarte(titlu, data);
                    break;
                }

                case 6: {
                    string titlu;
                    cout << "Titlul cartii de returnat: ";
                    getline(cin, titlu);

                    biblioteca.returneazaCarte(titlu);
                    break;
                }

                case 7: {
                    cout << "\nCarti imprumutate:\n";
                    bool existaCartiImprumutate = false;
                    for (const auto& carte : biblioteca.getCarti()) {
                        if (carte->esteImprumutata()) {
                            cout << *carte << "\n";
                            existaCartiImprumutate = true;
                        }
                    }
                    if (!existaCartiImprumutate) {
                        cout << "Nu exista carti imprumutate.\n";
                    }
                    break;
                }

                case 8: {
                    cout << "\nCarti sortate dupa titlu:\n";
                    auto cartiSortate = biblioteca.getCarti();
                    sort(cartiSortate.begin(), cartiSortate.end(), [](const shared_ptr<Carte>& a, const shared_ptr<Carte>& b) {
                        return a->getTitlu() < b->getTitlu();
                    });

                    for (const auto& carte : cartiSortate) {
                        cout << *carte << "\n";
                    }
                    break;
                }

                case 9:
                    cout << "Numar total utilizatori: " << Utilizator::getNumarUtilizatori() << "\n";
                    break;

                case 10:
                    cout << "Numar total carti: " << Carte::getNumarCarti() << "\n";
                    break;

                case 11: {
                    biblioteca.scrieCartiInFisier("carti.txt");
                    managerUtilizatori->scrieUtilizatoriInFisier("utilizatori.txt");
                    cout << "Datele au fost salvate cu succes.\n";
                    break;
                }

                case 0: {
                    biblioteca.scrieCartiInFisier("carti.txt");
                    ruleaza = false;
                    break;
                }
                default:
                    cout << "Optiune invalida!\n";
            }
        }
        catch (const exception &e) {
            cout << "Eroare: " << e.what() << "\n";
        }
    }

    return 0;
}