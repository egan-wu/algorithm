#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

namespace heap 
{
    // swap elements with extra O(1) space
    void swap(int* a, int* b) {
        int t = (*a);
        (*a) = (*b);
        (*b) = t;
    }

    void heapify(int numbers[], int size, int i) {
        int largest = i;
        int l = 2 * i + 1; // index in array of left-node from largest
        int r = 2 * i + 2; // index in array of right-node from largest

        if (l < size && numbers[l] > numbers[largest]) {
            largest = l;
        }

        if (r < size && numbers[r] > numbers[largest]) {
            largest = r;
        }

        // if largest is not root(i)
        if (largest != i) {
            swap(&numbers[i], &numbers[largest]);

            heapify(numbers, size, largest);
        }
    }

    void build_heap(int numbers[], int size) {
        // index of last non-leaf node
        int idx = (size / 2) - 1;

        for (int i = idx; i >= 0; i--) {
            heapify(numbers, size, i);
        }
    }

    void print_heap(int numbers[], int size) {
        for (int i = 0; i < size; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }
}