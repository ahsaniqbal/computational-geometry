#ifndef CONVEX_HULL_BRUTE_FORCE_HPP
#define CONVEX_HULL_BRUTE_FORCE_HPP

#include "convex_hull/convex_hull_strategy.hpp"

namespace algorithms::convex_hull
{
    /**
     * @brief A class to compute the convex hull of a set of points using the brute force approach. The time of complexity of this approach is O(n^3).
     * @tparam T The type of the coordinates of the points.
     */
    template <typename T>
    class ConvexHullBruteForce: public ConvexHullStrategy<T>
    {
    private:
        /**
         * @brief Method to find the successive edge whose starting point is same as given point.
         * @param edges The list of edges.
         * @param q The point to compare.
         * @return The successive edge.
         * @throw std::invalid_argument if no edge is found.
         */
        std::pair<core::Point3D<T>, core::Point3D<T>> findSuccessiveEdge(const std::vector<std::pair<core::Point3D<T>, core::Point3D<T>>>& edges, const core::Point3D<T>& q) {
            for (auto it = edges.begin(); it != edges.end(); ++it) {
                if (it->first == q) {
                    return *it;
                }
            }
            throw std::invalid_argument("No edge found.");
        }

        /**
         * @brief Method to prepare the result or convex hull such the vertices of the convex hull (or polygon) are sorted in clockwise.
         * @param edges The list of edges.
         * @return The sorted convex hull.
         */
        std::vector<core::Point3D<T>> prepareResult(const std::vector<std::pair<core::Point3D<T>, core::Point3D<T>>>& edges) {
            auto result = std::vector<core::Point3D<T>>();
            result.reserve(edges.size() * 2 - 1);
            auto edge = edges.front();
            size_t i = 0;
            do {
                result.emplace_back(edge.first);
                edge = findSuccessiveEdge(edges, edge.second);
                ++i;
            } while (i < edges.size());
            result.erase(std::unique(result.begin(), result.end()), result.end());
            return result;
        }
    public:
        /**
         * @brief Method to compute the convex hull of a set of points using the brute force approach.
         * @param points The list of points.
         * @return The list of points that form the convex hull.
         */
        std::vector<core::Point3D<T>> compute(std::vector<core::Point3D<T>>& points) override {
            auto edges = std::vector<std::pair<core::Point3D<T>, core::Point3D<T>>>();
            edges.reserve(points.size());

            for (size_t i = 0; i < points.size(); i++) {
                for (size_t j = 0; j < points.size(); j++) {
                    if (i == j) 
                        continue;
                    bool valid = true;
                    for (size_t k = 0; k < points.size(); k++) {
                        if (k == i || k == j) 
                            continue;

                        // Check if the three points (i->j->k) are oriented clockwise or not
                        if (utils::isCounterClockwiseOrientated(points[i], points[j], points[k])) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        edges.push_back({points[i], points[j]});
                    }
                }
            }
            return prepareResult(edges);
        }
    };
} // namespace algorithms::convex_hull

#endif