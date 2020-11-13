#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(){
    string x,prev_op = "/",op;
    int N,num;
    cin>>x;
    cin>>N;
    deque<string> d;
    d.push_back(x);
    for(int i=0;i<N;i++){
        cin>>op>>num;
        if((prev_op == "+" || prev_op == "-") && (op == "/" || op == "*")){
            d.push_front("(");
            d.push_back(") "+op+" "+to_string(num));
        }else{
            d.push_back(" "+op+" "+to_string(num));
        }
        prev_op = op;
    }
    while(d.size()>0){
        cout<<d.front();
        d.pop_front();
    }
    cout<<endl;
}