#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void GenerateReversedVector(int N, vector<int>& v){
    for(int i=N;i>=1;--i){
        v.push_back(i);
    }
}

void PrintPermutations(vector<int>::iterator first, vector<int>::iterator last){
    for(auto it=first;it<last;++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main(){
    int N;
    vector<int> v;
    cin>>N;
    GenerateReversedVector(N,v);
    do{
        PrintPermutations(begin(v),end(v));
    }while(prev_permutation(begin(v),end(v)));
}