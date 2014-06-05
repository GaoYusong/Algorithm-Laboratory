#ifndef ALGOLAB_DIJKSTRA_H_
#define ALGOLAB_DIJKSTRA_H_

#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <utility>


class Graph {
public:
  Graph()
    : vsize_(0), esize_(0)
  {

  }

  virtual void init(int vsize)
  {
    vsize_ = vsize;
  }

  virtual void AddEdge(int u, int v, int w) = 0;
  virtual int Distance(int u, int v) = 0;
  virtual int Begin(int u) = 0;
  virtual bool More(int u, int e) = 0;
  virtual int Next(int u, int e) = 0;
  virtual std::pair<int, int> Edge(int u, int e) = 0;

  int vsize()
  {
    return vsize_;
  }

  int esize()
  {
    return esize_;
  }

  static const int INF;
protected:
  bool checkv(int v)
  {
    return v >= 0 && v < vsize_;
  }
  
  static const int MAXVSIZE = 100;
  int vsize_, esize_;
};

class GraphMatrix : public Graph {
public:
  GraphMatrix() {
  }

  void init(int vsize)
  {
    Graph::init(vsize);
    for (int i = 0; i < vsize; i++) {
      for (int j = 0; j < vsize; j++) {
        g_[i][j] = INF;
      }
    }
  }

  // choose min weight
  void AddEdge(int u, int v, int w)
  {
    assert(checkv(u));
    assert(checkv(v));
    g_[u][v] = std::min(g_[u][v], w);
    esize_++;
  }


  int Distance(int u, int v)
  {
    assert(checkv(u));
    assert(checkv(v));
    return g_[u][v];
  }

  int Begin(int u)
  {
    assert(checkv(u));
    for (int v = 0; v < vsize_; v++) {
      if (g_[u][v] < INF)
        return v;
    }
    return vsize_;
  }

  bool More(int u, int e)
  {
    assert(checkv(u));
    return e < vsize_;
  }

  int Next(int u, int e)
  {
    assert(checkv(u));
    for (int v = e + 1; v < vsize_; v++) {
      if (g_[u][v] < INF)
        return v;
    }
    return vsize_;
  }

  std::pair<int, int> Edge(int u, int e)
  {
    return std::make_pair(e, g_[u][e]);
  }
  
private:
  int g_[MAXVSIZE][MAXVSIZE];
};

class GraphList: public Graph {
public:
  GraphList() {
    
  }

  void init(int vsize)
  {
    Graph::init(vsize);
    for (int i = 0; i < vsize; i++) {
      g_[i].clear();
    }
  }

  void AddEdge(int u, int v, int w)
  {
    assert(checkv(u));
    assert(checkv(v));
    g_[u].push_back(std::make_pair(v, w));
    esize_++;
  }

  int Distance(int u, int v)
  {
    assert(checkv(u));
    assert(checkv(v));
    int minv = INF;
    for (int i = 0; i < g_[u].size(); i++) {
      std::pair<int, int> p = g_[u][i];
      if (p.first == v) {
        minv = std::min(minv, p.second);
      }
    }
    return minv;
  }

  int Begin(int u)
  {
    assert(checkv(u));
    return 0;
  }

  bool More(int u, int e)
  {
    assert(checkv(u));
    return e < g_[u].size();
  }

  int Next(int u, int e)
  {
    assert(checkv(u));
    assert(g_[u].size() > e);
    return e + 1;
  }

  std::pair<int, int> Edge(int u, int e)
  {
    assert(checkv(u));
    assert(g_[u].size() > e);
    return g_[u][e];
  }
  
private:
  std::vector<std::pair<int, int> > g_[MAXVSIZE];
};

std::vector<int> DijkstraNN(Graph &g, int s);
std::vector<int> DijkstraNlogM(Graph &g, int s);

#endif
