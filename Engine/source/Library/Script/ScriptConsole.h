/**
 * ScriptConsole.h
 *
 *  Created on: May 8, 2012
 *      Author: ukaku
 */

#ifndef SCRIPTCONSOLE_H_
#define SCRIPTCONSOLE_H_

#include <iostream>
#include <sstream>

using namespace std;


class ScriptConsole {
public:
	ScriptConsole();

	static void print(string msg);
	static string toString(double number);
	virtual ~ScriptConsole();
};

#endif /* SCRIPTCONSOLE_H_ */
