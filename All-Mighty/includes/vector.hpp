#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

#include <ostream>
#include <cmath>

/*************************************************************************************************************
*
* ~ Vector2<> and Vector4<> templates classes ~
*
* You can manipulate 2D and 4D Vector easily
*
* x, y, w and h coords are publics, and you can use usuals operators to manipulate your Vector<> objects
* Vector2<> inherit from Vector4<>, w and h coordinates both equal to 0
* There are some alias -> Vector2i means Vector2<int>
*                         Vector2u -> Vector2<unsigned int>
*                         Vector2f -> Vector2<float>
*                         Same for Vector4<>
*
*
**************************************************************************************************************/

template<typename U>
class Vector4{

public:
    Vector4();
    Vector4(const U& a, const U& b, const U& c, const U& d);
    Vector4(const Vector4&);
    Vector4(Vector4&&) noexcept = default;
    virtual ~Vector4() = default;
    virtual float norm() const;
    virtual float distance(const Vector4& b) const;

    // Overloadings
    Vector4& operator=(const Vector4&) noexcept;
    virtual Vector4 operator+=(const Vector4& a) noexcept;
    virtual Vector4 operator-=(const Vector4& a) noexcept;
    virtual bool operator==(const Vector4& a) const noexcept;
    virtual bool operator!=(const Vector4& a) const noexcept;

    U x, y, w, h; // Public attributes
};

template<typename U>
Vector4<U> operator+(Vector4<U> a, const Vector4<U>& b) noexcept;
template<typename U>
Vector4<U> operator-(Vector4<U> a, const Vector4<U>& b) noexcept;

template<typename U>
std::ostream& operator<<(std::ostream& os, const Vector4<U>& a) noexcept{ // Stream overloading -> std::cout << v;
    os << "(" << a.x << "," << a.y << "," << a.w << "," << a.h << ")";
    return os;
}


/* Vector2<> template class which inherit from Vector4<> w = h = 0 */

template<typename T>
class Vector2 : public Vector4<T>{

public:
    Vector2();
    Vector2(const Vector2&);
    Vector2(const T& a, const T& b);
    Vector2(Vector2&&) noexcept = default;
    virtual ~Vector2() = default;
    Vector2& operator=(const Vector2&) noexcept;

    // Overloadings
    Vector2 operator+=(const Vector2& a) noexcept;
    Vector2 operator-=(const Vector2& a) noexcept;
    bool operator==(const Vector2& a) const noexcept;
    bool operator!=(const Vector2& a) const noexcept;
};

template<typename T>
Vector2<T> operator+(Vector2<T> a, const Vector2<T>& b) noexcept;
template<typename T>
Vector2<T> operator-(Vector2<T> a, const Vector2<T>& b) noexcept;

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& a) noexcept{ // Stream overloading -> std::cout << v;
    os << "(" << a.x << "," << a.y << ")";
    return os;
}

/* typedefs (shorter alias) */

typedef Vector4<int> Vector4i;
typedef Vector4<unsigned int> Vector4u;
typedef Vector4<float> Vector4f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float> Vector2f;

#include "vector.tpp"

#endif // VECTOR_HPP_INCLUDED
