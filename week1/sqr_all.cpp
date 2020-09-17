#include <iostream>
#include <map>
#include <vector>

using namespace std;

template<typename T> T Sqr(T x);
template<typename T> vector<T> Sqr(vector<T> vi);
template<typename Key,typename Value> map<Key,Value> Sqr(map<Key,Value> mi);
template<typename First,typename Second> pair<First,Second> Sqr(pair<First,Second> pi);

template<typename T>
T Sqr(T x){
    return x*x;
}

template<typename T>
vector<T> Sqr(vector<T> vi){
    for(auto& v:vi){
        v = Sqr(v);
    }
    return vi;
}

template<typename First,typename Second>
pair<First,Second> Sqr(pair<First,Second> pi){
    pi.first = Sqr(pi.first);
    pi.second = Sqr(pi.second);
    return pi;
}

template<typename Key,typename Value>
map<Key,Value> Sqr(map<Key,Value> mi){
    for(auto& item:mi){
        item.second = Sqr(item.second);
    }
    return mi;
}