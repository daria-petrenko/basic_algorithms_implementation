#include <iostream>

using namespace std;

void dfs(const vector<vector<int>>& graph,
         vector<bool> visited, int start_ind) {
  visited[start_ind] = true;
  for (int ind : graph[start_ind]) {
    if (!visited[ind]) {
      dfs(graph, visited, ind);
    }
  }
}
