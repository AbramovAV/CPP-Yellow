#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
      buses_to_stops[bus] = stops;
      for (string& stop : buses_to_stops[bus]) {
        stops_to_buses[stop].push_back(bus);
      }
  }

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
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

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
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