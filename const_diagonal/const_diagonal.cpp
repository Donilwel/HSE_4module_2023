#include "const_diagonal.h"

#include "iostream"

void BuildDiagonalArray(TableType table) {
    int k = 0;
    for (int ii = 0; ii < LINES + COLUMNS - 1; ii++) {
        for (int i = 0; i < LINES; i++) {
            int j = ii - i;
            if (j >= 0 && j < COLUMNS) {
                table[i][j] = k++;
            }
        }
    }
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            std::cout << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
