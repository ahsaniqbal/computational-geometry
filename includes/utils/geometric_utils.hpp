#ifndef GEOMETRIC_UTILS_HPP
#define GEOMETRIC_UTILS_HPP

#include <vector>
#include <limits>
#include <type_traits>
#include "core/point.hpp"

namespace utils {
    /**
     * @brief A constant to represent the epsilon value for floating point comparison.
     */
    template <typename T>
    constexpr T epsilonValue() {
        if constexpr (std::is_floating_point_v<T>) {
            return std::numeric_limits<T>::epsilon() * 10;
        }
        return T(0);
    }

    /**
     * @brief Method to check if three points are collinear or not.
     * @param a The first point.
     * @param b The second point.
     * @param c The third point.
     * @return `true` if the points are collinear, `false` otherwise.
     */
    template<typename T>
    bool areCollinear(const core::Point3D<T>& a, const core::Point3D<T>& b, const core::Point3D<T>& c) {
        return std::abs(a.dot(b * c)) <= epsilonValue<T>();
    }

    /**
     * @brief Method to check if three points (a->b->c) are clockwise orientated or not.
     * @param a The first point.
     * @param b The second point.
     * @param c The third point.
     * @return `true` if the points (a->b->c) are clockwise orientated, `false` otherwise.
     */
    template<typename T>
    bool isClockwiseOrientated(const core::Point3D<T>& a, const core::Point3D<T>& b, const core::Point3D<T>& c) {
        return a.dot(b * c) < -epsilonValue<T>();
    }

    /**
     * @brief Method to check if three points (a->b->c) are counter-clockwise orientated or not.
     * @param a The first point.
     * @param b The second point.
     * @param c The third point.
     * @return `true` if the points (a->b->c) are counter-clockwise orientated, `false` otherwise.
     */
    template<typename T>
    bool isCounterClockwiseOrientated(const core::Point3D<T>& a, const core::Point3D<T>& b, const core::Point3D<T>& c) {
        return a.dot(b * c) > epsilonValue<T>();
    }

    /**
     * @brief Method to get the index of the extreme right point in a list of points.
     * @param points The list of points.
     * @return The index of the extreme right point.
     */
    template<typename T>
    u_int32_t getIndexExtremeRightPoint(const std::vector<core::Point3D<T>>& points) {
        u_int32_t indexExtremeRight = 0;
        for (size_t i = 1; i < points.size(); i++) {
            if (points[i].getX() > points[indexExtremeRight].getX()) {
                indexExtremeRight = i;
            }
        }
        return indexExtremeRight;
    }

    /**
     * @brief Method to get the index of the extreme left point in a list of points.
     * @param points The list of points.
     * @return The index of the extreme left point.
     */
    template<typename T>
    u_int32_t getIndexExtremeLeftPoint(const std::vector<core::Point3D<T>>& points) {
        u_int32_t indexExtremeLeft = 0;
        for (size_t i = 1; i < points.size(); i++) {
            if (points[i].getX() < points[indexExtremeLeft].getX()) {
                indexExtremeLeft = i;
            }
        }
        return indexExtremeLeft;
    }
}
#endif