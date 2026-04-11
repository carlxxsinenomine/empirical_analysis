#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "sorting_algorithms.c"

int main()
{
    clock_t start, end;
    double cpu_time_used;

    srand(time(NULL));

    unsigned long int MAX_RANGE = 4294967295UL;
    unsigned long int N;
    int x;
    int choice;
    FILE *fp = NULL;

    printf("Enter the number of integers to be sorted: ");
    scanf("%lu", &N);

    unsigned long int *arr = (unsigned long int *)malloc(N * sizeof(unsigned long int));
    if (!arr) {
        fprintf(stderr, "malloc failed for array\n");
        return EXIT_FAILURE;
    }

    unsigned long int *original = (unsigned long int *)malloc(N * sizeof(unsigned long int));
    if (!original) {
        fprintf(stderr, "malloc failed for original array\n");
        free(arr);
        return EXIT_FAILURE;
    }

    printf("Select Data Generation Method:\n 1. Randomly Generated Integers\n 2. Increasing Sequence\n Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        for (unsigned long int i = 0; i < N; i++) {
            unsigned long int r = ((unsigned long int)rand() << 30)
                                | ((unsigned long int)rand() << 15)
                                |  (unsigned long int)rand();
            arr[i] = r % MAX_RANGE + 1;
        }
    } else {
        printf("Enter starting value: ");
        scanf("%d", &x);
        for (unsigned long int i = 0; i < N; i++) {
            arr[i] = x++;
        }
    }

    // Save the original unsorted array
    memcpy(original, arr, N * sizeof(unsigned long int));

    int algoChoice;
    printf("Please choose a sorting algorithm:\n[1] Selection [2] Bubble [3] Insertion [4] Merge [5] Quick [6] Heap: ");
    scanf("%d", &algoChoice);
    double average = 0.0;
    for (int run = 1; run <= 5; run++)
    {
        // Restore original array before each run
        memcpy(arr, original, N * sizeof(unsigned long int));

        switch (algoChoice) {
        case 1:
            start = clock(); selectionSort(arr, N); end = clock();
            fp = fopen("selection_sort_output.txt", "w");
            break;
        case 2:
            start = clock(); bubbleSort(arr, N); end = clock();
            fp = fopen("bubble_sort_output.txt", "w");
            break;
        case 3:
            start = clock(); insertionSort(arr, N); end = clock();
            fp = fopen("insertion_sort_output.txt", "w");
            break;
        case 4:
            start = clock(); mergeSort(arr, 0, N - 1); end = clock();
            fp = fopen("merge_sort_output.txt", "w");
            break;
        case 5:
            start = clock(); quickSort(arr, 0, N - 1); end = clock();
            fp = fopen("quick_sort_output.txt", "w");
            break;
        case 6:
            start = clock(); heapSort(arr, N); end = clock();
            fp = fopen("heap_sort_output.txt", "w");
            break;
        }

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        average += cpu_time_used;
        printf("\nRun %d, N: %lu\nExecution time: %.10lf seconds\n", run, N, cpu_time_used);
    }
    printf("\nAverage running time: %.5lf seconds\n", average / 5.0);

    if (!fp) {
        fprintf(stderr, "Failed to open output file for writing\n");
        free(arr);
        free(original);
        return EXIT_FAILURE;
    }

    fprintf(fp, "Original Array (%lu elements):\n", N);
    for (unsigned long int i = 0; i < N; i++) {
        fprintf(fp, "%lu", original[i]);
        if (i < N - 1) fprintf(fp, " ");
    }

    fprintf(fp, "\n\nSorted Array (%lu elements):\n", N);
    for (unsigned long int i = 0; i < N; i++) {
        fprintf(fp, "%lu", arr[i]);
        if (i < N - 1) fprintf(fp, " ");
    }
    fprintf(fp, "\n");

    fclose(fp);
    // printf("Arrays written to output file\n");

    free(original);
    free(arr);
    return 0;
}
