#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(){
    string x,op;
    int N,num;
    deque<string> d;
    cin>>x;
    cin>>N;
    d.push_back(x);
    for(int i=0;i<N;i++){
        cin>>op>>num;
        d.push_front("(");
        d.push_back(") "+op+" "+to_string(num));
    }
    while(d.size()>0){
        cout<<d.front();
        d.pop_front();
    }
    cout<<endl;
}