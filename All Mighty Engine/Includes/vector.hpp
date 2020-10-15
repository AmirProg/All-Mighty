#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

#include <ostream>
#include <cmath>

/*
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
*/

template<typename U>
class Vector4{

public:
    Vector4();
    Vector4(const U& a, const U& b, const U& c, const U& d);
    Vector4(const Vector4&);
    Vector4(const Vector4&&);
    virtual ~Vector4() = default;
    virtual float norm() const;

    // Overloadings
    Vector4& operator=(const Vector4&);
    virtual Vector4 operator+(const Vector4& a);
    virtual Vector4 operator+=(Vector4 a);
    virtual Vector4 operator-(const Vector4& a);
    virtual Vector4 operator-=(Vector4 a);
    virtual bool operator==(const Vector4& a) const;
    virtual bool operator!=(const Vector4& a) const;

    U x, y, w, h; // Public attributes
};

template<typename U>
std::ostream& operator<<(std::ostream& os, const Vector4<U>& a){ // Stream overloading -> std::cout << v;
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
    Vector2(const Vector2&&);
    virtual ~Vector2() = default;
    Vector2& operator=(const Vector2&);
    float norm() const;
    float distance(const Vector2& b) const;

    // Overloadings
    Vector2 operator+(const Vector2& a);
    Vector2 operator+=(Vector2 a);
    Vector2 operator-(const Vector2& a);
    Vector2 operator-=(Vector2 a);
    bool operator==(const Vector2& a) const;
    bool operator!=(const Vector2& a) const;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& a){ // Stream overloading -> std::cout << v;
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

/* Allow the compiler to know the types of the templates classes */

template class Vector4<int>;
template class Vector4<unsigned int>;
template class Vector4<float>;
template class Vector2<int>;
template class Vector2<unsigned int>;
template class Vector2<float>;

#endif // VECTOR_HPP_INCLUDED
