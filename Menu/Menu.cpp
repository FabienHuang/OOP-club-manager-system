#include "Menu.h"
#include"windows.h"

void CMenu::showMenu(const vector<string>& aMenu) {
	clearScr();//��ʾ�˵�ǰ���� ����
	vector<string>::const_iterator it;
	for (it = aMenu.begin(); it < aMenu.end(); it++) {
		cout << it->c_str() << endl;
	}
}

//����
void CMenu::clearScr() {
	//ͨ���� ���� ָ��
	//cout<<"\033c"<<flush;
	system("cls");
}