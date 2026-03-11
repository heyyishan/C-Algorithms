#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void bubble_sort(int arr[], size_t n) {
  for (size_t i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (size_t j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        swapped = true;
      }
    }
    if (!swapped)
      break; // Optimization for sorted arrays
  }
}

void selection_sort(int arr[], size_t n) {
  for (size_t i = 0; i < n - 1; i++) {
    size_t min_idx = i;
    for (size_t j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_idx])
        min_idx = j;
    }
    int temp = arr[min_idx];
    arr[min_idx] = arr[i];
    arr[i] = temp;
  }
}

int main(int argc, char *argv[]) {
  int arr[10] = {192, 2934, 942, 463, 12, 643, 70, 102, 593, 231, 949};
  bubble_sort(arr, 10);
  for (int i = 0; i < 10; i++) {
    printf("%d\n", arr[i]);
  }
  return 0;
}
