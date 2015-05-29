/*
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/
#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <vector>
#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "luacppinterface.h"

#include "AnimatedModel.h"
#include "Keyboard.h"
class LuaScript {
private:
	void L_Initialize();
	UINT mKey;
public:
	void setLuaVariable( std::string name, int value );
	void setLuaVariable( std::string name, std::string value );
	void setLuaVariable( std::string name, float value );
	void ietsMetKey( Library::Keyboard* board );
	LuaScript( int ok );
	LuaScript( const std::string& filename, bool stfs = false );
	~LuaScript();
	void printError( const std::string& variableName, const std::string& reason );
	std::vector<std::string> getArray( const std::string& name );
	std::vector<int> getIntVector( const std::string& name );
	std::vector<std::string> getTableKeys( const std::string& name );
	//void newCharacter(const std::string& filename, float xOffset, float yOffset, float zOffset, std::vector<GameComponent*> components, Camera* camera, Game* game);
	//static int l_newCharacter(const std::string& filename, float xOffset, float yOffset, float zOffset, std::vector<GameComponent*> components, Camera* camera, Game* game);
	void L_Update( float d );

	inline void clean()
	{
		int n = lua_gettop( L );
		lua_pop( L, n );
	}

	template<typename T>
	T get( const std::string& variableName )
	{
		if ( !L ) {
			printError( variableName, "Script is not loaded" );
			return lua_getdefault<T>();
		}

		T result;
		if ( lua_gettostack( variableName ) ) { // variable successfully on op of stack
			result = lua_get<T>( variableName );
		}
		else {
			result = lua_getdefault<T>();
		}

		clean();
		return result;
	}

	template<typename T>
	std::vector<T> getArray( const std::string& name )
	{
		std::vector<T> v;
		if ( !lua_gettostack( name.c_str() ) ) {
			printError( name, "Array not found" );
			clean();
			return std::vector<T>();
		}
		lua_pushnil( L );
		while ( lua_next( L, -2 ) ) {
			v.push_back( (T)lua_tonumber( L, -1 ) );
			lua_pop( L, 1 );
		}
		clean();
		return v;
	}

	bool lua_gettostack( const std::string& variableName )
	{
		level = 0;
		std::string var = "";
		for ( unsigned int i = 0; i < variableName.size(); i++ ) {
			if ( variableName.at( i ) == '.' ) {
				if ( level == 0 ) {
					lua_getglobal( L, var.c_str() );
				}
				else {
					lua_getfield( L, -1, var.c_str() );
				}
				if ( lua_isnil( L, -1 ) ) {
					printError( variableName, var + " is not defined" );
					return false;
				}
				else {
					var = "";
					level++;
				}
			}
			else {
				var += variableName.at( i );
			}
		}
		if ( level == 0 ) {
			lua_getglobal( L, var.c_str() );
		}
		else {
			lua_getfield( L, -1, var.c_str() );
		}
		if ( lua_isnil( L, -1 ) ) {
			printError( variableName, var + " is not defined" );
			return false;
		}

		return true;
	}
	// Generic get
	template<typename T>
	T lua_get( const std::string& variableName )
	{
		return 0;
	}

	template<typename T>
	T lua_getdefault()
	{
		return 0;
	}

private:
	lua_State* L;
	std::string filename;
	int level;
};

// Specializations

template <>
inline bool LuaScript::lua_get<bool>( const std::string& variableName )
{
	return (bool)lua_toboolean( L, -1 );
}

template <>
inline float LuaScript::lua_get<float>( const std::string& variableName )
{
	if ( !lua_isnumber( L, -1 ) ) {
		printError( variableName, "Not a number" );
	}
	return (float)lua_tonumber( L, -1 );
}

template <>
inline int LuaScript::lua_get<int>( const std::string& variableName )
{
	if ( !lua_isnumber( L, -1 ) ) {
		printError( variableName, "Not a number" );
	}
	return (int)lua_tonumber( L, -1 );
}

template <>
inline std::string LuaScript::lua_get<std::string>( const std::string& variableName )
{
	std::string s = "null";
	if ( lua_isstring( L, -1 ) ) {
		s = std::string( lua_tostring( L, -1 ) );
	}
	else {
		printError( variableName, "Not a string" );
	}
	return s;
}

template<>
inline std::string LuaScript::lua_getdefault<std::string>()
{
	return "null";
}
#endif