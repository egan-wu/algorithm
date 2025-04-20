### how to build and run
1. clone "sorting" into "./sorting"
2. clone "heap" into  "./sorting/heap"
3. terminal run: gcc -c ./sorting/heap/heap.c -o ./sorting/heap.o
4. terminal run: gcc -c ./sorting/sorting.c -o ./sorting/sorting.o
5. terminal run: gcc -o ./sorting/sorting.o ./sorting/heap.o ./sorting/sorting
6. terminal run: ./sorting/sorting