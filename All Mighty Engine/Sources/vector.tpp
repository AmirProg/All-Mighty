#include "vector.hpp"

/* Vector2<> */

template<typename T>
Vector2<T>::Vector2(){}

template<typename T>
Vector2<T>::Vector2(const T& a, const T& b) : x(a),y(b){}

template<typename T>
float Vector2<T>::norm() const{
    return sqrt(x*x + y*y);
}

template<typename T>
float Vector2<T>::distance(const Vector2<T>& b) const{
    return sqrt((b.x - x)*(b.x - x) + (b.y - y)*(b.y - y));
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& a) {
    return Vector2<T>(x + a.x, y + a.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator+=(Vector2<T> a){

    x = x + a.x;
    y = y + a.y;

    return *this;;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& a){
    return Vector2<T>(x - a.x, y - a.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-=(Vector2<T> a){

    x = x - a.x;
    y = y - a.y;

    return *this;
}

template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& a) const{
    return (x == a.x && y == a.y);
}

template<typename T>
bool Vector2<T>::operator!=(const Vector2<T>& a) const{
    return !(Vector2<T>(x,y)==a);
}

/* Vector4<> */

template<typename U>
Vector4<U>::Vector4(const U& x, const U& y,const U& a,const U& b) : Vector2<U>(x,y),w(a),h(b){}

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
