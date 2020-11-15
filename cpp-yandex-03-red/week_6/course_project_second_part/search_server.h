#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <deque>
#include <mutex>
#include <future>

using namespace std;

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T())
        : value(move(initial))
    {
    }

    struct Access {
        T& ref_to_value;
        lock_guard<mutex> lock;
    };

    Access GetAccess() {
        return {value, lock_guard(m)};
    }

private:
    T value;
    mutex m;
};

class InvertedIndex {
public:
    InvertedIndex() = default;
    explicit InvertedIndex(istream& document_input);

    const vector<pair<size_t, size_t>>& Lookup(const string_view& word) const;

    const string& GetDocument(size_t id) const {
        return docs[id];
    }

    size_t DocumentNumbers() const {
        return docs.size();
    }

private:
    unordered_map<string_view, vector<pair<size_t, size_t>>> index;
    deque<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  void UpdateDocumentBaseSingleThread(istream& document_input);
  void AddQueriesStreamSingleThread(istream& query_input, ostream& search_results_output);

  Synchronized<InvertedIndex> indexHandle;
  vector<future<void>> tasks;
};
