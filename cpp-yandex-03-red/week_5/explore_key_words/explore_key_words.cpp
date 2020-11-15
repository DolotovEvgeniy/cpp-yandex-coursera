#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <vector>
#include <future>
#include <iostream>

using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
    for (const auto& [word, count] : other.word_frequences) {
      word_frequences[word] += count;
    }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
  Stats result;
  size_t start = line.find_first_not_of(' ');
  while (start < line.size()) {
    size_t end = line.find(' ', start);
    string word = line.substr(start, end - start);
    if (key_words.count(word) > 0) {
      result.word_frequences[word] += 1;
    }
    if (end == string::npos) {
      break;
    }
    start = end + 1;
  }
  return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  Stats result;

  size_t threadCount = thread::hardware_concurrency();

  vector<stringstream> streams;
  streams.resize(threadCount);
  size_t streamIdx = 0;
  for (string line; getline(input, line); ) {
    streams[streamIdx] << move(line) << "\n";
    streamIdx = (streamIdx + 1) % streams.size();
  }

  vector<future<Stats>> futures;
  for (auto& stream : streams) {
    futures.push_back(async(
        ExploreKeyWordsSingleThread, ref(key_words), ref(stream)
    ));
  }

  for (auto& future : futures) {
    result += future.get();
  }

  return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
