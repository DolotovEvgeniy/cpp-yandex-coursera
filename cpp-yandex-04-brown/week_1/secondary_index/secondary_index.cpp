#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};

// Реализуйте этот класс
class Database {
public:
  bool Put(const Record& record) {
    auto [it, inserted] = data_.insert(
      {record.id, Item{record, {}, {}, {}}}
    );

    if (!inserted) {
      return false;
    }

    auto& item = it->second;
    const auto& recordRef = item.record;
    item.timestampIt = timestampIndex_.insert({record.timestamp, recordRef});
    item.karmaIt = karmaIndex_.insert({record.karma, recordRef});
    item.userIt = userIndex_.insert({record.user, recordRef});
    return true;
  }

  const Record* GetById(const string& id) const {
    auto it = data_.find(id);
    if (it == data_.end()) {
      return nullptr;
    }
    return &it->second.record;
  }

  bool Erase(const string& id) {
    auto it = data_.find(id);
    if (it == data_.end()) {
      return false;
    }
    const auto& item = it->second;
    timestampIndex_.erase(item.timestampIt);
    karmaIndex_.erase(item.karmaIt);
    userIndex_.erase(item.userIt);
    data_.erase(it);
    return true;
  }

  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const {
    auto begin = timestampIndex_.lower_bound(low);
    auto end = timestampIndex_.upper_bound(high);
    for (auto it = begin; it != end; it++) {
      if (!callback(it->second)) {
        break;
      }
    }
  }

  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const {
    auto begin = karmaIndex_.lower_bound(low);
    auto end = karmaIndex_.upper_bound(high);
    for (auto it = begin; it != end; it++) {
      if (!callback(it->second)) {
        break;
      }
    }
  }

  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const {
    auto [begin, end] = userIndex_.equal_range(user);
    for (auto it = begin; it != end; it++) {
      if (!callback(it->second)) {
        break;
      }
    }
  }

private:
  template <typename Type>
  using Index = multimap<Type, const Record&>;

  struct Item {
    Record record;
    Index<int>::iterator timestampIt;
    Index<int>::iterator karmaIt;
    Index<string>::iterator userIt;
  };

  map<string, Item> data_;
  Index<int> timestampIndex_;
  Index<int> karmaIndex_;
  Index<string> userIndex_;
};

void TestRangeBoundaries() {
  const int good_karma = 1000;
  const int bad_karma = -10;

  Database db;
  db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
  db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

  int count = 0;
  db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestSameUser() {
  Database db;
  db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
  db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

  int count = 0;
  db.AllByUser("master", [&count](const Record&) {
    ++count;
    return true;
  });

  ASSERT_EQUAL(2, count);
}

void TestReplacement() {
  const string final_body = "Feeling sad";

  Database db;
  db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
  db.Erase("id");
  db.Put({"id", final_body, "not-master", 1536107260, -10});

  auto record = db.GetById("id");
  ASSERT(record != nullptr);
  ASSERT_EQUAL(final_body, record->title);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestRangeBoundaries);
  RUN_TEST(tr, TestSameUser);
  RUN_TEST(tr, TestReplacement);
  return 0;
}
