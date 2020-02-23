// mystring_test9.cpp
// 实现一个简单的字符串类，支持初始化和复制
// 第九版：实现比较操作符和相关测试用例
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

    int Compare(const String& other)const
    {
        return strcmp(buffer_, other.buffer_);
    }

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

    String(String&& other)
        : length_{ other.length_ }
        , buffer_{ other.buffer_ }
    {
        other.buffer_ = nullptr;
    }

    ~String()
    {
        delete[] buffer_;
    }

    String& operator=(const String& rhs)
    {
        if (this != &rhs)
        {
            delete[] buffer_;
            length_ = strlen(rhs.buffer_);
            buffer_ = new char[length_ + 1];
            strcpy_s(buffer_, length_ + 1, rhs.buffer_);
        }
        return *this;
    }

    String& operator=(String&& rhs)
    {
        if (this != &rhs)
        {
            delete[] buffer_;
            length_ = rhs.length_;
            buffer_ = rhs.buffer_;
            rhs.buffer_ = nullptr;
        }
        return *this;
    }

    bool operator == (const String& rhs)const { return Compare(rhs) == 0; }
    bool operator != (const String& rhs)const { return Compare(rhs) != 0; }
    bool operator <  (const String& rhs)const { return Compare(rhs) <  0; }
    bool operator <= (const String& rhs)const { return Compare(rhs) <= 0; }
    bool operator >  (const String& rhs)const { return Compare(rhs) >  0; }
    bool operator >= (const String& rhs)const { return Compare(rhs) >= 0; }

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
    {
        String s = "This is a string!";
        String t = std::move(s);
        JSK_ASSERT(s.GetBuffer() == nullptr);
        JSK_ASSERT(t.GetBuffer() != nullptr);   
        JSK_ASSERT(t.GetLength() == 17);
        JSK_ASSERT(strcmp(t.GetBuffer(), "This is a string!") == 0);
    }
    {
        String s = "This is a string!";
        s = std::move(s);
        JSK_ASSERT(s.GetBuffer() != nullptr);
        JSK_ASSERT(strcmp(s.GetBuffer(), "This is a string!") == 0);
        JSK_ASSERT(s.GetBuffer()[17] == '\0');
        JSK_ASSERT(s.GetLength() == 17);
    }
    {
        String s = "This is a string!";
        String t;
        t = std::move(s);
        JSK_ASSERT(s.GetBuffer() == nullptr);
        JSK_ASSERT(t.GetBuffer() != nullptr);
        JSK_ASSERT(t.GetLength() == 17);
        JSK_ASSERT(strcmp(t.GetBuffer(), "This is a string!") == 0);
    }
    {
        String s = "This is a string!";
        String t = "This is a string!";
		JSK_ASSERT(s == s);
        JSK_ASSERT(s == t);
		JSK_ASSERT(s <= s);
		JSK_ASSERT(s >= s);
        JSK_ASSERT(s <= t);
        JSK_ASSERT(s >= t);
    }
    {
        String s = "abcd";
        String t = "aef";
        JSK_ASSERT(s != t);
        JSK_ASSERT(s <  t);
        JSK_ASSERT(s <= t);
        JSK_ASSERT(t >  s);
        JSK_ASSERT(t >= s);
    }
    return 0;
}