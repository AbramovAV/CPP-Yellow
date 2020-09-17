#include <iostream>

using namespace std;

int main(){
    int32_t N;
    uint64_t R;
    uint16_t W,H,D;
    uint64_t result=0;
    cin>>N>>R;
    for(int32_t i=0;i<N;++i){
        cin>>W>>H>>D;
        result += R*W*H*D;
    }
    cout<<result;
}