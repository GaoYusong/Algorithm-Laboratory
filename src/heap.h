#ifndef ALGOLAB_HEAP_H_
#define ALGOLAB_HEAP_H_

#include <assert.h>
#include <vector>
#include <algorithm>
#include <utility>

template<typename Elem>
class Heap {
public:
  Heap()
    : size_(0)
  { }

  Heap(const std::vector<Elem> &elems)
  {
    size_ = elems.size();

    for (int i = size_ / 2 + 1; i <= size_; i++) {
      elems_[i] = elems[i - 1];
    }

    for (int i = size_ / 2; i >= 1; i--) {
      elems_[i] = elems[i - 1];
      Sink(i);
    }
  }

  void Push(const Elem &elem)
  {
    assert(size_ < MAXSIZE);
    elems_[++size_] = elem;
    Rise(size_);
  }


  void Pop()
  {
    assert(size_ > 0);
    elems_[1] = elems_[size_--];
    if (size_ > 0) {
      Sink(1);
    }
  }

  Elem get_min()
  {
    assert(size_ > 0);
    return elems_[1];
  }

  int size()
  {
    return size_;
  }
  
private:
  void Rise(int idx)
  {
    assert(idx > 0 && idx <= size_);
    while (idx != 1 && elems_[idx] < elems_[idx / 2]) {
      std::swap(elems_[idx], elems_[idx / 2]);
      idx /= 2;
    }
  }

  void Sink(int idx)
  {
    assert(idx > 0 && idx <= size_);
    int limit = size_ / 2;
    while (idx <= limit) {
      int c, c1 = idx * 2, c2 = idx * 2 + 1;
      if (c2 <= size_ && elems_[c1] > elems_[c2]) {
        c = c2;
      } else {
        c = c1;
      }

      if (elems_[c] < elems_[idx]) {
        std::swap(elems_[c], elems_[idx]);
        idx = c;
      } else {
        break;
      }
    }
  
  }


  static const int MAXSIZE = 100000;

  Elem elems_[MAXSIZE + 1];
  int size_;
};

#endif
