#include <algorithm>
#include "sort.h"
#include "gtest/gtest.h"

bool TestSort(void (sort)(int [], int, int))
{
  int a[] = {1, 6, 2, 10, 6, 6, 6, 7, 8, 1, 2, 3, 6, 10, 15, 20, 4};
  int n = sizeof(a) / sizeof(int);
  int *b = new int[n];
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
  }
  std::sort(b, b + n);
  sort(a, 0, n);
  
  bool ok = true;
  for (int i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      ok = false;
      break;
    }
  }
  delete [] b;
  return ok;
}

TEST(QuickSort, All)
{
  bool ok = TestSort(QuickSort);
  EXPECT_TRUE(ok);
}

TEST(QuickSort2, All)
{
  bool ok = TestSort(QuickSort2);
  EXPECT_TRUE(ok);
}

TEST(MergeSort, All)
{
  bool ok = TestSort(MergeSort);
  EXPECT_TRUE(ok);
}


