#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <cstdint>
#include <climits>

using namespace std;

vector<int> dijkstra(const vector<vector<pair<int, int>>>& graph,  // elems: pairs (distance, index)
                     int start_ind) {
  int n = graph.size();
  vector<int64_t> dist(n, LLONG_MAX);
  vector<int> prev(n, -1);
  dist[start_ind] = 0;
  
  priority_queue<pair<int, int>, vector<pair<int, int>>, 
                greater<pair<int, int>>> pq;  // (distance, index)
  pq.push(make_pair(0, start_ind));
  
  while(!pq.empty()) {
    auto top = pq.top();
    pq.pop();
    if (top.first > dist[top.second]) {
      continue;
    }
    
    for (const auto& elem : graph[top.second]) {
      if (dist[elem.second] > dist[top.second] + elem.first) {
        dist[elem.second] = dist[top.second] + elem.first;
        pq.push(make_pair(dist[elem.second], elem.second));
        prev[elem.second] = top.second;
      }
    }
  }
  return prev;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>());
  for (int i = 0; i < m; i++) {
    int ind1, ind2, w;
    cin >> ind1 >> ind2 >> w;
    if (ind1 != ind2) {
      graph[ind1 - 1].push_back(make_pair(w, ind2 - 1));  // (dist, ind)
      graph[ind2 - 1].push_back(make_pair(w, ind1 - 1));
    }
  }
  
  vector<int> prev = dijkstra(graph, 0);
  if (prev[n - 1] == -1) {
    cout << -1 << endl;
  } else {
    vector<int> path;
    int curr_ind = n - 1;
    while(curr_ind != -1) {
      path.push_back(curr_ind);
      curr_ind = prev[curr_ind];
    }
    for (auto it = path.rbegin(); it != path.rend(); it++) {
      cout << *it + 1 << " ";
    }
    cout << endl;
  }
  return 0;
}
    
    
  
