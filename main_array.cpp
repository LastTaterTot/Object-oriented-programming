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

double vidurkis(const Student& s) {
    if (s.ndKiek == 0) return 0;
    double sum = 0;
    for (int i = 0; i < s.ndKiek; i++)
        sum += s.nd[i];
    return sum / s.ndKiek;
}

double mediana(Student s) {
    if (s.ndKiek == 0) return 0;
    sort(s.nd, s.nd + s.ndKiek);
    int n = s.ndKiek;

    if (n % 2 == 0)
        return (s.nd[n / 2 - 1] + s.nd[n / 2]) / 2.0;
    return s.nd[n / 2];
}

double galutinis(const Student& s, bool naudotiMediana) {
    double ndRez = naudotiMediana ? mediana(s) : vidurkis(s);
    return 0.4 * ndRez + 0.6 * s.egz;
}

int randomPazymys() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);
    return dist(gen);
}

int main() {
    Student studentai[MAX_STUD];
    int studKiek = 0;

    cout << "1 - Vidurkis\n2 - Mediana\n";
    int pasirinkimas;
    cin >> pasirinkimas;
    bool naudotiMediana = pasirinkimas == 2;

    cout << "1 - Rankinis ivedimas\n2 - Generavimas\n";
    int tipas;
    cin >> tipas;

    if (tipas == 1) {
        while (true) {
            Student s;
            cout << "Vardas (0 baigti): ";
            cin >> s.vardas;
            if (s.vardas == "0") break;

            cout << "Pavarde: ";
            cin >> s.pavarde;

            cout << "ND (0 baigti): ";
            while (true) {
                int x;
                cin >> x;
                if (x == 0) break;
                s.nd[s.ndKiek++] = x;
            }

            cout << "Egzaminas: ";
            cin >> s.egz;

            studentai[studKiek++] = s;
        }
    } else {
        int m, n;
        cout << "Studentu skaicius: ";
        cin >> m;
        cout << "ND kiekis: ";
        cin >> n;

        for (int i = 0; i < m; i++) {
            Student s;
            s.vardas = "Vardas" + to_string(i + 1);
            s.pavarde = "Pavarde" + to_string(i + 1);
            s.ndKiek = n;

            for (int j = 0; j < n; j++)
                s.nd[j] = randomPazymys();

            s.egz = randomPazymys();
            studentai[studKiek++] = s;
        }
    }

    cout << fixed << setprecision(2);

    cout << left << setw(15) << "Pavarde"
         << setw(15) << "Vardas"
         << "Galutinis\n";

    cout << "--------------------------------\n";

    for (int i = 0; i < studKiek; i++) {
        cout << setw(15) << studentai[i].pavarde
             << setw(15) << studentai[i].vardas
             << galutinis(studentai[i], naudotiMediana) << "\n";
    }
}
