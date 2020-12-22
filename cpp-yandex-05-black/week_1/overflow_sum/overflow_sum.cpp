#include <iostream>
#include <sstream>

using namespace std;

string OverflowSum(int64_t a, int64_t b) {
  bool is_sum_overflowed = false;
  if (a > 0 && b > 0){
    int64_t temp = INT64_MAX - a - b;
    is_sum_overflowed = temp < 0;
  } else if (a < 0 && b < 0){
    int64_t temp = INT64_MIN - a - b;
    is_sum_overflowed = temp > 0;
  }

  stringstream ss;
  if (is_sum_overflowed) {
    ss << "Overflow!";
  } else{
    ss << a + b;
  }

  return ss.str();
}

int main() {
  int64_t a, b;
  cin >> a >> b;
  cout << OverflowSum(a, b) << endl;

  return 0;
}