#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(
    const set<int>& numbers,
    int border){
        auto upper_it = numbers.lower_bound(border);
        auto lower_it = upper_it;
        if(upper_it!=begin(numbers)){
            lower_it = prev(upper_it);
        }
        if((*upper_it - border)<(border - *lower_it) && upper_it!=end(numbers)) return upper_it;
        return lower_it;
    }
