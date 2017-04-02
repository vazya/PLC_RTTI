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
	//return TypeInfo();
	return RTTI[objName];
}

void newObj( string typeName, string objName )
{
	TypeInfo typeInfo( typeName );
	RTTI.insert( pair<string, TypeInfo>( objName, typeInfo ) );
}

#define NEW(T, o) newObj((#T), (#o))

#define TYPEID(o) TypeId((#o))