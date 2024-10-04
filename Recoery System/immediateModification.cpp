#include<bits/stdc++.h>
using namespace std;

map<string, pair<bool, bool>> trx;      // 1st bool means isCommited and 2nd bool means toBeConsidered
map<string, pair<string, string>> blocks;       // 1st string means redo value and 2nd string means undo value
vector<string> commands;

vector<string> getRedoList();
vector<string> getUndoList();
void printList(vector<string> list);
void printAction();

int main(){
    freopen("input.txt", "r", stdin);
    string line, str;
    string t, bl, oldVal, newVal;
    int i = 0, starts = 0, ckptIndex = -1;
    vector<string> redoList, undoList;
    while(getline(cin, line)){
        line = line.substr(1, line.size() - 2);
        commands.push_back(line);
        if(line[0]=='S'){
            starts++;
            istringstream iss(line);
            iss >> str;
            iss >> str;
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

    redoList = getRedoList();
    undoList = getUndoList();

    cout << "Redo list: ";
    printList(redoList);
    cout << "Undo list: ";
    printList(undoList);

    for(i = commands.size() - 1; i >= 0; i--){
        if(commands[i][0] == 'T'){
            istringstream iss(commands[i]);
            iss >> t;
            if(!trx[t].second){
                continue;
            }
            iss >> bl;
            iss >> oldVal;
            iss >> newVal;
            auto it = blocks.begin();
            while(it != blocks.end()){
                if(it->first == bl){
                    break;
                }
                it++;
            }
            if(it != blocks.end()){
                if(trx[t].first){
                    it->second.first = newVal;
                }
                else{
                    it->second.second = oldVal;
                }
            }
        }
    }
    printAction();
    return 0;
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

void printAction(){
    cout << "\tRedo\t      Undo" << endl;
    auto it = blocks.begin();
    while (it != blocks.end()){
        cout << it->first << "=\t" << it->second.first << "\t| " << it->second.second << endl;
        it++;
    }
}