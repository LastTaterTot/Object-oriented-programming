#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "student.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

// ================= FILE GENERATION =================
void generateFile(const std::string& filename, int count);

// ================= READ =================
template <typename Container>
Container readFile(const std::string& filename) {
    Container students;
    std::ifstream in(filename);

    if (!in) throw std::runtime_error("Nepavyko atidaryti failo");

    Student s;
    while (in >> s.name >> s.surname >> s.finalGrade) {
        students.push_back(s);
    }

    return students;
}

// ================= WRITE =================
template <typename Container>
void writeStudentsToFile(const std::string& filename,
                         const Container& students) {
    std::ofstream out(filename);

    for (const auto& s : students) {
        out << s.name << " "
            << s.surname << " "
            << s.finalGrade << "\n";
    }
}

// ================= STRATEGY 1 =================
template <typename Container>
void splitStrategy1(const Container& students,
                    Container& vargsiukai,
                    Container& kietiakai) {

    for (const auto& s : students) {
        if (s.finalGrade < 5)
            vargsiukai.push_back(s);
        else
            kietiakai.push_back(s);
    }
}

// ================= STRATEGY 2 =================
template <typename Container>
void splitStrategy2(Container& students,
                    Container& vargsiukai) {

    for (auto it = students.begin(); it != students.end();) {
        if (it->finalGrade < 5) {
            vargsiukai.push_back(*it);
            it = students.erase(it);
        } else {
            ++it;
        }
    }
}

// ================= STRATEGY 3 =================
template <typename Container>
void splitStrategy3(Container& students,
                    Container& vargsiukai,
                    Container& kietiakai) {

    auto it = std::partition(students.begin(), students.end(),
        [](const Student& s) { return s.finalGrade >= 5; });

    kietiakai.insert(kietiakai.end(), students.begin(), it);
    vargsiukai.insert(vargsiukai.end(), it, students.end());
}

#endif
