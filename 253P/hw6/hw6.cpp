#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

// a vertex of a graph with name as tag and x, y as co-ordinates
class graphNode {
    public:
        string name;
        float x;
        float y;
        graphNode(string name, float x, float y): name(name), x(x), y(y) {}
        float distance(graphNode* other) {
            return sqrt(pow(x-other->x, 2) + pow(y-other->y, 2));
        }
};

// an edge between u and v with euclidean distance dist between then
class graphEdge {
    public:
        graphNode* u;
        graphNode* v;
        float dist;
        graphEdge(graphNode* u, graphNode* v): u(u), v(v) {
            dist = u->distance(v);
        }
};

// a node for the disjoint set with Union By Rank and Path Compression
class setNode {
    public:
        int rank;
        string name;
        setNode* parent;
        setNode(string name, int rank): rank(rank), name(name), parent(nullptr) {}
        setNode();
};

// DisjointSet implementation using Union By Rank and Path Compression
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

// return all the possible edges in the graph of nodes, sorted in ascending order by it's length.
vector<graphEdge> getSortedEdges(vector<graphNode>& nodes) {
    vector<graphEdge> edges;
    for (unsigned int i = 0; i < nodes.size(); i++)
        for (unsigned int j = i+1; j < nodes.size(); j++)
            edges.push_back(graphEdge(&nodes[i], &nodes[j]));
    
    sort(edges.begin(), edges.end(), compare);
    return edges;
}

// for all the zones log the nodes within a same zone.
void logZones(vector<graphNode>& nodes, DisjointSet& ds) {
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

// create a mst with graph of nodes till theree are k disjoint sets as zones
void getZones(vector<graphNode>& nodes, int k) {
    DisjointSet ds = DisjointSet(nodes);
    vector<graphEdge> mst;
    for (auto &&edge : getSortedEdges(nodes))
    {
        if (mst.size() == nodes.size() - k)
            break;
        if (ds.Union(edge.u->name, edge.v->name))
            mst.push_back(edge);
    }
    logZones(nodes, ds);
}

// parse input and create nodes for the graph
vector<graphNode> getNodes(int n) {
    vector<graphNode> nodes;
    string name;
    float x=0;
    float y=0;
    for (int i = 0; i < n; i++)
    {
        cin >> name;
        cin >> x;
        cin >> y;
        nodes.push_back(graphNode(name, x , y));
    }
    
    return nodes;
}

int main()
{
    int n=0;
    cin >> n;
    if (!cin || n <= 0) {
        cerr << "invalid n, n must be non negative integer" << endl;
        return -1;
    }
    cin.clear(); cin.ignore();
    vector<graphNode> nodes;
    nodes = getNodes(n);
    int k;
    while (true)
    {
        cin >> k;
        if (!cin || k < 0) {
            cerr << "invalid k, k must be non negative integer" << endl;
        } else {
            cout << "K=" << k << endl;
            getZones(nodes, max(1, min((int)nodes.size(), k)));
        }
        cin.clear(); cin.ignore();     
    }
    return 0;
}