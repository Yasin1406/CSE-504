#include<bits/stdc++.h>
using namespace std;

void takeInput();
void makeGraph();
void makeEdges(string pageName, char currOperation, int currTrx ,int currTime);
string getPageName(string str);
vector<vector<string>> trxs;
vector<vector<bool>> dependencyGraph;
vector<vector<int>> adjList;
bool isCyclic();
bool dfsCheck(int node, vector<int> &vis, vector<int> &pathVis);

int main(){
    takeInput();
    makeGraph();
    // cout << dependencyGraph.size() << " " << dependencyGraph[0].size() << endl;
    // for(auto dg : dependencyGraph){
    //     for(auto d : dg){
    //         if(d){
    //             cout << "1 ";
    //         }
    //         else{
    //             cout << "0 ";
    //         }
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // for(int i = 0; i < adjList.size(); i++){
    //     cout << i << ": ";
    //     for(int j = 0; j < adjList[i].size(); j++){
    //         cout << adjList[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << adjList.size() << endl;
    if(isCyclic()){
        cout << "Not serializable conflict" << endl;
    }
    else{
        cout << "Serializable conflict" << endl;
    }
    
    return 0;
}

void takeInput(){
    freopen("input5.txt", "r", stdin);
    string trx;
    while(getline(cin, trx)){
        vector<string> parsedTrx;
        istringstream iss(trx);
        string token;
        while(getline(iss, token, ',')){
            parsedTrx.push_back(token);
        }
        trxs.push_back(parsedTrx);
    }
    dependencyGraph.resize(trxs.size(), vector<bool>(trxs.size()));
}

void makeGraph(){
    for(int i = 0; i < trxs.size(); i++){
        // string trxName = trxs[i][0];
        for(int j = 1; j < trxs[i].size(); j++){
            if(trxs[i][j][0] == 'R' || trxs[i][j][0] == 'W'){
                string pageName = getPageName(trxs[i][j]);
                char currOperation = trxs[i][j][0];
                makeEdges(pageName, currOperation, i, j);
            }
        }
    }
    for(int i = 0; i < dependencyGraph.size(); i++){
        vector<int> adj;
        // cout << i << ": ";
        for(int j = 0; j < dependencyGraph.size(); j++){
            if(dependencyGraph[i][j]){
                // cout << j << " ";
                adj.push_back(j);
            }
        }
        // cout << endl;
        adjList.push_back(adj);
    }
}

string getPageName(string str){
    str = str.substr(2);
    str.pop_back();
    return str;
}

void makeEdges(string pageName, char currOperation, int currTrx, int currTime){
    for(int i = 0; i < trxs.size(); i++){
        if(i != currTrx){
            for(int j = currTime + 1; j < trxs[i].size(); j++){
                if(trxs[i][j][0] == 'R' || trxs[i][j][0] == 'W'){
                    string thisPage = getPageName(trxs[i][j]);
                    if(thisPage == pageName){
                        if(!(currOperation == 'R' && trxs[i][j][0] == 'R')){
                            dependencyGraph[currTrx][i] = true;
                            continue;
                        }
                    }
                }
            }
        }
    }
}

bool isCyclic(){
    vector<int> vis(adjList.size(), 0);
    vector<int> pathVis(adjList.size(), 0);
    for(int i = 0; i < adjList.size(); i++){
        if(!vis[i]){
            if(dfsCheck(i, vis, pathVis)){
                return true;
            }
        }
    }
    return false;
}

bool dfsCheck(int node, vector<int> &vis, vector<int> &pathVis){
    vis[node] = 1;
    pathVis[node] = 1;
    for(auto it : adjList[node]){
        if(!vis[it]){
            if(dfsCheck(it, vis, pathVis)){
                return true;
            }
        }
        else if(pathVis[it]){
            return true;
        }
    }
    pathVis[node] = 0;
    return false;
}