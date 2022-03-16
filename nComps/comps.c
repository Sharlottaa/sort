//
// Created by ну я on 15.03.2022.
//

#include "comps.h"

void Swap(void *a, void *b, size_t size) {
    char *pa = a;
    char *pb = b;
    for (size_t i = 0; i < size; i++) {
        char t = *pa;
        *pa = *pb;
        *pb = t;
        *pa++;
        *pb++;
    }
}

long long getBubbleSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (size_t i = 0; i < size - 1 && ++nComps; i++)
        for (size_t j = size - 1; j > i && ++nComps; j--)
            if (a[j - 1] > a[j] && ++nComps)
                Swap(&a[j - 1], &a[j], sizeof(int));

    return nComps;
}

long long getSelectionSortNComp(int *a, size_t n) {
    long long nComps = 0;
    for (int i = 0; ++nComps && i < n; i++) {
        int min = a[i];
        int minIndex = i;
        for (int j = i + 1; ++nComps && j < n; j++)
            if (++nComps && a[j] < min) {
                min = a[j];
                minIndex = j;
            }
        if (++nComps && i != minIndex)
            Swap(&a[i], &a[minIndex], sizeof(int));
    }

    return nComps;
}

long long getInsertionSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (size_t i = 1; i < size && ++nComps; i++) {
        int t = a[i];
        size_t j = i;
        while (j > 0 && ++nComps && a[j - 1] > t && ++nComps) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }

    return nComps;
}

long long getCombSortNComp(int *a, size_t size) {
    size_t step = size;
    int swapped = 1;
    long long nComps = 0;
    while (step > 1 && ++nComps || swapped && ++nComps) {
        if (step > 1 && ++nComps)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size && ++nComps; ++i, ++j) {
            if (a[i] > a[j] && ++nComps) {
                Swap(&a[i], &a[j], sizeof(int));
                swapped = 1;
            }
        }
    }

    return nComps;
}

long long getShellSortNComp(int *a, size_t size) {
    long long nComps = 0;
    for (size_t step = size / 2; step > 0 && ++nComps; step /= 2) {
        for (size_t i = step; i < size && ++nComps; i++) {
            int tmp = a[i];
            size_t j;
            for (j = i; j >= step && ++nComps; j -= step) {
                if (tmp < a[j - step] && ++nComps)
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
    }
    return nComps;
}

long long getRadixSortNComp_(unsigned int *begin, unsigned int *end, unsigned int bit) {
    long long nComps = 0;
    if (!bit && ++nComps || end < begin + 1 && ++nComps)
        return nComps;

    unsigned int *left = begin, *right = end - 1;
    while (++nComps) {
        while (left < right && ++nComps && !(*left & bit) && ++nComps)
            left++;
        while (left < right && ++nComps && (*right & bit) && ++nComps)
            right--;
        if (left >= right && ++nComps)
            break;
        Swap(left, right, sizeof(unsigned int));
    }

    if (!(bit & *left) && ++nComps && left < end && ++nComps)
        left++;
    bit >>= 1;

    getRadixSortNComp_(begin, left, bit);
    getRadixSortNComp_(left, end, bit);
}

long long getRadixSortNComp(int *a, size_t size) {
    size_t i;
    long long nComps = 0;
    for (i = 0; i < size && ++nComps; i++) {
        a[i] ^= INT_MIN;
    }
    nComps += getRadixSortNComp_(a, a + size, INT_MIN);
    for (i = 0; i < size && ++nComps; i++) {
        a[i] ^= INT_MIN;
    }
    return nComps;
}

long long mergeNComp(const int *a, const size_t n, const int *b, const size_t m, int *c) {
    long long nComps = 0;
    int i = 0, j = 0;
    while (i < n && ++nComps || j < m && ++nComps) {
        if (j == m && ++nComps || i < n && ++nComps && a[i] < b[j] && ++nComps) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }
    return nComps;
}


long long mergeSortNComp_(int *source, size_t l, size_t r, int *buffer) {
    size_t n = r - l;
    long long nComps = 0;
    if (n <= 1 && ++nComps)
        return nComps;

    size_t m = (l + r) / 2;
    mergeSortNComp_(source, l, m, buffer);
    mergeSortNComp_(source, m, r, buffer);

    nComps = mergeNComp(source + l, m - l, source + m, r - m, buffer);
    memcpy(source + l, buffer, sizeof(int) * n);

    return nComps;
}

long long getMergeSortNComp(int *a, size_t n) {
    int *buffer = (int *) malloc(sizeof(int) * n);
    long long nComp = mergeSortNComp_(a, 0, n, buffer);
    free(buffer);

    return nComp;
}

long long getCocktailSortNComp(int *a, size_t n) {
    long long nComps=0;
    int swapped = 1;
    int start = 0;
    int end = n - 1;

    while (swapped&&++nComps) {
        swapped = 0;
        for (int i = start; i < end&&++nComps; ++i) {
            if (a[i] > a[i + 1]&&++nComps) {
                Swap(&a[i], &a[i + 1], sizeof(int));
                swapped = 1;
            }
        }
        if (!swapped&&++nComps)
            break;

        swapped = 0;
        --end;
        for (int i = end - 1; i >= start&&++nComps; --i) {
            if (a[i] > a[i + 1]&&++nComps) {
                Swap(&a[i], &a[i + 1], sizeof(int));
                swapped = 1;
            }
        }
        ++start;
    }
    return nComps;
}
