
#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <cmath>

namespace cpputils::Math {

    // Vector2d

    template<typename T>
    struct Vector2 {
        Vector2(T x = 0, T y = 0) : x(x), y(y) {}
        Vector2(const Vector2 &other) { x = other.x; y = other.y;}
        ~Vector2() = default;

        Vector2 &operator=(const Vector2 &other) { x = other.x; y = other.y; return *this; }

        T length() const;
        Vector2 rotate(float angle) const;
        Vector2 unit() const;
        void fromJson(const nlohmann::json &json);
        nlohmann::json toJson() const;

        T x = 0;
        T y = 0;
    };

    template<typename T>
    Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b);
    template<typename T>
    Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b);
    template<typename T>
    Vector2<T> operator+=(Vector2<T> &a, const Vector2<T> &b);
    template<typename T>
    Vector2<T> operator-=(Vector2<T> &a, const Vector2<T> &b);
    template<typename T>
    Vector2<T> operator*(const Vector2<T> &a, const Vector2<T> &b);
    template<typename T>
    Vector2<T> operator*=(Vector2<T> &a, const Vector2<T> &b);

    template<typename T>
    Vector2<T> operator*(const Vector2<T> &a, T b);
    template<typename T>
    Vector2<T> operator*=(Vector2<T> &a, T b);
    template<typename T>
    Vector2<T> operator/(const Vector2<T> &a, T b);
    template<typename T>
    Vector2<T> operator/=(Vector2<T> &a, T b);

    template<typename T>
    std::ostream& operator<<(std::ostream &os, const Vector2<T> &v);
    template<typename T>
    std::istream& operator>>(std::istream &is, Vector2<T> &v);

    template<typename T>
    Vector2<T> operator*(T a, const Vector2<T> &b);
    template<typename T>
    Vector2<T> operator/(T a, const Vector2<T> &b);
    template<typename T>
    Vector2<T> operator*=(T a, Vector2<T> &b);
    template<typename T>
    Vector2<T> operator/=(T a, Vector2<T> &b);

    template<typename T>
    bool operator==(const Vector2<T> &a, const Vector2<T> &b);
    template<typename T>
    bool operator!=(const Vector2<T> &a, const Vector2<T> &b);

    using Vector2d = Vector2<double>;
    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int32_t>;
    using Vector2ui = Vector2<u_int32_t>;
    using Vector2l = Vector2<int64_t>;
    using Vector2ul = Vector2<u_int64_t>;
    using Vector2s = Vector2<int16_t>;
    using Vector2us = Vector2<u_int16_t>;
    using Vector2c = Vector2<int8_t>;
    using Vector2uc = Vector2<u_int8_t>;

    // Vector3d

    template<typename T>
    struct Vector3 {
        Vector3(T x = 0, T y = 0, T z = 0);
        Vector3(const Vector3 &other);
        ~Vector3() = default;

        Vector3 &operator=(const Vector3 &other);

        T length() const;
        Vector3 reflect(const Vector3 &normal) const;
        Vector3 cross(const Vector3 &other) const;
        T dot(const Vector3 &other) const;
        double squaredNorm() const;
        Vector3 rotate(T angleX, T angleY, T angleZ) const;
        Vector3 rotate(const Vector3 &offsetRotation) const;
        Vector3 unit() const;
        void fromJson(const nlohmann::json &json);
        nlohmann::json toJson() const;

        T x = 0;
        T y = 0;
        T z = 0;
    };

    template<typename T>
    T dot(const Vector3<T> &a, const Vector3<T> &b);

    template<typename T>
    Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b);
    template<typename T>
    Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b);
    template<typename T>
    Vector3<T> operator+=(Vector3<T> &a, const Vector3<T> &b);
    template<typename T>
    Vector3<T> operator-=(Vector3<T> &a, const Vector3<T> &b);
    template<typename T>
    Vector3<T> operator*(const Vector3<T> &a, const Vector3<T> &b);
    template<typename T>
    Vector3<T> operator*=(Vector3<T> &a, const Vector3<T> &b);

    template<typename T>
    Vector3<T> operator*(const Vector3<T> &a, T b);
    template<typename T>
    Vector3<T> operator*=(Vector3<T> &a, T b);
    template<typename T>
    Vector3<T> operator/(const Vector3<T> &a, T b);
    template<typename T>
    Vector3<T> operator/=(Vector3<T> &a, T b);

    template<typename T>
    std::ostream& operator<<(std::ostream &os, const Vector3<T> &v);
    template<typename T>
    std::istream& operator>>(std::istream &is, Vector3<T> &v);

    template<typename T>
    Vector3<T> operator*(T a, const Vector3<T> &b);
    template<typename T>
    Vector3<T> operator/(T a, const Vector3<T> &b);
    template<typename T>
    Vector3<T> operator*=(T a, Vector3<T> &b);
    template<typename T>
    Vector3<T> operator/=(T a, Vector3<T> &b);
    template<typename T>
    Vector3<T> operator-(const Vector3<T> &v);

    template<typename T>
    bool operator==(const Vector3<T> &a, const Vector3<T> &b);
    template<typename T>
    bool operator!=(const Vector3<T> &a, const Vector3<T> &b);

    using Vector3d = Vector3<double>;
    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int32_t>;
    using Vector3ui = Vector3<u_int32_t>;
    using Vector3l = Vector3<int64_t>;
    using Vector3ul = Vector3<u_int64_t>;
    using Vector3s = Vector3<int16_t>;
    using Vector3us = Vector3<u_int16_t>;
    using Vector3c = Vector3<int8_t>;
    using Vector3uc = Vector3<u_int8_t>;

    // Ray

    struct Ray {
        Ray() = default;
        Ray(const Vector3d &origin, const Vector3d &direction);
        Ray(const Ray &ray);
        ~Ray() = default;

        Ray &operator=(const Ray &ray);

        Vector3d origin = Vector3d();
        Vector3d direction = Vector3d(0, 0, 1);
    };

    inline Ray::Ray(const Vector3d &origin, const Vector3d &direction)
        : origin(origin), direction(direction)
    {
    }

    inline Ray::Ray(const Ray &ray)
        : origin(ray.origin), direction(ray.direction)
    {
    }

    inline Ray &Ray::operator=(const Ray &ray)
    {
        origin = ray.origin;
        direction = ray.direction;
        return *this;
    }

    template<typename T>
    T Vector2<T>::length() const
    {
        return std::sqrt(x * x + y * y);
    }

    template<typename T>
    Vector2<T> Vector2<T>::rotate(float angle) const
    {
        float rad = angle * M_PI / 180;
        float c = std::cos(rad);
        float s = std::sin(rad);

        return Vector2<T>(x * c - y * s, x * s + y * c);
    }

    template<typename T>
    Vector2<T> Vector2<T>::unit() const
    {
        T len = length();
        return Vector2<T>(x / len, y / len);
    }

    template<typename T>
    void Vector2<T>::fromJson(const nlohmann::json &json)
    {
        x = json[0];
        y = json[1];
    }

    template<typename T>
    nlohmann::json Vector2<T>::toJson() const
    {
        nlohmann::json json;
        json.push_back(x);
        json.push_back(y);
        return json;
    }

    template<typename T>
    Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b)
    {
        return Vector2<T>(a.x + b.x, a.y + b.y);
    }

    template<typename T>
    Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b)
    {
        return Vector2<T>(a.x - b.x, a.y - b.y);
    }

    template<typename T>
    Vector2<T> operator+=(Vector2<T> &a, const Vector2<T> &b)
    {
        a.x += b.x;
        a.y += b.y;
        return a;
    }

    template<typename T>
    Vector2<T> operator-=(Vector2<T> &a, const Vector2<T> &b)
    {
        a.x -= b.x;
        a.y -= b.y;
        return a;
    }

    template<typename T>
    Vector2<T> operator*(const Vector2<T> &a, const Vector2<T> &b)
    {
        return Vector2<T>(a.x * b.x, a.y * b.y);
    }

    template<typename T>
    Vector2<T> operator*=(Vector2<T> &a, const Vector2<T> &b)
    {
        a.x *= b.x;
        a.y *= b.y;
        return a;
    }

    template<typename T>
    Vector2<T> operator*(const Vector2<T> &a, T b)
    {
        return Vector2<T>(a.x * b, a.y * b);
    }

    template<typename T>
    Vector2<T> operator*=(Vector2<T> &a, T b)
    {
        a.x *= b;
        a.y *= b;
        return a;
    }

    template<typename T>
    Vector2<T> operator/(const Vector2<T> &a, T b)
    {
        return Vector2<T>(a.x / b, a.y / b);
    }

    template<typename T>
    Vector2<T> operator/=(Vector2<T> &a, T b)
    {
        a.x /= b;
        a.y /= b;
        return a;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream &os, const Vector2<T> &v)
    {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    template<typename T>
    std::istream& operator>>(std::istream &is, Vector2<T> &v)
    {
        is >> v.x >> v.y;
        return is;
    }

    template<typename T>
    Vector2<T> operator*(T a, const Vector2<T> &b)
    {
        return Vector2<T>(a * b.x, a * b.y);
    }

    template<typename T>
    Vector2<T> operator/(T a, const Vector2<T> &b)
    {
        return Vector2<T>(a / b.x, a / b.y);
    }

    template<typename T>
    Vector2<T> operator*=(T a, Vector2<T> &b)
    {
        b.x *= a;
        b.y *= a;
        return b;
    }

    template<typename T>
    Vector2<T> operator/=(T a, Vector2<T> &b)
    {
        b.x /= a;
        b.y /= a;
        return b;
    }

    template<typename T>
    bool operator==(const Vector2<T> &a, const Vector2<T> &b)
    {
        return a.x == b.x && a.y == b.y;
    }

    template<typename T>
    bool operator!=(const Vector2<T> &a, const Vector2<T> &b)
    {
        return !(a == b);
    }

    template class Vector2<int>;
    template class Vector2<float>;
    template class Vector2<double>;

} // namespace Math


namespace cpputils::Math {

    template<typename T>
    Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z)
    {
    }

    template<typename T>
    Vector3<T>::Vector3(const Vector3 &other) : x(other.x), y(other.y), z(other.z)
    {
    }

    template<typename T>
    Vector3<T> &Vector3<T>::operator=(const Vector3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    template<typename T>
    T Vector3<T>::length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    template<typename T>
    Vector3<T> Vector3<T>::reflect(const Vector3 &normal) const
    {
        return *this - normal * (2 * this->dot(normal));
    }

    template<typename T>
    Vector3<T> Vector3<T>::unit() const
    {
        T len = length();
        return Vector3<T>(x / len, y / len, z / len);
    }

    template<typename T>
    double Vector3<T>::squaredNorm() const
    {
        return x * x + y * y + z * z;
    }

    template<typename T>
    void Vector3<T>::fromJson(const nlohmann::json &json)
    {
        x = json[0];
        y = json[1];
        z = json[2];
    }

    template<typename T>
    nlohmann::json Vector3<T>::toJson() const
    {
        nlohmann::json json;
        json.push_back(x);
        json.push_back(y);
        json.push_back(z);
        return json;
    }

    template<typename T>
    Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b)
    {
        return Vector3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    template<typename T>
    Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b)
    {
        return Vector3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    template<typename T>
    Vector3<T> operator+=(Vector3<T> &a, const Vector3<T> &b)
    {
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
        return a;
    }

    template<typename T>
    Vector3<T> operator-=(Vector3<T> &a, const Vector3<T> &b)
    {
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
        return a;
    }

    template<typename T>
    Vector3<T> operator*(const Vector3<T> &a, const Vector3<T> &b)
    {
        return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
    }

    template<typename T>
    Vector3<T> operator*=(Vector3<T> &a, const Vector3<T> &b)
    {
        a.x *= b.x;
        a.y *= b.y;
        a.z *= b.z;
        return a;
    }

    template<typename T>
    Vector3<T> operator*(const Vector3<T> &a, T b)
    {
        return Vector3<T>(a.x * b, a.y * b, a.z * b);
    }

    template<typename T>
    Vector3<T> operator*=(Vector3<T> &a, T b)
    {
        a.x *= b;
        a.y *= b;
        a.z *= b;
        return a;
    }

    template<typename T>
    Vector3<T> operator/(const Vector3<T> &a, T b)
    {
        return Vector3<T>(a.x / b, a.y / b, a.z / b);
    }

    template<typename T>
    Vector3<T> operator/=(Vector3<T> &a, T b)
    {
        a.x /= b;
        a.y /= b;
        a.z /= b;
        return a;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const Vector3<T> &v)
    {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

    template<typename T>
    std::istream &operator>>(std::istream &is, Vector3<T> &v)
    {
        is >> v.x >> v.y >> v.z;
        return is;
    }

    template<typename T>
    Vector3<T> operator*(T a, const Vector3<T> &b)
    {
        return Vector3<T>(a * b.x, a * b.y, a * b.z);
    }

    template<typename T>
    Vector3<T> operator/(T a, const Vector3<T> &b)
    {
        return Vector3<T>(a / b.x, a / b.y, a / b.z);
    }

    template<typename T>
    Vector3<T> operator*=(T a, Vector3<T> &b)
    {
        b.x *= a;
        b.y *= a;
        b.z *= a;
        return b;
    }

    template<typename T>
    Vector3<T> operator/=(T a, Vector3<T> &b)
    {
        b.x /= a;
        b.y /= a;
        b.z /= a;
        return b;
    }

    template<typename T>
    T dot(const Vector3<T> &a, const Vector3<T> &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template<typename T>
    Vector3<T> Vector3<T>::cross(const Vector3 &other) const
    {
        return Vector3<T>(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    template<typename T>
    T Vector3<T>::dot(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    template<typename T>
    Vector3<T> Vector3<T>::rotate(T angleX, T angleY, T angleZ) const
    {
        T radX = angleX * M_PI / 180;
        T radY = angleY * M_PI / 180;
        T radZ = angleZ * M_PI / 180;
        T cosX = std::cos(radX);
        T sinX = std::sin(radX);
        T cosY = std::cos(radY);
        T sinY = std::sin(radY);
        T cosZ = std::cos(radZ);
        T sinZ = std::sin(radZ);

        return Vector3<T>(
            x * (cosY * cosZ) + y * (cosY * sinZ) + z * -sinY,
            x * (sinX * sinY * cosZ + -cosX * sinZ) + y * (sinX * sinY * sinZ + cosX * cosZ) + z * sinX * cosY,
            x * (cosX * sinY * cosZ + -sinX * sinZ) + y * (cosX * sinY * sinZ + sinX * cosZ) + z * cosX * cosY
        );
    }

    template<typename T>
    Vector3<T> Vector3<T>::rotate(const Vector3 &offsetRotation) const
    {
        return rotate(offsetRotation.x, offsetRotation.y, offsetRotation.z);
    }

    template<typename T>
    Vector3<T> operator-(const Vector3<T> &a)
    {
        return Vector3<T>(-a.x, -a.y, -a.z);
    }

    template<typename T>
    bool operator==(const Vector3<T> &a, const Vector3<T> &b)
    {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    template<typename T>
    bool operator!=(const Vector3<T> &a, const Vector3<T> &b)
    {
        return !(a == b);
    }

    template struct Vector3<int>;
    template struct Vector3<float>;
    template struct Vector3<double>;

} // namespace Math
