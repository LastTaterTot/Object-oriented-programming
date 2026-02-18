#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz = 0;
};

static random_device rd;
static mt19937 gen(rd());

int randInt(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}

double vidurkis(const vector<int>& nd) {
    if (nd.empty()) return 0.0;
    double s = 0.0;
    for (int x : nd) s += x;
    return s / nd.size();
}

double mediana(vector<int> nd) {
    if (nd.empty()) return 0.0;
    sort(nd.begin(), nd.end());
    int n = (int)nd.size();
    if (n % 2 == 0) return (nd[n/2 - 1] + nd[n/2]) / 2.0;
    return nd[n/2];
}

double galutinis(const Student& s, bool naudotiMediana) {
    double ndRez = naudotiMediana ? mediana(s.nd) : vidurkis(s.nd);
    return 0.4 * ndRez + 0.6 * s.egz;
}

void printTable(const vector<Student>& st, bool naudotiMediana) {
    cout << "\n";
    cout << left << setw(16) << "Pavarde"
         << left << setw(16) << "Vardas"
         << (naudotiMediana ? "Galutinis (Med.)" : "Galutinis (Vid.)") << "\n";
    cout << string(16 + 16 + 18, '-') << "\n";

    cout << fixed << setprecision(2);
    for (const auto& s : st) {
        cout << left << setw(16) << s.pavarde
             << left << setw(16) << s.vardas
             << galutinis(s, naudotiMediana) << "\n";
    }
}

vector<int> inputND_until0() {
    vector<int> nd;
    cout << "Veskite ND (1-10), 0 - baigti ND:\n";
    while (true) {
        cout << "ND: ";
        int x; cin >> x;
        if (x == 0) break;
        if (x >= 1 && x <= 10) nd.push_back(x);
        else cout << "Klaida: pazymys 1-10.\n";
    }
    return nd;
}

Student inputStudent_full() {
    Student s;
    cout << "Vardas: ";
    cin >> s.vardas;
    cout << "Pavarde: ";
    cin >> s.pavarde;
    s.nd = inputND_until0();
    cout << "Egzaminas (1-10): ";
    cin >> s.egz;
    return s;
}

Student inputStudent_nameOnly_generateGrades(int ndKiek) {
    Student s;
    cout << "Vardas: ";
    cin >> s.vardas;
    cout << "Pavarde: ";
    cin >> s.pavarde;

    s.nd.clear();
    s.nd.reserve(ndKiek);
    for (int i = 0; i < ndKiek; i++) s.nd.push_back(randInt(1, 10));
    s.egz = randInt(1, 10);
    return s;
}

Student generateStudent_all(int idx, int ndKiek) {
    Student s;
    s.vardas  = "Vardas" + to_string(idx);
    s.pavarde = "Pavarde" + to_string(idx);
    s.nd.reserve(ndKiek);
    for (int i = 0; i < ndKiek; i++) s.nd.push_back(randInt(1, 10));
    s.egz = randInt(1, 10);
    return s;
}

int main() {
    cout << "Skaiciavimo budas:\n1 - Vidurkis\n2 - Mediana\nPasirinkimas: ";
    int mode; cin >> mode;
    bool naudotiMediana = (mode == 2);

    vector<Student> studentai;

    while (true) {
        cout << "\nMeniu:\n";
        cout << "1 - Ivedimas ranka (vardas, pavarde, ND, egz)\n";
        cout << "2 - Generuoti tik pazymius (ivedi varda+pavarde)\n";
        cout << "3 - Generuoti varda+pavarde+pazymius\n";
        cout << "4 - Baigti\n";
        cout << "Pasirinkimas: ";

        int pasirinkimas;
        cin >> pasirinkimas;

        if (pasirinkimas == 4) break;

        if (pasirinkimas == 1) {
            cout << "\nIveskite studenta. (Vardas 0 - grizti i meniu)\n";
            while (true) {
                cout << "Vardas (0 - stop): ";
                string v; cin >> v;
                if (v == "0") break;

                Student s;
                s.vardas = v;
                cout << "Pavarde: ";
                cin >> s.pavarde;
                s.nd = inputND_until0();
                cout << "Egzaminas (1-10): ";
                cin >> s.egz;

                studentai.push_back(s);
            }
            printTable(studentai, naudotiMediana);
        }
        else if (pasirinkimas == 2) {
            int m, n;
            cout << "Kiek studentu ivesite? "; cin >> m;
            cout << "Kiek ND generuoti kiekvienam? "; cin >> n;

            for (int i = 0; i < m; i++) {
                cout << "\nStudentas #" << (i + 1) << "\n";
                studentai.push_back(inputStudent_nameOnly_generateGrades(n));
            }
            printTable(studentai, naudotiMediana);
        }
        else if (pasirinkimas == 3) {
            int m, n;
            cout << "Kiek studentu generuoti? "; cin >> m;
            cout << "Kiek ND generuoti kiekvienam? "; cin >> n;

            for (int i = 1; i <= m; i++) {
                studentai.push_back(generateStudent_all(i, n));
            }
            printTable(studentai, naudotiMediana);
        }
        else {
            cout << "Neteisingas pasirinkimas.\n";
        }
    }

    cout << "Baigta.\n";
    return 0;
}
