#ifndef __MASSORG___
#define __MASSORG___
#include <string>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class CMassOrg; //类的前向申明

//社团数据
class OrgData {
private:
	int nId; //社团编号
	std::string sName;
	//添加 其他属性 ..
public:
	OrgData() { nId = 0; sName = "未命名"; }
public: //友元函数、友元类
	friend class CMassOrg;
	//以下是用【友元函数】实现运算符重载

	//1、基本输入输出
	friend ostream& operator<<(ostream& os, const OrgData& data);
	friend istream& operator>>(istream& is, OrgData& data);

	//2、文件输入输出
	friend ofstream& operator<<(ofstream& os, const OrgData& data);
	friend ifstream& operator>>(ifstream& is, OrgData& data);

};

class CMassOrg {
private:
	vector<OrgData>aData;
	string sFileName;
public:
	//根据菜单项 调用 对应的函数
	void control();

	void display();
	void addData();
	void saveData();
	void readData();

	void deleteData();
	void changeData();
	void findData();

	CMassOrg();

	//写其他 成员函数：输入，输出，数据加工....曾、删、改、查

	static void showMenu();
};


#endif
