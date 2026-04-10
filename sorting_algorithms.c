#include <stdio.h>
#include <stdlib.h>

void merge(unsigned long int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    unsigned long int *leftArr = (unsigned long int *)malloc(n1 * sizeof(unsigned long int));
    unsigned long int *rightArr = (unsigned long int *)malloc(n2 * sizeof(unsigned long int));

    if (!leftArr || !rightArr)
    {
        fprintf(stderr, "malloc failed in merge()\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    while (i < n1)
        arr[k++] = leftArr[i++];
    while (j < n2)
        arr[k++] = rightArr[j++];

    free(leftArr);
    free(rightArr);
}

void mergeSort(unsigned long int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void swap(unsigned long int *f, unsigned long int *s)
{
    unsigned long int temp = *f;
    *f = *s;
    *s = temp;
}

void bubbleSort(unsigned long int arr[], int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void insertionSort(unsigned long int arr[], int N)
{

    // Starting from the second element
    for (int i = 1; i < N; i++)
    {
        unsigned long int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are
        // greater than key, to one position to
        // the right of their current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        // Move the key to its correct position
        arr[j + 1] = key;
    }
}

void selectionSort(unsigned long int arr[], int N)
{

    // Start with the whole array as unsored and one by
    // one move boundary of unsorted subarray towards right
    for (int i = 0; i < N - 1; i++)
    {

        // Find the minimum element in unsorted array
        int min_idx = i;
        for (int j = i + 1; j < N; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }

        // Swap the found minimum element with the first
        // element in the unsorted part
        unsigned long int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int partition(unsigned long int arr[], int low, int high)
{
    int mid = low + (high - low) / 2;
    if (arr[mid] < arr[low])
        swap(&arr[low], &arr[mid]);
    if (arr[high] < arr[low])
        swap(&arr[low], &arr[high]);
    if (arr[mid] < arr[high])
        swap(&arr[mid], &arr[high]);
    unsigned long int p = arr[high];

    int i = low;
    int j = high;

    while (i < j)
    {
        while (arr[i] <= p && i <= high - 1)
            i++;
        while (arr[j] > p && j >= low + 1)
            j--;
        if (i < j)
            swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quickSort(unsigned long int arr[], int low, int high)
{
    if (low < high)
    {

        // call partition function to find Partition Index
        int pi = partition(arr, low, high);

        // Recursively call quickSort() for left and right
        // half based on Partition Index
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// To heapify a subtree rooted with node i
void heapify(unsigned long int arr[], int n, int i)
{

    // Initialize largest as root
    int largest = i;

    // left index = 2*i + 1
    int l = 2 * i + 1;

    // right index = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        unsigned long int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(unsigned long int arr[], int n)
{

    // Build heap (rearrange vector)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--)
    {

        // Move current root to end
        unsigned long int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
