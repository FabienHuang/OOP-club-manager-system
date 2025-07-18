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
	int nId;   //��Դ���
	int clubID;   //���ű��
	int sourceNum;  //��Դ����
	std::string sName;   //��Դ����
	std::string measureWord;//����

public:
	CSourceData() { nId = 0; clubID = 0; sourceNum = 0; sName = "δ����"; }

public: //��Ԫ��������Ԫ��
	friend class CSource;
	//�������á���Ԫ������ʵ�����������

	//1�������������
	friend ostream& operator<<(ostream& os, const CSourceData& data);
	friend istream& operator>>(istream& is, CSourceData& data);

	//2���ļ��������
	friend ofstream& operator<<(ofstream& os, const CSourceData& data);
	friend ifstream& operator>>(ifstream& is, CSourceData& data);
};


class CSource {
private:
	vector<CSourceData>aData;
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

	void deleteByClubID(int clubID);

	CSource();

	//д���� ��Ա���������룬��������ݼӹ�....����ɾ���ġ���

	static void showMenu();
};





#endif