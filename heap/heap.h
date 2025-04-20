#ifndef HEAP_C
#define HEAP_C

namespace heap 
{
    void swap(int* a, int* b);
    void heapify(int numbers[], int size, int i);
    void build_heap(int numbers[], int size);
    void print_heap(int numebers[], int size);
};

#endif