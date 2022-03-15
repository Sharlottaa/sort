//
// Created by ну я on 13.03.2022.
//

#include "sorts_.h"

void swap(void *a, void *b, size_t size) {
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

void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; j > i; j--)
            if (a[j - 1] > a[j])
                swap(&a[j - 1], &a[j], sizeof(int));
}

void selectionSort(int *a, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos], sizeof(int));
    }
}

void insertionSort(int *a, size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void combSort(int *a, const size_t size) {
    size_t step = size;
    int swapped = 1;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j], sizeof(int));
                swapped = 1;
            }
    }
}

void ShellSort(int *a, size_t size) {
    int t;
    for (size_t step = size / 2; step > 0; step /= 2) {
        for (size_t i = step; i < size; i++) {
            t = a[i];
            size_t j;
            for (j = i; j >= step; j -= step) {
                if (t < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = t;
        }
    }
}

void radixSort_(unsigned int *from, unsigned int *to, unsigned int bit) {
    if (!bit || to < from + 1)
        return;

    unsigned int *left = from, *right = to - 1;
    while (1) {
        while (left < right && !(*left & bit))
            left++;
        while (left < right && (*right & bit))
            right--;
        if (left >= right)
            break;
        swap(left, right, sizeof(unsigned int));
    }

    if (!(bit & *left) && left < to)
        left++;
    bit >>= 1;

    radixSort_(from, left, bit);
    radixSort_(left, to, bit);
}

void radixSort(int *a, size_t size) {
    size_t i;
    for (i = 0; i < size; i++) {
        a[i] ^= INT_MIN;
    }
    radixSort_(a, a + size, INT_MIN);
    for (i = 0; i < size; i++) {
        a[i] ^= INT_MIN;
    }
}

void merge(const int *a, const size_t n,
           const int *b, const size_t m, int *c) {
    int i = 0, j = 0;
    while (i < n || j < m) {
        if (j == m || i < n && a[i] < b[j]) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }
}

void mergeSort_(int *source, size_t l, size_t r, int *buffer) {
    size_t n = r - l;
    if (n <= 1)
        return;

    size_t m = (l + r) / 2;
    mergeSort_(source, l, m, buffer);
    mergeSort_(source, m, r, buffer);

    merge(source + l, m - l, source + m, r - m, buffer);
    memcpy(source + l, buffer, sizeof(int) * n);
}

void mergeSort(int *a, size_t n) {
    int *buffer = (int *) malloc(sizeof(int) * n);
    mergeSort_(a, 0, n, buffer);
    free(buffer);
}

int isBiggerThenSwap(int *a, int i) {
    if (a[i] > a[i + 1]) {
        swap(&a[i], &a[i + 1], sizeof(int));
    }
    return 1;
}

void CocktailSort(int *a, size_t n) {
    int swapped = 1;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = 0;
        for (int i = start; i < end; ++i) {
            swapped = isBiggerThenSwap(a, i);
        }
        if (!swapped)
            break;

        swapped = 0;
        --end;
        for (int i = end - 1; i >= start; --i) {
            swapped = isBiggerThenSwap(a, i);
        }
        ++start;
    }
}