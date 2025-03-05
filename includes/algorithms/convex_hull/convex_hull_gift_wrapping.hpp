#ifndef CONVEX_HULL_GIFT_WRAPPING_HPP
#define CONVEX_HULL_GIFT_WRAPPING_HPP

#include "convex_hull/convex_hull_strategy.hpp"

namespace algorithms::convex_hull {
    /**
     * @brief A class to compute the convex hull of a set of points using the gift wrapping algorithm. The time of complexity of this approach is O(nh) where h is the number of vertices in the convex hull.
     * @tparam T The type of the coordinates of the points.
     */
    template <typename T>
    class ConvexHullGiftWrapping: public ConvexHullStrategy<T>
    {
    public:
        /**
         * @brief Compute convex hull of a set of points using the gift wrapping algorithm.
         * 
         * @param points Set of points.
         * @return std::vector<core::Point3D<T>> representing the Convex hull as set of vertices sorted in clockwise order.
         */
        std::vector<core::Point3D<T>> compute(std::vector<core::Point3D<T>>& points) override {
            auto start = utils::getIndexExtremeRightPoint(points);
            auto pivot = start;

            std::vector<core::Point3D<T>> hull;
            hull.reserve(points.size());

            do {
                hull.emplace_back(points[pivot]);
                auto current = (pivot + 1) % points.size();
                for (size_t next = (current + 1) % points.size(); next != current; next = (next + 1) % points.size()) {
                    if (utils::isCounterClockwiseOrientated(points[pivot], points[current], points[next])) {
                        current = next;
                    }
                }
                pivot = current;
            } while (pivot != start);
            return hull;
        }

        /**
         * @brief Destructor of the Convex Hull Gift Wrapping object
         */
        ~ConvexHullGiftWrapping() = default;
    };
}

#endif