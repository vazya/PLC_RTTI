#include <iostream>
#include <typeinfo>
#include "RTTI.h"
using namespace std;

class A {
public:
	A() { cout << "A constructor \n"; }
	void PrintName() { cout << "A" << endl; }
	~A() {}
	//virtual void PrintName() { cout << "A" << endl; }
	//virtual ~A() {}
};

class B : public A {
public:
	B() { cout << "B constructor \n"; }
	void PrintName() { cout << "B" << endl; }
	~B() {}
	//virtual void PrintName() { cout << "B" << endl; }
	//virtual ~B() {}
};
 
void fun()
{
	A* c = new A();
	if( c ) {
		cout << "A* c = new A() succeded \n";
		cout << "c name : " << typeid( *c ).name() << endl;
		cout << "c hash : " << typeid( *c ).hash_code() << endl << endl;
		delete c;
	} else {
		cout << "A* c = new A() failed \n";
	}

	A* d = new B();
	if( d ) {
		cout << "A* d = new B() succeded \n";
		cout << "d name : " << typeid( *d ).name() << endl;
		cout << "d hash : " << typeid( *d ).hash_code() << endl << endl;
		delete d;
	} else {
		cout << "A* d = new B() failed \n";
	}

	B* e = new B();
	if( e ) {
		cout << "B* e = new B() succeded \n";
		cout << "e name : " << typeid( *e ).name() << endl;
		cout << "e hash : " << typeid( *e ).hash_code() << endl << endl;
		delete e;
	} else {
		cout << "B* e = new B() failed \n";
	}

	B* f( 0 );
	try {
		//f = new A(); ��� ������
	}
	catch( exception& e ) {
		cout << "Exception: " << e.what() << endl;
	}
	if( f ) {
		cout << "B* f = new A() succeded \n";
		cout << "f name : " << typeid( *f ).name() << endl;
		cout << "f hash : " << typeid( *f ).hash_code() << endl << endl;
		delete f;
	} else {
		cout << "B* f = new A() failed \n";
	}
}

void notFun()
{
	A* c = NEW( A, c );
	if( c ) {
		cout << "A* c = NEW( A, c ) succeded \n";
		cout << "c name : " << TYPEID( *c ).Name() << endl;
		cout << "c hash : " << TYPEID( *c ).HashCode() << endl << endl;
		delete c;
	} else {
		cout << "A* c = NEW( A, c ) failed \n";
	}

	A* d = NEW( B, d );
	if( d ) {
		cout << "A* d = NEW( B, d ) succeded \n";
		cout << "d name : " << TYPEID( *d ).Name() << endl;
		cout << "d hash : " << TYPEID( *d ).HashCode() << endl << endl;
		delete d;
	} else {
		cout << "A* d = NEW( B, d ) failed \n";
	}

	B* e = NEW( B, e );
	if( e ) {
		cout << "B* e = NEW( B, e ) succeded \n";
		cout << "e name : " << TYPEID( *e ).Name() << endl;
		cout << "e hash : " << TYPEID( *e ).HashCode() << endl << endl;
		delete e;
	} else {
		cout << "B* e = NEW( B, e ) failed \n";
	}

	B* f( 0 );
	try {
		//f = NEW( A, f ); ��� ������
	}
	catch( exception& e ) {
		cout << "Exception: " << e.what() << endl;
	}
	if( f ) {
		cout << "B* f = NEW( A, f ) succeded \n";
		cout << "f name : " << TYPEID( *f ).Name() << endl;
		cout << "f hash : " << TYPEID( *f ).HashCode() << endl << endl;
		delete f;
	} else {
		cout << "B* f = NEW( A, f ) failed \n";
	}
}

void withRTTI()
{
	A* c = dynamic_cast< A* >( new A() );
	if( c ) {
		cout << "A* c = dynamic_cast<A*>( new A() ) succeded \n";
		cout << "c->Name: "; c->PrintName();
		cout << "c name : " << typeid( *c ).name() << endl;
		cout << "c hash : " << typeid( *c ).hash_code() << endl << endl;
		delete c;
	} else {
		cout << "A* c = dynamic_cast<A*>( new A() ) failed \n";
	}

	A* d = dynamic_cast< A* >( new B() );
	if( d ) {
		cout << "A* d = dynamic_cast<A*>( new B() ) succeded \n";
		cout << "d->Name: "; d->PrintName();
		cout << "d name : " << typeid( *d ).name() << endl;
		cout << "d hash : " << typeid( *d ).hash_code() << endl << endl;
		delete d;
	} else {
		cout << "A* d = dynamic_cast<A*>( new B() ) failed \n";
	}

	B* e = dynamic_cast< B* >( new B() );
	if( e ) {
		cout << "B* e = dynamic_cast<B*>( new B() ) succeded \n";
		cout << "e->Name: "; e->PrintName();
		cout << "e name : " << typeid( *e ).name() << endl;
		cout << "e hash : " << typeid( *e ).hash_code() << endl << endl;
		delete e;
	} else {
		cout << "B* e = dynamic_cast<B*>( new B() ) failed \n";
	}

	B* f( 0 );
	try {
		//f = dynamic_cast< B* >( new A() );
	} 
	catch( exception& e ) {
		cout << "Exception: " << e.what() << endl;
	}
	if( f ) {
		cout << "B* f = dynamic_cast<B*>( new A() ) succeded \n";
		cout << "f->Name: "; f->PrintName();
		cout << "f name : " << typeid( *f ).name() << endl;
		cout << "f hash : " << typeid( *f ).hash_code() << endl << endl;
		delete f;
	} else {
		cout << "B* f = dynamic_cast<B*>( new A() ) failed \n";
	}
}

void withoutRTTI()
{
	A* c = NEW( A, c );
	if( c ) {
		cout << "A* c = NEW( A, c ) succeded \n";
		cout << "c->Name: "; c->PrintName();
		cout << "c name : " << TYPEID( *c ).Name() << endl;
		cout << "c hash : " << TYPEID( *c ).HashCode() << endl << endl;
		delete c;
	} else {
		cout << "A* c = NEW( A, c ) failed \n";
	}

	A* d = NEW( B, d );
	if( d ) {
		cout << "A* d = NEW( B, d ) succeded \n";
		cout << "d->Name: "; d->PrintName();
		cout << "d name : " << TYPEID( *d ).Name() << endl;
		cout << "d hash : " << TYPEID( *d ).HashCode() << endl << endl;
		delete d;
	} else {
		cout << "A* d = NEW( B, d ) failed \n";
	}

	B* e = NEW( B, e );
	if( e ) {
		cout << "B* e = NEW( B, e ) succeded \n";
		cout << "e->Name: "; e->PrintName();
		cout << "e name : " << TYPEID( *e ).Name() << endl;
		cout << "e hash : " << TYPEID( *e ).HashCode() << endl << endl;
		delete e;
	} else {
		cout << "B* e = NEW( B, e ) failed \n";
	}

	B* f( 0 );
	try {
		//f = NEW( A, f ); ��� ������
	}
	catch( exception& e ) {
		cout << "Exception: " << e.what() << endl;
	}
	if( f ) {
		cout << "B* f = NEW( A, f ) succeded \n";
		cout << "f->Name: "; f->PrintName();
		cout << "f name : " << TYPEID( *f ).Name() << endl;
		cout << "f hash : " << TYPEID( *f ).HashCode() << endl << endl;
		delete f;
	} else {
		cout << "B* f = NEW( A, f ) failed \n";
	}
}

void veryNotFun()
{
	A* d1 = dynamic_cast< A* >( new B() );
	if( d1 ) {
		cout << "A* d1 = dynamic_cast<A*>( new B() ) succeded \n";
		cout << "d1->Name: "; d1->PrintName();
		cout << "d1 name : " << typeid( d1 ).name() << endl;
		cout << "d1 hash : " << typeid( d1 ).hash_code() << endl << endl;
		delete d1;
	} else {
		cout << "A* d1 = dynamic_cast<A*>( new B() ) failed \n";
	}

	A* d = NEW( B, d );
	if( d ) {
		cout << "A* d = NEW( B, d ) succeded \n";
		cout << "d->Name: "; d->PrintName();
		cout << "d name : " << TYPEID( d ).Name() << endl;
		cout << "d hash : " << TYPEID( d ).HashCode() << endl << endl;
		delete d;
	} else {
		cout << "A* d = NEW( B, d ) failed \n";
	}
}

void f()
{
	cout << typeid( new A() ).name() << endl;
	cout << typeid( new B() ).name() << endl;
	A* a = new B();
	cout << typeid( *a ).name() << endl;
	a->PrintName();
	cout << typeid( dynamic_cast< A* >( new B ) ).name() << endl;
}

int main()
{
	//f();
	
	fun(); cout << endl;
	//notFun();

	withRTTI(); cout << endl;
	//withoutRTTI();
	
	//veryNotFun();
	system( "pause" );
	return 0;
}