#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
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

    string line;
    getline(fin, line); // skip header

    while (getline(fin, line)) {

        stringstream ss(line);
        Student s;

        ss >> s.vardas >> s.pavarde;

        vector<int> grades;
        int x;

        while (ss >> x)
            grades.push_back(x);

        s.egz = grades.back();
        grades.pop_back();

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

    cout << "Pasirinkite faila:\n";
    cout << "1 - studentai10000.txt\n";
    cout << "2 - studentai100000.txt\n";
    cout << "3 - studentai1000000.txt\n";

    int choice;
    cin >> choice;

    string filename;

    if (choice == 1) filename = "studentai10000.txt";
    if (choice == 2) filename = "studentai100000.txt";
    if (choice == 3) filename = "studentai1000000.txt";

    vector<Student> students = readFile(filename);

    cout << "\nRikiuoti pagal:\n";
    cout << "1 - Varda\n";
    cout << "2 - Pavarde\n";
    cout << "3 - Galutini (Vid.)\n";
    cout << "4 - Galutini (Med.)\n";

    int sortChoice;
    cin >> sortChoice;

    switch (sortChoice) {

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
