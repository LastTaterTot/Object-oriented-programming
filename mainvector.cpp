#include "functions.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

    try {

        cout << "Pasirinkite faila:\n";
        cout << "1 - studentai10000.txt\n";
        cout << "2 - studentai100000.txt\n";
        cout << "3 - studentai1000000.txt\n";

        int choice;
        cin >> choice;

        if (!cin)
            throw runtime_error("Klaida: neteisinga ivestis.");

        string filename;

        if (choice == 1) filename = "studentai10000.txt";
        else if (choice == 2) filename = "studentai100000.txt";
        else if (choice == 3) filename = "studentai1000000.txt";
        else throw runtime_error("Klaida: blogas pasirinkimas.");

        vector<Student> students = readFile(filename);

        cout << "\nRikiuoti pagal:\n";
        cout << "1 - Varda\n";
        cout << "2 - Pavarde\n";
        cout << "3 - Galutini (Vid.)\n";
        cout << "4 - Galutini (Med.)\n";

        int sortChoice;
        cin >> sortChoice;

        if (!cin)
            throw runtime_error("Klaida: neteisinga ivestis.");

        sortStudents(students, sortChoice);

        printStudents(students);
    }

    catch (const exception& e) {

        cout << e.what() << endl;
    }

    return 0;
}
