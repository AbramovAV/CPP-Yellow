#include <iostream>
#include <string>
#include <map>
#include <exception>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key,Value>& m, Key k){
    if(m.count(k)==0){
        throw runtime_error("Key not found!");
    } else{
        return m[k];
    }
}
