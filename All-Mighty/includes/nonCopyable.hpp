#ifndef NONCOPYABLE_HPP_INCLUDED
#define NONCOPYABLE_HPP_INCLUDED

/****************************************************
*                                                   *
*                                                   *
*   ~ NonCopyable Class ~                           *
*                                                   *
*   If you want your class to be non copyable,      *
*   just make inherit your class from NonCopyable   *
*                                                   *
*                                                   *
****************************************************/

namespace am {

    class NonCopyable {

    protected:
        NonCopyable() = default; // You have to define a default constructor in your classes that inherit from NonCopyable
        virtual ~NonCopyable()
        {}

    private:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

#endif // NONCOPYABLE_HPP_INCLUDED
