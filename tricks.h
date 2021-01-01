// Created by zyh
// Version 0.1.20210101

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define COLOR_NONE "\033[0m"
#define FONT_COLOR_GREEN "\033[0;32m"
#define FONT_COLOR_YELLOW "\033[0;33m"
#define FONT_COLOR_CYAN "\033[0;36m"

#define COLOR_NONE_UNDERLINE "\033[4m"
#define FONT_COLOR_GREEN_UNDERLINE "\033[4;32m"
#define FONT_COLOR_YELLOW_UNDERLINE "\033[4;33m"
#define FONT_COLOR_CYAN_UNDERLINE "\033[4;36m"

//Print alarm info
#define printAlarm(cstr) printf("%s:%d:" cstr "\n", __FILE__, __LINE__)

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// Creates a two-dimensional array of one-dimensional representations
int** initMatrix(const int* start, int rowSize, int colSize)
{
    int** matrix = (int**)calloc(rowSize, sizeof(int*));
    int* head = (int*)calloc(rowSize * colSize, sizeof(int));
    if (matrix == NULL || head == NULL) {
        printAlarm("error: calloc return NULL");
        return NULL;
    }
    for (size_t i = 0; i < rowSize; i++) {
        matrix[i] = head + i * colSize;
    }
    memcpy(head, start, sizeof(int) * rowSize * colSize);
    return matrix;
}

// Releases a two-dimensional array of one-dimensional representations
void freeMatrix(int** matrix)
{
    free(matrix[0]);
    free(matrix);
}

void showMatrix(int** M, int rowSize, int colSize)
{
#ifdef AnimationMode
    HideCursor();
    gotoxy(0, 0);
#endif
    int width = 2;
    static int id = 0;
    static int** _M = NULL;
    static int _rowSize = 0;
    static int _colSize = 0;
    if (_rowSize != rowSize || _colSize != colSize) {

        if (_M != NULL) {
            free(_M[0]);
            free(_M);
        }

        _M = (int**)calloc(rowSize, sizeof(int*));
        if (_M == NULL) {
            printAlarm("calloc error");
            exit(-1);
        }

        _M[0] = (int*)calloc(rowSize * colSize, sizeof(int));
        if (_M[0] == NULL) {
            printAlarm("calloc error");
            exit(-1);
        }

        _rowSize = rowSize;
        _colSize = colSize;

        for (size_t r = 0; r < _rowSize; r++) {
            _M[r] = _M[0] + r * _colSize;
        }

        //memcpy(_M[0], M[0], sizeof(int) * rowSize * colSize);
    }
    printf(FONT_COLOR_YELLOW "%2d" COLOR_NONE " ---\n", id++);
    printf("  >");
    for (int col = 0; col < colSize; col++) {
        if (col % 10 == 0) {
            printf(FONT_COLOR_GREEN_UNDERLINE "%*d" COLOR_NONE, width, col % 10);
        } else {
            printf(COLOR_NONE_UNDERLINE "%*d" COLOR_NONE, width, col % 10);
        }
    }
    printf("\n");

    for (int row = 0; row < rowSize; row++) {

        if (row % 10 == 0) {
            printf(FONT_COLOR_GREEN "%2d" COLOR_NONE "|", row % 10);
        } else {
            printf("%2d|", row % 10);
        }

        for (int col = 0; col < colSize; col++) {
            if (_M != NULL && _M[row][col] != M[row][col]) {
                if (M[row][col] == 0) {
                    printf(FONT_COLOR_CYAN "%*s" COLOR_NONE, width, ".");
                } else if (M[row][col] == INT_MAX) {
                    printf(FONT_COLOR_CYAN "%*.*s" COLOR_NONE, width, width - 1, "MAX");
                } else {
                    printf(FONT_COLOR_CYAN "% *d" COLOR_NONE, width, M[row][col]);
                }

                _M[row][col] = M[row][col];

            } else {
                if (M[row][col] == 0) {
                    printf("%*s", width, ".");
                } else if (M[row][col] == INT_MAX) {
                    printf("%*.*s", width, width - 1, "MAX");
                } else {
                    printf("% *d", width, M[row][col]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void showArray(const int* arr, int size)
{
    int width = 3;
    static int id = 0;
    static int* _arr = NULL;
    static int _size = 0;

    if (_size != size) {

        if (_arr != NULL) {
            free(_arr);
        }

        _arr = (int*)calloc(size, sizeof(int));
        if (_arr == NULL) {
            printAlarm("calloc error");
            exit(-1);
        }
        _size = size;
    }

    printf(FONT_COLOR_GREEN "%d" COLOR_NONE " ---\n", id++);
    printf("# ");
    for (size_t i = 0; i < size; i++) {
        if (_arr != NULL && _arr[i] != arr[i]) {
            printf(FONT_COLOR_CYAN "%*d  " COLOR_NONE, width, arr[i]);
            _arr[i] = arr[i];
        } else {
            printf("%*d  ", width, arr[i]);
        }
    }
    printf("\n");

    return;
}

void showString(const char* cstr)
{
    // int width = 2;
    int size = strlen(cstr);
    static int id = 0;
    static int* _cstr = NULL;
    static int _size = 0;

    if (_size != size) {

        if (_cstr != NULL) {
            free(_cstr);
        }

        _cstr = (int*)calloc(size, sizeof(int));
        if (_cstr == NULL) {
            printAlarm("calloc error");
            exit(-1);
        }
        _size = size;
    }

    printf(FONT_COLOR_GREEN "%d" COLOR_NONE " ---\n", id++);
    printf("# ");
    for (size_t i = 0; i < size; i++) {
        if (_cstr != NULL && _cstr[i] != cstr[i]) {
            printf(FONT_COLOR_CYAN "%c " COLOR_NONE, cstr[i]);
            _cstr[i] = cstr[i];
        } else {
            printf("%c ", cstr[i]);
        }
    }
    printf("\n");
    return;
}

