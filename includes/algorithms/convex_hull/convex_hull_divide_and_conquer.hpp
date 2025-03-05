#ifndef CONVEX_HULL_DIVIDE_AND_CONQUER_HPP
#define CONVEX_HULL_DIVIDE_AND_CONQUER_HPP

#include <algorithm>
#include "utils/geometric_utils.hpp"
#include "convex_hull/convex_hull_strategy.hpp"

namespace algorithms::convex_hull {
    template <typename T>
    class ConvexHullDivideAndConquer: public ConvexHullStrategy<T>
    {
        
        std::vector<core::Point3D<T>> mergeHulls(std::vector<core::Point3D<T>>& leftHull, std::vector<core::Point3D<T>>& rightHull) {
            return std::vector<core::Point3D<T>>();
        }
        std::vector<core::Point3D<T>> computeDivideAndConquer(std::vector<core::Point3D<T>>& points, size_t start, size_t end) {
            if (end - start <= 3) {
                return points;
            }
            auto mid = start + (end - start) / 2;
            
            auto leftHull = computeDivideAndConquer(points, start, mid);
            auto rightHull = computeDivideAndConquer(points, mid, end);
            
        }
    public:
        std::vector<core::Point3D<T>> compute(std::vector<core::Point3D<T>>& points) override {
            std::sort(points.begin(), points.end());
            return std::vector<core::Point3D<T>>();
        }

        ~ConvexHullDivideAndConquer() = default;
    };
}

#endif