#include <iostream>

using namespace std;

vector<int> bfs(const vector<vector<int>>& graph, int start_ind) {
  int n = graph.size();
  vector<int> dist_to_start(n, -1);
  dist_to_start[start_ind] = 0;
  deque<int> dq;
  dq.push_back(start_ind);
  
  while (!dq.empty()) {
    int parent_ind = dq.front();
    dq.pop_front();
    for (int ind : graph[parent_ind]) {
      if (dist_to_start[ind] == -1) {
        dist_to_start[ind] = dist_to_start[parent_ind] + 1;
        dq.push_back(ind);
      }
    }
  }
  return dist_to_start;
}
