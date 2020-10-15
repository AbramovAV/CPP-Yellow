#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c) {
  double x1,x2,D;
    D = b*b - 4*a*c;
    if(D<0){return 0;}
    if(a==0){
        if(b==0){
            return 0;
        }
        return 1;
    }

    x1 = (-b + sqrt(D))/(2*a);
    x2 = (-b - sqrt(D))/(2*a);
    if(x1!=x2){
        return 2;
    } else{
        return 1;
    }
}

void TestUsualEq(){
    {
        double a = 2, b = 4, c = 1;
        AssertEqual(GetDistinctRealRootCount(a,b,c),2);
    }
    {
        double a = 1, b = 2, c = 1;
        AssertEqual(GetDistinctRealRootCount(a,b,c),1);
    }
}

void TestNegativeDisc(){
    {
        double a = 2, b = 4, c = 4;
        AssertEqual(GetDistinctRealRootCount(a,b,c),0);
    }
    {
        double a = 8, b = 4, c = 1;
        AssertEqual(GetDistinctRealRootCount(a,b,c),0);
    }
}

void TestZeroedA(){
    {
        double a = 0, b = 4, c = 4;
        AssertEqual(GetDistinctRealRootCount(a,b,c),1);
    }
}

void TestZeroedB(){
    {
        double a = 1, b = 0, c = -4;
        AssertEqual(GetDistinctRealRootCount(a,b,c),2);
    }
    {
        double a = 1, b = 0, c = 4;
        AssertEqual(GetDistinctRealRootCount(a,b,c),0);
    }
}

void TestZeroedC(){
    {
        double a = 1, b = 4, c = 0;
        AssertEqual(GetDistinctRealRootCount(a,b,c),2);
    }
}

void TestZeroedAB(){
    {
        double a = 0, b = 0, c = -4;
        AssertEqual(GetDistinctRealRootCount(a,b,c),0);
    }
}

void TestZeroedBC(){
    {
        double a = -4, b = 0, c = 0;
        AssertEqual(GetDistinctRealRootCount(a,b,c),1);
    }
}

void TestZeroedAC(){
    {
        double a = 0, b = -5, c = 0;
        AssertEqual(GetDistinctRealRootCount(a,b,c),1);
    }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestUsualEq,"TestUsualEq");
  runner.RunTest(TestNegativeDisc,"TestNegativeDisc");
  
  runner.RunTest(TestZeroedA,"TestZeroedA");
  runner.RunTest(TestZeroedB,"TestZeroedB");
  runner.RunTest(TestZeroedC,"TestZeroedC");
  
  runner.RunTest(TestZeroedAB,"TestZeroedAB");
  runner.RunTest(TestZeroedBC,"TestZeroedBC");
  runner.RunTest(TestZeroedAC,"TestZeroedAC");
  return 0;
}