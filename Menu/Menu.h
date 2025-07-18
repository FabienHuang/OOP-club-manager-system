//必须设置【条件编译】
#ifndef __MENU___
#define __MENU___

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <conio.h> //设备输入输出头。用于获取键盘事件且不回显

using namespace std;
class CMenu{
public:
	static void showMenu(const vector<string> &aMenu);

	//清屏
	static void clearScr();
};


#endif