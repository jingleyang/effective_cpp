## 1. View C++ as a federation of languages

There are four categrages of C++.

1. C. 
1. Object-Oriented C++
1. Template C++
1. STL

## 2. Prefer consts, enums, and inlines to `#define`

1. The enums can be used for SIZE of a array

```
class GamePlayer {
private:
	enum {
		// It is impossible to use &Numturns
		Numturns = 5
	};
	int scores[Numturns];
};
```

1. An example of template inline

```
void func(int val) {
	std::cout << "val : " << val << std::endl;
}
template<class T>
inline void callWithMax(const T& first, const T& second) {
	func(first<second? second.val : first.val);
}
```

## 3. Use const whenever possible

1. Using `const char* const ptr` to replace `#defeine`

```
#define APP_NAME "Jingle_code"
const char* const k_app_name = "Jingle_code";
```

1. The first const means it is impossible to change the content where this pointer points to. The second const means that it is impossible to change the address.

```
const char* ptr_name = k_app_name;
ptr_name = "bnu_code";
std::cout << ptr_name << std::endl;
//error C3892: 'ptr_name': you cannot assign to a variable that is const
//ptr_name[0] = 'a';
```

```
char* buff = new char[100];
char* const ptr_const_buffer = buff;
ptr_const_buffer[0] = 'a';
ptr_const_buffer[1] = 0;
std::cout << ptr_const_buffer << std::endl;

delete ptr_const_buffer;
// error C3892: 'ptr_const_buffer': you cannot assign to a variable that is const
// ptr_const_buffer = NULL;
```

1. The const iterator

```
typedef std::vector<int> INT_ARRAY;
INT_ARRAY arr = { 1,2,3,4,5 };
INT_ARRAY::const_iterator c_iter;
for (c_iter = arr.cbegin(); c_iter != arr.cend(); c_iter++) {
    std::cout << *c_iter << std::endl;
}
```

1. The keyword mutable. Mutable members of const classes are modifiable.

```
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
};
```

1. const_cast. const_cast makes it possible to form a reference or pointer to non-const type that is actually referring to a const object or a reference or pointer to non-volatile type that is actually referring to a volatile object.

Normally, non-const function will call a const function with the same logic.

```
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
```

## 4. Make sure that objects are initiallised before they are used.

1. The order of the data initalisation. The base classes initialised before derived classes. And within a class, data members are initialised in the order in which they are decleared.

```
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
```

2. Avoid initialisation order problems across translation units by replacing non-local static objects with local static objects.
Or using singleton.



