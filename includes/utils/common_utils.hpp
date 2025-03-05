#ifndef COMMON_UTILS_HPP
#define COMMON_UTILS_HPP

#include <vector>
#include <random>
#include "core/point.hpp"

namespace utils {
    std::random_device rd;
    std::mt19937 gen(rd());
    /**
     * @brief Method to flatten a list of points into a list of coordinates.
     * @param points The list of points.
     * @return The list of coordinates.
     */
    template<typename T>
    std::vector<T> flatten(const std::vector<core::Point3D<T>>& points) {
        std::vector<T> flattened;
        flattened.reserve(points.size() * 3);
        for (const auto& point : points) {
            flattened.push_back(point.getX());
            flattened.push_back(point.getY());
            flattened.push_back(point.getZ());
        }
        return flattened;
    }

    /**
     * @brief Method to get the uniform distribution for integers of given range.
     * @param min The minimum value of the range.
     * @param max The maximum value of the range.
     * @return The uniform distribution for integers of given range.
     */
    template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
    std::uniform_int_distribution<T> getUniformDistribution(T min, T max) {
        return std::uniform_int_distribution<T>(min, max);
    }

    /**
     * @brief Method to get the uniform distribution for floating point numbers of given range.
     * @param min The minimum value of the range.
     * @param max The maximum value of the range.
     * @return The uniform distribution for floating point numbers of given range.
     */
    template<typename T, std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
    std::uniform_real_distribution<T> getUniformDistribution(T min, T max) {
        return std::uniform_real_distribution<T>(min, max);
    }

    /**
     * @brief Method to generate random numbers of given type within a given range.
     * @param min The minimum value of the range.
     * @param max The maximum value of the range.
     * @return The random number in the given range.
     */
    template<typename T>
    T getRandomNumber(T min, T max) {
        auto dist = getUniformDistribution<T>(min, max);
        return dist(gen);
    }

    /**
     * @brief Method to generate a list of random points with the given x, y and z ranges.
     * @param numPoints The number of points to generate.
     * @param minX The minimum x value.
     * @param maxX The maximum x value.
     * @param minY The minimum y value.
     * @param maxY The maximum y value.
     * @param minZ The minimum z value.
     * @param maxZ The maximum z value.
     * @param is3D A flag to indicate if the points are 3D or not.
     * @return The list of random points.
     */
    template<typename T>
    std::vector<core::Point3D<T>> getRandomPoints(uint32_t numPoints, T minX, T maxX, T minY, T maxY, T minZ, T maxZ, bool is3D = false) {
        std::vector<core::Point3D<T>> points;
        points.reserve(numPoints);

        for (size_t i = 0; i < numPoints; i++) {
            auto x = getRandomNumber(minX, maxX);
            auto y = getRandomNumber(minY, maxY);
            auto z = is3D ? getRandomNumber(minZ, maxZ) : 1.0f;

            points.emplace_back(core::Point3D<T>(x, y, z));
        }
        return points;
    }
}

#endif