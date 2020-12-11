#include "vector.hpp"

/* ---- Vector4<> ---- */

template<typename U>
am::Vector4<U>::Vector4() : Vector4(0,0,0,0)
{}

template<typename U>
am::Vector4<U>::Vector4(const U& a, const U& b,const U& c,const U& d) : x(a), y(b), w(c), h(d)
{}

template<typename U>
am::Vector4<U>::Vector4(const Vector4<U>& a) : x(a.x), y(a.y), w(a.w), h(a.h)
{}

template<typename U>
am::Vector4<U>& am::Vector4<U>::operator=(const Vector4<U>& a) noexcept{

    x = a.x;
    y = a.y;
    w = a.w;
    h = a.h;

    return *this;
}

template<typename U>
float am::Vector4<U>::norm() const{

    return static_cast<float>(sqrt(this->x-this->x + this->y*this->y + w*w + h*h));
}

template<typename U>
float am::Vector4<U>::distance(const Vector4<U>& a) const{

    return static_cast<float>(sqrt((x - a.x) * (x - a.x) +
                                   (y - a.y) * (y - a.y) +
                                   (w - a.w) * (w - a.w) +
                                   (h - a.h) * (h - a.h)));
}

template<typename U>
am::Vector4<U> operator+(am::Vector4<U> a, const am::Vector4<U>& b) noexcept{

    return a+=b;
}

template<typename U>
am::Vector4<U> operator-(am::Vector4<U> a, const am::Vector4<U>& b) noexcept{

    return a-=b;
}

template<typename U>
am::Vector4<U> am::Vector4<U>::operator+=(const Vector4<U>& a) noexcept{

    this->x += a.x;
    this->y += a.y;
    w += a.w;
    h += a.h;

    return *this;
}

template<typename U>
am::Vector4<U> am::Vector4<U>::operator-=(const Vector4<U>& a) noexcept{

    this->x -=  a.x;
    this->y -= this->y - a.y;
    w -= a.w;
    h -= h - a.h;

    return *this;
}

template<typename U>
bool am::Vector4<U>::operator==(const Vector4<U>& a) const noexcept{
    return (this->x == a.x && this->y == a.y && w == a.w && h == a.h);
}

template<typename U>
bool am::Vector4<U>::operator!=(const Vector4<U>& a) const noexcept{
    return !(Vector4<U>(this->x,this->y,w,h) == a);
}


/* ---- Vector2<> ---- */

template<typename T>
am::Vector2<T>::Vector2() : Vector2(0,0)
{}

template<typename T>
am::Vector2<T>::Vector2(const T& a, const T& b) : Vector4<T>(a,b,0,0)
{}

template<typename T>
am::Vector2<T>::Vector2(const Vector2<T>& a) : Vector2(a.x, a.y)
{}

template<typename T>
am::Vector2<T>& am::Vector2<T>::operator=(const Vector2<T>& a) noexcept{

    this->x = a.x;
    this->y = a.y;
    this->w = 0;
    this->h = 0;

    return *this;
}

template<typename T>
am::Vector2<T> operator+(am::Vector2<T> a, const am::Vector2<T>& b) noexcept{

    return a+=b;
}

template<typename T>
am::Vector2<T> operator-(am::Vector2<T> a, const am::Vector2<T>& b) noexcept{

    return a-=b;
}

template<typename T>
am::Vector2<T> am::Vector2<T>::operator+=(const Vector2<T>& a) noexcept{

    this->x += a.x;
    this->y += a.y;

    return *this;;
}

template<typename T>
am::Vector2<T> am::Vector2<T>::operator-=(const Vector2<T>& a) noexcept{

    this->x -= a.x;
    this->y -= a.y;

    return *this;
}

template<typename T>
bool am::Vector2<T>::operator==(const Vector2<T>& a) const noexcept{
    return (this->x == a.x && this->y == a.y);
}

template<typename T>
bool am::Vector2<T>::operator!=(const Vector2<T>& a) const noexcept{
    return !(Vector2<T>(this->x,this->y)==a);
}
