//�������á��������롿
#ifndef __MENU___
#define __MENU___

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <conio.h> //�豸�������ͷ�����ڻ�ȡ�����¼��Ҳ�����

using namespace std;
class CMenu{
public:
	static void showMenu(const vector<string> &aMenu);

	//����
	static void clearScr();
};


#endif