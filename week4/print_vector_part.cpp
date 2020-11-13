#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers){
    if (numbers.size()>0){
        auto neg_it = find_if(begin(numbers),end(numbers),
                              [](float num){
                                    return num<0;
                              });
        for(auto it = neg_it-1;it>=begin(numbers);--it){
            std::cout<<*it<<" ";
        }
    }
}