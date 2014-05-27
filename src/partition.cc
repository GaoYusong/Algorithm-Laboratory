#include <algorithm>
#include "partition.h"

void Partition(int arr[], int lo, int hi, int idx)
{
  std::swap(arr[lo], arr[idx]);
  int split = arr[lo];

  int l = lo + 1, r = hi - 1;
  int x = lo + 1;
  while (l <= r) {
    while (l <= r && arr[l] < split)
      l++;
    while (l <= r && arr[r] > split)
      r--;
    if (l <= r) {
      if (arr[l] == split) {
        std::swap(arr[l], arr[x]);
        x++; l++;
      } else if (arr[r] == split) {
        arr[r] = arr[l];
        arr[l] = arr[x];
        arr[x] = split;
        x++; l++; r--;
      } else {
        std::swap(arr[l], arr[r]);
        l++; r--;
      }
    }
  }
  while (x > 0) {
    std::swap(arr[x - 1], arr[l - 1]);
    l--; x--;
  }
}



