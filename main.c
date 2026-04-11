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
    if (!arr)
    {
        fprintf(stderr, "malloc failed for array\n");
        return EXIT_FAILURE;
    }

    unsigned long int *original = (unsigned long int *)malloc(N * sizeof(unsigned long int));
    if (!original)
    {
        fprintf(stderr, "malloc failed for original array\n");
        free(arr);
        return EXIT_FAILURE;
    }

    printf("Select Data Generation Method:\n 1. Randomly Generated Integers\n 2. Increasing Sequence\n Choice: ");
    scanf("%d", &choice);

    int algoChoice;
    printf("Please choose a sorting algorithm:\n[1] Selection [2] Bubble [3] Insertion [4] Merge [5] Quick [6] Heap: ");
    scanf("%d", &algoChoice);

    if (choice > 1)
    {
        printf("Enter starting value: ");
        scanf("%d", &x);
    }

    switch (algoChoice)
    {
        case 1: fp = fopen("selection_sort_output.txt", "w"); break;
        case 2: fp = fopen("bubble_sort_output.txt",   "w"); break;
        case 3: fp = fopen("insertion_sort_output.txt","w"); break;
        case 4: fp = fopen("merge_sort_output.txt",    "w"); break;
        case 5: fp = fopen("quick_sort_output.txt",    "w"); break;
        case 6: fp = fopen("heap_sort_output.txt",     "w"); break;
    }

    if (!fp)
    {
        fprintf(stderr, "Failed to open output file for writing\n");
        free(arr);
        free(original);
        return EXIT_FAILURE;
    }

    double average = 0.0;
    for (int run = 1; run <= 5; run++)
    {
        if (choice == 1)
        {
            for (unsigned long int i = 0; i < N; i++)
            {
                unsigned long int r = ((unsigned long int)rand() << 30)
                                    | ((unsigned long int)rand() << 15)
                                    |  (unsigned long int)rand();
                arr[i] = r % MAX_RANGE + 1;
            }
        }
        else
        {
            for (unsigned long int i = 0; i < N; i++)
                arr[i] = x++;
        }

        // Save the orig
        memcpy(original, arr, N * sizeof(unsigned long int));

        switch (algoChoice)
        {
            case 1: start = clock(); selectionSort(arr, N);      end = clock(); break;
            case 2: start = clock(); bubbleSort(arr, N);         end = clock(); break;
            case 3: start = clock(); insertionSort(arr, N);      end = clock(); break;
            case 4: start = clock(); mergeSort(arr, 0, N - 1);  end = clock(); break;
            case 5: start = clock(); quickSort(arr, 0, N - 1);  end = clock(); break;
            case 6: start = clock(); heapSort(arr, N);           end = clock(); break;
        }

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        average += cpu_time_used;
        printf("\nRun %d, N: %lu\nExecution time: %.10lf seconds\n", run, N, cpu_time_used);

        // Write this run's arrays to the file
        fprintf(fp, "=== Run %d (N = %lu) ===\n", run, N);

        fprintf(fp, "Original Array:\n");
        for (unsigned long int i = 0; i < N; i++)
        {
            fprintf(fp, "%lu", original[i]);
            if (i < N - 1) fprintf(fp, " ");
        }

        fprintf(fp, "\n\nSorted Array:\n");
        for (unsigned long int i = 0; i < N; i++)
        {
            fprintf(fp, "%lu", arr[i]);
            if (i < N - 1) fprintf(fp, " ");
        }
        fprintf(fp, "\n\n");
    }

    printf("\nAverage running time: %.5lf seconds\n", average / 5.0);

    fclose(fp);

    free(original);
    free(arr);
    return 0;
}
