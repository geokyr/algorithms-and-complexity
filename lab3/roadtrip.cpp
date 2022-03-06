#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int n, m, q, u, v, length;

// Struct for a graph edge.
struct Edge {
    int u;
    int v;
    int d;
};

bool edge_compare(Edge e1, Edge e2) {
    return e1.d < e2.d;
}

// Struct for a cartesian node.
struct Node{
    int id;
    int value;
    int parent;
    int left = 0;
    int right = 0;

    Node(int id, int value, int parent, int left, int right) :
        id(id), value(value), parent(parent), left(left), right(right) {}
};

// Class for Disjoint Sets.
class DisjointSets {
    public:
        int *parent;
        int *rank;
        int n;

        DisjointSets() : n(0) {}
        DisjointSets(int n);

        int find(int u);
        void union_rank(int x, int y);
};

DisjointSets::DisjointSets(int n) : n(n) {
    // Parametrized constructor.
    
    // Allocate memory.
    parent = new int[n + 1];
    rank = new int[n + 1];

    // Initially, all vertices are in different sets (so their
    // parent is themselves) and have rank equal to 0.
    for(int i = 0; i <= n; i++) {
        rank[i] = 0;
        parent[i] = i;
    }
}

int DisjointSets::find(int u) {
    // Find with Path Compression.
    if(u != parent[u]) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void DisjointSets::union_rank(int x, int y) {
    x = find(x);
    y = find(y);

    // Union by rank.
    if(rank[x] > rank[y]) {
        parent[y] = x;
    }
    else {
        parent[x] = y;
    }
    if (rank[x] == rank[y]) {
        rank[y]++;
    }
}

// Class for a Graph.
class Graph {
    private:
        vector<vector<int>> adj_list;

    public:
        int n;
        int m;
        vector<Edge> edges;

        Graph() {}
        Graph(int n, int m);

        void add_edge(int u, int v, int d);
        void init_graph(int size);
        void kruskal_mst(vector<Edge> edges_vector);
};

Graph::Graph(int n, int m) : n(n), m(m) {
    // Parametrized constructor.
    
    adj_list = vector<vector<int>> (n + 1, vector<int>());
}

void Graph::add_edge(int u, int v, int d) {
    // Add an edge to this graph.
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);

    edges.push_back({u, v, d});
}

void Graph::init_graph(int size) {
    // Initialize this graph based on the input.
    int u, v, d;
    
    for (int i = 0; i < size; i++) {
        cin >> u >> v >> d;
        
        // Create a new edge, between vertices u and v, of distance w.
        add_edge(u, v, d);
    }
}

void Graph::kruskal_mst(vector<Edge> edges_vector) {
    // Sort the edges in increasing order based on their distance w.
    sort(edges_vector.begin(), edges_vector.end(), edge_compare);

    // Create a new instance of disjoint sets.
    DisjointSets s(n);

    // Iterare through the sorted edges.
    vector<Edge>::iterator it;
    for(it = edges_vector.begin(); it != edges_vector.end(); it++) {
        int u = it->u;
        int v = it->v;

        int set_u = s.find(u);
        int set_v = s.find(v);

        // Check if the selected edge is creating a cycle or not
        // by checking if the two vertices belong in the same set.
        // If not, then add the new edge to the MST and perform
        // union by rank to the two vertices sets.
        if(set_u != set_v) {
            add_edge(u, v, it->d);
            s.union_rank(set_u, set_v);
        }
    }
}

// Class to correct info about parents after union by rank.
class ParentInfo {
    public:
        vector<int> parent;
        DisjointSets s;

        ParentInfo(int n);

        void set_parent(int u, int v, int p);
        int get(int u);
};

ParentInfo::ParentInfo(int n) {
    parent = vector<int> (n + 1);
    
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }

    DisjointSets s(n);
    this->s = s;
}

void ParentInfo::set_parent(int u, int v, int p) {
    // When merging make sure the new parent of
    // both nodes will be set to p.
    s.union_rank(u, v);
    parent[s.find(u)] = p;
}

int ParentInfo::get(int u) {
    // Parent of the node is the grand-parent of node u.
    return parent[s.find(u)];
}

// Class that handles queries to give the final answer. 
class Query {
    private:
        int n;
        int m;
        Graph mst;
        Node* cartesian;
        int *ev, *l, *h;
        int **arr;
    
    public:
        Query(Graph mst);

        void create_cartesian();
        void create_elh(int node, int level, int *counter);
        void preprocess_queries(int *a, int n);
        int rmq(int *l, int i, int j);
        int query(int i, int j);
};

Query::Query(Graph mst) : mst(mst), n(mst.n), m(mst.m), 
    cartesian((Node*) malloc((n + m + 1) * sizeof(Node))),
    ev((int*) malloc(2 * (n + m) * sizeof(int))),
    l((int*) malloc(2 * (n + m) * sizeof(int))),
    h((int*) malloc(2 * (n + m) * sizeof(int))),
    arr((int**) malloc(2 * (n + m) * sizeof(int*))) {
    
    // Create the Cartesian tree from the mst.
    create_cartesian();

    // Prepare the arrays for the Euler Tour.
    int nv = 2 * (n + m);
    for(int i = 0; i < nv; i++) {
        ev[i] = l[i] = h[i] = 0;
    }

    // Euler Tour to convert out problem to an RMQ.
    int counter = 0;
    create_elh(n + m, 0, &counter);
    
    for(int i = 0; i < nv; i++) {
        arr[i] = (int*) malloc(ceil(log2(nv) * sizeof(int)));
    }

    preprocess_queries(l, nv);
}

void Query::create_cartesian() {
    // Sort the edges in increasing order.
    sort(mst.edges.begin(), mst.edges.end(), edge_compare);

    // Initialize the vector containing the nodes.
    for(int i = 1; i <= n + m; i++) {
        cartesian[i] = Node(i, i, 0, 0, 0);
    }

    ParentInfo parents(n);

    for(int i = n + 1; i <= n + m; i++) {
        Edge min_edge = mst.edges[i - n - 1];
        int u = min_edge.u , v = min_edge.v;

        // Set the correct children.
        cartesian[i].left = parents.get(u);
        cartesian[i].right = parents.get(v);
        cartesian[i].value = min_edge.d;

        // Update the parent values in the cartesian tree.
        cartesian[cartesian[i].left].parent = i;
        cartesian[cartesian[i].right].parent = i;

        // Update the values of the parents for the nodes.
        parents.set_parent(u, v, i);
    }
}

void Query::create_elh(int node, int level, int *counter) {
    // This function does the Eulerian Tour.
    (*counter)++;

    // Update the values of the arrays.
    ev[*counter] = node;
    l[*counter] = level;
    if(h[node] == 0) {
        h[node] = *counter;
    }
    
    // DFS on the left child.
    if(cartesian[node].left != 0) {
        create_elh(cartesian[node].left, level + 1, counter);

        // Add the new entries.
        (*counter)++;
        ev[*counter] = node;
        l[*counter] = level;
    }

    // DFS on the right child.
    if(cartesian[node].right != 0) {
        create_elh(cartesian[node].right, level + 1, counter);

        // Add the new entries.
        (*counter)++;
        ev[*counter] = node;
        l[*counter] = level;
    }
}

void Query::preprocess_queries(int *a, int n) {
    // This is the Sparce Matrix Optimization Method
    // for solving RMQs with <O(nlogn), O(1)>
    // preprocess and query complexities.
    int i, j;

    // Initialize M for the intervals with length 1.
    for (i = 0; i < n; i++) {
        arr[i][0] = i;
    }

    // Computer values from smaller to larger intervals.
    for (j = 1; 1 << j <= n; j++) {
        for(i = 0; i + (1 << j) - 1 < n; i++) {
            if(a[arr[i][j - 1]] < a[arr[i + (1 << (j - 1))][j - 1]]) {
                arr[i][j] = arr[i][j - 1];
            }
            else {
                arr[i][j] = arr[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int Query::rmq(int *a, int i, int j) {
    // This answers an RMQ in O(1) time based on the
    // arr[n][logn].
    int k = log2(j - i + 1);
    if (a[arr[i][k]] <= a[arr[j - (int)pow(2, k) + 1][k]]) {
        return arr[i][k];
    }
    else {
        return arr[j - (int)pow(2, k) + 1][k];
    }
}

int Query::query(int i, int j) {
    // This is the conversion of the LCA to RMQ problem.
    // We can solve RMQ query in O(1), so we can do the same
    // with the LCA on the cartesian tree.

    return cartesian[ev[rmq(l, min(h[i], h[j]), max(h[i], h[j]))]].value;
}

int main() {
    cin >> n >> m;

    // Initialize the input graph g and its MST.
    Graph g(n, m), mst(n, n - 1);

    // Update the graph based on the input.
    g.init_graph(m);

    // Create the MST of graph g.
    mst.kruskal_mst(g.edges);

    // Create a query class instance to solve the problem,
    // using an LCA to RMQ conversion and an RMQ preprocessing
    // that results in queries answered in constant time.
    Query answer(mst);

    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> u >> v;
        
        // Get the max-min length of the path.
        length = answer.query(u, v);
        cout << length << endl;
    }

    return 0;
}