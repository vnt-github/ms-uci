
// get distance using Floyd–Warshall
vector<vector<int>> getDist(vector<vector<int>>& edges, int n) {
    const int inf_int = numeric_limits<int>::max();
    vector<vector<int>> dist(n, vector<int>(n, inf_int));
    for (auto&& edge: edges) {
        dist[edge[0]][edge[1]] = edge[2];
        dist[edge[1]][edge[0]] = edge[2];
    }
    
    for (int i = 0; i < n; i++)
        dist[i][i] = 0;
    
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < inf_int && dist[k][j] < inf_int && dist[i][k]+dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k]+dist[k][j];
    
    return dist;
}

// count for each city the reachable cities based on Floyd–Warshall distance
int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    const int inf_int = numeric_limits<int>::max();
    vector<vector<int>> dist = getDist(edges, n);
    
    int min_reachable = inf_int, min_city = 0, curr_reachable=0;
    for (int i = 0; i < n; i++) {
        curr_reachable = 0;
        for (int j = 0; j < n; j++)
            if (i != j && dist[i][j] <= distanceThreshold)
                curr_reachable += 1;
        
        if (curr_reachable <= min_reachable) {
            min_reachable = curr_reachable;
            min_city = i;
        }
    }
    return min_city;
}