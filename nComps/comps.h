//
// Created by ну я on 15.03.2022.
//

#ifndef SORT_COMPS_H
#define SORT_COMPS_H
#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <memory.h>

long long getSelectionSortNComp(int *a, size_t n);

long long getInsertionSortNComp(int *a, size_t size);

long long getBubbleSortNComp(int *a, size_t size);

long long getCombSortNComp(int *a, size_t size);

long long getShellSortNComp(int *a, size_t size);

long long getRadixSortNComp(int *a, size_t size);

long long getMergeSortNComp(int *a, size_t n);

long long getCocktailSortNComp(int *a, size_t n);

#endif //SORT_COMPS_H
