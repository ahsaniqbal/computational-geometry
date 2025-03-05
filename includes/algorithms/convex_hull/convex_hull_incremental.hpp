#ifndef CONVEX_HULL_INCREMENTAL_HPP
#define CONVEX_HULL_INCREMENTAL_HPP

#include <algorithm>
#include "convex_hull/convex_hull_strategy.hpp"
namespace algorithms::convex_hull
{
    /**
     * @brief A class to compute the convex hull of a set of points using the incremental approach. The time of complexity of this approach is O(n log n).
     * @tparam T The type of the coordinates of the points.
     */
    template <typename T>
    class ConvexHullIncremental: public ConvexHullStrategy<T>
    {
        /**
         * @brief Method to build the upper hull of the convex hull.
         * @param points The list of points.
         * @return The list of points that form the upper hull sorted clockwise.
         */
        std::vector<core::Point3D<T>> buildUpperHull(const std::vector<core::Point3D<T>>& points) {
            auto upperHull = std::vector<core::Point3D<T>>();
            upperHull.reserve(points.size());

            upperHull.push_back(points[0]);
            upperHull.push_back(points[1]);

            for (size_t i = 2; i < points.size(); i++) {
                upperHull.emplace_back(points[i]);
                while(upperHull.size() > 2) {
                    auto it = upperHull.end();

                    auto itPointRight = --it;
                    auto itPointMid = --it;
                    auto itPointLeft = --it;

                    if (!utils::isClockwiseOrientated(*itPointLeft, *itPointMid, *itPointRight)) {
                        upperHull.erase(itPointMid);
                    }
                    else {
                        break;
                    }
                }
            }
            return upperHull;
        }

        /**
         * @brief Method to build the lower hull of the convex hull.
         * @param points The list of points.
         * @return The list of points that form the lower hull sorted clockwise.
         */
        std::vector<core::Point3D<T>> buildLowerHull(const std::vector<core::Point3D<T>>& points) {
            auto lowerHull = std::vector<core::Point3D<T>>();
            lowerHull.reserve(points.size());

            lowerHull.push_back(points[points.size() - 1]);
            lowerHull.push_back(points[points.size() - 2]);

            for (int i = points.size() - 3; i >= 0; i--) {
                lowerHull.emplace_back(points[i]);
                while(lowerHull.size() > 2) {
                    auto it = lowerHull.end();

                    auto itPointLeft = --it;
                    auto itPointMid = --it;
                    auto itPointRight = --it;

                    if (!utils::isClockwiseOrientated(*itPointRight, *itPointMid, *itPointLeft)) {
                        lowerHull.erase(itPointMid);
                    }
                    else {
                        break;
                    }
                }
            }
            return lowerHull;
        }

    public:
        /**
         * @brief Method to compute the convex hull of a set of points using the incremental approach.
         * @param points The list of points.
         * @return The list of points that form the convex hull.
         */
        std::vector<core::Point3D<T>> compute(std::vector<core::Point3D<T>>& points) override {
            std::sort(points.begin(), points.end());

            auto upperHull = buildUpperHull(points);
            auto lowerHull = buildLowerHull(points);

            auto result = std::vector<core::Point3D<T>>();
            result.reserve(upperHull.size() + lowerHull.size() - 2);

            for (auto it = upperHull.begin(); it != upperHull.end(); ++it) {
                result.emplace_back(*it);
            }
            for (auto it = ++lowerHull.begin(); it != --lowerHull.end(); ++it) {
                result.emplace_back(*it);
            }
            return result;
        }

        /**
         * @brief Destructor of the ConvexHullIncremental object.
         */
        virtual ~ConvexHullIncremental() = default;
    };
}
#endif