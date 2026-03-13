#include "functions.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

double vidurkis(const vector<int>& nd) {

    if (nd.empty()) return 0;

    double sum = 0;
    for (int x : nd)
        sum += x;

    return sum / nd.size();
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

vector<Student> readFile(const string& filename) {

    ifstream fin(filename);

    if (!fin)
        throw runtime_error("Klaida: failas nerastas.");

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

        if (grades.empty())
            throw runtime_error("Klaida: blogas failo formatas.");

        s.egz = grades.back();
        grades.pop_back();

        s.nd = grades;

        students.push_back(s);
    }

    return students;
}

void printStudents(const vector<Student>& students) {

    cout << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis (Vid.)"
         << setw(20) << "Galutinis (Med.)"
         << endl;

    cout << string(70, '-') << endl;

    cout << fixed << setprecision(2);

    for (const auto& s : students) {

        cout << setw(15) << s.vardas
             << setw(15) << s.pavarde
             << setw(20) << galutinisVid(s)
             << setw(20) << galutinisMed(s)
             << endl;
    }
}

void sortStudents(vector<Student>& students, int choice) {

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

    default:
        throw runtime_error("Klaida: neteisingas rikiavimo pasirinkimas.");
    }
}

#include <random>
#include <chrono>

void generateFile(const string& filename, int studentCount) {

    ofstream fout(filename);

    if (!fout)
        throw runtime_error("Nepavyko sukurti failo.");

    fout << "Vardas Pavarde ";
    for(int i=1;i<=15;i++)
        fout << "ND" << i << " ";
    fout << "Egz\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,10);

    for(int i=1;i<=studentCount;i++) {

        fout << "Vardas" << i << " Pavarde" << i << " ";

        for(int j=0;j<15;j++)
            fout << dist(gen) << " ";

        fout << dist(gen) << "\n";
    }
}

void splitStudents(
    const vector<Student>& students,
    vector<Student>& vargsiukai,
    vector<Student>& kietiakai
){

    for(const auto& s : students){

        if(galutinisVid(s) < 5)
            vargsiukai.push_back(s);
        else
            kietiakai.push_back(s);
    }
}

void writeStudentsToFile(
    const string& filename,
    const vector<Student>& students
){

    ofstream fout(filename);

    if(!fout)
        throw runtime_error("Nepavyko sukurti rezultatu failo.");

    fout << left << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis(Vid.)"
         << setw(20) << "Galutinis(Med.)"
         << "\n";

    fout << string(70,'-') << "\n";

    fout << fixed << setprecision(2);

    for(const auto& s : students){

        fout << setw(15) << s.vardas
             << setw(15) << s.pavarde
             << setw(20) << galutinisVid(s)
             << setw(20) << galutinisMed(s)
             << "\n";
    }
}
