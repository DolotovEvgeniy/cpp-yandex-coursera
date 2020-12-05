#pragma once

#include <iostream>

namespace RAII {

template <typename Provider>
class Booking {
public:
  Booking(Provider* provider, int id)
    : provider_(provider)
    , id_(id)
  {}

  Booking(const Booking&) = delete;
  Booking(Booking&& other) {
    id_ = other.id_;
    provider_ = other.provider_;

    other.provider_ = nullptr;
  }

  Booking& operator=(const Booking&) = delete;
  Booking& operator=(Booking&& other) {
    id_ = other.id_;
    provider_ = other.provider_;

    other.provider_ = nullptr;
    return *this;
  }

  ~Booking() {
    if (provider_ != nullptr) {
      provider_->CancelOrComplete(*this);
    }
  }

private:
  Provider* provider_;
  int id_;
};

}