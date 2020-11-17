class Node{
    public:
        bool visited=false;
        bool visiting=false;
        vector<Node*> neighbours;
};

// dfs and check if it's possible to visit
bool dfs(Node& current_node) {
    // if visited and again visiting then return false
    if (current_node.visited) return true;
    if (current_node.visiting) return false;
    current_node.visiting = true;
    for(auto&& each_neighbour: current_node.neighbours) {
        if (!dfs(*each_neighbour)) return  false;
    }
    current_node.visited = true;
    return true;
}

// preprocesses the input to make courses nodes and make call to dfs for each
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<Node*> courses(numCourses);

    // setup nodes
    for(int i = 0; i < numCourses; i++)
        courses[i] = new Node();
    
    // populate the neighbours
    for(auto&& each_edge: prerequisites)
        courses[each_edge[0]]->neighbours.push_back(courses[each_edge[1]]);

    for(auto&& each_node: courses)
        if (!dfs(*each_node)) return false;

    return true;
}