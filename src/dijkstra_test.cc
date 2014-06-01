
#include <stdio.h>
#include "dijkstra.h"
#include "gtest/gtest.h"

void Check(std::vector<int> (func)(Graph &, int), Graph &g)
{
  g.init(10);
  ASSERT_EQ(10, g.vsize());

  g.AddEdge(0, 1, 10);
  g.AddEdge(0, 1, 5);
  g.AddEdge(1, 0, 2);
  ASSERT_EQ(3, g.esize());
  
  g.AddEdge(1, 2, 3);
  g.AddEdge(0, 2, 6);
  g.AddEdge(2, 3, 15);
  g.AddEdge(1, 3, 4);
  g.AddEdge(0, 4, 100);
  g.AddEdge(4, 5, 100);
  g.AddEdge(5, 6, 100);
  g.AddEdge(6, 0, 100);
  
  g.AddEdge(7, 8, 100);
  g.AddEdge(7, 9, 100);
  
  
  std::vector<int> d = func(g, 0);
  int a[10] = {0, 5, 6, 9, 100,
               200, 300, Graph::INF, Graph::INF, Graph::INF};
  std::vector<int> expected(a, a + 10);
  ASSERT_EQ(expected, d);
}


TEST(DijkstraNN, Matrix)
{
  GraphMatrix g;
  Check(DijkstraNN, g);
}

// @NOTICE complexity is not O(N * N) when use adjacency list
TEST(DijkstraNN, List)
{
  GraphList g;
  Check(DijkstraNN, g);
}

// @NOTICE complexity is not O(NlogM) when use matrix
TEST(DijkstraNlogM, Matrix)
{
  GraphMatrix g;
  Check(DijkstraNlogM, g);
}

TEST(DijkstraNlogM, List)
{
  GraphList g;
  Check(DijkstraNlogM, g);
}
