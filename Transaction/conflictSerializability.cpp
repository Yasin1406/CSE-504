#include<bits/stdc++.h>
using namespace std;

void makeGraph();
void makeEdges(string pageName, char currOperation, int currTrx ,int currTime);
string getPageName(string str);
vector<vector<string>> trxs;
vector<vector<bool>> dependencyGraph;
int main(){
    freopen("input.txt", "r", stdin);
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
    makeGraph();
    // cout << dependencyGraph.size() << " " << dependencyGraph[0].size() << endl;
    for(auto dg : dependencyGraph){
        for(auto d : dg){
            if(d){
                cout << "1 ";
            }
            else{
                cout << "0 ";
            }
        }
        cout << endl;
    }
    
    
    return 0;
}

void makeGraph(){
    for(int i = 0; i < trxs.size(); i++){
        string trxName = trxs[i][0];
        for(int j = 1; j < trxs[i].size(); j++){
            if(trxs[i][j][0] == 'R' || trxs[i][j][0] == 'W'){
                string pageName = getPageName(trxs[i][j]);
                char currOperation = trxs[i][j][0];
                makeEdges(pageName, currOperation, i, j);
            }
        }
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
                            dependencyGraph[i][currTrx] = true;
                            continue;
                        }
                    }
                }
            }
        }
    }
}