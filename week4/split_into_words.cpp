#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s){
    vector<string> words;
    auto space_it = find(begin(s),end(s),' ');
    auto word_begin = begin(s);
    while(word_begin<end(s)){
        words.push_back({word_begin,space_it});
        word_begin = space_it+1;
        space_it = find(word_begin,end(s),' ');
    }
    return words;
}
