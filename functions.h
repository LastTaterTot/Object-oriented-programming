#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "student.h"
#include <string>

// FILE GENERATION
void generateFile(const std::string& filename, int count);

// TEMPLATE FUNKCIJOS
template <typename Container>
Container readFile(const std::string& filename);

template <typename Container>
void splitStrategy1(const Container& students,
                    Container& vargsiukai,
                    Container& kietiakai);

template <typename Container>
void splitStrategy2(Container& students,
                    Container& vargsiukai);

template <typename Container>
void splitStrategy3(Container& students,
                    Container& vargsiukai,
                    Container& kietiakai);

// WRITE
template <typename Container>
void writeStudentsToFile(const std::string& filename,
                         const Container& students);

#include "functions.tpp"

#endif
