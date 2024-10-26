#include <bits/stdc++.h>
using namespace std;

void makeGraph();
void makeEdges(string pageName, char currOperation, int currTrx, int currTime);
string getPageName(string str);
bool detectCycle(int V);

vector<vector<string>> trxs;
vector<vector<bool>> dependencyGraph;

int main(){
    freopen("input2.txt", "r", stdin);
    string trx;
    while (getline(cin, trx)) {
        vector<string> parsedTrx;
        istringstream iss(trx);
        string token;
        while (getline(iss, token, ',')) {
            parsedTrx.push_back(token);
        }
        trxs.push_back(parsedTrx);
    }
    dependencyGraph.resize(trxs.size(), vector<bool>(trxs.size()));
    makeGraph();

    // Output dependency graph
    for (auto dg : dependencyGraph) {
        for (auto d : dg) {
            cout << (d ? "1 " : "0 ");
        }
        cout << endl;
    }

    // Check for cycles in the dependency graph
    if (detectCycle(trxs.size())) {
        cout << "Cycle detected in the dependency graph." << endl;
    } else {
        cout << "No cycle detected in the dependency graph." << endl;
    }

    return 0;
}

void makeGraph() {
    for (int i = 0; i < trxs.size(); i++) {
        for (int j = 1; j < trxs[i].size(); j++) {
            if (trxs[i][j][0] == 'R' || trxs[i][j][0] == 'W') {
                string pageName = getPageName(trxs[i][j]);
                char currOperation = trxs[i][j][0];
                makeEdges(pageName, currOperation, i, j);
            }
        }
    }
}

string getPageName(string str) {
    str = str.substr(2);
    str.pop_back();
    return str;
}

void makeEdges(string pageName, char currOperation, int currTrx, int currTime) {
    for (int i = 0; i < trxs.size(); i++) {
        if (i != currTrx) {
            for (int j = currTime + 1; j < trxs[i].size(); j++) {
                if (trxs[i][j][0] == 'R' || trxs[i][j][0] == 'W') {
                    string thisPage = getPageName(trxs[i][j]);
                    if (thisPage == pageName) {
                        if (!(currOperation == 'R' && trxs[i][j][0] == 'R')) {
                            dependencyGraph[currTrx][i] = true;
                            continue;
                        }
                    }
                }
            }
        }
    }
}

// Single detectCycle function to detect cycles using a stack and visited vector
bool detectCycle(int V) {
    vector<int> visited(V, -1); // Initialize visited vector with -1 (unvisited)
    vector<int> parent(V, -1);  // Initialize parent vector with -1 (no parent)

            stack<int> st;
    for (int start = 0; start < V; start++) {
        if (visited[start] == -1) { // Unvisited node
            st.push(start);
            visited[start] = 1; // Mark as currently in stack

            while (!st.empty()) {
                int u = st.top();
                bool hasUnvisitedChild = false;

                for (int v = 0; v < V; v++) {
                    if (dependencyGraph[u][v]) { // Edge from u to v exists
                        if (visited[v] == -1) { // If v is unvisited
                            st.push(v);
                            visited[v] = 1; // Mark v as currently in the stack
                            parent[v] = u;  // Set u as parent of v
                            hasUnvisitedChild = true;
                            break;
                        } else if (visited[v] == 1 && parent[u] != v) { 
                            // Found a cycle
                            return true;
                        }
                    }
                }

                if (!hasUnvisitedChild) { // No unvisited child
                    visited[u] = 0; // Mark as processed (exited from stack)
                    st.pop();
                }
            }
        }
    }
    return false;
}
