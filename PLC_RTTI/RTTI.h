#pragma once
#include <string>
#include <map>

using namespace std;

struct TypeInfo {
	TypeInfo( const string& theName ) : name( theName ) {}
	size_t HashCode() { return hash<string>()( name ); }
	string& Name() { return name; }
	
	string name;
};

static map<string, TypeInfo> RTTI;

void newObj( string typeName, string objName )
{
	TypeInfo typeInfo( typeName );
	RTTI.insert( pair<string, TypeInfo>( objName, typeInfo ) );
}

#define NEW(T, o) newObj((#T), (#o))
