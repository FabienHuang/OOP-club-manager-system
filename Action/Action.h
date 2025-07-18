#ifndef __ACTION__
#define __ACTION__

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>


using namespace std;

class CAction;

class CActionData
{
private:
	int nId;   //活动编号
	int clubID;   //社团编号
	std::string sName;   //活动名称

public:
	CActionData() { nId = 0; clubID = 0; sName = "未命名"; }

public: //友元函数、友元类
	friend class CAction;
	//以下是用【友元函数】实现运算符重载

	//1、基本输入输出
	friend ostream& operator<<(ostream& os, const CActionData& data);
	friend istream& operator>>(istream& is, CActionData& data);

	//2、文件输入输出
	friend ofstream& operator<<(ofstream& os, const CActionData& data);
	friend ifstream& operator>>(ifstream& is, CActionData& data);
};

class CActionMemData
{
private:
	int nId;   //活动编号
	int clubID;   //社团编号
	std::string sName;   //活动参与者名称

public:
	CActionMemData() { nId = 0; clubID = 0; sName = "未命名"; }

public: //友元函数、友元类
	friend class CAction;
	//以下是用【友元函数】实现运算符重载

	//1、基本输入输出
	friend ostream& operator<<(ostream& os, const CActionMemData& data);
	friend istream& operator>>(istream& is, CActionMemData& data);

	//2、文件输入输出
	friend ofstream& operator<<(ofstream& os, const CActionMemData& data);
	friend ifstream& operator>>(ifstream& is, CActionMemData& data);
};


class CAction {
private:
	vector<CActionData>aData;
	string sFileName;
	string sFileNameForMem;  //参加活动的成员名单文件名
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

	void displayForN();

	void deleteByClubID(int clubID);

	CAction();

	//写其他 成员函数：输入，输出，数据加工....曾、删、改、查

	static void showMenu();
};



#endif








