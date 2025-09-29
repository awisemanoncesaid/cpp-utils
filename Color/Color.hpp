
#pragma once

#include <cstdint>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace cpputils {

    template <typename T>
    struct Color3 {
        Color3(T r = 0, T g = 0, T b = 0)
            : r(r), g(g), b(b)
        {
        }
        Color3(const std::string &hex)
        {
            fromHex(hex);
        }
        T r = 0;
        T g = 0;
        T b = 0;

        void fromHex(const std::string &hex)
        {
            if (hex[0] == '#')
            {
                fromHex(hex.substr(1));
                return;
            }
            if (hex.size() != 6)
            {
                throw std::invalid_argument("Invalid hex color");
            }
            r = std::stoi(hex.substr(0, 2), nullptr, 16) / 255.0;
            g = std::stoi(hex.substr(2, 2), nullptr, 16) / 255.0;
            b = std::stoi(hex.substr(4, 2), nullptr, 16) / 255.0;
        }

        std::string toHex() const
        {
            char buffer[8];
            sprintf(buffer, "%02X%02X%02X", r * 255, g * 255, b * 255);
            return std::string(buffer);
        }

        void fromBytes(const u_int8_t *data)
        {
            r = data[0] / 255.0;
            g = data[1] / 255.0;
            b = data[2] / 255.0;
        }

        void toBytes(u_int8_t *data) const
        {
            data[0] = r * 255;
            data[1] = g * 255;
            data[2] = b * 255;
        }

        Color3 operator+(const Color3 &other) const
        {
            return Color3(r + other.r, g + other.g, b + other.b);
        }

        Color3 operator-(const Color3 &other) const
        {
            return Color3(r - other.r, g - other.g, b - other.b);
        }

        Color3 operator*(float factor) const
        {
            return Color3(r * factor, g * factor, b * factor);
        }

        Color3 operator*(const Color3 &other) const
        {
            return Color3(r * other.r, g * other.g, b * other.b);
        }

        Color3 operator+=(const Color3 &other)
        {
            r += other.r;
            g += other.g;
            b += other.b;
            return *this;
        }

        Color3 operator*=(float factor)
        {
            r *= factor;
            g *= factor;
            b *= factor;
            return *this;
        }

        Color3 operator/=(float factor)
        {
            r /= factor;
            g /= factor;
            b /= factor;
            return *this;
        }

        Color3 operator*=(const Color3 &other)
        {
            r *= other.r;
            g *= other.g;
            b *= other.b;
            return *this;
        }

        bool operator==(const Color3 &other) const
        {
            return r == other.r && g == other.g && b == other.b;
        }

        std::string toString() const
        {
            return "Color3(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
        }

        u_int32_t toInt() const
        {
            u_int8_t c[4] = {
                r * 255,
                g * 255,
                b * 255,
                1
            };
            return *(u_int32_t *)&c;
        }
    };

    template <typename T>
    struct Color {
        Color3<T> color;
        T opacity = 0.0;

        Color(Color3<T> color = Color3<T>(), T opacity = 0.0)
            : color(color), opacity(opacity)
        {
        }

        Color(T r, T g, T b, T opacity = 0.0)
            : color(r, g, b), opacity(opacity)
        {
        }

        Color(const Color &other)
            : color(other.color), opacity(other.opacity)
        {
        }

        Color &operator=(const Color &other)
        {
            color = other.color;
            opacity = other.opacity;
            return *this;
        }

        Color(const u_int8_t *buffer)
        {
            fromBytes(buffer);
        }

        void toBytes(u_int8_t *buffer) const
        {
            buffer[0] = color.r * 255;
            buffer[1] = color.g * 255;
            buffer[2] = color.b * 255;
            buffer[3] = opacity * 255;
        }
        void fromBytes(const u_int8_t *buffer)
        {
            color.r = buffer[0] / 255.0;
            color.g = buffer[1] / 255.0;
            color.b = buffer[2] / 255.0;
            opacity = buffer[3] / 255.0;
        }

        void blend(const Color &bg) {
            T srcAlpha = opacity;
            T dstAlpha = bg.opacity * (1.0f - srcAlpha);
            T outAlpha = srcAlpha + dstAlpha;

            if (outAlpha > 0.0f) {  // Prevent division by zero
                color.r = (color.r * srcAlpha + bg.color.r * dstAlpha) / outAlpha;
                color.g = (color.g * srcAlpha + bg.color.g * dstAlpha) / outAlpha;
                color.b = (color.b * srcAlpha + bg.color.b * dstAlpha) / outAlpha;
            }

            opacity = outAlpha;
        }

        Color operator*(float factor) const
        {
            return Color(color * factor, opacity * factor);
        }

        Color operator+(const Color &other) const
        {
            return Color(color + other.color, opacity + other.opacity);
        }

        Color operator*(const Color &other) const
        {
            return Color(color * other.color, opacity * other.opacity);
        }

        Color operator+=(const Color &other)
        {
            color += other.color;
            opacity += other.opacity;
            return *this;
        }

        Color operator*=(float factor)
        {
            color *= factor;
            opacity *= factor;
            return *this;
        }

        Color operator /=(float factor)
        {
            color /= factor;
            opacity /= factor;
            return *this;
        }

        std::string toString() const
        {
            return "Color(" + color.toString() + ", " + std::to_string(opacity) + ")";
        }

        u_int32_t toInt() const
        {
            u_int8_t c[4] = {
                color.r * 255,
                color.g * 255,
                color.b * 255,
                opacity * 255
            };
            return *(u_int32_t *)&c;
        }

        Color clamp() const
        {
            return Color(
                std::clamp(color.r, 0.0f, 1.0f),
                std::clamp(color.g, 0.0f, 1.0f),
                std::clamp(color.b, 0.0f, 1.0f),
                std::clamp(opacity, 0.0f, 1.0f));
        }
    };

    using Color3f = Color3<float>;
    using Color3d = Color3<double>;
    using Color4f = Color<float>;
    using Color4d = Color<double>;

} // namespace cpputils
