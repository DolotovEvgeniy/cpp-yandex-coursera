#include "stats.h"

using namespace std;

Stats::Stats() {
  // init method stats
  methodStats_["GET"] = 0;
  methodStats_["POST"] = 0;
  methodStats_["PUT"] = 0;
  methodStats_["DELETE"] = 0;
  methodStats_["UNKNOWN"] = 0;

  // init uri stats
  uriStats_["/"] = 0;
  uriStats_["/order"] = 0;
  uriStats_["/product"] = 0;
  uriStats_["/basket"] = 0;
  uriStats_["/help"] = 0;
  uriStats_["unknown"] = 0;
}

void Stats::AddMethod(string_view method) {
  if (methodStats_.count(method) > 0) {
    methodStats_[method]++;
  } else {
    methodStats_["UNKNOWN"]++;
  }
}

void Stats::AddUri(string_view uri) {
  if (uriStats_.count(uri) > 0) {
    uriStats_[uri]++;
  } else {
    uriStats_["unknown"]++;
  }
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return methodStats_;
}

const map<string_view, int>& Stats::GetUriStats() const {
  return uriStats_;
}

HttpRequest ParseRequest(string_view line) {
  HttpRequest request;

  size_t notSpace = line.find_first_not_of(' ');
  if (notSpace != 0) {
    line.remove_prefix(notSpace);
  }

  size_t space = line.find(' ');
  request.method = line.substr(0, space);
  line.remove_prefix(space + 1);

  space = line.find(' ');
  request.uri = line.substr(0, space);
  line.remove_prefix(space + 1);

  space = line.find(' ');
  request.protocol = line.substr(0, space);

  return request;
}
