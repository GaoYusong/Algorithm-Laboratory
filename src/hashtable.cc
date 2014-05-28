
#include <assert.h>
#include <algorithm>
#include <string>

#include "hashtable.h"

HashTable::HashTable()
  : cur_(0)
{
  std::fill(head_, head_ + MOD, -1);
}

bool HashTable::Insert(const std::string &key, const std::string &val)
{
  int h = Hash(key);
  int p = Find(key, h);

  if (p != -1) {
    return false;
  }

  assert(cur_ < MAXSIZE);
    
  keys_[cur_] = key;
  vals_[cur_] = val;
  next_[cur_] = head_[h];
  head_[h] = cur_;
  cur_++;
  return true;
}

bool HashTable::Delete(const std::string &key)
{
  int h = Hash(key);
  int p = head_[h], *q = head_ + h;
    
  while (p != -1) {
    if (keys_[p] == key) {
      *q = next_[p];
      return true;
    }
    q = next_ + p;
    p = next_[p];
  }

  return false;
}

int HashTable::Lookup(const std::string &key)
{
  int h = Hash(key);
  return Find(key, h);
}
  

int HashTable::Find(const std::string &key, int h)
{
  int p = head_[h];
  while (p != -1) {
    if (keys_[p] == key) {
      return p;
    }
    p = next_[p];
  }
  return -1;
}
  
int HashTable::Hash(const std::string &s)
{
  int h = 0;
  for (int i = 0; i < s.length(); i++) {
    h = (h * 26 + (s[i] - 'a')) % MOD;
  }
  return h;
}
  
