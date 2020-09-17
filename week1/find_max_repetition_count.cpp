#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>

using namespace std;

tuple<string,string,map<Lang,string>,int64_t> GetRank(const Region& region){
    return tie(region.std_name,region.parent_std_name,region.names,region.population);
}

bool operator<(Region lhs, Region rhs){
    return GetRank(lhs)<GetRank(rhs);
}

int FindMaxRepetitionCount(const vector<Region>& regions){
    map<Region,int> repetitions;
    int max_repetition_count = 0;
    for(auto region:regions){
        repetitions[region]++;
        if(repetitions[region]>max_repetition_count) max_repetition_count = repetitions[region];
    }
    return max_repetition_count;
}
