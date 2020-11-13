#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){
    if ((range_end - range_begin)<2){
        return;
    }else{
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        vector<typename RandomIt::value_type> merged_elements;
        int third_size = elements.size()/3;
        auto begin_el = begin(elements);
        auto end_el = end(elements);
        MergeSort(begin_el,begin_el+third_size);
        MergeSort(begin_el+third_size,begin_el+2*third_size);
        MergeSort(begin_el+2*third_size,end_el);
        merge(begin_el,begin_el+third_size,
              begin_el+third_size,begin_el+2*third_size,
              back_inserter(merged_elements));
        merge(begin(merged_elements),end(merged_elements),
              begin_el+2*third_size,end_el,
              range_begin);
    }
}

