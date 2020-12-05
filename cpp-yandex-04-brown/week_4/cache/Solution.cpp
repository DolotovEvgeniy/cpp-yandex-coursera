#include "Common.h"

#include <map>
#include <mutex>
#include <iostream>

using namespace std;

class LruCache : public ICache {
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings)
    : books_unpacker_(books_unpacker)
    , settings_(settings)
    , size_(0u)
  {}

  BookPtr GetBook(const string& book_name) override {
    std::lock_guard lock(m);

    for (const auto& [rank, ptr] : cache_) {
      if (ptr->GetName() == book_name) {
        if (rank != cache_.rbegin()->first) {
          int newRank = cache_.rbegin()->first + 1;
          auto nh = cache_.extract(rank);
          nh.key() = newRank;
          cache_.insert(std::move(nh));
        }
        return ptr;
      }
    }

    BookPtr ptr = std::move(books_unpacker_->UnpackBook(book_name));
    size_t bookSize = ptr->GetContent().size();

    if (bookSize > settings_.max_memory) {
      return ptr;
    }

    while (size_ + bookSize > settings_.max_memory) {
      size_ -= cache_.begin()->second->GetContent().size();
      cache_.erase(cache_.begin());
    }

    int rank = 0;
    if (!cache_.empty()) {
      rank = cache_.rbegin()->first + 1;
    }

    cache_.emplace(rank, ptr);
    size_ += bookSize;

    return ptr;
  }

private:
  shared_ptr<IBooksUnpacker> books_unpacker_;
  Settings settings_;
  std::mutex m;
  std::map<int, BookPtr> cache_;
  size_t size_;
};

unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings)
{
  return make_unique<LruCache>(books_unpacker, settings);
}
