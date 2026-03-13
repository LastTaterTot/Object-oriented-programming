#include "functions.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main(){

    try{

        cout << "1 - Generuoti failus\n";
        cout << "2 - Testuoti programa\n";

        int mode;
        cin >> mode;

        if(mode == 1){

            generateFile("studentai1000.txt",1000);
            generateFile("studentai10000.txt",10000);
            generateFile("studentai100000.txt",100000);
            generateFile("studentai1000000.txt",1000000);
            generateFile("studentai10000000.txt",10000000);

            cout << "Failai sugeneruoti\n";
            return 0;
        }

        cout << "Pasirinkite faila:\n";
        cout << "1 - studentai1000.txt\n";
        cout << "2 - studentai10000.txt\n";
        cout << "3 - studentai100000.txt\n";
        cout << "4 - studentai1000000.txt\n";

        int choice;
        cin >> choice;

        string filename;

        if(choice==1) filename="studentai1000.txt";
        else if(choice==2) filename="studentai10000.txt";
        else if(choice==3) filename="studentai100000.txt";
        else if(choice==4) filename="studentai1000000.txt";
        else throw runtime_error("Blogas pasirinkimas.");

        auto start = chrono::high_resolution_clock::now();

        vector<Student> students = readFile(filename);

        auto readEnd = chrono::high_resolution_clock::now();

        vector<Student> vargsiukai;
        vector<Student> kietiakai;

        splitStudents(students,vargsiukai,kietiakai);

        auto splitEnd = chrono::high_resolution_clock::now();

        writeStudentsToFile("vargsiukai.txt",vargsiukai);
        writeStudentsToFile("kietiakai.txt",kietiakai);

        auto writeEnd = chrono::high_resolution_clock::now();

        cout<<"Nuskaitymo laikas: "
            <<chrono::duration<double>(readEnd-start).count()<<" s\n";

        cout<<"Skirstymo laikas: "
            <<chrono::duration<double>(splitEnd-readEnd).count()<<" s\n";

        cout<<"Rasymo laikas: "
            <<chrono::duration<double>(writeEnd-splitEnd).count()<<" s\n";
    }

    catch(const exception& e){
        cout << e.what() << endl;
    }

    return 0;
}
