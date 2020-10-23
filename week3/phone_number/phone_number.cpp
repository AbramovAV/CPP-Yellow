#include "phone_number.h"
#include <stdexcept>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number){
    char plus = international_number[0];
    if (plus == '+'){
        size_t first_sep = international_number.find("-");
        size_t second_sep = international_number.find("-",first_sep+1);
        if (first_sep != 1 && second_sep - first_sep > 1 && second_sep < international_number.size()-1){
            country_code_ = international_number.substr(1, first_sep - 1);
            city_code_ = international_number.substr(first_sep + 1, second_sep - first_sep - 1);
            local_number_ = international_number.substr(second_sep + 1);
        }
        else{
            throw invalid_argument("Cannot find positions of city code and local number");
        }
    }
    else{
        throw invalid_argument("Number does not start with +");
    }
}

string PhoneNumber::GetCountryCode() const{
    return country_code_;
}

string PhoneNumber::GetCityCode() const{
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const{
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const{
    return "+"+country_code_+"-"+city_code_+"-"+local_number_;
};