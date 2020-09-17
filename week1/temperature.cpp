#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N;
    int64_t avg_temp=0;
    cin>>N;
    vector<int> temps(N);
    vector<int> above_avg_temps;
    for(int& temp:temps){
        cin>>temp;
        avg_temp+=temp;
    }
    avg_temp/=N;
    int i=0;
    for(auto temp:temps){
        if(temp>avg_temp){
        above_avg_temps.push_back(i);
        }
        ++i;
    }
    cout<<above_avg_temps.size()<<endl;
    for(auto idx:above_avg_temps){
        cout<<idx<<" ";
    }


}