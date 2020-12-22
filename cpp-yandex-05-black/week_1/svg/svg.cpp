#include <iostream>
#include <sstream>
#include <optional>
#include <variant>
#include <vector>

namespace Svg {

struct Rgb {
  int red;
  int green;
  int blue;
};

class Color {
public:
  Color() = default;
  Color(const char* color) : value_(color) {}
  Color(const std::string& color) : value_(color) {}
  Color(const Rgb& color) {
    std::stringstream ss;
    ss << "rgb(" << color.red << "," << color.green << "," << color.blue << ")";
    value_ = ss.str();
  }

private:
  std::string value_ = "none";

  friend std::ostream& operator<<(std::ostream& os, const Color& color);
};

static const Color NoneColor("none");

std::ostream& operator<<(std::ostream& os, const Color& color) {
  os << '"' << color.value_ << '"';
  return os;
}


struct Point {
  double x;
  double y;
};

template <typename ObjectImpl>
class BaseObject {
public:
  ObjectImpl& SetFillColor(const Color& color) {
    fillColor_ = color;
    return *static_cast<ObjectImpl*>(this);
  }

  ObjectImpl& SetStrokeColor(const Color& color) {
    strokeColor_ = color;
    return *static_cast<ObjectImpl*>(this);
  }

  ObjectImpl& SetStrokeWidth(double width) {
    strokeWidth_ = width;
    return *static_cast<ObjectImpl*>(this);
  }

  ObjectImpl& SetStrokeLineCap(const std::string& lineCap) {
    strokeLineCap_ = lineCap;
    return *static_cast<ObjectImpl*>(this);
  }

  ObjectImpl& SetStrokeLineJoin(const std::string& lineJoin) {
    strokeLineJoin_ = lineJoin;
    return *static_cast<ObjectImpl*>(this);
  }

protected:
  void PrintBaseParams(std::ostream& out_stream) const {
    out_stream << "fill=" << fillColor_ << " ";
    out_stream << "stroke=" << strokeColor_ << " ";
    out_stream << "stroke-width=\"" << strokeWidth_ << "\"";
    if (strokeLineCap_) {
      out_stream << " stroke-linecap=\"" << *strokeLineCap_ << "\"";
    }
    if (strokeLineJoin_) {
      out_stream << " stroke-linejoin=\"" << *strokeLineJoin_ << "\"";
    }
  }

private:
  Color fillColor_ = NoneColor;
  Color strokeColor_ = NoneColor;
  double strokeWidth_ = 1.0;
  std::optional<std::string> strokeLineCap_ = std::nullopt;
  std::optional<std::string> strokeLineJoin_ = std::nullopt;
};

class Circle : public BaseObject<Circle> {
public:
  Circle() = default;

  Circle& SetCenter(Point center) {
    center_ = center;
    return *this;
  }

  Circle& SetRadius(double radius) {
    radius_ = radius;
    return *this;
  }

  void Render(std::ostream& out_stream) const {
    out_stream << "<circle ";
    out_stream << "cx=\"" << center_.x << "\" cy=\"" << center_.y << "\" ";
    out_stream << "r=\"" << radius_ << "\" ";
    PrintBaseParams(out_stream);
    out_stream << " />";
  }

private:
  double radius_ = 1.0;
  Point center_ = Point{0., 0.};
};

class Polyline : public BaseObject<Polyline> {
public:
  Polyline() = default;

  Polyline& AddPoint(Point point) {
    points_.push_back(point);
    return *this;
  }

  void Render(std::ostream& out_stream) const {
    out_stream << "<polyline ";
    out_stream << "points=\"";
    for (const auto& point : points_) {
      out_stream << point.x << "," << point.y << " ";
    }
    out_stream << "\" ";
    PrintBaseParams(out_stream);
    out_stream << " />";
  }

private:
  std::vector<Point> points_;
};

class Text : public BaseObject<Text> {
public:
  Text() = default;

  Text& SetPoint(Point coords) {
    coords_ = coords;
    return *this;
  }

  Text& SetOffset(Point offset) {
    offset_ = offset;
    return *this;
  }

  Text& SetFontSize(uint32_t fontSize) {
    fontSize_ = fontSize;
    return *this;
  }

  Text& SetFontFamily(const std::string& fontFamily) {
    fontFamily_ = fontFamily;
    return *this;
  }

  Text& SetData(const std::string& data) {
    data_ = data;
    return *this;
  }

  void Render(std::ostream& out_stream) const {
    out_stream << "<text ";
    out_stream << "x=\"" << coords_.x << "\" y=\"" << coords_.y << "\" ";
    out_stream << "dx=\"" << offset_.x << "\" dy=\"" << offset_.y << "\" ";
    out_stream << "font-size=\"" << fontSize_ << "\" ";
    if (fontFamily_) {
      out_stream << "font-family=\"" << *fontFamily_ << "\" ";
    }
    PrintBaseParams(out_stream);
    out_stream << ">" << data_ << "</text>";
  }

private:
  Point coords_ = Point{0., 0.};
  Point offset_ = Point{0., 0.};
  uint32_t fontSize_ = 1;
  std::optional<std::string> fontFamily_;
  std::string data_ = "";
};

using Object = std::variant<Circle, Polyline, Text>;

class Document {
public:

  void Add(const Object& object) {
    objects_.push_back(object);
  }

  void Render(std::ostream& out_stream) {
    out_stream << R"(<?xml version="1.0" encoding="UTF-8" ?>)";
    out_stream << R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)";
    for (const auto& object : objects_) {
      if (std::holds_alternative<Circle>(object)) {
        std::get<Circle>(object).Render(out_stream);
      } else if (std::holds_alternative<Polyline>(object)) {
        std::get<Polyline>(object).Render(out_stream);
      } else if (std::holds_alternative<Text>(object)) {
        std::get<Text>(object).Render(out_stream);
      } else {
        throw std::runtime_error("unknown object type");
      }
     // out_stream << "\n";
    }
    out_stream << "</svg>\n";
  }

private:
  std::vector<Object> objects_;
};

} // namespace Svg

int main() {
  Svg::Document svg;

  svg.Add(
    Svg::Polyline{}
    .SetStrokeColor(Svg::Rgb{140, 198, 63})  // soft green
    .SetStrokeWidth(16)
    .SetStrokeLineCap("round")
    .AddPoint({50, 50})
    .AddPoint({250, 250})
  );

  for (const auto point : {Svg::Point{50, 50}, Svg::Point{250, 250}}) {
    svg.Add(
      Svg::Circle{}
      .SetFillColor("white")
      .SetRadius(6)
      .SetCenter(point)
    );
  }

  svg.Add(
    Svg::Text{}
    .SetPoint({50, 50})
    .SetOffset({10, -10})
    .SetFontSize(20)
    .SetFontFamily("Verdana")
    .SetFillColor("black")
    .SetData("C")
  );
  svg.Add(
    Svg::Text{}
    .SetPoint({250, 250})
    .SetOffset({10, -10})
    .SetFontSize(20)
    .SetFontFamily("Verdana")
    .SetFillColor("black")
    .SetData("C++")
  );

  svg.Render(std::cout);

  return 0;
}
