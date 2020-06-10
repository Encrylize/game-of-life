#ifndef _VECTOR_2D_H
#define _VECTOR_2D_H

#include <functional>

#include "utils.h"

template <typename T>
class Vector2D {
public:
    Vector2D();
    Vector2D(T x, T y);

    template <typename U>
    Vector2D(const Vector2D<U>& vec);

    template <typename U>
    Vector2D& operator+=(const U& other);
    template <typename U>
    Vector2D& operator-=(const U& other);
    template <typename U>
    Vector2D& operator/=(const U& div);

    T x, y;
};

template <typename T>
struct std::hash<Vector2D<T>> {
    size_t operator()(const Vector2D<T>& vec) const {
        return utils::hash_combine(utils::hash_combine(0, vec.x), vec.y);
    }
};

template <typename T>
Vector2D<T>::Vector2D() : x(), y() {}

template <typename T>
Vector2D<T>::Vector2D(T x, T y) : x(x), y(y) {}

template <typename T>
template <typename U>
Vector2D<T>::Vector2D(const Vector2D<U>& vec) : x(vec.x), y(vec.y) {}

template <typename T>
template <typename U>
Vector2D<T>& Vector2D<T>::operator+=(const U& other) {
    *this = *this + other;
    return *this;
}

template <typename T>
template <typename U>
Vector2D<T>& Vector2D<T>::operator-=(const U& other) {
    *this = *this - other;
    return *this;
}

template <typename T>
template <typename U>
Vector2D<T>& Vector2D<T>::operator/=(const U& div) {
    *this = *this / div;
    return *this;
}

template <typename T, typename U>
auto operator+(const Vector2D<T>& a, const Vector2D<U>& b) {
    return Vector2D<decltype(T() + U())>(a.x + b.x, a.y + b.y);
}

template <typename T, typename U>
auto operator-(const Vector2D<T>& a, const Vector2D<U>& b) {
    return Vector2D<decltype(T() - U())>(a.x - b.x, a.y - b.y);
}

template <typename T, typename U>
auto operator/(const Vector2D<T>& vec, const U& div) {
    return Vector2D<decltype(T() / U())>(vec.x / div, vec.y / div);
}

template <typename T, typename U>
auto operator*(const Vector2D<T>& vec, const U& mul) {
    return Vector2D<decltype(T() * U())>(vec.x * mul, vec.y * mul);
}

template <typename T, typename U>
bool operator==(const Vector2D<T>& a, const Vector2D<U>& b) {
    return a.x == b.x && a.y == b.y;
}

#endif
