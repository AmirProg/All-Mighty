#include "vector.hpp"

/* ---- Vector4<> ---- */

template<typename U>
Vector4<U>::Vector4() : Vector4(0,0,0,0)
{}

template<typename U>
Vector4<U>::Vector4(const U& a, const U& b,const U& c,const U& d) : x(a), y(b), w(c), h(d)
{}

template<typename U>
Vector4<U>::Vector4(const Vector4<U>& a) : x(a.x), y(a.y), w(a.w), h(a.h)
{}

template<typename U>
Vector4<U>::Vector4(const Vector4<U>&& a) : Vector4(std::move(a.x), std::move(a.y), std::move(a.w), std::move(a.h))
{}

template<typename U>
float Vector4<U>::norm() const{
    return sqrt(this->x-this->x + this->y*this->y + w*w + h*h);
}

template<typename U>
Vector4<U> Vector4<U>::operator+(const Vector4<U>& a){
    return Vector4<U>(this->x + a.x, this->y + a.y, w + a.w, h + a.h);
}

template<typename U>
Vector4<U> Vector4<U>::operator+=(Vector4<U> a){

    this->x = this->x + a.x;
    this->y = this->y + a.y;
    w = w + a.w;
    h = h + a.h;

    return *this;
}

template<typename U>
Vector4<U>& Vector4<U>::operator=(const Vector4<U>& a){

    x = a.x;
    y = a.y;
    w = a.w;
    h = a.h;

    return *this;
}

template<typename U>
Vector4<U> Vector4<U>::operator-(const Vector4<U>& a){
    return Vector4<U>(this->x - a.x, this->y - a.y,w-a.w,h-a.h);
}

template<typename U>
Vector4<U> Vector4<U>::operator-=(Vector4<U> a){

    this->x = this->x - a.x;
    this->y = this->y - a.y;
    w = w - a.w;
    h = h - a.h;

    return *this;;
}

template<typename U>
bool Vector4<U>::operator==(const Vector4<U>& a) const{
    return (this->x == a.x && this->y == a.y && w == a.w && h == a.h);
}

template<typename U>
bool Vector4<U>::operator!=(const Vector4<U>& a) const{
    return !(Vector4<U>(this->x,this->y,w,h) == a);
}


/* ---- Vector2<> ---- */

template<typename T>
Vector2<T>::Vector2() : Vector2(0,0)
{}

template<typename T>
Vector2<T>::Vector2(const T& a, const T& b) : Vector4<T>(a,b,0,0)
{}

template<typename T>
Vector2<T>::Vector2(const Vector2<T>& a) : Vector2(a.x, a.y)
{}

template<typename T>
Vector2<T>::Vector2(const Vector2<T>&& a) : Vector2(std::move(a.x), std::move(a.y))
{}

template<typename T>
float Vector2<T>::norm() const{
    return sqrt(this->x*this->x + this->y*this->y);
}

template<typename T>
float Vector2<T>::distance(const Vector2<T>& b) const{
    return sqrt((b.x - this->x)*(b.x - this->x) + (b.y - this->y)*(b.y - this->y));
}

template<typename T>
Vector2<T>& Vector2<T>::operator=(const Vector2& a){

    this->x = a.x;
    this->y = a.y;
    this->w = 0;
    this->h = 0;

    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& a) {
    return Vector2<T>(this->x + a.x, this->y + a.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator+=(Vector2<T> a){

    this->x = this->x + a.x;
    this->y = this->y + a.y;

    return *this;;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& a){
    return Vector2<T>(this->x - a.x, this->y - a.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-=(Vector2<T> a){

    this->x = this->x - a.x;
    this->y = this->y - a.y;

    return *this;
}

template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& a) const{
    return (this->x == a.x && this->y == a.y);
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2<T>& a) const{
    return !(Vector2<T>(this->x,this->y)==a);
}
