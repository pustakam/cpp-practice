#ifndef __GOTTSCHLING_OOP_HPP__
#define __GOTTSCHLING_OOP_HPP__

template <typename T>
struct Inequality
{
    bool operator!=(const T& that) const
    {
        return !(*(static_cast<const T*>(this)) == that);
    }
};

template <typename T>
struct Cloneable
{
    T* clone() const
    {
        return new T(*(static_cast<const T*>(this)));
    }
};

struct Point : public Inequality<Point>, public Cloneable<Point>
{
    Point()
        : x_{}, y_{}
    {}
    Point(int x, int y)
        : x_{x}, y_{y}
    {}

    bool operator==(const Point& that) const
    {
        return x_ == that.x_ && y_ == that.y_;
    }

    int x_;
    int y_;
};

#endif // __GOTTSCHLING_OOP_HPP__
