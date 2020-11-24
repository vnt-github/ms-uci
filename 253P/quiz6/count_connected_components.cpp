#include <iostream>
#include <vector>

using namespace std;

// do a dfs and keep track of visited nodes
void dfs(int curr, \
        vector<bool>& visited, \
        vector<vector<int>>& adj_list)
{
    if (visited[curr]) return;
    visited[curr] = true;
    for (auto &&neighbour : adj_list[curr])
        dfs(neighbour, visited, adj_list);
}

// increment ans when starting dfs on unvisited node
int count_connected_components(\
        vector<vector<int>>& adj_list, int N)
{
    int ans = 0;
    vector<bool> visited(N, false);
    for (int i = 0; i < N; i++)
        if (!visited[i]) {
            ans+=1;
            dfs(i, visited, adj_list);
        }
    return ans;
}

int main(int argc, char const *argv[])
{
    vector<vector<int>> adj_list;

    adj_list = {{1, 2, 3}, {0, 3, 4}, {0, 4}, {0, 1}, {1, 2}, {6}, {5, 7}, {6}, {}};
    cout << count_connected_components(adj_list, 9);
    return 0;
}
