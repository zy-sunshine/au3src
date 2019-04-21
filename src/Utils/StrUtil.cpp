#include "StrUtil.h"
#include <string.h>

int CmpSort(const char* a, const char* b) {
    return strcmp(a, b);
}

int CmpSortReverse(const char* a, const char* b) {
    return strcmp(b, a);
}

int DistinctChars(const char *a)
{
    int dist = 0;
   
    while (*a != '\0') {
        if (!strchr(a + 1, *a))
            dist++;
        a++;
    }
    return dist;
}

int SortByNumberOfDistinctCharacters(const char* a, const char* b) {
    int res = DistinctChars(a) - DistinctChars(b);
    return (res) ? res : CmpSort(a, b);
}

int SortByLength(const char* a, const char* b) {
    int res = strlen(a) - strlen(b);
    return (res) ? res : CmpSort(a, b);
}
