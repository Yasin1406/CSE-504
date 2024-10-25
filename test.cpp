#include<bits/stdc++.h>
using namespace std;
string getPage(string str){
    str = str.substr(2);
    str.pop_back();
    return str;
}
int main(){
    cout << getPage("R(abcd)") << endl;
    return 0;
}