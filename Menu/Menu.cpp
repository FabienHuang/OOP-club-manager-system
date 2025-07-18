#include "Menu.h"
#include"windows.h"

void CMenu::showMenu(const vector<string>& aMenu) {
	clearScr();//显示菜单前，先 清屏
	vector<string>::const_iterator it;
	for (it = aMenu.begin(); it < aMenu.end(); it++) {
		cout << it->c_str() << endl;
	}
}

//清屏
void CMenu::clearScr() {
	//通用型 清屏 指令
	//cout<<"\033c"<<flush;
	system("cls");
}