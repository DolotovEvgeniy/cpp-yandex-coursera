#pragma once

#include "sphere.h"
#include "svg.h"
#include "utils.h"
#include <algorithm>
#include <cmath>
#include <optional>


namespace Sphere {

  class Projector {
  public:
    template <typename PointInputIt>
    Projector(PointInputIt points_begin, PointInputIt points_end,
              double max_width, double max_height, double padding);

    Svg::Point operator()(Point point) const;

  private:
    double min_lon_ = 0;
    double max_lat_ = 0;
    const double padding_;
    double zoom_coef_ = 0;
  };


  template <typename PointInputIt>
  Projector::Projector(PointInputIt points_begin, PointInputIt points_end,
                       double max_width, double max_height, double padding)
      : padding_(padding)
  {
    if (points_begin == points_end) {
      return;
    }

    const auto [left_it, right_it] =
        std::minmax_element(points_begin, points_end,
                            [](Point lhs, Point rhs) {
                              return lhs.longitude < rhs.longitude;
                            });
    min_lon_ = left_it->longitude;
    const double max_lon = right_it->longitude;

    const auto [bottom_it, top_it] =
        std::minmax_element(points_begin, points_end,
                            [](Point lhs, Point rhs) {
                              return lhs.latitude < rhs.latitude;
                            });
    const double min_lat = bottom_it->latitude;
    max_lat_ = top_it->latitude;

    std::optional<double> width_zoom_coef;
    if (!IsZero(max_lon - min_lon_)) {
      width_zoom_coef = (max_width - 2 * padding) / (max_lon - min_lon_);
    }

    std::optional<double> height_zoom_coef;
    if (!IsZero(max_lat_ - min_lat)) {
      height_zoom_coef = (max_height - 2 * padding) / (max_lat_ - min_lat);
    }

    if (width_zoom_coef && height_zoom_coef) {
      zoom_coef_ = std::min(*width_zoom_coef, *height_zoom_coef);
    } else if (width_zoom_coef) {
      zoom_coef_ = *width_zoom_coef;
    } else if (height_zoom_coef) {
      zoom_coef_ = *height_zoom_coef;
    }
  }

}
