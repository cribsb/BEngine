/**
 * ScriptError.h
 *
 *  Created on: Apr 30, 2012
 *      Author: ukaku
 */

#ifndef SCRIPTERROR_H_
#define SCRIPTERROR_H_

using namespace std;

#include <iostream>

class ScriptError {
public:
	ScriptError();

	static void msg(string event);
	virtual ~ScriptError();
};

#endif /* SCRIPTERROR_H_ */
