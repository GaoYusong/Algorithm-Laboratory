#include <assert.h>
#include <algorithm>


#include "sort.h"

static int Partition(int arr[], int lo, int hi);
static int Partition2(int arr[], int lo, int hi);

static void QuickSortSkel(int arr[], int lo, int hi, int (partition)(int [], int, int));

int c1 = 0, c2 = 0;

void QuickSort(int arr[], int lo, int hi)
{
  QuickSortSkel(arr, lo, hi, Partition);

}

void QuickSort2(int arr[], int lo, int hi)
{
  QuickSortSkel(arr, lo, hi, Partition2);

}


static void QuickSortSkel(int arr[], int lo, int hi, int (partition)(int [], int, int))
{
  if (lo >= hi)
    return;
  int sp = partition(arr, lo, hi);
  QuickSortSkel(arr, lo, sp, partition);
  QuickSortSkel(arr, sp + 1, hi, partition);
}

int Partition(int arr[], int lo, int hi)
{
  assert(lo < hi);
  
  int idx = lo; // choose a split
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
      l++; r--;
    }
  }
  std::swap(arr[lo], arr[r]);
  return r;
}

int Partition2(int arr[], int lo, int hi)
{
  assert(lo < hi);

  int idx = lo;
  std::swap(arr[idx], arr[lo]);
  int split = arr[lo];

  int i = lo;

  for (int j = lo + 1; j < hi; j++) {
    if (arr[j] <= split) {
      i++;
      if (i != j) {

        std::swap(arr[i], arr[j]);
      }
    }
  }
  std::swap(arr[lo], arr[i]);
  return i;
}

