// mystring_test4.cpp
// 实现一个简单的字符串类，只支持初始化和复制
// 第四版：实现复制构造函数 String(const String&)，通过第三个单元测试用例
#include <iostream>
#include <cstdlib>
#include <cstring>
#ifndef _MSC_VER
#define strcpy_s(DST,SIZE,SRC) strcpy((DST),(SRC))
#endif

struct String
{
private:
    size_t length_;
    char* buffer_;

public:
    String()
        : length_{0}
        , buffer_{ new char[1]{'\0'} }
    {
    }

    String(const char* buffer)
		: length_{ strlen(buffer) }
		, buffer_{ new char[length_ + 1] }
    {
		strcpy_s(buffer_, length_ + 1, buffer);
    }

    String(const String& other)
		: length_{ other.length_ }
		, buffer_{ new char[other.length_ + 1] }
    {
		strcpy_s(buffer_, length_ + 1, other.buffer_);
    }

    ~String()
    {
        delete[] buffer_;
    }

    String& operator=(const String& rhs)
    {
        if (this != &rhs)
        {
        }
        return *this;
    }

    const char* GetBuffer()const
    {
        return buffer_;
    }

    size_t GetLength()const
    {
        return length_;
    }
};

#define JSK_ASSERT(EXPRESSION) if(!(EXPRESSION)) throw 0;

int main()
{
    {
        String s;
        JSK_ASSERT(s.GetBuffer() != nullptr);
        JSK_ASSERT(s.GetBuffer()[0] == '\0');
        JSK_ASSERT(s.GetLength() == 0);
    }
    {
        String s = "This is a string!";
        JSK_ASSERT(s.GetBuffer() != nullptr);
        JSK_ASSERT(strcmp(s.GetBuffer(), "This is a string!") == 0);
        JSK_ASSERT(s.GetBuffer()[17] == '\0');
        JSK_ASSERT(s.GetLength() == 17);
    }
    {
        String s = "This is a string!";
        String t = s;
        JSK_ASSERT(t.GetBuffer() != nullptr);
        JSK_ASSERT(s.GetBuffer() != t.GetBuffer());
        JSK_ASSERT(s.GetLength() == t.GetLength());
        JSK_ASSERT(strcmp(s.GetBuffer(), t.GetBuffer()) == 0);
    }
    {
        String s = "This is a string!";
        s = s;
        JSK_ASSERT(s.GetBuffer() != nullptr);
        JSK_ASSERT(strcmp(s.GetBuffer(), "This is a string!") == 0);
        JSK_ASSERT(s.GetBuffer()[17] == '\0');
        JSK_ASSERT(s.GetLength() == 17);
    }
    {
        String s = "This is a string!";
        String t;
        t = s;
        JSK_ASSERT(t.GetBuffer() != nullptr);
        JSK_ASSERT(s.GetBuffer() != t.GetBuffer());
        JSK_ASSERT(s.GetLength() == t.GetLength());
        JSK_ASSERT(strcmp(s.GetBuffer(), t.GetBuffer()) == 0);
    }
    return 0;
}