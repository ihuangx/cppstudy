#include <iostream>

struct Point
{
    float x, y;
};

struct Vector
{
    float x, y;
};

// 向量相加仍然是一个向量
Vector operator+(Vector a, Vector b)
{
    return Vector{a.x + b.x, a.y + b.y};
}

// 向量可以变换点
Point operator+(Point a, Vector b)
{
    return Point{a.x + b.x, a.y + b.y};
}

Point operator+(Vector a, Point b)
{
    return Point{a.x + b.x, a.y + b.y};
}

int main()
{
    Point a{1, 2};
    Vector b{3, 4};
    
    auto x = b + b;
    std::cout << "b + b = {" << x.x << ", " << x.y << "}" << std::endl;
    
    auto y = a + b;
    std::cout << "a + b = {" << y.x << ", " << y.y << "}" << std::endl;
    
    auto z = b + a;
    std::cout << "b + a = {" << z.x << ", " << z.y << "}" << std::endl;

    return 0;
}