
#include <vector>
#include "heap.h"
#include "gtest/gtest.h"


TEST(Heap, Create)
{
  int a[10] = {2, 3, 1, 5, 4, 8, 9, 6, 7, 0};
  std::vector<int> arr(a, a + 10);
  
  Heap<int> heap(arr);

  int n = arr.size();
  ASSERT_EQ(n, heap.size());

  for (int i = 0; i < n; i++) {
    ASSERT_EQ(i, heap.get_min());
    heap.Pop();
  }
  ASSERT_EQ(0, heap.size());
}

TEST(Heap, PushPop)
{
  int a[10] = {2, 3, 1, 5, 4, 8, 9, 6, 7, 0};
  Heap<int> heap;
  for (int i = 0; i < 10; i++) {
    heap.Push(a[i]);
  }

  ASSERT_EQ(10, heap.size());

  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(i, heap.get_min());
    heap.Pop();
  }
  ASSERT_EQ(5, heap.size());

  for (int i = 0; i < 5; i++) {
    heap.Push(i);
    heap.Push(10 + i);
    heap.Pop();
  }
  for (int i = 5; i < 10; i++) {
    ASSERT_EQ(i, heap.get_min());
    heap.Pop();
  }
  ASSERT_EQ(5, heap.size());
  for (int i = 10; i < 15; i++) {
    ASSERT_EQ(i, heap.get_min());
    ASSERT_EQ(i, heap.get_min());
    heap.Pop();
  }
  ASSERT_EQ(0, heap.size());
}
