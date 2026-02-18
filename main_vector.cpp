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

double vidurkis(const vector<int>& nd) {
    if (nd.empty()) return 0;
    double s = 0;
    for (int x : nd) s += x;
    return s / nd.size();
}

double mediana(vector<int> nd) {
    if (nd.empty()) return 0;
    sort(nd.begin(), nd.end());
    int n = nd.size();
    if (n % 2 == 0)
        return (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
    return nd[n / 2];
}

double galutinis(const Student& s, bool naudotiMediana) {
    double ndRez = naudotiMediana ? mediana(s.nd) : vidurkis(s.nd);
    return 0.4 * ndRez + 0.6 * s.egz;
}

int randomPazymys() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10);
    return dist(gen);
}

vector<Student> rankinisIvedimas() {
    vector<Student> studentai;

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
            s.nd.push_back(x);
        }

        cout << "Egzaminas: ";
        cin >> s.egz;

        studentai.push_back(s);
    }

    return studentai;
}

vector<Student> generavimas() {
    int m, n;
    cout << "Studentu skaicius: ";
    cin >> m;
    cout << "ND kiekis: ";
    cin >> n;

    vector<Student> studentai;

    for (int i = 0; i < m; i++) {
        Student s;
        s.vardas = "Vardas" + to_string(i + 1);
        s.pavarde = "Pavarde" + to_string(i + 1);

        for (int j = 0; j < n; j++)
            s.nd.push_back(randomPazymys());

        s.egz = randomPazymys();
        studentai.push_back(s);
    }

    return studentai;
}

int main() {
    cout << "1 - Vidurkis\n2 - Mediana\n";
    int pasirinkimas;
    cin >> pasirinkimas;
    bool naudotiMediana = pasirinkimas == 2;

    cout << "1 - Rankinis ivedimas\n2 - Generavimas\n";
    int tipas;
    cin >> tipas;

    vector<Student> studentai =
        (tipas == 1) ? rankinisIvedimas() : generavimas();

    cout << fixed << setprecision(2);

    cout << left << setw(15) << "Pavarde"
         << setw(15) << "Vardas"
         << "Galutinis\n";

    cout << "--------------------------------\n";

    for (auto& s : studentai) {
        cout << setw(15) << s.pavarde
             << setw(15) << s.vardas
             << galutinis(s, naudotiMediana) << "\n";
    }
}
