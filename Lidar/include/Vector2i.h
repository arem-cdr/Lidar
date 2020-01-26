#pragma once

#include <iostream>

class Vector2i
{

public:
    Vector2i() : x(0), y(0) {}
    Vector2i(int x, int y) : x(x), y(y) {}

    int getX() { return y; }
    int getY() { return x; }

private:
    int x;
    int y;

    friend std::ostream &operator<<(std::ostream &flux, Vector2i const &v)
    {
        std::cout << v.x << " " << v.y << std::endl;

        return flux;
    }
    friend bool operator==(Vector2i v1, Vector2i v2)
    {

        return (v1.x == v2.x) && (v1.y == v2.y);
    }

    /*friend void operator+= (Vector2 v1){
        x += v1.x;
        y += v1.y;
    }*/
    friend Vector2i operator+(Vector2i v1, Vector2i v2)
    {
        Vector2i copy(v1);
        copy.x += v2.x;
        copy.y += v2.y;
        return copy;
    }
    friend Vector2i operator*(Vector2i v1, Vector2i v2)
    {
        Vector2i copy(v1);
        copy.x *= v2.x;
        copy.y *= v2.y;
        return copy;
    }
    friend Vector2i operator-(Vector2i v1, Vector2i v2)
    {
        Vector2i copy(v1);
        copy.x -= v2.x;
        copy.y -= v2.y;
        return copy;
    }
    friend int dot(Vector2i v1, Vector2i v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }
};