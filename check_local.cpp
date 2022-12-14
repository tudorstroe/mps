#include <bits/stdc++.h>
#include <experimental/filesystem>

using namespace std;
using recursive_directory_iterator = std::experimental::filesystem::recursive_directory_iterator;

const int no_thresholds = 10;
const int no_levels = 4;

recursive_directory_iterator get_directory() {
    return recursive_directory_iterator(std::experimental::filesystem::current_path().string() + "/mps-local/MPS-Local");
}

void read_data_from_file(string& filePath, vector<double*>& thresholds, vector<int>& pixel_class) {
    ifstream f(filePath);

    while (!f.eof()) {
        char dump_char;
        int aux;
        double* t = new double[no_thresholds + 1];
        thresholds.push_back(t);

        f >> t[0] >> dump_char;

        f >> aux >> dump_char;
        pixel_class.push_back(aux);
        for (int i = 1; i <= no_thresholds; i++) {
            f >> t[i] >> dump_char;
        }
    }
}

double get_pixel_threshold(double* &original_thresholds);

double get_file_score(vector<double*> &thresholds, vector<int> &pixel_class) {
    int TP = 0, FP = 0, TN = 0, FN = 0;
    for (int i = 0; i < (int)pixel_class.size(); ++i) {
        double pixel_threshold = get_pixel_threshold(thresholds[i]);
        double pixel_deduced_class;

        if (pixel_threshold > thresholds[i][0]) {
            pixel_deduced_class = 1;
        } else {
            pixel_deduced_class = 0;
        }

        if (pixel_deduced_class == 1 && pixel_class[i] == 1) {
            ++TP;
        } else if (pixel_deduced_class == 1 && pixel_class[i] == 0) {
            ++FP;
        } else if (pixel_deduced_class == 0 && pixel_class[i] == 0) {
            ++TN;
        } else if (pixel_deduced_class == 0 && pixel_class[i] == 1) {
            ++FN;
        }
    }
    return 1.0 * TP / (1.0 * TP + 0.5 * (FP + FN));
}

int main() {
    srand(time(0));
    auto directory = get_directory();
    int number_of_files = 0;

    for (auto& file : directory) {
        ++number_of_files;
    }
    directory = get_directory();

    int index = 0;

    vector<double*>* thresholds = new vector<double*>[number_of_files];
    vector<int>* pixel_class = new vector<int>[number_of_files];

    for (auto& file : directory) {
        string filePath = file.path().string();

        read_data_from_file(filePath, thresholds[index], pixel_class[index]);
        ++index;
    }

    double score = 0;
    for (int i = 0; i < number_of_files; ++i) {
        score += get_file_score(thresholds[i], pixel_class[i]);
    }

    score /= (1.0 * number_of_files);

    cout << "\nScore for local: " << score << '\n';

    return 0;
}
double get_pixel_threshold(double* &original_thresholds) {
    int no_levels = 4, no_thresholds = 10;
    vector<int>** levels;
    levels = new vector<int>*[no_levels];

    for (int i = 0; i < no_levels; ++i) {
        levels[i] = new vector<int>[no_thresholds + 1];
        for (int j = 0; j <= no_thresholds; ++j) {
            for (int k = 0; k < no_thresholds; ++k) {
                levels[i][j].push_back(0);
            }
        }
    }
    levels[0][1][0] = 3;
    levels[0][1][1] = 5;
    levels[0][1][2] = 6;
    levels[0][1][3] = 7;
    levels[0][1][4] = 8;
    levels[0][1][5] = 0;
    levels[0][1][6] = 0;
    levels[0][1][7] = 0;
    levels[0][1][8] = 0;
    levels[0][1][9] = 0;
    levels[0][2][0] = 2;
    levels[0][2][1] = 5;
    levels[0][2][2] = 8;
    levels[0][2][3] = 0;
    levels[0][2][4] = 0;
    levels[0][2][5] = 0;
    levels[0][2][6] = 0;
    levels[0][2][7] = 0;
    levels[0][2][8] = 0;
    levels[0][2][9] = 0;
    levels[0][3][0] = 4;
    levels[0][3][1] = 8;
    levels[0][3][2] = 9;
    levels[0][3][3] = 0;
    levels[0][3][4] = 0;
    levels[0][3][5] = 0;
    levels[0][3][6] = 0;
    levels[0][3][7] = 0;
    levels[0][3][8] = 0;
    levels[0][3][9] = 0;
    levels[0][4][0] = 4;
    levels[0][4][1] = 8;
    levels[0][4][2] = 10;
    levels[0][4][3] = 0;
    levels[0][4][4] = 0;
    levels[0][4][5] = 0;
    levels[0][4][6] = 0;
    levels[0][4][7] = 0;
    levels[0][4][8] = 0;
    levels[0][4][9] = 0;
    levels[0][5][0] = 3;
    levels[0][5][1] = 4;
    levels[0][5][2] = 8;
    levels[0][5][3] = 0;
    levels[0][5][4] = 0;
    levels[0][5][5] = 0;
    levels[0][5][6] = 0;
    levels[0][5][7] = 0;
    levels[0][5][8] = 0;
    levels[0][5][9] = 0;
    levels[0][6][0] = 4;
    levels[0][6][1] = 7;
    levels[0][6][2] = 9;
    levels[0][6][3] = 0;
    levels[0][6][4] = 0;
    levels[0][6][5] = 0;
    levels[0][6][6] = 0;
    levels[0][6][7] = 0;
    levels[0][6][8] = 0;
    levels[0][6][9] = 0;
    levels[0][7][0] = 4;
    levels[0][7][1] = 8;
    levels[0][7][2] = 10;
    levels[0][7][3] = 0;
    levels[0][7][4] = 0;
    levels[0][7][5] = 0;
    levels[0][7][6] = 0;
    levels[0][7][7] = 0;
    levels[0][7][8] = 0;
    levels[0][7][9] = 0;
    levels[0][8][0] = 1;
    levels[0][8][1] = 5;
    levels[0][8][2] = 7;
    levels[0][8][3] = 8;
    levels[0][8][4] = 10;
    levels[0][8][5] = 0;
    levels[0][8][6] = 0;
    levels[0][8][7] = 0;
    levels[0][8][8] = 0;
    levels[0][8][9] = 0;
    levels[0][9][0] = 4;
    levels[0][9][1] = 5;
    levels[0][9][2] = 6;
    levels[0][9][3] = 8;
    levels[0][9][4] = 0;
    levels[0][9][5] = 0;
    levels[0][9][6] = 0;
    levels[0][9][7] = 0;
    levels[0][9][8] = 0;
    levels[0][9][9] = 0;
    levels[0][10][0] = 1;
    levels[0][10][1] = 2;
    levels[0][10][2] = 4;
    levels[0][10][3] = 6;
    levels[0][10][4] = 10;
    levels[0][10][5] = 0;
    levels[0][10][6] = 0;
    levels[0][10][7] = 0;
    levels[0][10][8] = 0;
    levels[0][10][9] = 0;
    levels[1][1][0] = 3;
    levels[1][1][1] = 5;
    levels[1][1][2] = 8;
    levels[1][1][3] = 0;
    levels[1][1][4] = 0;
    levels[1][1][5] = 0;
    levels[1][1][6] = 0;
    levels[1][1][7] = 0;
    levels[1][1][8] = 0;
    levels[1][1][9] = 0;
    levels[1][2][0] = 1;
    levels[1][2][1] = 2;
    levels[1][2][2] = 5;
    levels[1][2][3] = 8;
    levels[1][2][4] = 0;
    levels[1][2][5] = 0;
    levels[1][2][6] = 0;
    levels[1][2][7] = 0;
    levels[1][2][8] = 0;
    levels[1][2][9] = 0;
    levels[1][3][0] = 2;
    levels[1][3][1] = 4;
    levels[1][3][2] = 6;
    levels[1][3][3] = 8;
    levels[1][3][4] = 10;
    levels[1][3][5] = 0;
    levels[1][3][6] = 0;
    levels[1][3][7] = 0;
    levels[1][3][8] = 0;
    levels[1][3][9] = 0;
    levels[1][4][0] = 1;
    levels[1][4][1] = 5;
    levels[1][4][2] = 8;
    levels[1][4][3] = 9;
    levels[1][4][4] = 0;
    levels[1][4][5] = 0;
    levels[1][4][6] = 0;
    levels[1][4][7] = 0;
    levels[1][4][8] = 0;
    levels[1][4][9] = 0;
    levels[1][5][0] = 2;
    levels[1][5][1] = 3;
    levels[1][5][2] = 5;
    levels[1][5][3] = 8;
    levels[1][5][4] = 10;
    levels[1][5][5] = 0;
    levels[1][5][6] = 0;
    levels[1][5][7] = 0;
    levels[1][5][8] = 0;
    levels[1][5][9] = 0;
    levels[1][6][0] = 3;
    levels[1][6][1] = 7;
    levels[1][6][2] = 10;
    levels[1][6][3] = 0;
    levels[1][6][4] = 0;
    levels[1][6][5] = 0;
    levels[1][6][6] = 0;
    levels[1][6][7] = 0;
    levels[1][6][8] = 0;
    levels[1][6][9] = 0;
    levels[1][7][0] = 4;
    levels[1][7][1] = 5;
    levels[1][7][2] = 9;
    levels[1][7][3] = 0;
    levels[1][7][4] = 0;
    levels[1][7][5] = 0;
    levels[1][7][6] = 0;
    levels[1][7][7] = 0;
    levels[1][7][8] = 0;
    levels[1][7][9] = 0;
    levels[1][8][0] = 4;
    levels[1][8][1] = 5;
    levels[1][8][2] = 8;
    levels[1][8][3] = 9;
    levels[1][8][4] = 10;
    levels[1][8][5] = 0;
    levels[1][8][6] = 0;
    levels[1][8][7] = 0;
    levels[1][8][8] = 0;
    levels[1][8][9] = 0;
    levels[1][9][0] = 3;
    levels[1][9][1] = 4;
    levels[1][9][2] = 6;
    levels[1][9][3] = 10;
    levels[1][9][4] = 0;
    levels[1][9][5] = 0;
    levels[1][9][6] = 0;
    levels[1][9][7] = 0;
    levels[1][9][8] = 0;
    levels[1][9][9] = 0;
    levels[1][10][0] = 4;
    levels[1][10][1] = 5;
    levels[1][10][2] = 6;
    levels[1][10][3] = 9;
    levels[1][10][4] = 10;
    levels[1][10][5] = 0;
    levels[1][10][6] = 0;
    levels[1][10][7] = 0;
    levels[1][10][8] = 0;
    levels[1][10][9] = 0;
    levels[2][1][0] = 4;
    levels[2][1][1] = 5;
    levels[2][1][2] = 9;
    levels[2][1][3] = 10;
    levels[2][1][4] = 0;
    levels[2][1][5] = 0;
    levels[2][1][6] = 0;
    levels[2][1][7] = 0;
    levels[2][1][8] = 0;
    levels[2][1][9] = 0;
    levels[2][2][0] = 1;
    levels[2][2][1] = 2;
    levels[2][2][2] = 5;
    levels[2][2][3] = 9;
    levels[2][2][4] = 10;
    levels[2][2][5] = 0;
    levels[2][2][6] = 0;
    levels[2][2][7] = 0;
    levels[2][2][8] = 0;
    levels[2][2][9] = 0;
    levels[2][3][0] = 4;
    levels[2][3][1] = 7;
    levels[2][3][2] = 0;
    levels[2][3][3] = 0;
    levels[2][3][4] = 0;
    levels[2][3][5] = 0;
    levels[2][3][6] = 0;
    levels[2][3][7] = 0;
    levels[2][3][8] = 0;
    levels[2][3][9] = 0;
    levels[2][4][0] = 3;
    levels[2][4][1] = 6;
    levels[2][4][2] = 8;
    levels[2][4][3] = 10;
    levels[2][4][4] = 0;
    levels[2][4][5] = 0;
    levels[2][4][6] = 0;
    levels[2][4][7] = 0;
    levels[2][4][8] = 0;
    levels[2][4][9] = 0;
    levels[2][5][0] = 2;
    levels[2][5][1] = 4;
    levels[2][5][2] = 5;
    levels[2][5][3] = 9;
    levels[2][5][4] = 0;
    levels[2][5][5] = 0;
    levels[2][5][6] = 0;
    levels[2][5][7] = 0;
    levels[2][5][8] = 0;
    levels[2][5][9] = 0;
    levels[2][6][0] = 3;
    levels[2][6][1] = 6;
    levels[2][6][2] = 8;
    levels[2][6][3] = 0;
    levels[2][6][4] = 0;
    levels[2][6][5] = 0;
    levels[2][6][6] = 0;
    levels[2][6][7] = 0;
    levels[2][6][8] = 0;
    levels[2][6][9] = 0;
    levels[2][7][0] = 1;
    levels[2][7][1] = 3;
    levels[2][7][2] = 4;
    levels[2][7][3] = 5;
    levels[2][7][4] = 7;
    levels[2][7][5] = 0;
    levels[2][7][6] = 0;
    levels[2][7][7] = 0;
    levels[2][7][8] = 0;
    levels[2][7][9] = 0;
    levels[2][8][0] = 3;
    levels[2][8][1] = 4;
    levels[2][8][2] = 8;
    levels[2][8][3] = 10;
    levels[2][8][4] = 0;
    levels[2][8][5] = 0;
    levels[2][8][6] = 0;
    levels[2][8][7] = 0;
    levels[2][8][8] = 0;
    levels[2][8][9] = 0;
    levels[2][9][0] = 3;
    levels[2][9][1] = 5;
    levels[2][9][2] = 7;
    levels[2][9][3] = 10;
    levels[2][9][4] = 0;
    levels[2][9][5] = 0;
    levels[2][9][6] = 0;
    levels[2][9][7] = 0;
    levels[2][9][8] = 0;
    levels[2][9][9] = 0;
    levels[2][10][0] = 1;
    levels[2][10][1] = 2;
    levels[2][10][2] = 4;
    levels[2][10][3] = 7;
    levels[2][10][4] = 8;
    levels[2][10][5] = 9;
    levels[2][10][6] = 0;
    levels[2][10][7] = 0;
    levels[2][10][8] = 0;
    levels[2][10][9] = 0;
    levels[3][1][0] = 2;
    levels[3][1][1] = 5;
    levels[3][1][2] = 8;
    levels[3][1][3] = 10;
    levels[3][1][4] = 0;
    levels[3][1][5] = 0;
    levels[3][1][6] = 0;
    levels[3][1][7] = 0;
    levels[3][1][8] = 0;
    levels[3][1][9] = 0;
    levels[3][2][0] = 2;
    levels[3][2][1] = 6;
    levels[3][2][2] = 9;
    levels[3][2][3] = 0;
    levels[3][2][4] = 0;
    levels[3][2][5] = 0;
    levels[3][2][6] = 0;
    levels[3][2][7] = 0;
    levels[3][2][8] = 0;
    levels[3][2][9] = 0;
    levels[3][3][0] = 1;
    levels[3][3][1] = 4;
    levels[3][3][2] = 6;
    levels[3][3][3] = 9;
    levels[3][3][4] = 0;
    levels[3][3][5] = 0;
    levels[3][3][6] = 0;
    levels[3][3][7] = 0;
    levels[3][3][8] = 0;
    levels[3][3][9] = 0;
    levels[3][4][0] = 4;
    levels[3][4][1] = 7;
    levels[3][4][2] = 9;
    levels[3][4][3] = 10;
    levels[3][4][4] = 0;
    levels[3][4][5] = 0;
    levels[3][4][6] = 0;
    levels[3][4][7] = 0;
    levels[3][4][8] = 0;
    levels[3][4][9] = 0;
    levels[3][5][0] = 4;
    levels[3][5][1] = 8;
    levels[3][5][2] = 10;
    levels[3][5][3] = 0;
    levels[3][5][4] = 0;
    levels[3][5][5] = 0;
    levels[3][5][6] = 0;
    levels[3][5][7] = 0;
    levels[3][5][8] = 0;
    levels[3][5][9] = 0;
    levels[3][6][0] = 3;
    levels[3][6][1] = 7;
    levels[3][6][2] = 10;
    levels[3][6][3] = 0;
    levels[3][6][4] = 0;
    levels[3][6][5] = 0;
    levels[3][6][6] = 0;
    levels[3][6][7] = 0;
    levels[3][6][8] = 0;
    levels[3][6][9] = 0;
    levels[3][7][0] = 2;
    levels[3][7][1] = 5;
    levels[3][7][2] = 6;
    levels[3][7][3] = 7;
    levels[3][7][4] = 0;
    levels[3][7][5] = 0;
    levels[3][7][6] = 0;
    levels[3][7][7] = 0;
    levels[3][7][8] = 0;
    levels[3][7][9] = 0;
    levels[3][8][0] = 3;
    levels[3][8][1] = 7;
    levels[3][8][2] = 10;
    levels[3][8][3] = 0;
    levels[3][8][4] = 0;
    levels[3][8][5] = 0;
    levels[3][8][6] = 0;
    levels[3][8][7] = 0;
    levels[3][8][8] = 0;
    levels[3][8][9] = 0;
    levels[3][9][0] = 1;
    levels[3][9][1] = 3;
    levels[3][9][2] = 5;
    levels[3][9][3] = 7;
    levels[3][9][4] = 10;
    levels[3][9][5] = 0;
    levels[3][9][6] = 0;
    levels[3][9][7] = 0;
    levels[3][9][8] = 0;
    levels[3][9][9] = 0;
    levels[3][10][0] = 4;
    levels[3][10][1] = 5;
    levels[3][10][2] = 7;
    levels[3][10][3] = 10;
    levels[3][10][4] = 0;
    levels[3][10][5] = 0;
    levels[3][10][6] = 0;
    levels[3][10][7] = 0;
    levels[3][10][8] = 0;
    levels[3][10][9] = 0;
    auto *thresholds = new double[no_thresholds + 1];
    for (int i = 0; i <= no_thresholds; ++i) {
        thresholds[i] = original_thresholds[i];
    }

    double *threshold_copy;

    threshold_copy = new double[no_thresholds + 1];
    double end_threshold = 1;

    for (int i = 0; i < no_levels; ++i) {
        for (int j = 1; j <= no_thresholds; ++j) {
            int count = 0;
            for (int k = 0; k < no_thresholds; ++k) {
                int index = levels[i][j][k];
                if (index != 0 && thresholds[index] != 0) {
                    ++count;
                    threshold_copy[j] += thresholds[index];
                }
            }
            if (count == 0) {
                threshold_copy[j] = 0;
            } else {
                threshold_copy[j] /= 1.0 * count;
            }
        }

        for (int j = 1; j <= no_thresholds; ++j) {
            thresholds[j] = threshold_copy[j];
            if (thresholds[j] != 0) {
                end_threshold = min(end_threshold, thresholds[j]);
            }
        }
    }
    if (end_threshold > 1) {
        end_threshold = 1;
    }
    delete[] thresholds;
    delete[] threshold_copy;

    for (int i = 0; i < no_levels; ++i) {
        delete[] levels[i];
    }
    delete[] levels;
    return min(end_threshold * 5.53 / 5, 1.0);
}