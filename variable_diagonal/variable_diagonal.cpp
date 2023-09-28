#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** a = new int*[lines];
    for (size_t i = 0; i < lines; ++i) {
        a[i] = new int[columns];
    }
    int k = 0;
    for (int d = 0; d < lines + columns - 1; d++) {
        for (int i = 0; i < lines; i++) {
            int j = d - i;
            if (j >= 0 && j < columns) {
                a[i][j] = k++;
            }
        }
    }
    return a;
}