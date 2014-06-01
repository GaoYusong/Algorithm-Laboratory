
#include <stdio.h>
#include <string>
#include "rbtree.h"
#include "gtest/gtest.h"

TEST(RBTree, Basic)
{
  RBTree<int, int> rbtree;
  rbtree.Put(4, 64);
  rbtree.Put(2, 62);
  rbtree.Put(3, 63);
  rbtree.Put(1, 61);
  rbtree.Put(5, 65);

  ASSERT_EQ(5, rbtree.size());

  bool r;
  int val;
  r = rbtree.Get(4, val);
  EXPECT_TRUE(r);
  ASSERT_EQ(64, val);

  rbtree.Put(4, 74);
  r = rbtree.Get(4, val);
  EXPECT_TRUE(r);
  ASSERT_EQ(74, val);
  
  EXPECT_FALSE(rbtree.Get(10, val));

  /*
  rbtree.Delete(4);
  EXPECT_FALSE(rbtree.Get(4, val));

  rbtree.Delete(3);
  EXPECT_FALSE(rbtree.Get(3, val));
  */
}

::testing::AssertionResult AssertRBTreeEqual(const char *expected_expr,
                                             const char *actual_expr,
                                             const RBTree<int, int> &expected,
                                             const RBTree<int, int> &actual)
{
  if (expected.Equal(actual)) {
    return ::testing::AssertionSuccess();
  }
  return ::testing::AssertionFailure()
    << "Actual:\n" << actual.Serialize() << "\n"
    << "Expected:\n" << expected.Serialize();
}

void Check(const RBTree<int, int> &rbtree, const std::string &tree)
{
  RBTree<int, int> expected;
  EXPECT_TRUE(expected.Deserialize(tree));
  EXPECT_PRED_FORMAT2(AssertRBTreeEqual, expected, rbtree);
}

TEST(RBTree, Structure)
{
  RBTree<int, int> rbtree;

  // insert to 2-node: < it
  rbtree.Put(50, 50);
  rbtree.Put(25, 25);
  Check(rbtree, "((50 50 0) ((25 25 1) () ()) ())");

  // insert to 3-node: > it 
  rbtree.Put(75, 75);
  Check(rbtree, "((50 50 0) ((25 25 0) () ()) ((75 75 0) () ()))");

  // insert to 2-node: > it
  rbtree.Put(37, 37);
  Check(rbtree, "((50 50 0) ((37 37 0) ((25 25 1) () ()) ()) ((75 75 0) () ()))");

  // insert to 3-node: < it
  rbtree.Put(13, 13);
  Check(rbtree, "((50 50 0) ((25 25 1) ((13 13 0) () ()) ((37 37 0) () ())) ((75 75 0) () ()))");
  
  // insert to 2-node: > it
  rbtree.Put(100, 100);
  Check(rbtree, "((50 50 0) ((25 25 1) ((13 13 0) () ()) ((37 37 0) () ())) ((100 100 0) ((75 75 1) () ()) ()))");

  // insert to 3-node: middle it
  // cascade update
  rbtree.Put(87, 87);
  Check(rbtree, "((50 50 0) ((25 25 0) ((13 13 0) () ()) ((37 37 0) () ())) ((87 87 0) ((75 75 0) () ()) ((100 100 0) () ())))");
}



