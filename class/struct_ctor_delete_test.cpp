#include <iostream>

struct X
{
    X() = delete; // 阻止编译生成缺省构造函数
    X(const X&) = delete; // 阻止编译器生成缺省拷贝构造函数
    X(int) {} // 显式定义一个有参构造函数
};

/*
// A:
struct Y
{
    X x;
    Y() = delete;
    Y(const Y&) = delete;
};

int main()
{
    // Do nothing.
    return 0;
}
// 结果：没有编译语法错误

// B: 因为 X 不存在缺省和拷贝构造函数，自然编译器也无法给Y生成缺省和拷贝构造函数
struct Y
{
    X x;
};

int main()
{
    Y y1; // 调用缺省构造函数。error C2280: “Y::Y(void)”: 尝试引用已删除的函数
    Y y2 = y1; // 调用缺省拷贝构造函数。 假设y1能正常构造，error C2280: “Y::Y(const Y &)”: 尝试引用已删除的函数
    return 0;
}

// C: 因为X不存在缺省构造函数，因此 Y() = default 的意思就是没有缺省构造函数
struct Y
{
    X x;
    Y() = default;
    Y(const Y&) = delete;
};

int main()
{
    Y y1; // 调用缺省构造函数。error C2280: “Y::Y(void)”: 尝试引用已删除的函数
    // 复制构造函数被标记为删除，无法调用
}
*/
// D: 因为X不存在缺省构造函数，因此 Y(const Y&) = default 的意思就是没有拷贝构造函数
struct Y
{
    X x;
    Y() = delete;
    Y(const Y&) = default;
    Y(int):x{0}{}
};

int main()
{
    Y y1{0};
    Y y2 = y1; // error C2280: “Y::Y(const Y &)”: 尝试引用已删除的函数
    return 0;
}