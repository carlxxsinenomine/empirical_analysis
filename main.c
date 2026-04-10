#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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
  FILE *fp;

  printf("Enter the number of integers to be sorted: ");
  scanf("%lu", &N);

  unsigned long int *arr = (long int *)malloc(N * sizeof(long int));
  if (!arr)
  {
    fprintf(stderr, "malloc failed for array\n");
    return EXIT_FAILURE;
  }

  // Allocate a copy to preserve the original before sorting
  unsigned long int *original = (long int *)malloc(N * sizeof(long int));
  if (!original)
  {
    fprintf(stderr, "malloc failed for original array\n");
    free(arr);
    return EXIT_FAILURE;
  }

  printf("Select Data Generation Method:\n 1. Randomly Generated Integers\n 2. Increasing Sequence\n Choice: ");
  scanf("%d", &choice);

  if (choice == 1)
  {
    for (int i = 0; i < N; i++)
    {
      unsigned long int r = ((unsigned long int)rand() << 30) | ((unsigned long int)rand() << 15) | (unsigned long int)rand();
      arr[i] = (long int)(r % MAX_RANGE + 1);
    }
  }
  else
  {
    printf("Enter starting value: ");
    scanf("%d", &x);
    for (int i = 0; i < N; i++)
    {
      arr[i] = x++;
    }
  }

  // Save a copy of the original array
  for (long int i = 0; i < N; i++)
  {
    original[i] = arr[i];
  }

  int algoChoice;
  printf("Please choose a sorting algorithm: \n[1] Selection [2] Bubble [3] Insertion [4] Merge [5] Quick [6] Heap: ");
  scanf("%d", &algoChoice);

  fflush(stdout);
  switch (algoChoice)
  {
  case 1:
    start = clock();
    selectionSort(arr, N);
    end = clock();
    fp = fopen("selection_sort_output.txt", "w");
    break;
  case 2:
    start = clock();
    bubbleSort(arr, N);
    end = clock();
    fp = fopen("bubble_sort_output.txt", "w");
    break;
  case 3:
    start = clock();
    insertionSort(arr, N);
    end = clock();
    fp = fopen("insertion_sort_output.txt", "w");
    break;
  case 4:
    start = clock();
    mergeSort(arr, 0, N - 1);
    end = clock();
    fp = fopen("merge_sort_output.txt", "w");
    break;
  case 5:
    start = clock();
    quickSort(arr, 0, N - 1);
    end = clock();
    fp = fopen("quick_sort_output.txt", "w");
    break;
  case 6:
    start = clock();
    heapSort(arr, N);
    end = clock();
    fp = fopen("heap_sort_output.txt", "w");
    break;
  }
  // start = clock();
  // mergeSort(arr, 0, N - 1);
  // end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("\n\nN: %d\nExecution time: %.10lf seconds\n", N, cpu_time_used);

  // Save ouput to .txt
  if (!fp)
  {
    fprintf(stderr, "Failed to open output.txt for writing\n");
    free(arr);
    free(original);
    return EXIT_FAILURE;
  }

  fprintf(fp, "Original Array (%lu elements):\n", N);
  for (long int i = 0; i < N; i++)
  {
    fprintf(fp, "%lu", original[i]);
    if (i < N - 1)
      fprintf(fp, " ");
  }

  fprintf(fp, "\n\nSorted Array (%lu elements):\n", N);
  for (long int i = 0; i < N; i++)
  {
    fprintf(fp, "%lu", arr[i]);
    if (i < N - 1)
      fprintf(fp, " ");
  }
  fprintf(fp, "\n");

  fclose(fp);

  free(original);
  free(arr);
  return 0;
}
