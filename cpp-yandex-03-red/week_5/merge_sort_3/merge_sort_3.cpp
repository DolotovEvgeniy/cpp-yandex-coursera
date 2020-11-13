#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  size_t length = range_end - range_begin;
  if (length < 2) {
    return;
  }

  vector<typename RandomIt::value_type> elems(
    make_move_iterator(range_begin),
    make_move_iterator(range_end)
  );

  size_t batch_size = length / 3;
  for (size_t i = 0; i < 3; i++) {
    MergeSort(begin(elems) + i * batch_size, begin(elems) + (i + 1) * batch_size);
  }

  vector<typename RandomIt::value_type> tmpElems;
  merge(
    make_move_iterator(begin(elems)),  make_move_iterator(begin(elems) + batch_size),
    make_move_iterator(begin(elems)) + batch_size,  make_move_iterator(begin(elems) + 2 * batch_size),
    back_inserter(tmpElems)
  );
  merge(
    make_move_iterator(begin(tmpElems)),  make_move_iterator(end(tmpElems)),
    make_move_iterator(begin(elems)) + 2 * batch_size,  make_move_iterator(end(elems)),
    range_begin
  );
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
