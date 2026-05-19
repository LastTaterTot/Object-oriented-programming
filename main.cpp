#include "functions.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ================= TEST FUNKCIJA =================
template <typename Container>
void runTest(const string& filename, const string& typeName) {

    cout << "\n==== " << typeName << " ====\n";

    // ---------- READ ----------
    auto start = high_resolution_clock::now();
    Container students = readFile<Container>(filename);
    auto readEnd = high_resolution_clock::now();

    cout << "Nuskaitymas: "
         << duration<double>(readEnd - start).count() << " s\n";

    // ---------- STRATEGY 1 ----------
    {
        Container vargsiukai, kietiakai;

        auto t1 = high_resolution_clock::now();
        splitStrategy1(students, vargsiukai, kietiakai);
        auto t2 = high_resolution_clock::now();

        cout << "Strategija 1: "
             << duration<double>(t2 - t1).count() << " s\n";
    }

    // ---------- STRATEGY 2 ----------
    {
        Container temp = students;
        Container vargsiukai;

        auto t1 = high_resolution_clock::now();
        splitStrategy2(temp, vargsiukai);
        auto t2 = high_resolution_clock::now();

        cout << "Strategija 2: "
             << duration<double>(t2 - t1).count() << " s\n";
    }

    // ---------- STRATEGY 3 ----------
    {
        Container temp = students;
        Container vargsiukai, kietiakai;

        auto t1 = high_resolution_clock::now();
        splitStrategy3(temp, vargsiukai, kietiakai);
        auto t2 = high_resolution_clock::now();

        cout << "Strategija 3 (partition): "
             << duration<double>(t2 - t1).count() << " s\n";
    }
}

// ================= MAIN =================
int main() {
    try {
        cout << "1 - Generuoti failus\n";
        cout << "2 - Testuoti\n";

        int mode;
        cin >> mode;

        if (mode == 1) {
            generateFile("studentai1000.txt", 1000);
            generateFile("studentai10000.txt", 10000);
            generateFile("studentai100000.txt", 100000);
            generateFile("studentai1000000.txt", 1000000);
            generateFile("studentai10000000.txt", 10000000);

            cout << "Failai sugeneruoti\n";
            return 0;
        }

        cout << "Pasirink faila:\n";
        cout << "1 - 1k\n2 - 10k\n3 - 100k\n4 - 1M\n";

        int c;
        cin >> c;

        string file;
        if (c==1) file="studentai1000.txt";
        else if (c==2) file="studentai10000.txt";
        else if (c==3) file="studentai100000.txt";
        else if (c==4) file="studentai1000000.txt";
        else throw runtime_error("Blogas pasirinkimas");

        runTest<vector<Student>>(file, "vector");
        runTest<list<Student>>(file, "list");
        runTest<deque<Student>>(file, "deque");

    } catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
