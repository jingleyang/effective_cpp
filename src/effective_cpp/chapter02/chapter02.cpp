// chapter02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

// patch test
int add(int a, int b){
	return a+b;
}
// patch test end

class Uncopyable {
protected:
	Uncopyable() {}
	~Uncopyable() {}
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

class NoCopy : public Uncopyable {
public:
	explicit NoCopy(int a):val(a){
	}
	~NoCopy(){}
private:
	int val;
};

template <class T>
class UnCopyAbleTpl {
protected:
	UnCopyAbleTpl() {}
	~UnCopyAbleTpl() {}
private:
	UnCopyAbleTpl(const UnCopyAbleTpl&);
	UnCopyAbleTpl& operator=(const UnCopyAbleTpl&);
};

class NoCopyA : public UnCopyAbleTpl<NoCopyA> {
private:
	int val;
};

class NoCopyB : public UnCopyAbleTpl<NoCopyB> {
private:
	int val;
};

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);		\
	void operator=(const TypeName&)


class NoCopyC{
public:
	int val;
	NoCopyC(int a=0) :val(a){

	}
private:
	DISALLOW_COPY_AND_ASSIGN(NoCopyC);
};

class TimeKeeper {
public:
	TimeKeeper() {
	};
	virtual ~TimeKeeper() {
		std::cout << "Call Destructor in TimeKeeper" << std::endl;
	};
};



class AtomicClock : public TimeKeeper {
public:
	AtomicClock() {};
	virtual ~AtomicClock() {
		std::cout << "Call Destructor in AtomicClock" << std::endl;
	};
};

TimeKeeper* getKeeper() {
	return static_cast<TimeKeeper*>(new AtomicClock());
}

int main()
{
	NoCopy a(100);
	//error C2280: 'NoCopy::NoCopy(const NoCopy &)': attempting to reference a deleted function
	//NoCopy b(a);

	//error C2280: 'NoCopy::NoCopy(const NoCopy &)': attempting to reference a deleted function
	//NoCopy b = a;

	NoCopyA aA;
	//error C2280: 'NoCopyA::NoCopyA(const NoCopyA &)': attempting to reference a deleted function
	//NoCopyA bA(aA);

	NoCopyC aC;
	// error C2248: 'NoCopyC::NoCopyC': cannot access private member declared in class 'NoCopyC'
	//NoCopyC bC(aC);

	TimeKeeper* keeper = getKeeper();
	delete keeper;
	int base_size = sizeof(TimeKeeper);
	int dirived_size = sizeof(AtomicClock);
	// all 8 bytes
	return 0;
}
