//
// Created by ну я on 13.03.2022.
//

#ifndef SORT_SORTS__H
#define SORT_SORTS__H
#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <memory.h>


void bubbleSort(int *a, size_t size);

void selectionSort(int *a, size_t size);

void insertionSort(int *a, size_t size);

void combSort(int *a, const size_t size);

void ShellSort(int *a, size_t size);

void radixSort(int *a, size_t size);

void mergeSort(int *a, size_t n);

void CocktailSort(int *a, size_t n);

#endif //SORT_SORTS__H
