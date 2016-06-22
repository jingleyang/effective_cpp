// effective_cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>

#define APP_NAME "Jingle_code"
const char* const k_app_name = "Jingle_code";

class GamePlayer {
private:
	enum {
		// It is impossible to use &Numturns
		Numturns = 5
	};
	int scores[Numturns];
};

class Item {
public:
	int val;
	Item(int input=0):val(input) {

	}
	bool operator < (const Item& rhs) const {
		return this->val < rhs.val;
	}
};

void func(int val) {
	std::cout << "val : " << val << std::endl;
}
template<class T>
inline void callWithMax(const T& first, const T& second) {
	func(first<second? second.val : first.val);
}

class TextBlock {
public:
	// mutable is necessary
	// error C3490: 'textLength' cannot be modified because it is being accessed through a const object
	mutable std::size_t textLength;
	mutable bool lengthIsValid;
	std::string strVal;
	TextBlock():textLength(0), lengthIsValid(false), strVal("abc"){

	}
	std::size_t getLength() const {
		if (!lengthIsValid) {
			textLength = strVal.size();
			lengthIsValid = false;
		}
		return textLength;
	}
	const std::string& getConstStr() const {
		return this->strVal;
	}
	//std::string& getStr() {
	//	return this->strVal;
	//}
	std::string& getStr() {
		// It is also ok.
		//return const_cast<std::string&>((static_cast<const TextBlock&>(*this)).getConstStr());
		return const_cast<std::string&>(this->getConstStr());
	}
};

static int g_count = 0;
class InitDemo {
public:
	InitDemo(): a(g_count++),
				b(g_count++),
				c(g_count++),
				x(g_count++),
				y(g_count++),
				z(g_count++){
		std::cout << x << std::endl;
		std::cout << y << std::endl;
		std::cout << z << std::endl;
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;

		std::cout << "ptr x = " << &x << std::endl;
		std::cout << "ptr a = " << &a << std::endl;
		std::cout << "sizeof int" << sizeof(a) << std::endl;
	}
private:
	int x;
	int y;
	int z;
	int a;
	int b;
	int c;
};
int main()
{
	std::cout << k_app_name << std::endl;
	// inline template
	Item first(1);
	Item second(2);
	callWithMax(first, second);

	// const char* test

	//error C2440: 'initializing': cannot convert from 'const char *const ' to 'char *'
	//char* ptr_name = k_app_name;

	const char* ptr_name = k_app_name;
	ptr_name = "bnu_code";
	std::cout << ptr_name << std::endl;
	//error C3892: 'ptr_name': you cannot assign to a variable that is const
	//ptr_name[0] = 'a';

	//error C2440: 'initializing': cannot convert from 'const char *const ' to 'char *'
	//char* const ptr_key = k_app_name;

	//error C3892: 'k_app_name': you cannot assign to a variable that is const
	//k_app_name = "abc";

	char* const ptr_const = "abc";
	// Access violation writing location 0x01368B40. However, it pass the compile check
	// ptr_const[0] = 'f';
	// error C3892: 'ptr_const': you cannot assign to a variable that is const
	// ptr_const = "cba";

	char* buff = new char[100];
	char* const ptr_const_buffer = buff;
	ptr_const_buffer[0] = 'a';
	ptr_const_buffer[1] = 0;
	std::cout << ptr_const_buffer << std::endl;
	
	delete ptr_const_buffer;
	// error C3892: 'ptr_const_buffer': you cannot assign to a variable that is const
	// ptr_const_buffer = NULL;

	typedef std::vector<int> INT_ARRAY;
	INT_ARRAY arr = { 1,2,3,4,5 };
	INT_ARRAY::const_iterator c_iter;
	for (c_iter = arr.cbegin(); c_iter != arr.cend(); c_iter++) {
		std::cout << *c_iter << std::endl;
	}

	TextBlock tb;
	int len = tb.getLength();
	std::cout << "len: " << len << std::endl;
	const std::string& ref_const_str = tb.getConstStr();
	std::string& ref_str = tb.getStr();
	// error C3892: 'ref_const_str': you cannot assign to a variable that is const
	// ref_const_str[0]='x';
	ref_str[0] = 'x';
	std::cout << ref_str << std::endl;

	InitDemo demo;

    return 0;
}

