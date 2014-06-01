
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "hashtable.h"
#include "gtest/gtest.h"


TEST(HashTable, Insert)
{
  HashTable hash;

  EXPECT_TRUE(hash.Insert("hello", "world"));
  EXPECT_FALSE(hash.Insert("hello", "nihao"));

}

TEST(HashTable, Lookup)
{
  HashTable hash;

  hash.Insert("hello", "world");
  hash.Insert("hello", "nihao");
  hash.Insert("nihao", "shijie");
  
  std::string expect = "world";
  std::string result = hash.GetVal(hash.Lookup("hello"));
  ASSERT_EQ(expect, result);
  expect = "shijie";
  result = hash.GetVal(hash.Lookup("nihao"));
  ASSERT_EQ(expect, result);

  ASSERT_EQ(-1, hash.Lookup("notfound"));
    
}

TEST(HashTable, Delete)
{
  HashTable hash;

  hash.Insert("hello", "world");
  hash.Insert("hello", "nihao");
  hash.Insert("nihao", "shijie");
  EXPECT_TRUE(hash.Delete("hello"));
  ASSERT_EQ(-1, hash.Lookup("hello"));
  EXPECT_FALSE(hash.Delete("hello"));
}

std::string GenString(int code)
{
  std::string r;
  do {
    r += code % 26 + 'a';
    code /= 26;
  } while (code);

  std::reverse(r.begin(), r.end());
  return r;
}

TEST(HashTable, Collision)
{
  std::vector<std::string> keys;
  HashTable hash;
  
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 6; j++) {
      std::string key = GenString(i + j * HashTable::MOD);
      EXPECT_TRUE(hash.Insert(key, key));
      std::string result = hash.GetVal(hash.Lookup(key));
      ASSERT_EQ(key, result);
    }
  }

  std::string key1 = GenString(HashTable::MOD),
    key2 = GenString(2 * HashTable::MOD);
  EXPECT_TRUE(hash.Delete(key1));
  EXPECT_TRUE(hash.Delete(key2));
  EXPECT_FALSE(hash.Delete(key1));

  ASSERT_EQ(-1, hash.Lookup(key1));
  ASSERT_EQ(-1, hash.Lookup(key2));
}

