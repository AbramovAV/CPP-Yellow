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

bool IsPalindrom(string s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

void TestEmptyString(){
  AssertEqual(IsPalindrom(""),true);
}

void TestOneCharString(){
  AssertEqual(IsPalindrom("a"),true);
  AssertEqual(IsPalindrom("1"),true);
  AssertEqual(IsPalindrom(" "),true);
  AssertEqual(IsPalindrom("_"),true);
}

void TestRegularString(){
  AssertEqual(IsPalindrom("madam"),true);
  AssertEqual(IsPalindrom("level"),true);
  AssertEqual(IsPalindrom("wasitacaroracatisaw"),true);
  AssertEqual(IsPalindrom("leveel"),false);
}

void TestFirstAndLastChar(){
  AssertEqual(IsPalindrom("amadam"),false);
  AssertEqual(IsPalindrom("madama"),false);
  AssertEqual(IsPalindrom("alevel"),false);
  AssertEqual(IsPalindrom("levela"),false);
}

void TestEarlyStop(){
  AssertEqual(IsPalindrom("asitacaroracatisaw"),false);
  AssertEqual(IsPalindrom("wsitacaroracatisaw"),false);
  AssertEqual(IsPalindrom("waitacaroracatisaw"),false);
  AssertEqual(IsPalindrom("wastacaroracatisaw"),false);
  AssertEqual(IsPalindrom("wasiacaroracatisaw"),false);
  AssertEqual(IsPalindrom("wasitcaroracatisaw"),false);
  AssertEqual(IsPalindrom("wasitaaroracatisaw"),false);
  AssertEqual(IsPalindrom("wasitacroracatisaw"),false);
  AssertEqual(IsPalindrom("wasitacaoracatisaw"),false);
  AssertEqual(IsPalindrom("wasitacarracatisaw"),true);
  AssertEqual(IsPalindrom("wasitacaroacatisaw"),false);
  AssertEqual(IsPalindrom("wasitacarorcatisaw"),false);
  AssertEqual(IsPalindrom("wasitacaroraatisaw"),false);
  AssertEqual(IsPalindrom("wasitacaroractisaw"),false);
  AssertEqual(IsPalindrom("wasitacaroracaisaw"),false);
  AssertEqual(IsPalindrom("wasitacaroracatsaw"),false);
  AssertEqual(IsPalindrom("wasitacaroracatiaw"),false);
  AssertEqual(IsPalindrom("wasitacaroracatisw"),false);
  AssertEqual(IsPalindrom("wasitacaroracatisa"),false);
}

void TestIgnoreSpaces(){
  AssertEqual(IsPalindrom("w asitacaroracatisaw"),false);
  AssertEqual(IsPalindrom("w asitacaroracatisa w"),true);
  AssertEqual(IsPalindrom("w asitacaroracatisa  w"),false);
  AssertEqual(IsPalindrom("w asitacaroracatisa_ w"),false);
  AssertEqual(IsPalindrom("w __ asitacaroracatisa _ w"),false);
}

void TestCapitalLetter(){
  AssertEqual(IsPalindrom("ABBA"),true);
  AssertEqual(IsPalindrom("ABba"),false);
  AssertEqual(IsPalindrom("abBA"),false);
}

void TestDigits(){
  AssertEqual(IsPalindrom("1234567890987654321"),true);
  AssertEqual(IsPalindrom("12345678909870654321"),false);
  AssertEqual(IsPalindrom("ab12ba"),false);
  AssertEqual(IsPalindrom("77777"),true);
  AssertEqual(IsPalindrom("77778"),false);
}

int main() {
  TestRunner runner;
  runner.RunTest(TestEmptyString,"TestEmptyString");
  runner.RunTest(TestOneCharString,"TestOneCharString");
  runner.RunTest(TestRegularString,"TestRegularString");
  runner.RunTest(TestFirstAndLastChar,"TestFirstAndLastChar");
  runner.RunTest(TestEarlyStop,"TestEarlyStop");
  runner.RunTest(TestIgnoreSpaces,"TestIgnoreSpaces");
  runner.RunTest(TestCapitalLetter,"TestCapitalLetter");
  runner.RunTest(TestDigits,"TestDigits");
  return 0;
}
