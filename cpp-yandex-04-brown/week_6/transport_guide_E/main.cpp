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

#include "json.h"
#include "graph.h"
#include "router.h"

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


struct RoutingSettings {
  int busWaitTime;
  double busVelocity;

  static RoutingSettings ParseFrom(const Json::Document& doc) {
    const auto& valueByName = doc.GetRoot().AsMap().at("routing_settings").AsMap();
    RoutingSettings settings;
    settings.busWaitTime = valueByName.at("bus_wait_time").AsInt();
    settings.busVelocity = valueByName.at("bus_velocity").AsDouble();
    return settings;
  }
};


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

template <typename T>
struct PairHash {
  size_t operator()(const pair<T, T>& item) const {
    static constexpr size_t x = 165'041;
    size_t r1 = shash(item.first);
    size_t r2 = shash(item.second);
    return r1 * x + r2;
  }
  hash<T> shash;
};

struct RouteItem {
  enum class Type {
    WAIT,
    BUS,
  };

  virtual void PrintJson(ostream& out_stream = cout) const = 0;
  Type type;
};

using RouteItemHolder = shared_ptr<RouteItem>;

struct WaitRouteItem : RouteItem {
  virtual void PrintJson(ostream& out_stream = cout) const {
    out_stream << "      {\n";
    out_stream << "        \"type\": \"Wait\",\n";
    out_stream << "        \"stop_name\": \"" << stopName << "\",\n";
    out_stream << "        \"time\": " << time << "\n";
    out_stream << "      }";
  }

  string stopName;
  size_t time;
};

struct BusRouteItem : RouteItem {
  virtual void PrintJson(ostream& out_stream = cout) const {
    out_stream << "      {\n";
    out_stream << "        \"type\": \"Bus\",\n";
    out_stream << "        \"bus\": \"" << busName << "\",\n";
    out_stream << "        \"span_count\": " << spanCount << ",\n";
    out_stream << "        \"time\": " << time << "\n";
    out_stream << "      }";
  }

  string busName;
  size_t spanCount;
  double time ;
};

struct Route {
  double totalTime;
  vector<RouteItemHolder> items;
};

class TransportGuide {
public:
  TransportGuide(const RoutingSettings& settings)
    : settings(settings)
  {}

  void AddStop(const Stop& stop) {
    stopIndxByName[stop.name] = stops.size();
    stops.push_back(stop);
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
    return stopIndxByName.count(name);
  }

  const Stop& GetStop(const string& name) const {
    return stops[stopIndxByName.at(name)];
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

  void InitRouter() {
    roadGraph = make_unique<Graph::DirectedWeightedGraph<double>>(2 * stops.size());
    for (size_t i = 0; i < stops.size(); i++) {
      roadGraph->AddEdge(Graph::Edge<double>{
        .from = 2 * i,
        .to = 2 * i + 1,
        .weight = static_cast<double>(settings.busWaitTime)
      });
      WaitRouteItem item;
      item.stopName = stops[i].name;
      item.time = settings.busWaitTime;

      routeItems.push_back(make_shared<WaitRouteItem>(item));
    }

    for (const auto& [busName, bus] : busByName) {
      BusRouteItem item;
      item.busName = busName;
      const auto& stops = bus.stops;
      for (size_t i = 0; i < stops.size(); i++) {
        double time = 0.;
        size_t spanCount = 0;
        for (size_t j = i + 1; j < stops.size(); j++) {
          time += GetDistance(stops[j - 1], stops[j]) / (settings.busVelocity * 1000 / 60.);
          roadGraph->AddEdge(Graph::Edge<double>{
            .from = 2 * stopIndxByName.at(stops[i]) + 1,
            .to = 2 * stopIndxByName.at(stops[j]),
            .weight = time
          });

          item.time = time;
          item.spanCount = ++spanCount;

          routeItems.push_back(make_shared<BusRouteItem>(item));
        }
      }
    }

    router = make_unique<Graph::Router<double>>(*roadGraph);
  }

  optional<Route> GetRoute(const string& from, const string& to) const {
    size_t fromIndx = 2 * stopIndxByName.at(from);
    size_t toIndx = 2 * stopIndxByName.at(to);
    auto route = router->BuildRoute(fromIndx, toIndx);

    if (!route) {
      return nullopt;
    }

    std::vector<RouteItemHolder> items;
    auto id = route->id;
    for (size_t i = 0; i < route->edge_count; i++) {
      size_t edgeId = router->GetRouteEdge(id, i);
      items.push_back(routeItems[edgeId]);
    }

    return Route{
      .totalTime = route->weight,
      .items = move(items)
    };
  }

private:
  RoutingSettings settings;

  unordered_map<string, size_t> stopIndxByName;
  vector<Stop> stops;
  unordered_map<string, Bus> busByName;
  unordered_map<string, set<string>> stopToBuses;
  unordered_map<pair<string, string>, double, PairHash<string>> distances;

  std::unique_ptr<Graph::DirectedWeightedGraph<double>> roadGraph = nullptr;
  std::unique_ptr<Graph::Router<double>> router = nullptr;
  std::vector<RouteItemHolder> routeItems;
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
  virtual void ParseFrom(const Json::Node& node) = 0;
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

  virtual void ParseFrom(const Json::Node& node) {
    const auto& valueByName = node.AsMap();
    stop.name = valueByName.at("name").AsString();
    stop.coords.lat = valueByName.at("latitude").AsDouble();
    stop.coords.lon = valueByName.at("longitude").AsDouble();
    const auto& distanceByStop = valueByName.at("road_distances").AsMap();
    for (const auto& [name, distanceNode] : distanceByStop) {
      distances[{stop.name, name}] = distanceNode.AsDouble();
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
  unordered_map<pair<string, string>, double, PairHash<string>> distances;
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

  virtual void ParseFrom(const Json::Node& node) {
    const auto& valueByName = node.AsMap();
    bus.name = valueByName.at("name").AsString();
    const auto& stopNodes = valueByName.at("stops").AsArray();
    for (const auto& stopNode : stopNodes) {
      bus.stops.push_back(stopNode.AsString());
    }
    bool isRoundTrip = valueByName.at("is_roundtrip").AsBool();
    if (isRoundTrip) {
      return;
    }
    for (int i = bus.stops.size() - 2; i >= 0; i--) {
      bus.stops.push_back(bus.stops[i]);
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

UpdateRequestHolder ParseUpdateRequest(const Json::Node& requestNode) {
  const auto& valueByName = requestNode.AsMap();
  const auto requestType = ConvertUpdateRequestTypeFromString(requestNode.AsMap().at("type").AsString());
  if (!requestType) {
    return nullptr;
  }
  UpdateRequestHolder request = UpdateRequest::Create(*requestType);
  if (request) {
    request->ParseFrom(requestNode);
  }
  return request;
}

vector<UpdateRequestHolder> GetUpdateRequests(const Json::Document& doc) {
  const auto requestNodes = doc.GetRoot().AsMap().at("base_requests").AsArray();
  vector<UpdateRequestHolder> requests;
  requests.reserve(requestNodes.size());

  for (const auto& requestNode : requestNodes) {
    if (auto request = ParseUpdateRequest(requestNode)) {
      requests.push_back(move(request));
    }
  }

  return requests;
}


struct ReadRequest;
using ReadRequestHolder = unique_ptr<ReadRequest>;

struct Response {
  virtual void PrintJson(ostream& out_stream = cout) const = 0;

  size_t id;
};

using ResponseHolder = unique_ptr<Response>;

struct ReadRequest {
  enum class Type {
    BUS,
    STOP,
    ROUTE,
  };

  ReadRequest(Type type) : type(type) {};
  static ReadRequestHolder Create(Type type);
  virtual void ParseFrom(const Json::Node& node) = 0;
  virtual ResponseHolder Process(const TransportGuide& guide) const = 0;
  virtual ~ReadRequest() = default;

  const Type type;
  size_t id;
};

optional<ReadRequest::Type> ConvertReadRequestTypeFromString(string_view typeStr) {
  static const unordered_map<string_view, ReadRequest::Type> STR_TO_TYPE = {
    {"Bus"sv, ReadRequest::Type::BUS},
    {"Stop"sv, ReadRequest::Type::STOP},
    {"Route"sv, ReadRequest::Type::ROUTE},
  };

  const auto it = STR_TO_TYPE.find(typeStr);
  if (it != STR_TO_TYPE.end()) {
    return it->second;
  } else {
    return nullopt;
  }
}

struct BusResponse : Response {
  virtual void PrintJson(ostream& out_stream = cout) const {
    out_stream << "  {\n";
    out_stream << "    \"request_id\": " << id << ",\n";
    if (!exists) {
      out_stream << "    \"error_message\": \"not found\"\n";
    } else {
      out_stream << "    \"stop_count\": " << stopsCount << ",\n";
      out_stream << "    \"unique_stop_count\": " << uniqueStopsCount << ",\n";
      out_stream << "    \"route_length\": " <<routeLength << ",\n";
      out_stream << "    \"curvature\": " << curvature << "\n";
    }
    out_stream << "  }";
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

  virtual void ParseFrom(const Json::Node& node) {
    const auto& valueByName = node.AsMap();
    name = valueByName.at("name").AsString();
    id = valueByName.at("id").AsInt();
  }

  virtual ResponseHolder Process(const TransportGuide& guide) const {
    BusResponse response;
    response.id = id;
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
  virtual void PrintJson(ostream& out_stream = cout) const {
    out_stream << "  {\n";
    out_stream << "    \"request_id\": " << id << ",\n";
    if (!exists) {
      out_stream << "    \"error_message\": \"not found\"\n";
    } else {
      out_stream << "    \"buses\": [";
      for (auto it = buses.begin(); it != buses.end(); it++) {
        out_stream << "\n      \"" << *it << '"';
        if (prev(buses.end()) != it) {
          out_stream << ",";
        } else {
          out_stream << "\n    ";
        }
      }
      out_stream << "]\n";
    }
    out_stream << "  }";
  }


  string name;
  bool exists;
  set<string> buses;
};

struct StopReadRequest : ReadRequest {
  StopReadRequest() : ReadRequest(Type::STOP) {}

  virtual void ParseFrom(const Json::Node& node) {
    const auto& valueByName = node.AsMap();
    name = valueByName.at("name").AsString();
    id = valueByName.at("id").AsInt();
  }

  virtual ResponseHolder Process(const TransportGuide& guide) const {
    StopResponse response;
    response.id = id;
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

struct RouteResponse : Response {
  virtual void PrintJson(ostream& out_stream = cout) const {
    out_stream << "  {\n";
    out_stream << "    \"request_id\": " << id << ",\n";
    if (!route) {
      out_stream << "    \"error_message\": \"not found\"\n";
    } else {
      out_stream << "    \"total_time\": " << route->totalTime << ",\n";
      out_stream << "    \"items\": [";
      for (size_t i = 0; i < route->items.size(); i++) {
        out_stream << "\n";
        route->items[i]->PrintJson(out_stream);
        if (route->items.size() != i + 1) {
          out_stream << ",";
        } else {
          out_stream << "\n    ";
        }
      }
      out_stream << "]\n";
    }
    out_stream << "  }";
  }

  size_t id;
  optional<Route> route;
};

struct RouteReadRequest : ReadRequest {
  RouteReadRequest() : ReadRequest(Type::ROUTE) {}

  virtual void ParseFrom(const Json::Node& node) {
    const auto& valueByName = node.AsMap();
    from = valueByName.at("from").AsString();
    to = valueByName.at("to").AsString();
    id = valueByName.at("id").AsInt();
  }

  virtual ResponseHolder Process(const TransportGuide& guide) const {
    RouteResponse response;
    response.id = id;
    response.route = guide.GetRoute(from, to);
    return make_unique<RouteResponse>(move(response));
  }

  string from;
  string to;
};


ReadRequestHolder ReadRequest::Create(ReadRequest::Type type) {
  switch (type) {
    case ReadRequest::Type::BUS:
      return make_unique<BusReadRequest>();
    case ReadRequest::Type::STOP:
      return make_unique<StopReadRequest>();
    case ReadRequest::Type::ROUTE:
      return make_unique<RouteReadRequest>();
    default:
      return nullptr;
  }
}

ReadRequestHolder ParseReadRequest(const Json::Node& requestNode) {
  const auto requestType = ConvertReadRequestTypeFromString(requestNode.AsMap().at("type").AsString());
  if (!requestType) {
    return nullptr;
  }
  ReadRequestHolder request = ReadRequest::Create(*requestType);
  if (request) {
    request->ParseFrom(requestNode);
  }
  return request;
}

vector<ReadRequestHolder> GetReadRequests(const Json::Document& doc) {
  const auto requestNodes = doc.GetRoot().AsMap().at("stat_requests").AsArray();

  vector<ReadRequestHolder> requests;
  requests.reserve(requestNodes.size());

  for (const auto& requestNode : requestNodes) {
    if (auto request = ParseReadRequest(requestNode)) {
      requests.push_back(move(request));
    }
  }

  return requests;
}

TransportGuide ProcessUpdateRequests(
  const RoutingSettings& settings,
  const vector<UpdateRequestHolder>& requests)
{
  TransportGuide guide(settings);
  for (const auto& request : requests) {
    request->Process(guide);
  }
  guide.InitRouter();
  return guide;
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

void PrintResponses(
  const vector<ResponseHolder>& responses,
  ostream& out_stream = cout)
{
  out_stream << "[\n";
  for (size_t i = 0; i < responses.size(); i++) {
    responses[i]->PrintJson(out_stream);
    if (responses.size() != i + 1) {
      cout << ",";
    }
    cout << "\n";
  }
  out_stream << "]\n";
}

int main() {
  cout.precision(10);

  Json::Document doc = Json::Load(cin);

  const auto settings = RoutingSettings::ParseFrom(doc);
  const auto updateRequests = GetUpdateRequests(doc);
  TransportGuide guide = ProcessUpdateRequests(settings, updateRequests);

  const auto readRequests = GetReadRequests(doc);
  const auto responses = ProcessReadRequests(guide, readRequests);

  PrintResponses(responses);

  return 0;
}
