/*
 * action.cpp
 * Action library is a framework to add multiple functions in Arduino
 * loop via callback functions of menu (including user defined programs)
 * and running multiple function in background. An array actionFuncList 
 * stores the pointer of function(s) to be executed in Arduino loop everytime.
 * actionFuncList is a pointer to a function.
 * 
 * This is licensed under GNU GPL V3 [http://www.gnu.org/licenses/gpl.txt].
 * Written by Dhrupal R Shah for evive platform, Agilo Research.
 * Contact: support@evive.cc
 * Copyright (c) 2017 Agilo Research.  All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include "Action.h"

actionFunc actionFuncList[7] = { };//maximum 7 functions, mofidy to increase size
uint8_t actionFuncListNum = 0;			//must be greater than or equals to 0

//for avoiding multiple includes of same function for multiple times in one loop
//if flag = 1, checks for repetition
void actionAdd(actionFunc addFun, bool flag) {
	if (flag) {
		for (uint8_t i = 0; i < actionFuncListNum; i++) {
			if (actionFuncList[i] == addFun)
				return;
		}
	}
	actionFuncList[actionFuncListNum++] = addFun;
#ifdef __DEBUG__
	Serial.print("funList: ");
	Serial.println(actionFuncListNum);
#endif
	return;
}

void actionAdd(actionFunc addFun) {
	actionFuncList[actionFuncListNum++] = addFun;
#ifdef __DEBUG__
	Serial.print("funList: ");
	Serial.println(actionFuncListNum);
#endif
	return;
}

void actionRemove(actionFunc removeFun) {
	for (uint8_t i = 0; i < actionFuncListNum; i++) {
		if (actionFuncList[i] == removeFun) {
			for (; i < actionFuncListNum - 1; i++)
				actionFuncList[i] = actionFuncList[i + 1];
			actionFuncListNum--;
			return;						//remove single entry of same function
		}
	}
}

void actionRemove(uint8_t removeFunNum) {
	for (uint8_t i = removeFunNum; i < actionFuncListNum - 1; i++)
		actionFuncList[i] = actionFuncList[i + 1];
	actionFuncListNum--;
}

void actionRemoveAll() {
	actionFuncListNum = 0;
}

void action() {
//	Serial.println(actionFuncListNum);
	for (uint8_t i = 0; i < actionFuncListNum; i++) {
		(*actionFuncList[i])();
	}
}
