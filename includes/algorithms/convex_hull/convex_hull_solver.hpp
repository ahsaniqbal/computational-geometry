#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include<vector>
#include <memory> 
#include"core/point.hpp"
#include"convex_hull/convex_hull_strategy.hpp"

namespace algorithms::convex_hull {
    template <typename T>
    class ConvexHullSolver
    {
        /**
         * @brief Strategy to compute the convex hull.
         */
        std::unique_ptr<ConvexHullStrategy<T>> strategy;
    public:
        /**
         * @brief Construct a new Convex Hull object
         * 
         * @param strategy_ Strategy to compute the convex hull.
         */
        ConvexHullSolver(std::unique_ptr<ConvexHullStrategy<T>> strategy_): strategy(std::move(strategy_)) {}

        /**
         * @brief Compute the convex hull of a set of points.
         * 
         * @param points Set of points.
         * @return std::vector<core::Point3D<T>> representing the Convex hull as set of vertices sorted in clockwise order.
         */
        std::vector<core::Point3D<T>> compute(std::vector<core::Point3D<T>>& points) {
            return strategy->compute(points);
        }

        /**
         * @brief Set the Strategy object
         * 
         * @param strategy_ Strategy to compute the convex hull.
         */
        void setStrategy(std::unique_ptr<ConvexHullStrategy<T>> strategy_) {
            strategy = std::move(strategy_);
        }

        /**
         * @brief Destroy the Convex Hull object
         * 
         */
        ~ConvexHullSolver() = default;
    };
}

#endif