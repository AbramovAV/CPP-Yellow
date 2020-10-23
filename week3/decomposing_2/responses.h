#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct BusesForStopResponse {
  string response;
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
  string response;
  vector<pair<string,vector<string>>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
  string response;
  vector<pair<string,vector<string>>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);