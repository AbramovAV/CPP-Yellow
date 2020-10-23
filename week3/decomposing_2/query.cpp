#include "query.h"

using namespace std;

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