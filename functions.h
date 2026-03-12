#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "student.h"
#include <vector>
#include <string>

double vidurkis(const std::vector<int>& nd);
double mediana(std::vector<int> nd);

double galutinisVid(const Student& s);
double galutinisMed(const Student& s);

std::vector<Student> readFile(const std::string& filename);

void printStudents(const std::vector<Student>& students);

void sortStudents(std::vector<Student>& students, int choice);

#endif
