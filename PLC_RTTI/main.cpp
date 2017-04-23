#include <iostream>
#include <typeinfo>
#include "RTTI.h"
using namespace std;

class A {
public:
	A() { c = 'A'; c = 111; cout << "A constructor \n"; }
	//void PrintName() { cout << "A" << endl; }
	//~A() {}
	virtual void PrintName() { cout << c << endl; }
	virtual ~A() {}
	int c;
};

class B : public A {
public:
	int b;
	B() { b = 777;  c = 'B'; c = 222; cout << "B constructor \n"; }
	//void PrintName() { cout << "B" << endl; }
	//~B() {}
	virtual void PrintName() { cout << c << c << endl; }
	virtual ~B() {}
};

class C : public A {
public:
	int cc;
	C() { cc = 1488;  c = 'C';  c = 333; cout << "C constructor \n"; }
	//void PrintName() { cout << "C" << endl; }
	//~C() {}
	virtual void PrintName() { cout << c << c << c << endl; }
	virtual ~C() {}
};

class D : public B, public C {
public:
	int d;
	D() { d = 666;  B::c = 'D'; C::c = 'd'; B::c = 223; C::c = 332; cout << "D constructor \n"; }
	//void PrintName() { cout << "C" << endl; }
	//~C() {}
	virtual void PrintName() { cout << B::c << B::c << C::c << C::c << endl; }
	virtual ~D() {}
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
		//f = new A(); так нельз€
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
		//f = NEW( A, f ); так нельз€
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
	EXTEND( D, B );
	EXTEND( D, C );

	EXTENDORDER( B, vector<string>{ "A" } );
	EXTENDORDER( C, vector<string>{ "A" } );
	vector<string> dExtendorder{ "B", "C" };
	EXTENDORDER( D, dExtendorder );
	//vector<string> bExtendorder{ 'A' } ;
	//auto cc = NEW( A, cc );
	////auto it = RTTI.find( "cc" );
	////assert( it != RTTI.end() );
	////auto iter = ANCESTORS[( RTTI.find( ( "cc" ) )->second ).Name()].find( ( "A*" ) );
	////assert( iter != ANCESTORS[( RTTI.find( ( "cc" ) )->second ).Name()].end() );

	//A* c = DYNAMIC_CAST( A*, cc, c );
	////A* c = DYNAMIC_CAST( A*, NEW( A, c ) )
	//if( c ) {
	//	cout << "A* c =  DYNAMIC_CAST( A*, NEW( A, c ) ) succeded \n";
	//	cout << "c->Name: "; c->PrintName();
	//	cout << "c name : " << TYPEID( *c ).Name() << endl;
	//	cout << "c hash : " << TYPEID( *c ).HashCode() << endl << endl;
	//	delete c;
	//} else {
	//	cout << "A* c =  DYNAMIC_CAST( A*, NEW( A, c ) ) failed \n";
	//}

	//auto dd = NEW( B, dd );
	//A* d = DYNAMIC_CAST( A*, dd, d );
	////A* d = DYNAMIC_CAST( A*, NEW( B, d ) );
	//if( d ) {
	//	cout << "A* d = DYNAMIC_CAST( A*, NEW( B, d ) ) \n";
	//	cout << "d->Name: "; d->PrintName();
	//	cout << "d name : " << TYPEID( *d ).Name() << endl;
	//	cout << "d hash : " << TYPEID( *d ).HashCode() << endl << endl;
	//	delete d;
	//} else {
	//	cout << "A* d = DYNAMIC_CAST( A*, NEW( B, d ) ) failed \n";
	//}

	//auto ee = NEW( B, ee );
	//B* e = DYNAMIC_CAST( B*, ee, e );
	////B* e = DYNAMIC_CAST( B*, NEW( B, e ) );
	//if( e ) {
	//	cout << "B* e = DYNAMIC_CAST( B*, NEW( B, e ) ) succeded \n";
	//	cout << "e->Name: "; e->PrintName();
	//	cout << "e name : " << TYPEID( *e ).Name() << endl;
	//	cout << "e hash : " << TYPEID( *e ).HashCode() << endl << endl;
	//	delete e;
	//} else {
	//	cout << "B* e = DYNAMIC_CAST( B*, NEW( B, e ) ) failed \n";
	//}

	//auto kk = NEW( C, kk );
	//C* k = DYNAMIC_CAST( C*, kk, k );
	//if( k ) {
	//	cout << "C* k =  DYNAMIC_CAST( C*, NEW( C, k ) ) succeded \n";
	//	cout << "k->Name: "; k->PrintName();
	//	cout << "k name : " << TYPEID( *k ).Name() << endl;
	//	cout << "k hash : " << TYPEID( *k ).HashCode() << endl << endl;
	//	delete k;
	//} else {
	//	cout << "C* k =  DYNAMIC_CAST( C*, NEW( C, k ) ) failed \n";
	//}

	//auto jj = NEW( C, jj );
	//B* j = DYNAMIC_CAST( B*, jj, j );
	//if( j ) {
	//	cout << "B* j =  DYNAMIC_CAST( B*, NEW( C, j ) ) succeded \n";
	//	cout << "j->Name: "; j->PrintName();
	//	cout << "j name : " << TYPEID( *j ).Name() << endl;
	//	cout << "j hash : " << TYPEID( *j ).HashCode() << endl << endl;
	//	delete j;
	//} else {
	//	cout << "B* j =  DYNAMIC_CAST( B*, NEW( C, j ) ) failed \n";
	//}

	//auto tt = NEW( C, tt );
	//A* t = DYNAMIC_CAST( A*, tt, t );
	//if( t ) {
	//	cout << "A* t =  DYNAMIC_CAST( A*, NEW( C, t ) ) succeded \n";
	//	cout << "t->Name: "; t->PrintName();
	//	cout << "t name : " << TYPEID( *t ).Name() << endl;
	//	cout << "t hash : " << TYPEID( *t ).HashCode() << endl << endl;
	//	delete t;
	//} else {
	//	cout << "A* t =  DYNAMIC_CAST( A*, NEW( C, t ) ) failed \n";
	//}

	auto ff = NEW( D, ff );
	cout << sizeof( A ) << ' ' << sizeof( B ) << ' ' << sizeof( C ) << ' ' << sizeof( D ) << endl;
	cout << sizeof( "A" ) << ' ' << sizeof( "B" ) << ' ' << sizeof( "C" ) << ' ' << sizeof( "D" ) << endl;
	//cout << ff << ' ' << sizeof( *ff ) << endl;
	//for( int i = 0; i < 10; i++ ) {
	//	cout << ff + i << ' ' << *( (int*)ff + i ) << endl;
	//}
	//ff->PrintName();
	// 00D00910 - начало объекта и начало A
	// 00¬0092— - начало B
	// 
	//
	//


	////bool flag = ( RTTI.find( string("ff") ) != RTTI.end() );
	////string name = ( RTTI.find( string("ff") )->second ).Name();
	////bool falg = ( ANCESTORS[( RTTI.find( string( "ff" ) )->second ).Name()].find( string( "B*" ) ) != ANCESTORS[( RTTI.find( string( "ff" ) )->second ).Name()].end() );
	////bool glaf = regObj( string( "ff" ), string( "f" ) );
	//B* f = DYNAMIC_CAST( B*, ff, f );
	//if( f ) {
	//	cout << "B* f =  DYNAMIC_CAST( B*, NEW( D, f ) ) succeded \n";
	//	cout << "f->Name: "; f->PrintName();
	//	cout << "f name : " << TYPEID( *f ).Name() << endl;
	//	cout << "f ptr : " << f << endl;
	//	cout << "sizeof(f) : " << sizeof( *f ) << endl << endl;
	//	//cout << "f hash : " << TYPEID( *f ).HashCode() << endl << endl;
	//	//delete f;
	//} else {
	//	cout << "B* f =  DYNAMIC_CAST( B*, NEW( D, f ) ) failed \n";
	//}

	//auto rr = NEW( D, rr );
	C* r = DYNAMIC_CAST( C*, ff, r );
	if( r ) {
		cout << ff << ' ' << sizeof( *ff ) << endl;
		cout << r << ' ' << sizeof( *r ) << endl;
		cout << "C* r =  DYNAMIC_CAST( C*, NEW( D, r ) ) succeded \n";
		cout << "r name : " << TYPEID( *r ).Name() << endl;
		cout << "r ptr : " << r << endl;
		cout << "sizeof(r) : " << sizeof( *r ) << endl << endl;
		//delete r;
	} else {
		cout << "C* r =  DYNAMIC_CAST( C*, NEW( D, r ) ) failed \n";
	}

	//------------------------------------------------------------------------------------------
	// дальше идут касты которые нельз€ делать, соответственно они падают

		//auto ff = NEW( A, ff );
		//B* f( 0 );
		//try {
		//	f = DYNAMIC_CAST( B*, ff ); // так нельз€
		//}
		//catch( exception& e ) {
		//	cout << "Exception: " << e.what() << endl;
		//}
		//if( f ) {
		//	cout << "B* f =  DYNAMIC_CAST( B*, NEW( A, f ) ) succeded \n";
		//	cout << "f->Name: "; f->PrintName();
		//	cout << "f name : " << TYPEID( *f ).Name() << endl;
		//	cout << "f hash : " << TYPEID( *f ).HashCode() << endl << endl;
		//	delete f;
		//} else {
		//	cout << "B* f =  DYNAMIC_CAST( B*, NEW( A, f ) ) failed \n";
		//}

		//auto gg = NEW( A, gg );
		////auto it = RTTI.find( "gg" );
		////assert( it != RTTI.end() );
		////auto iter = ANCESTORS[( RTTI.find( ( "gg" ) )->second ).Name()].find( ( "C*" ) );
		////assert( iter != ANCESTORS[( RTTI.find( ( "gg" ) )->second ).Name()].end() );
		//C* g = DYNAMIC_CAST( C*, gg ); // так нельз€
		//if( g ) {
		//	cout << "C* g =  DYNAMIC_CAST( C*, NEW( A, g ) ) succeded \n";
		//	cout << "g->Name: "; g->PrintName();
		//	cout << "g name : " << TYPEID( *g ).Name() << endl;
		//	cout << "g hash : " << TYPEID( *g ).HashCode() << endl << endl;
		//	delete g;
		//} else {
		//	cout << "C* g =  DYNAMIC_CAST( C*, NEW( A, g ) ) failed \n";
		//}

		//auto hh = NEW( B, hh );
		//C* h = DYNAMIC_CAST( C*, hh );
		//if( h ) {
		//	cout << "C* h =  DYNAMIC_CAST( C*, NEW( B, h ) ) succeded \n";
		//	cout << "h->Name: "; h->PrintName();
		//	cout << "h name : " << TYPEID( *h ).Name() << endl;
		//	cout << "h hash : " << TYPEID( *h ).HashCode() << endl << endl;
		//	delete h;
		//} else {
		//	cout << "C* h =  DYNAMIC_CAST( C*, NEW( B, h ) ) failed \n";
		//}

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

void trash()
{
	class Base0 {
		int field0;
		virtual int get()
		{
			return field0;
		}
	};

	class BaseA : public Base0 {
		int fieldA;
		virtual int get()
		{
			return fieldA;
		}
	};

	class BaseB : public Base0 {
		int fieldB;
		virtual int get()
		{
			return fieldB;
		}
	};

	class Derived : public BaseA, public BaseB {
		int fieldD;
		virtual int get()
		{
			return fieldD;
		}
	};

	class D : public Derived {
		int filed;
		virtual int get()
		{
			return filed;
		}
	};

	Derived* pDer = new Derived;
	BaseA* pBaseA = pDer;
	BaseB* pBaseB = pDer;

	if( pDer ) {
		cout << "pDer name : " << typeid( *pDer ).name() << " " << pDer << endl;
	}
	if( pBaseA ) {
		cout << "pBaseA name : " << typeid( *pBaseA ).name() << " " << pBaseA << endl;
	}
	if( pBaseB ) {
		cout << "pBaseB name : " << typeid( *pBaseB ).name() << " " << pBaseB << endl;
	}

	Derived* ptrA = new Derived;

	if( ptrA ) {
		cout << "ptrA name : " << typeid( *ptrA ).name() << " " << ptrA << endl;
	}

	BaseA* ptrD = dynamic_cast< BaseA* >( ptrA );
	if( ptrD ) {
		cout << "ptrD name : " << typeid( *ptrD ).name() << " " << ptrD << endl;
	} else {
		cout << "BaseA* ptrD = dynamic_cast< BaseA* >( ptrA ); failed" << endl;
	}

	BaseB* ptrDD = dynamic_cast< BaseB* >( ptrA );
	if( ptrDD ) {
		cout << "ptrDD name : " << typeid( *ptrDD ).name() << " " << ptrDD << endl;
	} else {
		cout << "BaseB* ptrDD = dynamic_cast< BaseB* >( ptrA ); failed" << endl;
	}

	cout << sizeof( BaseA ) << endl;
	cout << sizeof( BaseB ) << endl;
	cout << sizeof( *ptrA ) << endl;

	//D* pDer = new D;
	//BaseA* pBaseA = pDer;
	//BaseB* pBaseB = pDer;
	//Derived* pDerived = pDer;

	//cout << "pDer = " << pDer << endl;
	//cout << "pBaseA = " << pBaseA << endl;
	//cout << "pBaseB = " << pBaseB << endl;
	//cout << "pDerived = " << pDerived << endl;
}

void smthelse()
{

}

int main()
{
	//f();

	//fun(); cout << endl;
	//notFun(); cout << endl;

	//withRTTI(); cout << endl;
	withoutRTTI(); cout << endl; //<-закомменченные методы должны падать и собственно падают

	//veryNotFun();

	//trash();

	//smthelse();

	system( "pause" );
	return 0;
}