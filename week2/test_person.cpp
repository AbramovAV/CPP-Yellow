#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

void TestIncognito(){
    {
        Person person;
        person.ChangeFirstName(1965,"Alexey");
        person.ChangeLastName(1965,"Abramov");
        AssertEqual(person.GetFullName(1960),"Incognito");
    }
    {
        Person person;
        AssertEqual(person.GetFullName(2000),"Incognito");
    }
    {
        Person person;
        person.ChangeLastName(1965,"Abramov");
        AssertEqual(person.GetFullName(1960),"Incognito");
    }
    {
        Person person;
        person.ChangeFirstName(1965,"Alexey");
        AssertEqual(person.GetFullName(1960),"Incognito");
    }
}

void TestUnknownFirstname(){
    {
        Person person;
        person.ChangeLastName(1965,"Abramov");
        AssertEqual(person.GetFullName(1965),"Abramov with unknown first name");
    }
    {
        Person person;
        person.ChangeFirstName(1970,"Alexey");
        person.ChangeLastName(1965,"Abramov");
        AssertEqual(person.GetFullName(1965),"Abramov with unknown first name");
    }
}

void TestUnknownLastname(){
    {
        Person person;
        person.ChangeFirstName(1965,"Alexey");
        AssertEqual(person.GetFullName(1965),"Alexey with unknown last name");
    }
    {
        Person person;
        person.ChangeLastName(1970,"Abramov");
        person.ChangeFirstName(1965,"Alexey");
        AssertEqual(person.GetFullName(1965),"Alexey with unknown last name");
    }
}

void TestFullName(){
    {
        Person person;
        person.ChangeLastName(1965,"Abramov");
        person.ChangeFirstName(1965,"Alexey");
        AssertEqual(person.GetFullName(1965),"Alexey Abramov");
        AssertEqual(person.GetFullName(1985),"Alexey Abramov");
    }
    {
        Person person;
        person.ChangeLastName(1955,"Abramov");
        person.ChangeFirstName(1965,"Alexey");
        AssertEqual(person.GetFullName(1965),"Alexey Abramov");
        AssertEqual(person.GetFullName(1985),"Alexey Abramov");
    }
    {
        Person person;
        person.ChangeLastName(1965,"Abramov");
        person.ChangeFirstName(1955,"Alexey");
        AssertEqual(person.GetFullName(1965),"Alexey Abramov");
        AssertEqual(person.GetFullName(1985),"Alexey Abramov");
    }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIncognito,"TestIncognito");
  runner.RunTest(TestUnknownFirstname,"TestUnknownFirstname");
  runner.RunTest(TestUnknownLastname,"TestUnknownLastname");
  runner.RunTest(TestFullName,"TestFullName");
  return 0;
}
