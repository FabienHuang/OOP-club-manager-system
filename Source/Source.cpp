#include "Source.h"
#include "../Menu/Menu.h"

//1、基本输入输出
ostream& operator<<(ostream& os, const CSourceData& data) {
	os << data.clubID << "\t" << data.nId << "\t"<<data.sourceNum<< data.measureWord.c_str() << data.sName.c_str() << "\t" << endl;
	return os;
}

istream& operator>>(istream& is, CSourceData& data) {
	is >> data.clubID;
	if (data.clubID <= 0) {//输入的编号 <= 0 表示结束输入
		return is;
	}
	is >> data.nId;

	is >> data.sourceNum;
	is >> data.measureWord;
	is >> data.sName;

	return is;
}

//2、文件输入输出
ofstream& operator<<(ofstream& os, const CSourceData& data) {
	os << data.clubID << "\t" << data.nId << "\t"
		<< data.sourceNum << "\t"
		<< data.measureWord << "\t"
		<< data.sName << endl;
	return os;
}


ifstream& operator>>(ifstream& is, CSourceData& data) {
	is >> data.clubID >> data.nId >> data.sourceNum;

	// 读取量词
	is >> ws; // 清除前导空白
	getline(is, data.measureWord, '\t'); // 以 tab 为分隔符

	// 读取资源名称
	getline(is, data.sName); // 读到行尾

	return is;
}


//---------------------------------
/**********************************
   CAction 开始定义
***********************************/
//---------------------------------
//根据菜单项 调用 对应的函数
void CSource::control() {
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

void CSource::showMenu() {
	vector<string> aMenu;
	aMenu.push_back("1、添加资源信息");
	aMenu.push_back("2、显示资源信息");
	aMenu.push_back("3、查找资源信息");
	aMenu.push_back("4、修改资源信息");
	aMenu.push_back("5、删除资源");
	aMenu.push_back("6、保存数据");
	aMenu.push_back("Esc 返回主菜单");

	CMenu::showMenu(aMenu);
}

void CSource::display() {
	cout << "请输入社团编号（输入 666 显示所有资源）：";
	int clubID;
	cin >> clubID;

	cout << endl;

	vector<CSourceData> toDisplay;

	if (clubID == 666) {
		toDisplay = aData; // 显示全部
	}
	else {
		// 筛选出该社团编号对应的资源
		for (const auto& item : aData) {
			if (item.clubID == clubID) {
				toDisplay.push_back(item);
			}
		}
	}

	if (toDisplay.empty()) {
		cout << "未找到该社团编号的资源记录。" << endl;
	}
	else {
		cout << "共有 " << toDisplay.size() << " 条资源记录" << endl << endl;
		cout << "从左到右分别为：社团编号、资源编号、资源数量+量词+资源名称" << endl << endl;

		for (const auto& item : toDisplay) {
			cout << item;
		}
	}

	cout << "按任意键返回..." << endl;
	_getch();
}



void CSource::addData() {
	cout << "请分别输入：社团编号、资源编号、资源数量、量词、资源名称（输入社团编号 <= 0 终止输入）" << endl;

	while (true) {
		CSourceData data;
		cin >> data;

		if (data.clubID <= 0) {
			return;
		}

		// 检查资源编号是否已存在
		bool exists = false;
		for (const auto& item : aData) {
			if (item.nId == data.nId) {
				cout << "资源编号 " << data.nId << " 已存在，请重新输入一个不同的资源编号。" << endl;
				exists = true;
				break;
			}
		}

		if (exists) {
			continue; // 资源编号重复，重新输入
		}

		aData.push_back(data);
		cout << "添加成功！请输入下一条记录，或输入社团编号 <= 0 结束添加。" << endl;
	}
}


void CSource::saveData() {
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

	cout << "共保存了 " << aData.size() << " 条资源数据到文件中" << endl;
	_getch();
}

void CSource::readData() {
	ifstream file(sFileName.c_str());

	if (!file) {
		string s;
		s = "打开文件失败：" + sFileName;
		throw s.c_str();
	}

	CSourceData data;
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
	cout << "共读取 " << aData.size() << " 条资源数据" << endl;
	_getch();
}

void CSource::deleteData() {
	cout << "请输入要删除的资源编号：";
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
		cout << "已删除 " << count << " 条资源编号为 " << nId << " 的记录。" << endl;
	}
	else {
		cout << "没有找到该资源编号的记录。" << endl;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}


void CSource::changeData() {
	cout << "请输入要修改的资源编号：";
	int nId;
	cin >> nId;

	bool found = false;
	for (auto& data : aData) {
		if (data.nId == nId) {
			cout << "找到记录：" << data;
			cout << "请输入新的资源数量：";
			cin >> data.sourceNum;

			cout << "请输入新的量词：";
			cin >> data.measureWord;

			cout << "请输入新的资源名称：";
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
		cout << "未找到对应的资源编号。" << endl;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}


void CSource::findData() {
	cout << "您需要查找哪个社团的资源？请输入社团编号：";
	int clubID;
	cin >> clubID;

	cout << "请输入要查找的资源编号：";
	int nId;
	cin >> nId;

	bool found = false;
	for (const auto& data : aData) {
		if (data.clubID == clubID && data.nId == nId) {
			if (!found) {
				cout << "查找到的资源记录如下：" << endl;
			}
			cout << data;
			found = true;
		}
	}

	if (!found) {
		cout << "没有找到该社团编号和活动编号对应的资源记录。" << endl;
	}

	cout << "按任意键返回..." << endl;
	_getch();
}


void CSource::deleteByClubID(int clubID) {
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
	cout << "已删除社团编号为 " << clubID << " 的 " << count << " 条资源记录。" << endl;
}



CSource::CSource() {
	sFileName = "csourcedata.txt";

	readData();
}







