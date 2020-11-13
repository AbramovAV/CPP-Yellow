#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end,const string& prefix){
    RandomIt lower_it = lower_bound(range_begin,range_end,prefix,[](string first,string second){
    return first<second;
    });
    const string next_prefix = prefix.substr(0,prefix.size()-1) + static_cast<char>(prefix.back()+1);
    RandomIt upper_it = lower_bound(range_begin,range_end,next_prefix,[](string first,string second){
        return first<second;
    });
    return make_pair(lower_it,upper_it);
}
