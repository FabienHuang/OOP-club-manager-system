#ifndef __MASSORG___
#define __MASSORG___
#include <string>
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

class CMassOrg; //���ǰ������

//��������
class OrgData {
private:
	int nId; //���ű��
	std::string sName;
	//��� �������� ..
public:
	OrgData() { nId = 0; sName = "δ����"; }
public: //��Ԫ��������Ԫ��
	friend class CMassOrg;
	//�������á���Ԫ������ʵ�����������

	//1�������������
	friend ostream& operator<<(ostream& os, const OrgData& data);
	friend istream& operator>>(istream& is, OrgData& data);

	//2���ļ��������
	friend ofstream& operator<<(ofstream& os, const OrgData& data);
	friend ifstream& operator>>(ifstream& is, OrgData& data);

};

class CMassOrg {
private:
	vector<OrgData>aData;
	string sFileName;
public:
	//���ݲ˵��� ���� ��Ӧ�ĺ���
	void control();

	void display();
	void addData();
	void saveData();
	void readData();

	void deleteData();
	void changeData();
	void findData();

	CMassOrg();

	//д���� ��Ա���������룬��������ݼӹ�....����ɾ���ġ���

	static void showMenu();
};


#endif
