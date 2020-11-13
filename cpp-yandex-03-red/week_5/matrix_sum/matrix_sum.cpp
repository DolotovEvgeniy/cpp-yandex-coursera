#include "test_runner.h"
#include <vector>
#include <thread>
#include <future>
#include <numeric>

using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  // Реализуйте эту функцию
  size_t threadCount = thread::hardware_concurrency();
  size_t batchSize = matrix.size() / threadCount;
  if (batchSize == 0) {
    batchSize = matrix.size();
  }

  vector<future<int64_t>> futures;
  for (size_t i = 0; i < matrix.size(); i += batchSize) {
    futures.push_back(std::async(std::launch::async,
      [i, batchSize, &matrix] {
        int64_t sum = 0;
        for (size_t j = i; j < min(i + batchSize, matrix.size()); j++) {
          sum += accumulate(matrix[j].begin(), matrix[j].end(), 0);
        }
        return sum;
      }
    ));
  }

  int64_t sum = 0;
  for (auto& future : futures) {
    sum += future.get();
  }

  return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
