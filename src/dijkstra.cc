#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include "dijkstra.h"

std::vector<int> DijkstraNN(Graph &g, int s)
{
  std::vector<int> d(g.vsize(), Graph::INF);
  std::vector<bool> vis(g.vsize(), false);
  d[s] = 0;
  while (true) {
    int u = -1;
    for (int i = 0; i < g.vsize(); i++) {
      if (!vis[i]) {
        if (u == -1 || d[u] > d[i]) {
          u = i;
        }
      }
    }
    if (u == -1)
      break;
    vis[u] = true;

    for (int i = 0; i < g.vsize(); i++) {
      int w = g.Distance(u, i);
      if (d[i] > d[u] + w) {
        d[i] = d[u] + w;
      }
    }
    
  }

  return d;
}

std::vector<int> DijkstraNlogM(Graph &g, int s)
{
  std::vector<int> d(g.vsize(), Graph::INF);
  d[s] = 0;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > pq;

  pq.push(std::make_pair(d[s], s));
  while (!pq.empty()) {
    std::pair<int, int> p = pq.top();
    pq.pop();
    int u = p.second;
    if (d[u] < p.first) {
      continue;
    }
    for (int e = g.Begin(u); g.More(u, e); e = g.Next(u, e)) {
      std::pair<int, int> edge = g.Edge(u, e);
      int v = edge.first, w = edge.second;
      if (d[v] > d[u] + w) {
        d[v] = d[u] + w;
        pq.push(std::make_pair(d[v], v));
      }
    }
    
  }

  return d;
}
