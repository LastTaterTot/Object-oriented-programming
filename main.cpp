#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
};

double vidurkis(const vector<int>& nd) {
    if (nd.empty()) return 0;
    double s = 0;
    for (int x : nd) s += x;
    return s / nd.size();
}

double galutinis(const Student& s) {
    return 0.4 * vidurkis(s.nd) + 0.6 * s.egz;
}

int main() {
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

    cout << left << setw(15) << "Pavarde"
         << setw(15) << "Vardas"
         << "Galutinis (Vid.)\n";

    cout << "-------------------------------------\n";

    cout << fixed << setprecision(2);
    for (auto& s : studentai) {
        cout << setw(15) << s.pavarde
             << setw(15) << s.vardas
             << galutinis(s) << "\n";
    }
}
