#include <map>
#include <string>
#include <iostream>

using namespace std;

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year){
      string first_name = "",last_name = "";
    auto first_name_it = first_names.upper_bound(year);
    auto last_name_it = last_names.upper_bound(year);
    if(first_name_it!=begin(first_names)) first_name= (*prev(first_name_it)).second;
    if(last_name_it!=begin(last_names)) last_name = (*prev(last_name_it)).second;
    if(!first_name.size() && !last_name.size()){
        return "Incognito";
    }
    if(first_name.size()>0 && !last_name.size()){
        return first_name+" with unknown last name";
    }
    if(!first_name.size() && last_name.size()>0){
        return last_name+" with unknown first name";
    }
    if(first_name.size()>0 && last_name.size()>0){
        return first_name+" "+last_name;
    }
  }
private:
  map<int,string> first_names;
  map<int,string> last_names;
};
