#ifndef _VECTOR_2D_H
#define _VECTOR_2D_H


template <typename T>
class Vector2D {
public:
    Vector2D(T x, T y);

    T x, y;
};

template <typename T>
Vector2D<T>::Vector2D(T x, T y) : x(x), y(y) {}

#endif
