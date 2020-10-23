#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if(!r.response.size()){
    for (const string& bus : r.buses) {
          os<<bus<<" ";
        }
  }else{
    os<<r.response;
  }
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if(!r.response.size()){
    int counter = 0;
    for (const auto& stop_item : r.stops) {
        counter++;
        os << "Stop " << stop_item.first << ": ";
        for(const string& bus:stop_item.second){
          os<<bus<<" ";
        }
        if(counter != r.stops.size()) os<<endl;
    }
  }else{
    os<<r.response;
  }
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if(!r.response.size()){
    int counter = 0;
    for (const auto& bus_item : r.buses) {
        counter++;
        os << "Bus " << bus_item.first << ": ";
        for(const string& stop:bus_item.second){
          os<<stop<<" ";
        }
        if(counter != r.buses.size()) os<<endl;
    }
  }else{
    os<<r.response;
  }
  return os;
}