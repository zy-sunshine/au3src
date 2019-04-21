#pragma once

int CmpSort(const char* a, const char* b);
int CmpSortReverse(const char* a, const char* b);
int SortByNumberOfDistinctCharacters(const char* a, const char* b);
int SortByLength(const char* a, const char* b);
/* simple bubble sort :) */
template <typename T>
void Sort(T* arr, int len, int (*cmp_func)(const T a, const T b))
{
    char* temp;
    int i, j;
    for (i=0; i < len-1; i++) {
        for (j=0; j < len-1-i; j++) {
            if (cmp_func(arr[j], arr[j+1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
