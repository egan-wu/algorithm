#ifndef SORTING_H
#define SORTING_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../heap/heap.h"

#define MAX_INPUT_SIZE  10

namespace sort 
{
    const char BUBBLE_SORT     = '1';
    const char QUICK_SORT      = '2';
    const char MERGE_SORT      = '3';
    const char INSERTION_SORT  = '4';
    const char BUCKET_SORT     = '5';
    const char HEAP_SORT       = '6';
    const char ASCENDING       = '1';
    const char DESCENDING      = '2';
    
    void bubble_sort(int numbers[], int size, const char mode = ASCENDING );
    void quick_sort(int numbers[], int low, int high, const char mode = ASCENDING);
    void merge_sort(int numbers[], int left, int right, const char mode = ASCENDING);
    void insertion_sort(int numbers[], int size, const char mode = ASCENDING);
    void bucket_sort(int numbers[], int size, int bucket_num, int bucket_max, const char mode = ASCENDING);
    void heap_sort(int numbers[], int size, const char mode = ASCENDING);
    void sort(int numbers[], int size, const char algo = QUICK_SORT, const char mode = ASCENDING);
};

#endif