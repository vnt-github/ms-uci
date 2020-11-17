#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

class graphNode {
    public:
        float x;
        float y;
        string name;
        graphNode(string name, float x, float y): name(name), x(x), y(y) {}
        float distance(graphNode* other) {
            return sqrt(pow(x-other->x, 2) + pow(y-other->y, 2));
        }
};

class graphEdge {
    public:
        graphNode* u;
        graphNode* v;
        float dist;
        graphEdge(graphNode* u, graphNode* v): u(u), v(v) {
            dist = u->distance(v);
        }
};

class setNode {
    public:
        int rank;
        string name;
        setNode* parent;
        setNode(string name, int rank): rank(rank), name(name), parent(nullptr) {}
        setNode();
};

class DisjointSet
{
public:
    unordered_map<string, setNode*> node_map;
    DisjointSet(vector<graphNode>& data) {
        int counter = 0;
        for (auto &&node : data)
            node_map[node.name] = new setNode(node.name, counter++);
    };

    setNode* Find(string query_name) {
        if (node_map.find(query_name) == node_map.end())
            return nullptr;
        
        setNode* node = node_map[query_name];
        if (!node->parent)
            return node_map[query_name];
        
        node->parent = Find(node->parent->name);
        return node->parent;
    }

    bool Union(string name_a, string name_b) {
        setNode* rank_node_a = Find(name_a);
        setNode* rank_node_b = Find(name_b);

        if (rank_node_a->rank > rank_node_b->rank)
            rank_node_a->parent = rank_node_b;
        else if (rank_node_a->rank < rank_node_b->rank)
            rank_node_b->parent = rank_node_a;
        else
            return false;

        return true;
    }

};

bool compare(graphEdge a, graphEdge b) {
    return  a.dist < b.dist;
}

vector<graphEdge> getSortedEdges(vector<graphNode> nodes) {
    vector<graphEdge> edges;
    for (int i = 0; i < nodes.size(); i++)
        for (int j = i+1; j < nodes.size(); j++)
            edges.push_back(graphEdge(&nodes[i], &nodes[j]));
    
    sort(edges.begin(), edges.end(), compare);
    return edges;
}

void logZones(vector<graphEdge>& mst, vector<graphNode>& nodes, DisjointSet& ds) {
    unordered_map<string, vector<string>> rank_map;
    for (auto &&each : nodes)
        rank_map[ds.Find(each.name)->name].push_back(each.name);
    
    int group_counter=0;
    for (auto &&key_values: rank_map)
    {
        cout << "\tCluster " << ++group_counter << ": ";
        for (auto &&value : key_values.second)
            cout << value << ", ";
        cout << endl;
    }
}

void getZones(vector<graphNode>& nodes, int k) {
    DisjointSet ds = DisjointSet(nodes);
    vector<graphEdge> mst;
    for (auto &&edge : getSortedEdges(nodes))
    {
        if (ds.Union(edge.u->name, edge.v->name))
            mst.push_back(edge);
        if (mst.size() == nodes.size() - k)
            break;
    }
    logZones(mst, nodes, ds);
}

vector<graphNode> getNodes() {
    vector<graphNode> nodes;
    int n=0;
    cin >> n;
    string name;
    int x=0;
    int y=0;
    for (int i = 0; i < n; i++)
    {
        cin >> name;
        cin >> x;
        cin >> y;
        nodes.push_back(graphNode(name, x , y));
    }
    
    return nodes;
}

int main(int argc, char const *argv[])
{
    vector<graphNode> nodes;
    nodes = getNodes();
    int k;
    while (true)
    {
        cin >> k;
        if (k < 0) {
            cout << "invalid k should be non-negative" << endl;
            continue;
        } else {
            cout << "K=" << k << endl;
            getZones(nodes, max(1, k));
        }
            
    }
    return 0;
}


// nodes = {
//     graphNode("A", 6, 2),
//     graphNode("B", 7, 3),
//     graphNode("C", 9, 3),
//     graphNode("D", 8, 5),
//     graphNode("E", 9, 8),
//     graphNode("F", 8, 9),
//     graphNode("M", 2, 8),
//     graphNode("N", 2, 6),
//     graphNode("O", 3, 5),
//     graphNode("G", 7, 10),
//     graphNode("H", 6, 11),
//     graphNode("I", 8, 14),
//     graphNode("J", 6, 14),
//     graphNode("K", 4, 14),
//     graphNode("L", 2, 14)
// };
//
// NOTE:  k > 0 check or K >= num_nodes then return
