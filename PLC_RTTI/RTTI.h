#pragma once
#include <string>
#include <map>

using namespace std;

struct TypeInfo {
	TypeInfo( string typeName = string( "" ) ) : name( typeName ) {}
	size_t HashCode() { return hash<string>()( name ); }
	string& Name() { return name; }
	
	string name;
};

static map<string, TypeInfo> RTTI;

TypeInfo TypeId( string objName )
{
	return RTTI[objName];
}

template<typename T>
static T* newObj( string typeName, string objName )
{
	TypeInfo typeInfo( typeName );
	RTTI.insert( pair<string, TypeInfo>( objName, typeInfo ) );
	return new T();
}

// нужно в качестве параметра передавать имя объекта
#define NEW(T, o) newObj<T>((#T), (#o))

#define TYPEID(o) TypeId((#o))