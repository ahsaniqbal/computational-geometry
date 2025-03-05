#ifndef POINT_HPP
#define POINT_HPP

#include<iostream>
#include <cmath> 
/**
 * @struct Point3D
 * @brief A class that represents a point or vector in 3D space.
 * 
 * This class encapsulates a point in 3-dimensional space with X, Y, and Z coordinates. It provides 
 * basic methods for manipulating 3D points such as addition, subtraction, distance calculation, etc.
 */

namespace core {
    template<typename T>
    class Point3D {
        T x, y, z;

    public:
        /**
         * @brief Default constructor that initializes the point/vector to (0, 0, 0).
         */
        Point3D() : x(0), y(0), z(0) {}

        /**
         * @brief Constructor to initialize point/vector with specific coordinates.
         * @param x_ The X coordinate.
         * @param y_ The Y coordinate.
         * @param z_ The Z coordinate.
         */
        Point3D(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

        /**
         * @brief Copy constructor.
         * @param other The `Point3D` object to copy.
         */
        Point3D(const Point3D& other) : x(other.x), y(other.y), z(other.z) {}

        /**
         * @brief Move constructor.
         * @param other The `Point3D` object to move.
         */
        Point3D(Point3D&& other) : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)) {}

        /**
         * @brief Copy assignment operator.
         * @param other The `Point3D` object to copy.
         * @return A reference to the this `Point3D` object.
         */
        Point3D& operator=(const Point3D& other) {
            if (this != &other) {
                x = other.x;
                y = other.y;
                z = other.z;
            }
            return *this;
        }

        /**
         * @brief Move assignment operator.
         * @param other The `Point3D` object to move.
         * @return A reference to the this `Point3D` object.
         */
        Point3D& operator=(Point3D&& other) {
            if (this != &other) {
                x = std::move(other.x);
                y = std::move(other.y);
                z = std::move(other.z);
            }
            return *this;
        }

        /**
         * @brief Destructor.
         */
        ~Point3D() {}

        /**
         * @brief Method to get the X coordinate.
         */
        T getX() const {
            return x;
        }

        /**
         * @brief Method to get the Y coordinate.
         */
        T getY() const {
            return y;
        }

        /**
         * @brief Method to get the Z coordinate.
         */
        T getZ() const {
            return z;
        }

        /**
         * @brief Addition operator.
         * @param other The `Point3D` object to add.
         * @return A new `Point3D` object representing the sum of this and other.
         */
        Point3D operator+(const Point3D& other) const {
            return Point3D(x + other.x, y + other.y, z + other.z);
        }

        /**
         * @brief Subtraction operator.
         * @param other The `Point3D` object to subtract.
         * @return A new `Point3D` object representing the difference of this and other.
         */
        Point3D operator-(const Point3D& other) const {
            return Point3D(x - other.x, y - other.y, z - other.z);
        }

        /**
         * @brief Scalar vector multiplication.
         * @param c The scalar value to multiply with.
         * @return A new `Point3D` object representing the product of this and c.
         */
        Point3D operator*(T c) const {
            return Point3D(x * c, y * c, z * c);
        }

        /**
         * @brief Cross product operator.
         * @param other The `Point3D` object to cross with.
         * @return A new `Point3D` object representing the cross product (this x other).
         */
        Point3D operator*(const Point3D& other) const {
            return Point3D(y * other.z - z * other.y, -(x * other.z - z * other.x), x * other.y - y * other.x);
        }

        /**
         * @brief Method to calculate the dot product.
         * @param other The `Point3D` object to dot with.
         * @return The dot product of this and other.
         */
        T dot(const Point3D& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        /**
         * @brief Method to calculate the L2 norm of the vector.
         * @return The L2 norm of the vector.
         */
        T normP2() const {
            return std::sqrt(dot(*this));
        }

        /**
         * @brief Equality operator.
         * @param other The `Point3D` object to compare with.
         * @return `true` if this and other are equal, `false` otherwise.
         */
        bool operator==(const Point3D& other) const {
            return x == other.x && y == other.y && z == other.z;
        }

        /**
         * @brief Less than operator.
         * @param other The `Point3D` object to compare with.
         * @return `true` if this is less than (lexiographically) other, `false` otherwise.
         */
        bool operator<(const Point3D& p) const {
            if (*this == p) return false;
            if (x != p.x) 
                return x < p.x;
            if (y != p.y)
                return y < p.y;
            
            return z < p.z;
        }
    };
}
#endif