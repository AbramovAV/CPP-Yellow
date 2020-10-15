#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <utility>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
  string query;
  is>>query;
  if(query=="NEW_BUS"){
    q.type = QueryType::NewBus;
    int stop_count;
    is>>q.bus>>stop_count;
    q.stops.resize(stop_count);
    for(string& stop:q.stops){
      is>>stop;
    }
  }else if(query=="BUSES_FOR_STOP"){
    q.type = QueryType::BusesForStop;
    is>>q.stop;
  }else if(query=="STOPS_FOR_BUS"){
    q.type = QueryType::StopsForBus;
    is>>q.bus;
  }else if(query=="ALL_BUSES"){
    q.type = QueryType::AllBuses;
  }
  return is;
}

struct BusesForStopResponse {
  string response;
  vector<string> buses;
};

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

struct StopsForBusResponse {
  string response;
  vector<pair<string,vector<string>>> stops;
};

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

struct AllBusesResponse {
  string response;
  vector<pair<string,vector<string>>> buses;
};

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

class BusManager {
private:
  map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
  void AddBus(const string& bus, const vector<string>& stops) {
      buses_to_stops[bus] = stops;
      for (string& stop : buses_to_stops[bus]) {
        stops_to_buses[stop].push_back(bus);
      }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
      BusesForStopResponse response;
      if (stops_to_buses.count(stop) == 0) {
        response.response = "No stop";
      } else {
        for (const string& bus : stops_to_buses.at(stop)) {
          response.buses.push_back(bus);
        }
      }
      return response;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
      StopsForBusResponse response;
      if (buses_to_stops.count(bus) == 0) {
        response.response = "No bus";
      } else {
        for (const string& stop : buses_to_stops.at(bus)) {
          vector<string> buses;
          if (stops_to_buses.at(stop).size() == 1) {
            buses.push_back("no interchange");
          } else {
            for (const string& other_bus : stops_to_buses.at(stop)) {
              if (bus != other_bus) {
                buses.push_back(other_bus);
              }
            }
          }
          auto stops_for_bus = make_pair(stop,buses);
          response.stops.push_back(stops_for_bus);
        }
      }
      return response;
  }

  AllBusesResponse GetAllBuses() const {
    AllBusesResponse response;
    if (buses_to_stops.empty()) {
        response.response = "No buses";
      } else {
        for (const auto& bus_item : buses_to_stops) {
          vector<string> stops;
          for (const string& stop : bus_item.second) {
            stops.push_back(stop);
          }
          auto buses_for_stops = make_pair(bus_item.first,stops);
          response.buses.push_back(buses_for_stops);
        }
      }
    return response;
  }
};