#include <algorithm>
#include <iomanip>
#include <iostream>
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
    if (nd.empty()) return 0.0;
    double sum = 0;
    for (int x : nd) sum += x;
    return sum / nd.size();
}

double mediana(vector<int> nd) {
    if (nd.empty()) return 0.0;
    sort(nd.begin(), nd.end());
    size_t n = nd.size();
    if (n % 2 == 1) return nd[n / 2];
    return (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
}

double galutinis(const Student& s, bool naudotiMediana) {
    double ndRez = naudotiMediana ? mediana(s.nd) : vidurkis(s.nd);
    return 0.4 * ndRez + 0.6 * s.egz;
}

int main() {
    vector<Student> studentai;

    cout << "Skaiciavimo budas:\n1 - Vidurkis\n2 - Mediana\nPasirinkimas: ";
    int mode;
    cin >> mode;
    bool naudotiMediana = (mode == 2);

    while (true) {
        Student s;
        cout << "\nVardas (0 - baigti): ";
        cin >> s.vardas;
        if (s.vardas == "0") break;

        cout << "Pavarde: ";
        cin >> s.pavarde;

        cout << "ND pazymiai (1-10), 0 - baigti ND:\n";
        while (true) {
            cout << "ND: ";
            int x;
            cin >> x;
            if (x == 0) break;
            s.nd.push_back(x);
        }

        cout << "Egzaminas (1-10): ";
        cin >> s.egz;

        studentai.push_back(s);
    }

    cout << "\n";
    cout << left << setw(16) << "Pavarde"
         << left << setw(16) << "Vardas"
         << (naudotiMediana ? "Galutinis (Med.)" : "Galutinis (Vid.)") << "\n";
    cout << string(16 + 16 + 18, '-') << "\n";

    cout << fixed << setprecision(2);
    for (const auto& s : studentai) {
        cout << left << setw(16) << s.pavarde
             << left << setw(16) << s.vardas
             << galutinis(s, naudotiMediana) << "\n";
    }
}
