#include<stdio.h>
#include<time.h>
#include <stdlib.h>

void insertLast(int arr[], int *n, int val) {
  arr[*n] = val;
  (*n)++; // !ref
}

int main() {
  unsigned long int MAX_RANGE = 4294967295;
  // User input
  unsigned long int N = rand() % (MAX_RANGE);
  int x;

  printf("Enter a value for x");
  scanf("%d", &x);
  if(x < 0) return -1;
  int arr[N]; // If valid
  // For loop?
  for(int i = 0; i < N; i++) {
    // Prob
    insertLast(arr, &i, (x + i)); // array, index, value 
  }
  int arrLen = sizeof(arr) / sizeof(arr[0]);
  for (int i=0;i<arrLen; i++) {
    printf("%d, ", arr[i]);
  }
  return 0;
}
