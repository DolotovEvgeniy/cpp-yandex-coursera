#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string_view> SplitIntoWords(string_view line) {
  vector<string_view> result;
  while (line.size() > 0) {
    size_t start = line.find_first_not_of(' ');
    if (start >= line.size()) {
      break;
    }
    size_t end = line.find(' ', start);
    result.push_back(line.substr(start, end - start));
    if (end >= line.size()) {
      break;
    }
    line.remove_prefix(end);
  }
  return result;
}

SearchServer::SearchServer(istream& document_input)
  : indexHandle(InvertedIndex(document_input))
{}

void SearchServer::UpdateDocumentBaseSingleThread(istream& document_input) {
  InvertedIndex new_index(document_input);
  swap(indexHandle.GetAccess().ref_to_value, new_index);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  tasks.push_back(async(launch::async, [&]() {
    return UpdateDocumentBaseSingleThread(document_input);
  }));
}

void SearchServer::AddQueriesStreamSingleThread(
  istream& query_input, ostream& search_results_output
) {
  vector<pair<size_t, size_t>> search_results;
  for (string current_query; getline(query_input, current_query); ) {
    {
      auto access = indexHandle.GetAccess();
      auto& index = access.ref_to_value;

      search_results.assign(index.DocumentNumbers(), { 0, 0 });

      for (const auto& word : SplitIntoWords(current_query)) {
        for (const auto& [docid, hitcount] : index.Lookup(word)) {
          search_results[docid].first = docid;
          search_results[docid].second += hitcount;
        }
      }
    }

    partial_sort(
      begin(search_results),
      search_results.size() < 5
        ? end(search_results)
        : begin(search_results) + 5,
      end(search_results),
      [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
        int64_t lhs_docid = lhs.first;
        auto lhs_hit_count = lhs.second;
        int64_t rhs_docid = rhs.first;
        auto rhs_hit_count = rhs.second;
        return make_pair(lhs_hit_count, -lhs_docid)
             > make_pair(rhs_hit_count, -rhs_docid);
      }
    );

    search_results_output << current_query << ':';
    for (auto[docid, hitcount] : Head(search_results, 5)) {
      if (hitcount == 0) {
        break;
      }
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }
    search_results_output << endl;
  }
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  tasks.push_back(async(launch::async, [&]() {
    return AddQueriesStreamSingleThread(query_input, search_results_output);
  }));
}

InvertedIndex::InvertedIndex(istream& document_input) {
  for (string current_document; getline(document_input, current_document); ) {
    docs.push_back(move(current_document));
    size_t docid = docs.size() - 1;
    for (const string_view& word : SplitIntoWords(docs.back())) {
      auto& index_word = index[word];
      if (!index_word.empty() && index_word.back().first == docid) {
        index_word.back().second++;
      } else {
        index_word.push_back({docid, 1});
      }
    }
  }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string_view& word) const {
  static const vector<pair<size_t, size_t>> empty;
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return empty;
  }
}
