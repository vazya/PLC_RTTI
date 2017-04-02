#include <iostream>
#include <typeinfo>
#include "RTTI.h"
using namespace std;

class A {
public:
	A() { cout << "A constructor \n"; }
	virtual void PrintName() { cout << "A" << endl; }
	//~A() { cout << "A destructor \n"; }
	virtual ~A() { /*cout << "A destructor \n";*/ }
};

class B : public A {
public:
	B() { cout << "B constructor \n"; }
	virtual void PrintName() { cout << "B" << endl; }
	//~B() { cout << "B destructor \n"; }
	virtual ~B() { /*cout << "B destructor \n";*/ }
};

void fun()
{
	A* a = new A();
	cout << "A* a->PrintName() = "; a->PrintName();
	A* b = new B();
	cout << "A* b->PrintName() = "; b->PrintName();
	B* bb = new B();
	cout << "B* bb->PrintName() = "; bb->PrintName();
	//B* ba = new A(); так нельзя

	delete a;
	delete b;
	delete bb;
}

void withRTTI()
{
	A* c = dynamic_cast< A* >( new A() );
	if( c ) {
		cout << "A* c = dynamic_cast<A*>( new A() ) succeded \n";
		cout << "c name : " << typeid( c ).name() << endl;
		cout << "c hash : " << typeid( c ).hash_code() << endl << endl;
		delete c;
	} else {
		cout << "A* c = dynamic_cast<A*>( new A() ) failed \n";
	}

	A* d = dynamic_cast< A* >( new B() );
	if( d ) {
		cout << "A* d = dynamic_cast<A*>( new B() ) succeded \n";
		cout << "d name : " << typeid( d ).name() << endl;
		cout << "d hash : " << typeid( d ).hash_code() << endl << endl;
		delete d;
	} else {
		cout << "A* d = dynamic_cast<A*>( new B() ) failed \n";
	}

	B* e = dynamic_cast< B* >( new B() );
	if( e ) {
		cout << "B* e = dynamic_cast<B*>( new B() ) succeded \n";
		cout << "e name : " << typeid( e ).name() << endl;
		cout << "e hash : " << typeid( e ).hash_code() << endl << endl;
		delete e;
	} else {
		cout << "B* e = dynamic_cast<B*>( new B() ) failed \n";
	}

	B* f( 0 );
	try {
		f = dynamic_cast< B* >( new A() );
	} 
	catch( exception& e ) {
		cout << "Exception: " << e.what() << endl;
	}
	if( f ) {
		cout << "B* f = dynamic_cast<B*>( new A() ) succeded \n";
		cout << "f name : " << typeid( f ).name() << endl;
		cout << "f hash : " << typeid( f ).hash_code() << endl << endl;
		delete f;
	} else {
		cout << "B* f = dynamic_cast<B*>( new A() ) failed \n";
	}
}

void notFun()
{
	NEW( A*, pa );
	NEW( A, a );
	NEW( B*, pb );
	NEW( B, b );
	NEW( B, bb );
	cout << "RTTI size = " << RTTI.size() << endl;

	cout << "pa.name = " << TYPEID( pa ).Name() << endl;
	cout << "pa.hash_code = " << TYPEID( pa ).HashCode() << endl;
	cout << "a.name = " << TYPEID( a ).Name() << endl;
	cout << "a.hash_code = " << TYPEID( a ).HashCode() << endl;
	cout << "pb.name = " << TYPEID( pb ).Name() << endl;
	cout << "pb.hash_code = " << TYPEID( pb ).HashCode() << endl;
	cout << "b.name = " << TYPEID( b ).Name() << endl;
	cout << "b.hash_code = " << TYPEID( b ).HashCode() << endl;
	cout << "bb.name = " << TYPEID( bb ).Name() << endl;
	cout << "bb.hash_code = " << TYPEID( bb ).HashCode() << endl;
	cout << "zz.name = " << TYPEID( zz ).Name() << endl;
	cout << "zz.hash_code = " << TYPEID( zz ).HashCode() << endl;
}

template<typename T>
static T* constructNewObj()
{
	return new T();
}

#define VZ(T) constructNewObj<T>()

void veryNotFun()
{
	int* a = constructNewObj<int>();
	cout << a << endl;
	A* pa = constructNewObj<A>();
	cout << "pa name = "; pa->PrintName();
	B* pb = VZ( B );
	cout << "pb name = "; pb->PrintName();
}

int main()
{
	//fun();
	//withRTTI();
	//notFun();
	veryNotFun();
	system( "pause" );
	return 0;
}