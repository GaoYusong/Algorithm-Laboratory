
#include <algorithm>
#include "partition.h"


int Partition(int arr[], int lo, int hi, int idx)
{
  if (lo >= hi) {
    return -1;
  }
  std::swap(arr[idx], arr[lo]);
  int split = arr[lo];
  int l = lo + 1, r = hi - 1;
  while (l <= r) {
    while (l <= r && arr[l] <= split)
      l++;
    while (l <= r && arr[r] > split)
      r--;
    if (l <= r) {
      std::swap(arr[l], arr[r]);
      l++;
      r--;
    }
  }
  std::swap(arr[lo], arr[r]);
  return r;
}

void QuickSort(int arr[], int lo, int hi)
{
  if (lo >= hi) {
    return;
  }
  int sp = Partition(arr, lo, hi, lo);
  QuickSort(arr, lo, sp);
  QuickSort(arr, sp + 1, hi);
}

void Sort(int arr[], int n)
{
  QuickSort(arr, 0, n);
}



