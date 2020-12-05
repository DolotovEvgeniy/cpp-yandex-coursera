#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
  T* ptr_;

public:
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator = (const UniquePtr&) = delete;

  UniquePtr(): ptr_(nullptr) {}
  UniquePtr(nullptr_t) : ptr_(nullptr) {}
  UniquePtr(T * ptr) : ptr_(ptr) {}
  UniquePtr(UniquePtr&& other): ptr_(other.Release()) {}

  T& operator * () const { return *ptr_; }
  T * operator -> () const { return ptr_; }

  T * Get() const { return ptr_; }

  ~UniquePtr() { Reset(); }

  UniquePtr& operator = (nullptr_t) {
    Reset();
    return *this;
  }

  UniquePtr& operator = (UniquePtr&& other) {
    Reset();
    ptr_ = other.Release();
    return *this;
  }

  T* Release() {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  }

  void Reset(nullptr_t = nullptr) {
    if (ptr_ != nullptr) {
      delete ptr_;
    }
    ptr_ = nullptr;
  }

  void Reset(T * ptr) {
    if (ptr_ != nullptr) {
      delete ptr_;
    }
    ptr_ = ptr;
  }

  void Swap(UniquePtr& other) {
    swap(ptr_, other.ptr_);
  }
};


struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
  }
};

int Item::counter = 0;


void TestLifetime() {
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);

  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    delete rawPtr;
    ASSERT_EQUAL(Item::counter, 0);
  }
  ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
  UniquePtr<Item> ptr(new Item(42));
  ASSERT_EQUAL(ptr.Get()->value, 42);
  ASSERT_EQUAL((*ptr).value, 42);
  ASSERT_EQUAL(ptr->value, 42);
}

int main() {
  TestRunner tr;

  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);

  return 0;
}
