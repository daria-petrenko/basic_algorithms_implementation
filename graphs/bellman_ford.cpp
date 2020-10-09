#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <climits>

using namespace std;

pair<bool, vector<int>> bellman_ford(const vector<tuple<int, int, int>> edges,  // (c1, c2, w)
                 int num_vertices, int start_ind) {
  vector<int> dist(num_vectices, INT_MAX);
  dist[start_ind] = 0;
  vector<int> prev(num_vertices, -1);
  bool if_changed = false;
  
  int i = 0;
  for (; i < num_vectices; i++) {
    for (auto& edge : edges) {
      if (dist[edge.get<0>] != MAX_INT && 
          dist[edge.get<1>] > dist[edge.get<0>] + edge.get<2>) {
        dist[edge.get<1>] = dist[edge.get<0>] + edge.get<2>;
        prev[edge.get<1>] = edge.get<0>;
        if_changed = true;
      }
    }
    if (!if_changed) {
      return make_pair(true, dist);
    }
    if_changed = false;
  }
  return make_pair(false, dist);
}
  
