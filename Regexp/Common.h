#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

static inline void Write(string s)
{
	cout << s << endl;
}

static inline void WriteLine(string s)
{
	cout << s << endl;
}

static inline string ReadLine()
{
	string result;
	getline(cin, result);
	return result;
}
