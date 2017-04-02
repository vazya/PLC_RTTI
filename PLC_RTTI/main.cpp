#include <iostream>
#include <typeinfo>
#include "RTTI.h"
using namespace std;

class A {
public:
	A() { c = 'A'; cout << "A constructor \n"; }
	//void PrintName() { cout << "A" << endl; }
	//~A() {}
	virtual void PrintName() { cout << c << endl; }
	virtual ~A() {}
	char c;
};

class B : public A {
public:
	B() { c = 'B'; cout << "B constructor \n"; }
	//void PrintName() { cout << "B" << endl; }
	//~B() {}
	virtual void PrintName() { cout << c << c << endl; }
	virtual ~B() {}
};

class C: public B {
public:
	C() { c = 'C'; cout << "C constructor \n"; }
	//void PrintName() { cout << "C" << endl; }
	//~C() {}
	virtual void PrintName() { cout << c << c << c << endl; }
	virtual ~C() {}
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
		//f = new A(); так нельзя
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
		//f = NEW( A, f ); так нельзя
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
	EXTEND( B, A );
	EXTEND( C, B );

	auto cc = NEW( A, cc );
	auto it = RTTI.find( "cc" );
	assert( it != RTTI.end() );
	auto iter = ANCESTORS[( RTTI.find( ( "cc" ) )->second ).Name()].find( ( "A*" ) );
	assert( iter != ANCESTORS[( RTTI.find( ( "cc" ) )->second ).Name()].end() );

	A* c = DYNAMIC_CAST( A*, cc );
	if( c ) {
		cout << "A* c =  DYNAMIC_CAST( A*, NEW( A, c ) ) succeded \n";
		cout << "c->Name: "; c->PrintName();
		cout << "c name : " << TYPEID( *c ).Name() << endl;
		cout << "c hash : " << TYPEID( *c ).HashCode() << endl << endl;
		delete c;
	} else {
		cout << "A* c =  DYNAMIC_CAST( A*, NEW( A, c ) ) failed \n";
	}

	A* d = DYNAMIC_CAST( A*, NEW( B, d ) );
	if( d ) {
		cout << "A* d = DYNAMIC_CAST( A*, NEW( B, d ) ) \n";
		cout << "d->Name: "; d->PrintName();
		cout << "d name : " << TYPEID( *d ).Name() << endl;
		cout << "d hash : " << TYPEID( *d ).HashCode() << endl << endl;
		delete d;
	} else {
		cout << "A* d = DYNAMIC_CAST( A*, NEW( B, d ) ) failed \n";
	}

	B* e = DYNAMIC_CAST( B*, NEW( B, e ) );
	if( e ) {
		cout << "B* e = DYNAMIC_CAST( B*, NEW( B, e ) ) succeded \n";
		cout << "e->Name: "; e->PrintName();
		cout << "e name : " << TYPEID( *e ).Name() << endl;
		cout << "e hash : " << TYPEID( *e ).HashCode() << endl << endl;
		delete e;
	} else {
		cout << "B* e = DYNAMIC_CAST( B*, NEW( B, e ) ) failed \n";
	}

	B* f( 0 );
	try {
		f = DYNAMIC_CAST( B*, NEW( A, f ) ); // так нельзя
	}
	catch( exception& e ) {
		cout << "Exception: " << e.what() << endl;
	}
	if( f ) {
		cout << "B* f =  DYNAMIC_CAST( B*, NEW( A, f ) ) succeded \n";
		cout << "f->Name: "; f->PrintName();
		cout << "f name : " << TYPEID( *f ).Name() << endl;
		cout << "f hash : " << TYPEID( *f ).HashCode() << endl << endl;
		delete f;
	} else {
		cout << "B* f =  DYNAMIC_CAST( B*, NEW( A, f ) ) failed \n";
	}

	C* g = DYNAMIC_CAST( C*, NEW( A, g ) );
	if( g ) {
		cout << "C* g =  DYNAMIC_CAST( C*, NEW( A, g ) ) succeded \n";
		cout << "g->Name: "; g->PrintName();
		cout << "g name : " << TYPEID( *g ).Name() << endl;
		cout << "g hash : " << TYPEID( *g ).HashCode() << endl << endl;
		delete g;
	} else {
		cout << "C* g =  DYNAMIC_CAST( C*, NEW( A, g ) ) failed \n";
	}

	C* h = DYNAMIC_CAST( C*, NEW( B, h ) );
	if( h ) {
		cout << "C* h =  DYNAMIC_CAST( C*, NEW( B, h ) ) succeded \n";
		cout << "h->Name: "; h->PrintName();
		cout << "h name : " << TYPEID( *h ).Name() << endl;
		cout << "h hash : " << TYPEID( *h ).HashCode() << endl << endl;
		delete h;
	} else {
		cout << "C* h =  DYNAMIC_CAST( C*, NEW( B, h ) ) failed \n";
	}

	C* k = DYNAMIC_CAST( C*, NEW( C, k ) );
	if( h ) {
		cout << "C* k =  DYNAMIC_CAST( C*, NEW( C, k ) ) succeded \n";
		cout << "k->Name: "; k->PrintName();
		cout << "k name : " << TYPEID( *k ).Name() << endl;
		cout << "k hash : " << TYPEID( *k ).HashCode() << endl << endl;
		delete k;
	} else {
		cout << "C* k =  DYNAMIC_CAST( C*, NEW( C, k ) ) failed \n";
	}
}

void veryNotFun()
{
	A* d0 = new B();
	if( d0 ) {
		cout << "A* d0 = new B() succeded \n";
		cout << "d1->Name: "; d0->PrintName();
		cout << "d0 name : " << typeid( *d0 ).name() << endl;
		cout << "d0 hash : " << typeid( *d0 ).hash_code() << endl << endl;
		delete d0;
	} else {
		cout << "A* d0 = new B() failed \n";
	}

	A* d1 = dynamic_cast< A* >( new B() );
	if( d1 ) {
		cout << "A* d1 = dynamic_cast<A*>( new B() ) succeded \n";
		cout << "d1->Name: "; d1->PrintName();
		cout << "d1 name : " << typeid( *d1 ).name() << endl;
		cout << "d1 hash : " << typeid( *d1 ).hash_code() << endl << endl;
		delete d1;
	} else {
		cout << "A* d1 = dynamic_cast<A*>( new B() ) failed \n";
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
	
	//fun(); cout << endl;
	//notFun(); cout << endl;

	//withRTTI(); cout << endl;
	withoutRTTI(); cout << endl;
	
	//veryNotFun();
	system( "pause" );
	return 0;
}