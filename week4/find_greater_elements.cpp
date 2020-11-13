#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
    auto border_it = find_if(begin(elements),end(elements),
                             [border](T el){
                                return el>border;
                             });
    return {border_it,end(elements)};
}
