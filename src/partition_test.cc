#include <algorithm>
#include <map>
#include "partition.h"
#include "gtest/gtest.h"


TEST(Partition, All)
{
  int a[] = {1, 6, 2, 10, 6, 6, 6, 7, 8, 1, 2, 3, 6, 10, 15, 20, 4};
  int n = sizeof(a) / sizeof(int);
  int idx = 4;

  int split = a[idx];
  std::map<int, int> aset;
  for (int i = 0; i < n; i++) {
    aset[a[i]]++;
  }
  Partition(a, 0, n, idx);
  
  for (int i = 0; i < n; i++) {
    aset[a[i]]--;
  }
  bool ok = true;
  for (std::map<int, int>::iterator it = aset.begin(); it != aset.end(); ++it) {
    if (it->second != 0) {
      ok = false;
      break;
    }
  }

  int state = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] < split) {
      if (state != 0) {
        ok = false;
        break;
      }
    } else if (a[i] == split) {
      if (state < 1) {
        state = 1;
      } else if (state != 1) {
        ok = false;
        break;
      }
    } else {
      if (state < 2) {
        state = 2;
      } else if (state != 2) {
        ok = false;
        break;
      }
    }
  }

  EXPECT_TRUE(ok);
}







