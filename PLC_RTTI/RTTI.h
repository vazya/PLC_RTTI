#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

struct TypeInfo {
	TypeInfo( string typeName = string( "" ) ) : name( typeName ) {}
	size_t HashCode() { return hash<string>()( name ); }
	string& Name() { return name; }
	
	string name;
};
TypeInfo TypeId( string objName );


static map<string, TypeInfo> RTTI;
static map<string, set<string>> ANCESTORS;
static map<string, vector<string>> ANCESTORSORDERS;
static map<string, int> SIZEOFTYPES;

template<typename T>
static void regAncestorsOrder( string derived, string base )
{
	auto it = ANCESTORSORDERS.find( derived );
	vector<string> ancestorsoOrders;
	if( it == ANCESTORSORDERS.end() ) {
		ANCESTORSORDERS.insert( pair<string, vector<string>>( derived, vector<string>( { base } ) ) );
	} else {
		it->second.push_back( base );
	}
	SIZEOFTYPES.insert( pair<string, int>( base, sizeof( T ) ) );
}

int getSizeOfType( string typeName )
{
	auto it = SIZEOFTYPES.find( typeName );
	if( it == SIZEOFTYPES.end() ) {
		cout << "ERROR in getSizeOfType! Can't find typeName" << endl;
	}
	return it->second;
}

int stride( string objName, string typeName )
{
	typeName.erase( typeName.size() - 1 );	
	string objType( TypeId( objName ).Name() );

	auto it = ANCESTORSORDERS.find( objType );
	if( it == ANCESTORSORDERS.end() ) {
		return 0;
	}
	vector<string> ancestorsOrder( it->second );
	int matchParent = 0;
	for( int i = 0; i < ancestorsOrder.size(); i++ ) {
		if( typeName == ancestorsOrder[i] ) {
			matchParent = i;
		}
	}
	int byteShift = 0;
	if( matchParent != 0 ) {
		string parent = ancestorsOrder[matchParent];
		byteShift = getSizeOfType( parent );
	}
	int shift = byteShift / sizeof( int );
	return byteShift / sizeof(int);
}

static void regAncestors( string derived, string base )
{
	if( ANCESTORS.find( base ) == ANCESTORS.end() ) {
		ANCESTORS.insert( pair<string, set<string>>( base, set<string>( { base + '*' } ) ) );
	}
	if( ANCESTORS.find( derived ) == ANCESTORS.end() ) {
		ANCESTORS.insert( pair<string, set<string>>( derived, set<string>( { derived + '*' } ) ) );
	}

	auto baseAncestros = ANCESTORS[base];
	auto derivedAncestors = ANCESTORS.find(derived);
	for( auto it = baseAncestros.begin(); it != baseAncestros.end(); it++ ) {
		derivedAncestors->second.insert( *it );
	}
	derivedAncestors->second.insert( base + '*' );
}

TypeInfo TypeId( string objName )
{
	return RTTI[objName];
}

static bool regObj( string objName, string newObjName )
{
	string typeName = TypeId( objName ).Name();
	TypeInfo typeInfo( typeName );
	RTTI.insert( pair<string, TypeInfo>( "*" + newObjName, typeInfo ) );
	return true;
}

template<typename T>
static T* newObj( string typeName, string objName )
{
	TypeInfo typeInfo( typeName );
	//RTTI.insert( pair<string, TypeInfo>( "*" + objName, typeInfo ) );
	RTTI.insert( pair<string, TypeInfo>( objName, typeInfo ) );
	return new T();
}

// нужно в качестве параметра передавать имя объекта
#define NEW( T, o ) newObj<T>( (#T), (#o) )

#define TYPEID( o ) TypeId( (#o) )

#define DYNAMIC_CAST( T, o, n ) ( assert( RTTI.find( (#o) ) != RTTI.end() ),\
assert( ANCESTORS[(RTTI.find( (#o) )->second).Name()].find( (#T) ) != ANCESTORS[(RTTI.find( (#o) )->second).Name()].end() ),\
assert( regObj( (#o), (#n) ) ),\
reinterpret_cast<T>( o + stride( (#o), (#T) ) ) )

//#define DYNAMIC_CAST( T, o, n ) ( assert( RTTI.find( (#o) ) != RTTI.end() ),\
//assert( ANCESTORS[(RTTI.find( (#o) )->second).Name()].find( (#T) ) != ANCESTORS[(RTTI.find( (#o) )->second).Name()].end() ),\
//assert( regObj( (#o), (#n) ) ),\
//reinterpret_cast<T>( o ) )

#define EXTEND( D, B ) regAncestors( (#D), (#B) )
#define EXTENDORDER(D, B) regAncestorsOrder<B>( (#D), (#B) )