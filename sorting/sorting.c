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
    const char HEAP_SORT     = '6';

    const char ASCENDING   = '1';
    const char DESCENDING  = '2';

    /********************************
     *  General function for sorting
     *  1) swap
     *  2) reverse
     ********************************/

    // swap elements with extra O(1) space
    void swap(int* a, int* b) {
        int t = (*a);
        (*a) = (*b);
        (*b) = t;
    }

    // swap elements without extra space
    void swap_(int* a, int* b) {
        (*a) = (*a) + (*b);
        (*b) = (*a) - (*b);
        (*a) = (*a) - (*b);
    }
    
    // reverse array with extra O(1) space
    void reverse(int numbers[], int size) {
        int tmp;
        for (int i = 0; i < (size / 2); ++i) {
            swap(&numbers[i], &numbers[size-i-1]);
        }
    }
    
    /********************************
    *  Bubble Sort
    *  Time Complexity O(n^2)
    *  Not extra space require
    ********************************/
    void bubble_sort(int numbers[], int size, char mode = ASCENDING ) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < i; ++j) {
                if (numbers[i] < numbers[j]) {
                    swap(&numbers[i], &numbers[j]);
                }
            }
        }
        if (mode == DESCENDING) { reverse(numbers, size); }
    }

    /********************************
    *  Quick Sort
    *  Time Complexity: general O(log(n)), worst O(n^2)
    *  Space Complexity: O(1)
    ********************************/
    // partition function: choose right-most element as pivot
    int partition(int numbers[], int low, int high) {
        int pivot = numbers[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            // if current element is smaller than or equal to pivot
            if (numbers[j] <= pivot) {
                i++; // increment element count which is smallar than or equal to pivot
                swap(&numbers[i], &numbers[j]);
            }
        }

        // swap pivot element to correct index
        swap(&numbers[i+1], &numbers[high]);
        return (i + 1);
    }

    void quick_sort(int numbers[], int low, int high, char mode = ASCENDING) {
        if (low < high) {
            int partition_location = partition(numbers, low, high);
            
            // quick sort seperately on first and second partition
            quick_sort(numbers, low, partition_location - 1);
            quick_sort(numbers, partition_location + 1, high);
        }

        if (mode == DESCENDING) { reverse(numbers, (high-low+1)); }
    }

    /********************************
    *  Merge Sort
    *  Time Complexity: general O(nlog(n)), worst O(nlog(n)), best O(nlog(n))
    *  Space Complexity: O(log(n))
    ********************************/
    // merge two sub-array arr1[left...mid], arr2[mid+1...right]
    void merge_sorted_array(int numbers[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // create temporary array
        int *tmp1 = (int*)malloc(n1 * sizeof(int));
        int *tmp2 = (int*)malloc(n2 * sizeof(int));

        // copy data to temporary array
        memcpy(tmp1, &numbers[left], n1 * sizeof(int));
        memcpy(tmp2, &numbers[mid + 1], n2 * sizeof(int));

        int i = 0; // this pointing to tmp1
        int j = 0; // this pointing to tmp2
        int k = left; // this pointing to numbers

        // merge two sorted array
        while (i < n1 && j < n2) {
            if (tmp1[i] <= tmp2[j]) {
                numbers[k] = tmp1[i++];
            } else {
                numbers[k] = tmp2[j++];
            }
            k++;
        }

        // copy rest of the numbers
        while (i < n1) { numbers[k++] = tmp1[i++]; }
        while (j < n2) { numbers[k++] = tmp2[j++]; }

        free(tmp1);
        free(tmp2);
    }

    void merge_sort(int numbers[], int left, int right, const char mode = ASCENDING) {
        if (left < right) {
            int mid = left + ((right - left) >> 1);

            // recusively sort first and second partition
            merge_sort(numbers, left, mid);
            merge_sort(numbers, mid + 1, right);
        
            // merge two sorted partitions
            merge_sorted_array(numbers, left, mid, right);
        }

        if (mode == DESCENDING) { reverse(numbers, (right-left+1)); }
    }

    /********************************
    *  Insertion Sort
    *  Time Complexity: general O(n^2), best O(n), worst O(n^2)
    *  No extra space require
    ********************************/
    void insertion_sort(int numbers[], int size, const char mode = ASCENDING) {
        if (size == 1) { return; }

        int j;
        for (int i = 1; i < size; i++) {
            j = i;
            while ((j > 0) && (numbers[j-1] > numbers[j])) {
                swap(&numbers[j-1], &numbers[j]);
                j--;
            }
        }

        if (mode == DESCENDING) { reverse(numbers, size); }
    }

    /********************************
    *  Bucket Sort
    *  Assume number is in range 0 ~ 99
    *  Time Complexity: 
    *  Space Complexity:
    ********************************/
    void bucket_sort(int numbers[], int size, int bucket_num, int bucket_max, const char mode = ASCENDING) {
        int **buckets = (int**)malloc(bucket_num * sizeof(int*));
        int *element_counts = (int*)malloc(bucket_num * sizeof(int));

        for (int i = 0; i < bucket_num; i++) {
            buckets[i] = (int*)malloc(bucket_max * sizeof(int));
            element_counts[i] = 0;
        }

        // insert number into related bucket
        int bucket_index;
        for (int i = 0; i < size; i++) {
            bucket_index = numbers[i] / bucket_num;
            buckets[bucket_index][element_counts[bucket_index]] = numbers[i];
            element_counts[bucket_index]++;
        }

        // sort each bucket
        for (int i = 0; i < bucket_num; i++) {
            merge_sort(buckets[i], 0, element_counts[i]-1, mode);
        }

        // merge each bucket
        int offset = 0;
        for (int i = 0; i < bucket_num; i++) {
            memcpy(numbers + offset, buckets[i], element_counts[i] * sizeof(int));
            offset += element_counts[i];
        }

        for (int i = 0; i < bucket_num; i++) {
            free(buckets[i]);
        }
        free(element_counts);
        free(buckets);

        if (mode == DESCENDING) { reverse(numbers, size); }
    }

    /********************************
    *  Heap Sort
    *  Time Complexity: general O(nlog(n))
    *  No extra space require
    ********************************/
    void heap_sort(int numbers[], int size, const char mode = ASCENDING) {
        for (int i = 0; i < size; i++) {
            heap::build_heap(numbers, size - i);
            swap(&numbers[0], &numbers[size-i-1]);
        }
        if (mode == DESCENDING) { reverse(numbers, size); }
    }

    void sort(int numbers[], int size, const char algo = QUICK_SORT, const char mode = ASCENDING) {
        switch (algo) {
        case QUICK_SORT:
            printf("quick ");
            quick_sort(numbers, 0, size-1, mode);
            break;
        case BUBBLE_SORT:
            printf("bubble ");
            bubble_sort(numbers, size, mode);
            break;
        case MERGE_SORT:
            printf("merge ");
            merge_sort(numbers, 0, size-1, mode);
            break;
        case INSERTION_SORT:
            printf("insertion ");
            insertion_sort(numbers, size, mode);
            break;
        case BUCKET_SORT:
            printf("bucket ");
            bucket_sort(numbers, size, 10, 10, mode);
            break;
        case HEAP_SORT:
            printf("heap ");
            heap_sort(numbers, size, mode);
            break;
        default:
            printf("\nundefined sorting option: %c\n", mode);
        }
    }
};

namespace timer
{
    clock_t get_time() {
        return clock();
    }

    inline double time_elapse(clock_t start, clock_t end) {
        return ((double)(end - start)) / CLOCKS_PER_SEC;
    }

    void print_time_elapse(clock_t start, clock_t end) {
        double elapse = time_elapse(start, end);
        printf("elaspe time: %f seconds \n", elapse);
    }
};

void print_array(int numbers[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

int main() {

    char algo[MAX_INPUT_SIZE];
    char mode[MAX_INPUT_SIZE];

    while (1) 
    {
        printf(" 0: EXIT\n");
        printf(" 1: BUBBLE_SORT\n");
        printf(" 2: QUICK_SORT\n");
        printf(" 3: MERGE_SORT\n");
        printf(" 4: INSERTION_SORT\n");
        printf(" 5: BUCKET_SORT\n");
        printf(" 6: HEAP_SORT\n");
        printf(" Enter a sorting algorithm: ");
        if (fgets(algo, MAX_INPUT_SIZE, stdin) != NULL) {
            size_t len = strlen(algo);
            if (len > 0 && algo[len - 1] == '\n') {
                algo[len - 1] = '\0';
            }
        }

        if (algo[0] != '0') {

            printf(" 1: Ascending\n");
            printf(" 2: Descending\n");
            printf(" Enter a sorting order: ");
            if (fgets(mode, MAX_INPUT_SIZE, stdin) != NULL) {
                size_t len = strlen(mode);
                if (len > 0 && mode[len - 1] == '\n') {
                    mode[len - 1] = '\0';
                }
            }

            int numbers[] = {50, 32, 28, 72, 61, 84, 18, 41, 99, 5, 35, 75, 79, 15, 43, 70, 66};
            int size = sizeof(numbers) / sizeof(numbers[0]);

            printf("=============================\n");
            printf("unsorted: ");
            print_array(numbers, size);
            clock_t start_time = timer::get_time();
            sort::sort(numbers, size, algo[0], mode[0]);
            clock_t end_time = timer::get_time();
            printf("sorted: ");
            print_array(numbers, size);
            timer::print_time_elapse(start_time, end_time);
            printf("=============================\n");
        
        } else { break; }
    }

    return 0;
}