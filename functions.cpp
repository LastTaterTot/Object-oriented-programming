#include "functions.h"
#include <random>

void generateFile(const std::string& filename, int count) {
    std::ofstream out(filename);

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist(1.0, 10.0);

    for (int i = 0; i < count; i++) {
        out << "Vardas" << i << " "
            << "Pavarde" << i << " "
            << dist(gen) << "\n";
    }
}
