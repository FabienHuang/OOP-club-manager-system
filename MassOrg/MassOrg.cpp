#include "MassOrg.h"
#include "../Menu/Menu.h"
#include"../Action/Action.h"
#include "../Member/Member.h"
#include "../Source/Source.h"


//1、基本输入输出
ostream& operator<<(ostream& os, const OrgData& data) {
	os << data.nId << "\t" << data.sName.c_str() << "\t" << endl;
	return os;
}

istream& operator>>(istream& is, OrgData& data) {
	is >> data.nId;
	if (data.nId <= 0) {//输入的编号 <= 0 表示结束输入
		return is;
	}
	is >> data.sName;
	return is;
}

//2、文件输入输出
ofstream& operator<<(ofstream& os, const OrgData& data) {
	os << data.nId << "\t" << data.sName << "\t" << endl;//实际是写 文件
	return os;
}

ifstream& operator>>(ifstream& is, OrgData& data) {
	is >> data.nId >> data.sName;//读取文件数据 到 data 中
	return is;
}

//---------------------------------
/**********************************
   CMassOrg 开始定义
***********************************/
//---------------------------------
//根据菜单项 调用 对应的函数
void CMassOrg::control() {
	while (true) {
		showMenu();//显示菜单
		int nKey = _getch(); //等候用户选择
		CMenu::clearScr(); //清屏

		switch (nKey) {
		case '1': //添加
			addData();
			break;
		case '2'://显示
			display();
			break;
		case '3'://查找
			findData();
			break;
		case '4'://改变名称
			changeData();
			break;
		case '5'://删除
			deleteData();
			break;
		case '6'://保存
			saveData();
			break;
		case 27: //返回
			return;
		}
	}
}

void CMassOrg::showMenu() {
	vector<string> aMenu;
	aMenu.push_back("1、添加社团信息");
	aMenu.push_back("2、显示社团信息");
	aMenu.push_back("3、查找社团");
	aMenu.push_back("4、改变社团名称");
	aMenu.push_back("5、删除社团");
	aMenu.push_back("6、保存数据");

	aMenu.push_back("Esc 返回主菜单");

	CMenu::showMenu(aMenu);
}

void CMassOrg::display() {
	cout << "共有 " << aData.size() << " 条社团记录" << endl;
	cout << endl;
	cout << "从左到右分别为社团编号、社团名称" << endl;
	cout << endl;
	vector<OrgData>::const_iterator it;
	for (it = aData.begin(); it < aData.end(); it++) {
		cout << *it;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}

void CMassOrg::addData() {
	cout << "请输入社团编号和名称（编号<=0 则终止输入）：" << endl;

	OrgData data;
	while (true) {
		cin >> data;
		if (data.nId <= 0) {
			break;
		}

		// 检查编号是否重复
		bool exists = false;
		for (const auto& d : aData) {
			if (d.nId == data.nId) {
				exists = true;
				break;
			}
		}

		if (exists) {
			cout << "该编号已存在，请重新输入：" << endl;
			continue;
		}

		aData.push_back(data);
		cout << "添加成功。继续输入下一个社团（或输入编号<=0 结束）：" << endl;
	}
}



void CMassOrg::saveData() {
	ofstream file(sFileName.c_str());
	if (!file) {
		string s;
		s = "打开文件失败：" + sFileName;
		throw s.c_str();
	}

	//不用迭代器，用[]
	for (int i = 0; i < aData.size(); i++) {
		file << aData[i];
	}

	file.close();

	cout << "共保存了 " << aData.size() << " 条社团数据到文件中" << endl;
	_getch();
}

void CMassOrg::readData() {
	ifstream file(sFileName.c_str());

	if (!file) {
		string s;
		s = "打开文件失败：" + sFileName;
		throw s.c_str();
	}

	OrgData data;
	while (!file.eof()) {
		file >> data;
		if (file.fail()) {//避免 最后一行 读 2 次
			break;
		}
		else {
			aData.push_back(data);
		}
	}

	file.close();
	cout << "共读取 " << aData.size() << " 条社团数据" << endl;
}

void CMassOrg::deleteData() {
	int idToDelete;
	cout << "请输入要删除的社团编号：";
	cin >> idToDelete;

	bool found = false;
	for (auto it = aData.begin(); it != aData.end(); ++it) {
		if (it->nId == idToDelete) {
			aData.erase(it);
			found = true;
			break;
		}
	}

	if (found) {
		saveData(); // 删除社团后保存
		cout << "社团删除成功。" << endl;

		CAction action;
		action.deleteByClubID(idToDelete);

		CSource source;
		source.deleteByClubID(idToDelete);

		//这里还要完成成员的联动删除
	}
	else {
		cout << "未找到该编号的社团。" << endl;
	}

	_getch();
}


void CMassOrg::changeData() {
	int id;
	cout << "请输入要修改的社团编号：";
	cin >> id;

	bool found = false;
	for (auto& data : aData) {
		if (data.nId == id) {
			cout << "当前信息：" << endl;
			cout << data;

			cout << "请输入新的社团名称：";
			cin >> data.sName;

			cout << "修改成功。" << endl;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "未找到编号为 " << id << " 的社团。" << endl;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}

void CMassOrg::findData() {
	int id;
	cout << "请输入要查找的社团编号：";
	cin >> id;

	bool found = false;
	for (const auto& data : aData) {
		if (data.nId == id) {
			cout << "找到社团：" << endl;
			cout << data;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "未找到编号为 " << id << " 的社团。" << endl;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}


CMassOrg::CMassOrg() {
	sFileName = "orgdata.txt";

	readData();
}