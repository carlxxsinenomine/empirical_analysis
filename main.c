#include<stdio.h>
#include<time.h>
#include <stdlib.h>

void insertLast(int arr[], int *n, int val) {
  arr[*n] = val;
  (*n)++; // !ref
}

int main() {
  unsigned long int MAX_RANGE = 4294967295;
  srand((unsigned long int) time(NULL));
  // User input
  // int N = rand();
  int N;
  scanf("%d", &N);
  int M;
  printf("choose data generation meth: 1 or 2");
  int arr[N];

  scanf("%d", &M);
  int F;
  if(M==1) {
  // First method
    for(int i=0; i<N;i++) {
      insertLast(arr, &i, rand());
    }
  } else {
  // Sec Method 
  int x;
  printf("Enter a value for x");
  scanf("%d", &x);
  if(x < 0) return -1;
  // For loop?
  for(int i = 0; i < N; i++) {
    // Prob
    insertLast(arr, &i, (x + i)); // array, index, value 
  }
  }
  int arrLen = sizeof(arr) / sizeof(arr[0]);
  for (int i=0;i<arrLen; i++) {
    printf("%d, ", arr[i]);
  }
  return 0;
}
