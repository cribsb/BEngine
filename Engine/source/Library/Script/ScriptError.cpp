/**
 * ScriptError.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: ukaku
 */

#include "ScriptError.h"
#include <string>

ScriptError::ScriptError() {
	// TODO Auto-generated constructor stub

}

void ScriptError::msg(string event) {
	cout << "ScriptRuntimeError: " << event << endl;
}

ScriptError::~ScriptError() {
	// TODO Auto-generated destructor stub
}

