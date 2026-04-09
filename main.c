#include<stdio.h>
#include<time.h>
#include <stdlib.h>

int main() {

  srand(time(NULL));

  const unsigned long int MAX_RANGE = 4294967295;
  int N;
  int x;
  int choice;

  printf("Enter the number of integers to be sorted: ");
  scanf("%d", &N);
  int arr[N];

  printf("Select Data Generation Method: \n 1. Randomly Generated Integers \n 2. Increasing Sequence \n Choice:");
  scanf("%d", &choice);

  if (choice == 1){
    for(int i = 0; i < N; i++){
    arr[i] = (rand() % MAX_RANGE + 1);
    }

    for(int i = 0; i < N; i++){
    printf("%d ", arr[i]);
    }
  }

  else {
    printf("Enter starting value: ");
    scanf("%d", &x);

    for (int i = 0; i < N; i++){
      arr[i] = x;
      x++;
    }

    for(int i = 0; i < N; i++){
    printf("%d ", arr[i]);
    }
  }
  


  return 0;
  
}
