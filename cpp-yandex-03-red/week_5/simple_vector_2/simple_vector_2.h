#include <cstdint>
#include <algorithm>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;

  explicit SimpleVector(size_t size)
    : data(new T[size])
    , size(size)
    , capacity(size)
  {}

  ~SimpleVector() {
    delete[] data;
  }

  T& operator[](size_t index) {
    return data[index];
  }

  T* begin() {
    return data;
  }

  T* end() {
    return data + size;
  }

  size_t Size() const {
    return size;
  }

  size_t Capacity() const {
    return capacity;
  }

  void PushBack(T value) {
    if (size == capacity) {
      size_t newCapacity = (capacity == 0) ? 1 : 2 * capacity;
      T* newData = new T[newCapacity];
      move(begin(), end(), newData);
      delete[] data;
      data = newData;
      capacity = newCapacity;
    }
    data[size++] = move(value);
  }

private:
  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};
