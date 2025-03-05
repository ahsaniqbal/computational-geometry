#ifndef CONVEX_HULL_STRATEGY_HPP
#define CONVEX_HULL_STRATEGY_HPP

#include <vector>
#include "core/point.hpp"
#include "utils/geometric_utils.hpp"

namespace algorithms::convex_hull {
    template <typename T>
    class ConvexHullStrategy {
    public:
        virtual ~ConvexHullStrategy() = default;
        virtual std::vector<core::Point3D<T>> compute(std::vector<core::Point3D<T>>& points) = 0;
    };
}
#endif