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
#include "LuaScript.h"
#include "Keyboard.h"
#include "GameComponent.h"

UINT mmKey;
Keyboard* mKeyboard;

HKL currentHKL = GetKeyboardLayout(0);

void LuaScript::ietsMetKey(Keyboard* board)
{
	mKeyboard = board;
}

void write(const char* msg)
{
	printf(msg);
	printf("\n");
}

static int l_write(lua_State* L)
{
	const char* str = lua_tostring(L, 1);
	write(str);
	return 0;
}

static int l_checkInput(lua_State* L)
{
	std::string key = lua_tostring(L, 1);
	
	if (mKeyboard->IsKeyDownC(key))
	{
		lua_pushnumber(L, 1);
	}
	else
	{
		lua_pushnumber(L, 0);
	}
	return 1;
}

void LuaScript::L_Initialize()
{
	lua_getglobal(L, "Initialize");

	lua_pcall(L, 0, 0, 0);
}

void LuaScript::L_Update(float d)
{
	lua_getglobal(L, "Update");
	lua_pushnumber(L, d);
	lua_pcall(L, 1, 0, 0);
}

LuaScript::LuaScript(const std::string& filename, bool stfs) {
	L = luaL_newstate();


	if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0)) {
		std::cout << "Error: failed to load (" << filename << ")" << std::endl;
		L = 0;
	}

	if (L) luaL_openlibs(L);

	if (stfs)
	{
		L_Initialize();
		std::cout << "call" << std::endl;
	}

	lua_pushcfunction(L, l_checkInput);
	lua_setglobal(L, "keyPressed");

	lua_pushcfunction(L, l_write);
	lua_setglobal(L, "write");
	lua_pcall(L, 0, 0, 0);
}

LuaScript::LuaScript(int ok)
{

}

LuaScript::~LuaScript() {
	if (L) lua_close(L);
}

extern "C" int newCharacter(lua_State* L)
{
	return 0;
}

void LuaScript::printError(const std::string& variableName, const std::string& reason) {
	std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
}

std::vector<std::string> LuaScript::getArray(const std::string& name) {
	std::vector<std::string> v;
	if (!lua_gettostack(name.c_str())) {
		printError(name, "Array not found");
		clean();
		return std::vector<std::string>();
	}
	lua_pushnil(L);
	while (lua_next(L, -2)) {
		v.push_back(std::string(lua_tostring(L, -1)));
		lua_pop(L, 1);
	}
	clean();
	return v;
}


std::vector<int> LuaScript::getIntVector(const std::string& name) {
	std::vector<int> v;
	lua_gettostack(name.c_str());
	if (lua_isnil(L, -1)) { // array is not found
		return std::vector<int>();
	}
	lua_pushnil(L);
	while (lua_next(L, -2)) {
		v.push_back((int)lua_tonumber(L, -1));
		lua_pop(L, 1);
	}
	clean();
	return v;
}

std::vector<std::string> LuaScript::getTableKeys(const std::string& name) {
	std::string code =
		"function getKeys(name) "
		"s = \"\""
		"for k, v in pairs(_G[name]) do "
		"    s = s..k..\",\" "
		"    end "
		"return s "
		"end"; // function for getting table keys
	luaL_loadstring(L,
		code.c_str()); // execute code
	lua_pcall(L, 0, 0, 0);
	lua_getglobal(L, "getKeys"); // get function
	lua_pushstring(L, name.c_str());
	lua_pcall(L, 1, 1, 0); // execute function
	std::string test = lua_tostring(L, -1);
	std::vector<std::string> strings;
	std::string temp = "";
	std::cout << "TEMP:" << test << std::endl;
	for (unsigned int i = 0; i < test.size(); i++) {
		if (test.at(i) != ',') {
			temp += test.at(i);
		}
		else {
			strings.push_back(temp);
			temp = "";
		}
	}
	clean();
	return strings;
}