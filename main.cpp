#include <bits/stdc++.h>

using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

const int no_thresholds = 15;
const int no_f_measure = 256;

int main() {
    auto directory = recursive_directory_iterator(std::filesystem::current_path().string() + "\\..\\mps-global");

    int number_of_files = 0;
    double average = 0;
    for (auto& file : directory) {
        ++number_of_files;

        string filePath = file.path().string();
        ifstream f(filePath);

        auto *thresholds = new double[no_thresholds + 1];
        auto *f_measure = new double[no_f_measure + 1];
        char dump_char;
        for (int i = 0; i <= no_thresholds; i++) {
            f >> thresholds[i] >> dump_char;
        }
        for (int i = 1; i <= no_f_measure; i++) {
            f >> f_measure[i] >> dump_char;
        }
        average += f_measure[(int)(thresholds[0] * 255.0)];
    }

    average /= number_of_files;
    cout << average << '\n';

    return 0;
}