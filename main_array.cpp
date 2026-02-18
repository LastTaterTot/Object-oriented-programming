#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

using namespace std;

const int MAX_STUD = 1000;
const int MAX_ND = 50;

struct Student {
    string vardas;
    string pavarde;
    int nd[MAX_ND];
    int ndKiek = 0;
    int egz = 0;
};

static random_device rd;
static mt19937 gen(rd());

int randInt(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}

double vidurkis(const Student& s) {
    if (s.ndKiek == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < s.ndKiek; i++) sum += s.nd[i];
    return sum / s.ndKiek;
}

double mediana(Student s) { // kopija, kad galetume rikiuoti
    if (s.ndKiek == 0) return 0.0;
    sort(s.nd, s.nd + s.ndKiek);
    int n = s.ndKiek;
    if (n % 2 == 0) return (s.nd[n/2 - 1] + s.nd[n/2]) / 2.0;
    return s.nd[n/2];
}

double galutinis(const Student& s, bool naudotiMediana) {
    double ndRez = naudotiMediana ? mediana(s) : vidurkis(s);
    return 0.4 * ndRez + 0.6 * s.egz;
}

void printTable(const Student st[], int kiek, bool naudotiMediana) {
    cout << "\n";
    cout << left << setw(16) << "Pavarde"
         << left << setw(16) << "Vardas"
         << (naudotiMediana ? "Galutinis (Med.)" : "Galutinis (Vid.)") << "\n";
    cout << string(16 + 16 + 18, '-') << "\n";

    cout << fixed << setprecision(2);
    for (int i = 0; i < kiek; i++) {
        cout << left << setw(16) << st[i].pavarde
             << left << setw(16) << st[i].vardas
             << galutinis(st[i], naudotiMediana) << "\n";
    }
}

void inputND_until0(Student& s) {
    s.ndKiek = 0;
    cout << "Veskite ND (1-10), 0 - baigti ND:\n";
    while (true) {
        cout << "ND: ";
        int x; cin >> x;
        if (x == 0) break;
        if (x >= 1 && x <= 10) {
            if (s.ndKiek < MAX_ND) s.nd[s.ndKiek++] = x;
            else {
                cout << "Pasiektas MAX_ND limitas (" << MAX_ND << ").\n";
                break;
            }
        } else {
            cout << "Klaida: pazymys 1-10.\n";
        }
    }
}

Student inputStudent_full() {
    Student s;
    cout << "Vardas: ";
    cin >> s.vardas;
    cout << "Pavarde: ";
    cin >> s.pavarde;
    inputND_until0(s);
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

    if (ndKiek > MAX_ND) ndKiek = MAX_ND;
    s.ndKiek = ndKiek;
    for (int i = 0; i < s.ndKiek; i++) s.nd[i] = randInt(1, 10);
    s.egz = randInt(1, 10);
    return s;
}

Student generateStudent_all(int idx, int ndKiek) {
    Student s;
    s.vardas  = "Vardas" + to_string(idx);
    s.pavarde = "Pavarde" + to_string(idx);

    if (ndKiek > MAX_ND) ndKiek = MAX_ND;
    s.ndKiek = ndKiek;
    for (int i = 0; i < s.ndKiek; i++) s.nd[i] = randInt(1, 10);
    s.egz = randInt(1, 10);
    return s;
}

int main() {
    cout << "Skaiciavimo budas:\n1 - Vidurkis\n2 - Mediana\nPasirinkimas: ";
    int mode; cin >> mode;
    bool naudotiMediana = (mode == 2);

    Student studentai[MAX_STUD];
    int studKiek = 0;

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
            cout << "\nIveskite studentus. (Vardas 0 - grizti i meniu)\n";
            while (true) {
                if (studKiek >= MAX_STUD) {
                    cout << "Pasiektas MAX_STUD limitas (" << MAX_STUD << ").\n";
                    break;
                }

                cout << "Vardas (0 - stop): ";
                string v; cin >> v;
                if (v == "0") break;

                Student s;
                s.vardas = v;
                cout << "Pavarde: ";
                cin >> s.pavarde;
                inputND_until0(s);
                cout << "Egzaminas (1-10): ";
                cin >> s.egz;

                studentai[studKiek++] = s;
            }
            printTable(studentai, studKiek, naudotiMediana);
        }
        else if (pasirinkimas == 2) {
            int m, n;
            cout << "Kiek studentu ivesite? "; cin >> m;
            cout << "Kiek ND generuoti kiekvienam? "; cin >> n;

            for (int i = 0; i < m; i++) {
                if (studKiek >= MAX_STUD) {
                    cout << "Pasiektas MAX_STUD limitas (" << MAX_STUD << ").\n";
                    break;
                }
                cout << "\nStudentas #" << (i + 1) << "\n";
                studentai[studKiek++] = inputStudent_nameOnly_generateGrades(n);
            }
            printTable(studentai, studKiek, naudotiMediana);
        }
        else if (pasirinkimas == 3) {
            int m, n;
            cout << "Kiek studentu generuoti? "; cin >> m;
            cout << "Kiek ND generuoti kiekvienam? "; cin >>
