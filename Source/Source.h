#ifndef __SOURCE__
#define __SOURCE__


#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>


using namespace std;

class CSource;

class CSourceData
{
private:
	int nId;   //资源编号
	int clubID;   //社团编号
	int sourceNum;  //资源数量
	std::string sName;   //资源名称
	std::string measureWord;//量词

public:
	CSourceData() { nId = 0; clubID = 0; sourceNum = 0; sName = "未命名"; }

public: //友元函数、友元类
	friend class CSource;
	//以下是用【友元函数】实现运算符重载

	//1、基本输入输出
	friend ostream& operator<<(ostream& os, const CSourceData& data);
	friend istream& operator>>(istream& is, CSourceData& data);

	//2、文件输入输出
	friend ofstream& operator<<(ofstream& os, const CSourceData& data);
	friend ifstream& operator>>(ifstream& is, CSourceData& data);
};


class CSource {
private:
	vector<CSourceData>aData;
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

	void deleteByClubID(int clubID);

	CSource();

	//写其他 成员函数：输入，输出，数据加工....曾、删、改、查

	static void showMenu();
};





#endif