#include<bits/stdc++.h>
using namespace std;

map<string, pair<bool, bool>> trx;      
map<string, pair<string, string>> blocks;       
vector<string> commands, redoList, undoList;
string line, str;
string t, bl, oldVal, newVal;
int i = 0, ckptIndex = -1;

vector<string> getRedoList();
vector<string> getUndoList();
void printList(vector<string> list);
void printAction();
void readInput();
void getActions();

int main(){
    
    readInput();

    redoList = getRedoList();
    undoList = getUndoList();

    cout << "Redo list: ";
    printList(redoList);
    cout << "Undo list: ";
    printList(undoList);

    getActions();    
    printAction();
    return 0;
}

void readInput(){
    freopen("input.txt", "r", stdin);

    while(getline(cin, line)){
        line = line.substr(1, line.size() - 2);
        commands.push_back(line);
        if(line[0]=='S'){
            istringstream iss(line);
            iss >> str; // START
            iss >> str; // T1
            trx[str].first = false;
            trx[str].second = true;
        }
        else if(line[1] == 'K'){
            ckptIndex = i;
        }
        else if(line[1] == 'O'){
            istringstream iss(line);
            iss >> str;
            iss >> str;
            trx[str].first = true;
        }
        else if(line[0] == 'T'){
            istringstream iss(line);
            iss >> str;
            iss >> str;
            blocks[str] = {"", ""};
        }
        i++;
    }
    if(ckptIndex != -1){
        for(i = 0; i < ckptIndex; i++){
            if(commands[i][1] == 'O'){
                istringstream iss(commands[i]);
                iss >> str;
                iss >> str;
                trx[str].second = false;
            }
        }
    }
}

vector<string> getRedoList(){
    vector<string> redoList;
    auto it = trx.begin();
    while(it != trx.end()){
        if(it->second.second && it->second.first){
            redoList.push_back(it->first);
        }
        it++;
    }
    return redoList;
}

vector<string> getUndoList(){
    vector<string> undoList;
    auto it = trx.begin();
    while(it != trx.end()){
        if(it->second.second && !it->second.first){
            undoList.push_back(it->first);
        }
        it++;
    }
    return undoList;
}

void printList(vector<string> list){
    for(auto l : list){
        cout << l << " ";
    }
    cout<<endl;
}

void getActions(){
    for(i = commands.size() - 1; i >= 0; i--){
        if(commands[i][0] == 'T'){
            istringstream iss(commands[i]);
            iss >> t;
            if(!trx[t].second){ // not considered
                continue;
            }
            iss >> bl;
            iss >> oldVal;
            iss >> newVal;
            if(!trx[t].first) {
                blocks[bl].second = oldVal;   
            }
        }
    }
    for(i = commands.size() - 1; i >= 0; i--){
        if(commands[i][0] == 'T'){
            istringstream iss(commands[i]);
            iss >> t;
            if(!trx[t].second){ // not considered
                continue;
            }
            iss >> bl;
            iss >> oldVal;
            iss >> newVal;
            if(trx[t].first) {
                blocks[bl].first = newVal;   
            }
        }
    }
}

void printAction(){
    cout << "\tRedo\t      Undo" << endl;
    auto it = blocks.begin();
    while (it != blocks.end()){
        cout << it->first << "=\t" << it->second.first << "\t| " << it->second.second << endl;
        it++;
    }
}