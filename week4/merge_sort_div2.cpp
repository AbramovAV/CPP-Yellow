#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if ((range_end - range_begin)<2){
        return;
    }else{
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        vector<typename RandomIt::value_type> merged_elements;
        int half_size = elements.size()/2;
        auto middle = begin(elements) + half_size;
        MergeSort(begin(elements),middle);
        MergeSort(middle,end(elements));
        merge(begin(elements),middle,
              middle,end(elements),
              range_begin);
    }
}
