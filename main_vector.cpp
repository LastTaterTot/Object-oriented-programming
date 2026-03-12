#include <algorithm>
#include <fstream>
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
    double sum = 0;
    for (int x : nd) sum += x;
    return nd.empty() ? 0 : sum / nd.size();
}

double mediana(vector<int> nd) {
    if (nd.empty()) return 0;

    sort(nd.begin(), nd.end());
    int n = nd.size();

    if (n % 2 == 0)
        return (nd[n/2 - 1] + nd[n/2]) / 2.0;

    return nd[n/2];
}

double galutinisVid(const Student& s) {
    return 0.4 * vidurkis(s.nd) + 0.6 * s.egz;
}

double galutinisMed(const Student& s) {
    return 0.4 * mediana(s.nd) + 0.6 * s.egz;
}

vector<Student> readFile(string filename) {
    ifstream fin(filename);
    vector<Student> students;

    string vardas, pavarde;

    fin >> vardas >> pavarde; // skip header

    while (fin) {
        Student s;

        fin >> s.vardas >> s.pavarde;
        if (!fin) break;

        int x;
        vector<int> grades;

        for (int i = 0; i < 5; i++) {
            fin >> x;
            grades.push_back(x);
        }

        fin >> s.egz;
        s.nd = grades;

        students.push_back(s);
    }

    return students;
}

void printStudents(const vector<Student>& st) {

    cout << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis (Vid.)"
         << setw(20) << "Galutinis (Med.)"
         << endl;

    cout << string(70, '-') << endl;

    cout << fixed << setprecision(2);

    for (const auto& s : st) {
        cout << setw(15) << s.vardas
             << setw(15) << s.pavarde
             << setw(20) << galutinisVid(s)
             << setw(20) << galutinisMed(s)
             << endl;
    }
}

int main() {

    vector<Student> students = readFile("kursiokai.txt");

    cout << "Rikiavimo pasirinkimas:\n";
    cout << "1 - Vardas\n";
    cout << "2 - Pavarde\n";
    cout << "3 - Galutinis (Vid.)\n";
    cout << "4 - Galutinis (Med.)\n";

    int choice;
    cin >> choice;

    switch (choice) {

    case 1:
        sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.vardas < b.vardas;
            });
        break;

    case 2:
        sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.pavarde < b.pavarde;
            });
        break;

    case 3:
        sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return galutinisVid(a) < galutinisVid(b);
            });
        break;

    case 4:
        sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return galutinisMed(a) < galutinisMed(b);
            });
        break;
    }

    printStudents(students);

    return 0;
}
