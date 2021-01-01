#define AnimationMode
#include "tricks.h"

int main()
{
    system("cls");
    int m[][4] = {
        { 2, 6, 4, 5 },
        { 6, 7, 3, 9 },
        { 5, 6, 8, 2 }
    };
    int rowSize = sizeof(m) / sizeof(m[0]);
    int colSize = sizeof(m[0]) / sizeof(int);
    int** p = initMatrix(m[0], rowSize, colSize);
    showMatrix(p, rowSize, colSize);

    for (size_t i = 0; i < rowSize; i++) {
        for (size_t j = 0; j < colSize; j++) {
            p[i][j] = (p[i][j] + 1) % 10;
            showMatrix(p, rowSize, colSize);
#ifdef AnimationMode
            getchar();
#endif
        }
    }
    printAlarm("hello world!");
    freeMatrix(p);
    // getchar();
    return 0;
}

