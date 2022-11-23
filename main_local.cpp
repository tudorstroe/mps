#include <bits/stdc++.h>
#include <experimental/filesystem>

using namespace std;
using recursive_directory_iterator = std::experimental::filesystem::recursive_directory_iterator;

const int no_thresholds = 10;
const int no_f_measure = 256;
const int no_levels = 4;
const int trees_to_generate = 1000;
const int trees_in_set = 5;
const double train = 0.7;
const double validation = 0.25;

int get_random(int start, int end) {
    if (start > end) {
        return 0;
    }
    return start + rand() % (end - start + 1);
}

class Tree {

private:
    vector<int>** levels;
    vector<double*>* thresholds_ref;
    vector<int>* pixel_class_ref;
    int no_files;
    int start_set;
    int end_set;

    double get_pixel_threshold(const double* original_thresholds) {
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
        return end_threshold;
    }

    double get_file_score(vector<double*> thresholds, vector<int> pixel_class) {
        int TP = 0, FP = 0, TN = 0, FN = 0;

        for (int i = 0; i < (int)pixel_class.size(); ++i) {
            double pixel_threshold = get_pixel_threshold(thresholds[i]);
            double pixel_deduced_class;

            if (pixel_threshold > thresholds[i][0]) {
                pixel_deduced_class = 1;
            } else {
                pixel_deduced_class = 0;
            }

            if (pixel_deduced_class == 0 && pixel_class[i] == 0) {
                ++TP;
            } else if (pixel_deduced_class == 0 && pixel_class[i] == 1) {
                ++FP;
            } else if (pixel_deduced_class == 1 && pixel_class[i] == 1) {
                ++TN;
            } else if (pixel_deduced_class == 1 && pixel_class[i] == 0) {
                ++FN;
            }
        }
        return 1.0 * TP / (1.0 * TP + 0.5 * (FP + FN));
    }

    double get_overall_score() {
        double current_score = 0;
        for (int i = start_set; i <= end_set; ++i) {
            current_score += get_file_score(thresholds_ref[i], pixel_class_ref[i]);
        }

        return current_score / (1.0 * no_files);
    }

public:
    double score;

    explicit Tree(vector<double*>* thresholds, vector<int>* pixel_class, int no_files, int start_set, int end_set) {
        this->thresholds_ref = thresholds;
        this->pixel_class_ref = pixel_class;
        this->no_files = no_files;
        this->start_set = start_set;
        this->end_set = end_set;

        levels = new vector<int>*[no_levels];

        for (int i = 0; i < no_levels; ++i) {
            levels[i] = new vector<int>[no_thresholds + 1];

            for (int j = 1; j <= no_thresholds; ++j) {
                int prev = 0;
                bool prev_max_updated = false;
                for (int k = 0; k < no_thresholds; ++k) {
                    levels[i][j].push_back(get_random(prev + 1, min(prev + 4, no_thresholds + 1)));

                    if (levels[i][j][k] == no_thresholds + 1) {
                        levels[i][j][k] = 0;
                        if (!prev_max_updated) {
                            prev = no_thresholds + 1;
                            prev_max_updated = true;
                        }
                    } else if (levels[i][j][k] != 0) {
                        prev = levels[i][j][k];
                    }
                }
            }
        }
        this->score = this->get_overall_score();
    }

    void change_set(int start, int end) {
        this->start_set = start;
        this->end_set = end;
        this->score = this->get_overall_score();
    }

    void print_tree() {
        cout << "double get_global(const double* original_thresholds) {\n"
                "        int no_levels = 4, no_thresholds = 15;\n"
                "        vector<int>** levels;\n"
                "        levels = new vector<int>*[no_levels];\n"
                "\n"
                "for (int i = 0; i < no_levels; ++i) {\n"
                "   levels[i] = new vector<int>[no_thresholds + 1];\n"
                "   for (int j = 0; j <= no_thresholds; ++j) {\n"
                "       for (int k = 0; k < no_thresholds; ++k) {\n"
                "           levels[i][j].push_back(0);\n"
                "       }\n"
                "   }\n"
                "}\n";
        for (int i = 0; i < no_levels; ++i) {
            for (int j = 1; j <= no_thresholds; ++j) {
                for (int k = 0; k < no_thresholds; ++k) {
                    cout << "levels[" << i << "][" << j << "][" << k << "] = " << levels[i][j][k] << ";\n";
                }
            }
        }
        cout << "        auto *thresholds = new double[no_thresholds + 1];\n"
                "        for (int i = 0; i < no_thresholds; ++i) {\n"
                "            thresholds[i + 1] = original_thresholds[i];\n"
                "        }\n"
                "\n"
                "        double *threshold_copy;\n"
                "\n"
                "        threshold_copy = new double[no_thresholds + 1];\n"
                "        double end_threshold = 1;\n"
                "\n"
                "        for (int i = 0; i < no_levels; ++i) {\n"
                "            for (int j = 1; j <= no_thresholds; ++j) {\n"
                "                int count = 0;\n"
                "                for (int k = 0; k < no_thresholds; ++k) {\n"
                "                    int index = levels[i][j][k];\n"
                "                    if (index != 0 && thresholds[index] != 0) {\n"
                "                        ++count;\n"
                "                        threshold_copy[j] += thresholds[index];\n"
                "                    }\n"
                "                }\n"
                "                if (count == 0) {\n"
                "                    threshold_copy[j] = 0;\n"
                "                } else {\n"
                "                    threshold_copy[j] /= 1.0 * count;\n"
                "                }\n"
                "            }\n"
                "\n"
                "            for (int j = 1; j <= no_thresholds; ++j) {\n"
                "                thresholds[j] = threshold_copy[j];\n"
                "                if (thresholds[j] != 0) {\n"
                "                    end_threshold = min(end_threshold, thresholds[j]);\n"
                "                }\n"
                "            }\n"
                "        }\n"
                "        if (end_threshold > 1) {\n"
                "            end_threshold = 1;\n"
                "        }\n"
                "        return end_threshold;\n"
                "    }";
    }
};

recursive_directory_iterator get_directory() {
    return recursive_directory_iterator(std::experimental::filesystem::current_path().string() + "/mps-global/MPS-Global");
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
        for (int i = 1; i <= no_thresholds; i++) {
            f >> t[i] >> dump_char;
        }
    }
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

    vector<Tree*> train_trees;

    for (int k = 0; k < trees_to_generate; ++k) {
        Tree* tree = new Tree(thresholds, pixel_class, number_of_files, 0, (int)(number_of_files * train));
        double score = tree->score;

        if (train_trees.size() < trees_in_set) {
            train_trees.push_back(tree);
        } else {
            int min_index = 0;
            for (int i = 1; i < trees_in_set; ++i) {
                if (train_trees[i]->score > train_trees[min_index]->score) {
                    min_index = i;
                }
            }

            if (score > train_trees[min_index]->score) {
                train_trees[min_index] = tree;
            }
        }
    }

    Tree* train_tree;
    for (int k = 0; k < trees_in_set; ++k) {
        if (k == 0) {
            train_tree = train_trees[k];
        } else {
            if (train_trees[k]->score > train_tree->score) {
                train_tree = train_trees[k];
            }
        }
    }

    Tree* validation_tree;
    for (int k = 0; k < trees_in_set; ++k) {
        train_trees[k]->change_set((int)(number_of_files * train), (int)(number_of_files * (train + validation)));
        if (k == 0) {
            validation_tree = train_trees[0];
        }
        if (train_trees[k]->score > validation_tree->score) {
            validation_tree = train_trees[k];
        }
    }

    train_tree->change_set((int)(number_of_files * (train + validation)), number_of_files - 1);
    validation_tree->change_set((int)(number_of_files * (train + validation)), number_of_files - 1);

    Tree* result_tree = train_tree;
    if (validation_tree->score > train_tree->score) {
        result_tree = validation_tree;
    }

    result_tree->change_set(0, number_of_files - 1);

    result_tree->print_tree();

    cout << "\nBest tree score for local: " << result_tree->score << '\n';

    return 0;
}
