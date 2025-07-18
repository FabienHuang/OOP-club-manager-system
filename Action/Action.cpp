#include "Action.h"
#include "../Menu/Menu.h"

//1、基本输入输出
ostream& operator<<(ostream& os, const CActionData& data) {
	os << data.clubID<< "\t"<<  data.nId << "\t" <<data.sName.c_str() << "\t" << endl;
	return os;
}

istream& operator>>(istream& is, CActionData& data) {
	is >> data.clubID;
	if (data.clubID <= 0) {//输入的编号 <= 0 表示结束输入
		return is;
	}
	is >> data.nId;
	is >> data.sName;	
	
	return is;
}

//2、文件输入输出(活动名称）
ofstream& operator<<(ofstream& os, const CActionData& data) {
	os << data.clubID << "\t" <<data.nId << "\t" << data.sName << "\t" << endl;//实际是写 文件
	return os;
}

ifstream& operator>>(ifstream& is, CActionData& data) {
	is >> data.clubID>>data.nId >> data.sName;//读取文件数据 到 data 中
	return is;
}

//活动参与者名称
ofstream& operator<<(ofstream& os, const CActionMemData& data) {
	os << data.clubID << "\t" << data.nId << "\t" << data.sName << "\t" << endl;//实际是写 文件
	return os;
}

ifstream& operator>>(ifstream& is, CActionMemData& data) {
	is >> data.clubID >> data.nId >> data.sName;//读取文件数据 到 data 中
	return is;
}

//---------------------------------
/**********************************
   CAction 开始定义
***********************************/
//---------------------------------
//根据菜单项 调用 对应的函数
void CAction::control() {
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
		case '4'://修改
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

void CAction::showMenu() {
	vector<string> aMenu;
	aMenu.push_back("1、添加活动信息");
	aMenu.push_back("2、显示活动信息");
	aMenu.push_back("3、查找活动信息");
	aMenu.push_back("4、修改活动信息");
	aMenu.push_back("5、删除活动");
	aMenu.push_back("6、保存数据");
	//.........
	aMenu.push_back("Esc 返回主菜单");

	CMenu::showMenu(aMenu);
}

void CAction::display() {
	cout << "请输入社团编号（输入666表示显示全部活动）：";
	int clubID;
	cin >> clubID;

	cout << endl;

	if (clubID == 666) {
		cout << "共有 " << aData.size() << " 条活动记录" << endl;
		cout << "从左到右分别为社团编号、活动编号、活动名称" << endl;
		for (const auto& data : aData) {
			cout << data;
		}
	}
	else {
		int count = 0;
		cout << "社团编号为 " << clubID << " 的活动记录如下：" << endl;
		cout << "从左到右分别为社团编号、活动编号、活动名称" << endl;

		for (const auto& data : aData) {
			if (data.clubID == clubID) {
				cout << data;
				count++;
			}
		}

		if (count == 0) {
			cout << "未找到该社团的活动记录。" << endl;
		}
	}

	cout << endl << "按任意键返回..." << endl;
	_getch();
}


void CAction::displayForN() {    //这个函数是为后续的普通成员显示和参加活动做准备
	cout << "请输入社团编号：";
	int clubID;
	cin >> clubID;

	cout << endl;

		int count = 0;
		cout << "社团编号为 " << clubID << " 的活动记录如下：" << endl;
		cout << "从左到右分别为社团编号、活动编号、活动名称" << endl;

		for (const auto& data : aData) {
			if (data.clubID == clubID) {
				cout << data;
				count++;
			}
		}

		if (count == 0) {
			cout << "未找到该社团的活动记录。" << endl;
		}

		cout << "请输入想要参加的活动编号:" << endl;
		int getId;
		cin >> getId;

		for (const auto& data : aData) {
			if (data.clubID == clubID && data.nId == getId) {
				CActionMemData memData;
				memData.clubID = clubID;
				memData.nId = getId;
				cout << "请输入您的姓名：";
				cin >> memData.sName;

				ofstream fout("cactionmemdata.txt", ios::app);
				if (fout.is_open()) {
					fout << memData;
					fout.close();
					cout << "报名信息已保存到文件。" << endl;
				}
				else {
					cout << "保存失败，无法打开文件！" << endl;
				}


				cout << "您已成功参加活动：" << data.sName << endl;
				break;
			}
		}

	cout << endl << "按任意键返回..." << endl;
	_getch();
}


void CAction::addData() {
	cout << "请分别输入社团编号、活动编号、活动名称（输入社团编号 <= 0 终止输入）" << endl;

	while (true) {
		CActionData data;
		cin >> data;

		if (data.clubID <= 0) {
			return;
		}

		// 检查活动编号是否重复,每个活动编号都是独一无二的
		bool exists = false;
		for (const auto& item : aData) {
			if (item.nId == data.nId) {
				cout << "活动编号 " << data.nId << " 已存在，请重新输入一个不同的活动编号。" << endl;
				exists = true;
				break;
			}
		}

		if (exists) {
			continue; // 如果重复，则重新输入
		}

		aData.push_back(data);
		cout << "添加成功！继续输入或输入社团编号 <= 0 结束添加。" << endl;
	}
}


void CAction::saveData() {
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

	cout << "共保存了 " << aData.size() << " 条活动数据到文件中" << endl;
	_getch();
}

void CAction::readData() {
	ifstream file(sFileName.c_str());

	if (!file) {
		string s;
		s = "打开文件失败：" + sFileName;
		throw s.c_str();
	}

	CActionData data;
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
	cout << "共读取 " << aData.size() << " 条活动数据" << endl;
}

void CAction::deleteData() {
	cout << "请输入要删除的活动编号：";
	int nId;
	cin >> nId;

	int count = 0;
	for (auto it = aData.begin(); it != aData.end(); ) {
		if (it->nId == nId) {
			it = aData.erase(it);
			count++;
		}
		else {
			++it;
		}
	}

	if (count > 0) {
		saveData(); // 删除后保存
		cout << "已删除 " << count << " 条活动编号为 " << nId << " 的记录。" << endl;
	}
	else {
		cout << "没有找到该活动编号的记录。" << endl;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}


void CAction::changeData() {
	cout << "请输入要修改的活动编号：";
	int nId;
	cin >> nId;

	bool found = false;
	for (auto& data : aData) {
		if (data.nId == nId) {
			cout << "找到记录：" << data;
			cout << "请输入新的活动名称：";
			cin >> data.sName;
			found = true;
			break;
		}
	}

	if (found) {
		saveData();
		cout << "修改成功。" << endl;
	}
	else {
		cout << "未找到对应的活动编号。" << endl;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}

void CAction::findData() {
	cout << "您需要查找哪个社团的资源？请输入社团编号：";
	int clubID;
	cin >> clubID;

	cout << "请输入要查找的活动编号：";
	int nId;
	cin >> nId;

	bool found = false;
	for (const auto& data : aData) {
		if (data.clubID == clubID && data.nId == nId) {
			if (!found) {
				cout << "查找到的活动记录如下：" << endl;
			}
			cout << data;
			found = true;
		}
	}

	if (!found) {
		cout << "没有找到该社团编号和活动编号对应的记录。" << endl;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}


void CAction::deleteByClubID(int clubID) {
	int count = 0;
	for (auto it = aData.begin(); it != aData.end(); ) {
		if (it->clubID == clubID) {
			it = aData.erase(it);
			count++;
		}
		else {
			++it;
		}
	}
	saveData(); // 更新保存文件
	cout << "已删除社团编号为 " << clubID << " 的 " << count << " 条活动记录。" << endl;
}


CAction::CAction() {
	sFileName = "cactiondata.txt";
	sFileNameForMem = "cactionmemdata.txt"; // 参加活动的成员名单文件名

	readData();
}






