#include <ctime>
#include <iostream>
#include <vector>
#include <optional>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <set>
#include <map>

using namespace std;

template <typename Number>
Number ReadNumberOnLine(istream& in_stream) {
  Number number;
  in_stream >> number;
  string dummy;
  getline(in_stream, dummy);
  return number;
}

pair<string_view, optional<string_view>> SplitTwoStrict(string_view s, string_view delimiter = " ") {
  const size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    return {s, nullopt};
  } else {
    return {s.substr(0, pos), s.substr(pos + delimiter.length())};
  }
}

pair<string_view, string_view> SplitTwo(string_view s, string_view delimiter = " ") {
  const auto [lhs, rhs_opt] = SplitTwoStrict(s, delimiter);
  return {lhs, rhs_opt.value_or("")};
}

string_view ReadToken(string_view& s, string_view delimiter = " ") {
  const auto [lhs, rhs] = SplitTwo(s, delimiter);
  s = rhs;
  return lhs;
}

int ConvertToInt(string_view str) {
  size_t pos;
  const int result = stoi(string(str), &pos);
  if (pos != str.length()) {
    stringstream error;
    error << "string " << str
          << " contains " << (str.length() - pos) << " trailing chars";
  }
  return result;
}

double ConvertToDouble(string_view str) {
  size_t pos;
  const double result = stod(string(str), &pos);
  if (pos != str.length()) {
    stringstream error;
    error << "string " << str
          << " contains " << (str.length() - pos) << " trailing chars";
  }
  return result;
}

struct Coords {
  static Coords FromString(string_view str) {
    Coords coords;
    coords.lat = ConvertToDouble(ReadToken(str, ", "));
    coords.lon = ConvertToDouble(ReadToken(str));
    return coords;
  }

  double lat;
  double lon;
};

double ToRadian(double degree) {
  return degree * 3.1415926535 / 180.0;
}

double GetLength(const Coords& lhs, const Coords& rhs) {
  static constexpr double EARTH_RADIUS = 6371000;

  double lhsLatRad = ToRadian(lhs.lat);
  double lhsLonRad = ToRadian(lhs.lon);
  double rhsLatRad = ToRadian(rhs.lat);
  double rhsLonRad = ToRadian(rhs.lon);

  return acos(sin(lhsLatRad) * sin(rhsLatRad) +
              cos(lhsLatRad) * cos(rhsLatRad) *
                  cos(abs(lhsLonRad - rhsLonRad))
         ) * EARTH_RADIUS;
}

struct Stop {
  string name;
  Coords coords;
};

double GetLength(const Stop& lhs, const Stop& rhs) {
  return GetLength(lhs.coords, rhs.coords);
}

struct Bus {
  string name;
  vector<string> stops;
};

size_t GetStopsNumber(const Bus& bus) {
  return bus.stops.size();
}

size_t GetUniqueStopsNumber(const Bus& bus) {
  set<string> names;
  for (const auto& stop : bus.stops) {
    names.insert(stop);
  }
  return names.size();
}

double GetRouteLength(const Bus& bus) {

}

struct StopPairHash {
  size_t operator()(const pair<string, string>& stopPair) const {
    static constexpr size_t x = 165'041;
    size_t r1 = shash(stopPair.first);
    size_t r2 = shash(stopPair.second);
    return r1 * x + r2;
  }
  hash<string> shash;
};

class TransportGuide {
public:
  void AddStop(const Stop& stop) {
    stopByName.emplace(stop.name, stop);
  }

  void AddBus(const Bus& bus) {
    busByName[bus.name] = bus;
    for (const auto& stop : bus.stops) {
      stopToBuses[stop].insert(bus.name);
    }
  }

  bool HasBus(const string& name) const {
    return busByName.count(name);
  }

  const Bus& GetBus(const string& name) const {
    return busByName.at(name);
  }

  bool HasStop(const string& name) const {
    return stopByName.count(name);
  }

  const Stop& GetStop(const string& name) const {
    return stopByName.at(name);
  }

  const set<string>& GetBusesByStop(const string& name) const {
    static const set<string> empty = {};
    auto it = stopToBuses.find(name);
    if (it != stopToBuses.end()) {
      return it->second;
    } else {
      return empty;
    }
  }

  void AddDistance(const string& stop1, const string& stop2, double distance) {
    distances[{stop1, stop2}] = distance;
  }

  double GetDistance(const string& stop1, const string& stop2) const {
    auto it1 = distances.find({stop1, stop2});
    if (it1 != distances.end()) {
      return it1->second;
    }
    auto it2 = distances.find({stop2, stop1});
    if (it2 != distances.end()) {
      return it2->second;
    }
    return GetGeoDistance(stop1, stop2);
  }

  double GetGeoDistance(const string& stop1, const string& stop2) const {
    return GetLength(GetStop(stop1), GetStop(stop2));
  }

private:
  unordered_map<string, Stop> stopByName;
  unordered_map<string, Bus> busByName;
  unordered_map<string, set<string>> stopToBuses;
  unordered_map<pair<string, string>, double, StopPairHash> distances;
};


struct UpdateRequest;
using UpdateRequestHolder = unique_ptr<UpdateRequest>;

struct UpdateRequest {
  enum class Type {
    STOP,
    BUS,
  };

  UpdateRequest(Type type) : type(type) {};
  static UpdateRequestHolder Create(Type type);
  virtual void ParseFrom(string_view input) = 0;
  virtual void Process(TransportGuide& guide) const = 0;
  virtual ~UpdateRequest() = default;

  const Type type;
};

optional<UpdateRequest::Type> ConvertUpdateRequestTypeFromString(string_view typeStr) {
  static const unordered_map<string_view, UpdateRequest::Type> STR_TO_TYPE = {
    {"Stop"sv, UpdateRequest::Type::STOP},
    {"Bus"sv, UpdateRequest::Type::BUS},
  };

  const auto it = STR_TO_TYPE.find(typeStr);
  if (it != STR_TO_TYPE.end()) {
    return it->second;
  } else {
    return nullopt;
  }
}

struct StopUpdateRequest : UpdateRequest {
  StopUpdateRequest() : UpdateRequest(Type::STOP) {}

  virtual void ParseFrom(string_view input) {
    stop.name = ReadToken(input, ": ");
    stop.coords.lat = ConvertToDouble(ReadToken(input, ", "));
    stop.coords.lon = ConvertToDouble(ReadToken(input, ", "));
    while (input.length() > 0) {
      string_view token = ReadToken(input, ", ");
      double distance = ConvertToDouble(ReadToken(token, "m to "));
      string name(token);
      distances[{stop.name, name}] = distance;
    }
  }

  virtual void Process(TransportGuide& guide) const {
    guide.AddStop(stop);
    for (const auto& [stops, distance] : distances) {
      const auto& [stop1, stop2] = stops;
      guide.AddDistance(stop1, stop2, distance);
    }
  }

  Stop stop;
  unordered_map<pair<string, string>, double, StopPairHash> distances;
};

struct BusUpdateRequest : UpdateRequest {
  BusUpdateRequest() : UpdateRequest(Type::BUS) {}

  virtual void ParseFrom(string_view input) {
    bus.name = ReadToken(input, ": ");
    string_view delimiter = input.find(" - ") != input.npos ? " - " : " > ";
    while (input.length() > 0) {
      string_view stop = ReadToken(input, delimiter);
      bus.stops.emplace_back(stop);
    }
    if (delimiter == " - ") {
      for (int i = bus.stops.size() - 2; i >= 0; i--) {
        bus.stops.push_back(bus.stops[i]);
      }
    }
  }

  virtual void Process(TransportGuide& guide) const {
    guide.AddBus(bus);
  }

  Bus bus;
};

UpdateRequestHolder UpdateRequest::Create(UpdateRequest::Type type) {
  switch (type) {
    case UpdateRequest::Type::STOP:
      return make_unique<StopUpdateRequest>();
    case UpdateRequest::Type::BUS:
      return make_unique<BusUpdateRequest>();
    default:
      return nullptr;
  }
}

UpdateRequestHolder ParseUpdateRequest(string_view requestStr) {
  const auto requestType = ConvertUpdateRequestTypeFromString(ReadToken(requestStr));
  if (!requestType) {
    return nullptr;
  }
  UpdateRequestHolder request = UpdateRequest::Create(*requestType);
  if (request) {
    request->ParseFrom(requestStr);
  }
  return request;
}

vector<UpdateRequestHolder> GetUpdateRequests(istream& in_stream = cin) {
  const size_t requestCount = ReadNumberOnLine<size_t>(in_stream);

  vector<UpdateRequestHolder> requests;
  requests.reserve(requestCount);

  for (size_t i = 0; i < requestCount; i++) {
    string requestStr;
    getline(in_stream, requestStr);
    if (auto request = ParseUpdateRequest(requestStr)) {
      requests.push_back(move(request));
    }
  }

  return requests;
}


struct ReadRequest;
using ReadRequestHolder = unique_ptr<ReadRequest>;

struct Response {
  virtual void Print(ostream& out_stream = cout) const = 0;
};

using ResponseHolder = unique_ptr<Response>;

struct ReadRequest {
  enum class Type {
    BUS,
    STOP,
  };

  ReadRequest(Type type) : type(type) {};
  static ReadRequestHolder Create(Type type);
  virtual void ParseFrom(string_view input) = 0;
  virtual ResponseHolder Process(const TransportGuide& guide) const = 0;
  virtual ~ReadRequest() = default;

  const Type type;
};

optional<ReadRequest::Type> ConvertReadRequestTypeFromString(string_view typeStr) {
  static const unordered_map<string_view, ReadRequest::Type> STR_TO_TYPE = {
    {"Bus"sv, ReadRequest::Type::BUS},
    {"Stop"sv, ReadRequest::Type::STOP},
  };

  const auto it = STR_TO_TYPE.find(typeStr);
  if (it != STR_TO_TYPE.end()) {
    return it->second;
  } else {
    return nullopt;
  }
}

struct BusResponse : Response {
  virtual void Print(ostream& out_stream = cout) const {
    out_stream << "Bus " << name << ": ";
    if (!exists) {
      out_stream << "not found";
      return;
    }
    out_stream << stopsCount << " stops on route, ";
    out_stream << uniqueStopsCount << " unique stops, ";
    out_stream << routeLength << " route length, ";
    out_stream << curvature << " curvature";
  }

  string name;
  bool exists;
  size_t stopsCount;
  size_t uniqueStopsCount;
  double routeLength;
  double curvature;
};

struct BusReadRequest : ReadRequest {
  BusReadRequest() : ReadRequest(Type::BUS) {}

  virtual void ParseFrom(string_view input) {
    name = input;
  }

  virtual ResponseHolder Process(const TransportGuide& guide) const {
    BusResponse response;
    response.name = name;
    if (guide.HasBus(name)) {
      const auto& bus = guide.GetBus(name);
      response.exists = true;
      response.stopsCount = GetStopsNumber(bus);
      response.uniqueStopsCount = GetUniqueStopsNumber(bus);

      const auto& stops = bus.stops;
      response.routeLength = 0.;
      double geoRouteLength = 0.;
      for (size_t i = 0; i < stops.size() - 1; i++) {
        response.routeLength += guide.GetDistance(stops[i], stops[i + 1]);
        geoRouteLength += guide.GetGeoDistance(stops[i], stops[i + 1]);
      }
      response.curvature = response.routeLength / geoRouteLength;
    } else {
      response.exists = false;
    }

    return make_unique<BusResponse>(response);
  }

  string name;
};


struct StopResponse : Response {
  virtual void Print(ostream& out_stream = cout) const {
    out_stream << "Stop " << name << ": ";
    if (!exists) {
      out_stream << "not found";
      return;
    }
    if (buses.empty()) {
      out_stream << "no buses";
      return;
    }
    out_stream << "buses";
    for (const auto& bus : buses) {
      out_stream << " " << bus;
    }
  }

  string name;
  bool exists;
  set<string> buses;
};

struct StopReadRequest : ReadRequest {
  StopReadRequest() : ReadRequest(Type::STOP) {}

  virtual void ParseFrom(string_view input) {
    name = input;
  }

  virtual ResponseHolder Process(const TransportGuide& guide) const {
    StopResponse response;
    response.name = name;
    if (guide.HasStop(name)) {
      response.exists = true;
      response.buses = guide.GetBusesByStop(name);
    } else {
      response.exists = false;
    }

    return make_unique<StopResponse>(response);
  }

  string name;
};

ReadRequestHolder ReadRequest::Create(ReadRequest::Type type) {
  switch (type) {
    case ReadRequest::Type::BUS:
      return make_unique<BusReadRequest>();
    case ReadRequest::Type::STOP:
      return make_unique<StopReadRequest>();
    default:
      return nullptr;
  }
}

ReadRequestHolder ParseReadRequest(string_view requestStr) {
  const auto requestType = ConvertReadRequestTypeFromString(ReadToken(requestStr));
  if (!requestType) {
    return nullptr;
  }
  ReadRequestHolder request = ReadRequest::Create(*requestType);
  if (request) {
    request->ParseFrom(requestStr);
  }
  return request;
}

vector<ReadRequestHolder> GetReadRequests(istream& in_stream = cin) {
  const size_t requestCount = ReadNumberOnLine<size_t>(in_stream);

  vector<ReadRequestHolder> requests;
  requests.reserve(requestCount);

  for (size_t i = 0; i < requestCount; i++) {
    string requestStr;
    getline(in_stream, requestStr);
    if (auto request = ParseReadRequest(requestStr)) {
      requests.push_back(move(request));
    }
  }

  return requests;
}

void ProcessUpdateRequests(
  TransportGuide& guide,
  const vector<UpdateRequestHolder>& requests)
{
  for (const auto& request : requests) {
    request->Process(guide);
  }
}

vector<ResponseHolder> ProcessReadRequests(
  const TransportGuide& guide,
  const vector<ReadRequestHolder>& requests)
{
  vector<ResponseHolder> responses;
  for (const auto& request : requests) {
    responses.push_back(request->Process(guide));
  }
  return responses;
}

void PrintResponses(const vector<ResponseHolder>& responses) {
  for (const auto& response : responses) {
    response->Print(cout);
    cout << endl;
  }
}

int main() {
  cout.precision(10);
  TransportGuide guide;
  ProcessUpdateRequests(guide, GetUpdateRequests());
  const auto responses = ProcessReadRequests(guide, GetReadRequests());
  PrintResponses(responses);
  return 0;
}
