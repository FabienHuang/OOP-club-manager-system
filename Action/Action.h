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
	int nId;   //����
	int clubID;   //���ű��
	std::string sName;   //�����

public:
	CActionData() { nId = 0; clubID = 0; sName = "δ����"; }

public: //��Ԫ��������Ԫ��
	friend class CAction;
	//�������á���Ԫ������ʵ�����������

	//1�������������
	friend ostream& operator<<(ostream& os, const CActionData& data);
	friend istream& operator>>(istream& is, CActionData& data);

	//2���ļ��������
	friend ofstream& operator<<(ofstream& os, const CActionData& data);
	friend ifstream& operator>>(ifstream& is, CActionData& data);
};

class CActionMemData
{
private:
	int nId;   //����
	int clubID;   //���ű��
	std::string sName;   //�����������

public:
	CActionMemData() { nId = 0; clubID = 0; sName = "δ����"; }

public: //��Ԫ��������Ԫ��
	friend class CAction;
	//�������á���Ԫ������ʵ�����������

	//1�������������
	friend ostream& operator<<(ostream& os, const CActionMemData& data);
	friend istream& operator>>(istream& is, CActionMemData& data);

	//2���ļ��������
	friend ofstream& operator<<(ofstream& os, const CActionMemData& data);
	friend ifstream& operator>>(ifstream& is, CActionMemData& data);
};


class CAction {
private:
	vector<CActionData>aData;
	string sFileName;
	string sFileNameForMem;  //�μӻ�ĳ�Ա�����ļ���
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

	void displayForN();

	void deleteByClubID(int clubID);

	CAction();

	//д���� ��Ա���������룬��������ݼӹ�....����ɾ���ġ���

	static void showMenu();
};



#endif








