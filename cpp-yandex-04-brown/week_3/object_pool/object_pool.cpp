#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    T* object;
    if (pool_.empty()) {
      object = new T();
    } else {
      object = pool_.front();
      pool_.pop();
    }

    objects_.insert(object);
    return object;
  }

  T* TryAllocate() {
    if (pool_.empty()) {
      return nullptr;
    }
    T* object = pool_.front();
    pool_.pop();
    objects_.insert(object);
    return object;
  }

  void Deallocate(T* object) {
    auto it = objects_.find(object);
    if (it == objects_.end()) {
      throw invalid_argument("failed");
    }
    objects_.erase(it);
    pool_.push(object);
  }

  ~ObjectPool() {
    for (auto& object : objects_) {
      if (object != nullptr) {
        delete object;
      }
    }
    while (!pool_.empty()) {
      T* object = pool_.front();
      pool_.pop();
      if (object != nullptr) {
        delete object;
      }
    }
  }

private:
  set<T*> objects_;
  queue<T*> pool_;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
