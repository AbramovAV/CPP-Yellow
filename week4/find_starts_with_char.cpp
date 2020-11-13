#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end,char prefix){
    RandomIt lower_it = lower_bound(range_begin,range_end,prefix,[](string first,char second){
        return first[0]<second;
    });
    RandomIt upper_it = lower_bound(range_begin,range_end,static_cast<char>(prefix+1),[](string first,char second){
        return first[0]<second;
    });
    return make_pair(lower_it,upper_it);
}
