#ifndef ALGOLAB_HASHTABLE_H_
#define ALGOLAB_HASHTABLE_H_

#include <string>

class HashTable {
public:
  HashTable();
  
  bool Insert(const std::string &key, const std::string &val);
  
  bool Delete(const std::string &key);
  
  int Lookup(const std::string &key);
  
  std::string GetVal(int idx)
  {
    return vals_[idx];
  }

  static const int MOD = 1007;
  
private:
  int Find(const std::string &key, int h);
  int Hash(const std::string &s);
  
  static const int MAXSIZE = 100000;

  int head_[MOD], next_[MAXSIZE];
  std::string keys_[MAXSIZE];
  std::string vals_[MAXSIZE];
  int cur_;
  
};
#endif
