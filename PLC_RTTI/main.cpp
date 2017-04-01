#include <iostream>
#include <typeinfo>
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
	} else {
		cout << "A* c = dynamic_cast<A*>( new A() ) failed \n";
	}
	cout << "c name : " << typeid( c ).name() << endl;
	cout << "c hash : " << typeid( c ).hash_code() << endl << endl;
	delete c;

	A* d = dynamic_cast< A* >( new B() );
	if( d ) {
		cout << "A* d = dynamic_cast<A*>( new B() ) succeded \n";
	} else {
		cout << "A* d = dynamic_cast<A*>( new B() ) failed \n";
	}
	cout << "d name : " << typeid( d ).name() << endl;
	cout << "d hash : " << typeid( d ).hash_code() << endl << endl;
	delete d;

	B* e = dynamic_cast< B* >( new B() );
	if( e ) {
		cout << "B* e = dynamic_cast<B*>( new B() ) succeded \n";
	} else {
		cout << "B* e = dynamic_cast<B*>( new B() ) failed \n";
	}
	cout << "e name : " << typeid( e ).name() << endl;
	cout << "e hash : " << typeid( e ).hash_code() << endl << endl;
	delete e;

	//B* f = dynamic_cast< B* >( new A() );
	//if( f ) {
	//	cout << "B* f = dynamic_cast<B*>( new A() ) succeded \n";
	//} else {
	//	cout << "B* f = dynamic_cast<B*>( new A() ) failed \n";
	//}
	//cout << "f name : " << typeid( f ).name() << endl;
	//cout << "f hash : " << typeid( f ).hash_code() << endl << endl;
	//delete f;
}

void withoutRTTI()
{
	A* c = dynamic_cast< A* >( new A() );
	if( c ) {
		cout << "A* c = dynamic_cast<A*>( new A() ) succeded \n";
	} else {
		cout << "A* c = dynamic_cast<A*>( new A() ) failed \n";
	}
	cout << "c name : " << typeid( c ).name() << endl;
	cout << "c hash : " << typeid( c ).hash_code() << endl << endl;
	delete c;

	A* d = dynamic_cast< A* >( new B() );
	if( d ) {
		cout << "A* d = dynamic_cast<A*>( new B() ) succeded \n";
	} else {
		cout << "A* d = dynamic_cast<A*>( new B() ) failed \n";
	}
	cout << "d name : " << typeid( d ).name() << endl;
	cout << "d hash : " << typeid( d ).hash_code() << endl << endl;
	delete d;

	B* e = dynamic_cast< B* >( new B() );
	if( e ) {
		cout << "B* e = dynamic_cast<B*>( new B() ) succeded \n";
	} else {
		cout << "B* e = dynamic_cast<B*>( new B() ) failed \n";
	}
	cout << "e name : " << typeid( e ).name() << endl;
	cout << "e hash : " << typeid( e ).hash_code() << endl << endl;
	delete e;

	//try {
	//	B* f = dynamic_cast< B* >( new A() );
	//	if( f ) {
	//		cout << "B* f = dynamic_cast<B*>( new A() ) succeded \n";
	//	} else {
	//		cout << "B* f = dynamic_cast<B*>( new A() ) failed \n";
	//	}
	//	cout << "f name : " << typeid( f ).name() << endl;
	//	cout << "f hash : " << typeid( f ).hash_code() << endl << endl;
	//	delete f;
	//}
	//catch( std::exception& e ) {
	//	cout << e.what() << endl;
	//}
}

int main()
{
	fun();
	//withRTTI();
	withoutRTTI();
	system( "pause" );
	return 0;
}