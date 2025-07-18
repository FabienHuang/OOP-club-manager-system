#include "MassOrg.h"
#include "../Menu/Menu.h"
#include"../Action/Action.h"
#include "../Member/Member.h"
#include "../Source/Source.h"


//1�������������
ostream& operator<<(ostream& os, const OrgData& data) {
	os << data.nId << "\t" << data.sName.c_str() << "\t" << endl;
	return os;
}

istream& operator>>(istream& is, OrgData& data) {
	is >> data.nId;
	if (data.nId <= 0) {//����ı�� <= 0 ��ʾ��������
		return is;
	}
	is >> data.sName;
	return is;
}

//2���ļ��������
ofstream& operator<<(ofstream& os, const OrgData& data) {
	os << data.nId << "\t" << data.sName << "\t" << endl;//ʵ����д �ļ�
	return os;
}

ifstream& operator>>(ifstream& is, OrgData& data) {
	is >> data.nId >> data.sName;//��ȡ�ļ����� �� data ��
	return is;
}

//---------------------------------
/**********************************
   CMassOrg ��ʼ����
***********************************/
//---------------------------------
//���ݲ˵��� ���� ��Ӧ�ĺ���
void CMassOrg::control() {
	while (true) {
		showMenu();//��ʾ�˵�
		int nKey = _getch(); //�Ⱥ��û�ѡ��
		CMenu::clearScr(); //����

		switch (nKey) {
		case '1': //���
			addData();
			break;
		case '2'://��ʾ
			display();
			break;
		case '3'://����
			findData();
			break;
		case '4'://�ı�����
			changeData();
			break;
		case '5'://ɾ��
			deleteData();
			break;
		case '6'://����
			saveData();
			break;
		case 27: //����
			return;
		}
	}
}

void CMassOrg::showMenu() {
	vector<string> aMenu;
	aMenu.push_back("1�����������Ϣ");
	aMenu.push_back("2����ʾ������Ϣ");
	aMenu.push_back("3����������");
	aMenu.push_back("4���ı���������");
	aMenu.push_back("5��ɾ������");
	aMenu.push_back("6����������");

	aMenu.push_back("Esc �������˵�");

	CMenu::showMenu(aMenu);
}

void CMassOrg::display() {
	cout << "���� " << aData.size() << " �����ż�¼" << endl;
	cout << endl;
	cout << "�����ҷֱ�Ϊ���ű�š���������" << endl;
	cout << endl;
	vector<OrgData>::const_iterator it;
	for (it = aData.begin(); it < aData.end(); it++) {
		cout << *it;
	}

	cout << "�����������..." << endl;
	_getch();
}

void CMassOrg::addData() {
	cout << "���������ű�ź����ƣ����<=0 ����ֹ���룩��" << endl;

	OrgData data;
	while (true) {
		cin >> data;
		if (data.nId <= 0) {
			break;
		}

		// ������Ƿ��ظ�
		bool exists = false;
		for (const auto& d : aData) {
			if (d.nId == data.nId) {
				exists = true;
				break;
			}
		}

		if (exists) {
			cout << "�ñ���Ѵ��ڣ����������룺" << endl;
			continue;
		}

		aData.push_back(data);
		cout << "��ӳɹ�������������һ�����ţ���������<=0 ��������" << endl;
	}
}



void CMassOrg::saveData() {
	ofstream file(sFileName.c_str());
	if (!file) {
		string s;
		s = "���ļ�ʧ�ܣ�" + sFileName;
		throw s.c_str();
	}

	//���õ���������[]
	for (int i = 0; i < aData.size(); i++) {
		file << aData[i];
	}

	file.close();

	cout << "�������� " << aData.size() << " ���������ݵ��ļ���" << endl;
	_getch();
}

void CMassOrg::readData() {
	ifstream file(sFileName.c_str());

	if (!file) {
		string s;
		s = "���ļ�ʧ�ܣ�" + sFileName;
		throw s.c_str();
	}

	OrgData data;
	while (!file.eof()) {
		file >> data;
		if (file.fail()) {//���� ���һ�� �� 2 ��
			break;
		}
		else {
			aData.push_back(data);
		}
	}

	file.close();
	cout << "����ȡ " << aData.size() << " ����������" << endl;
}

void CMassOrg::deleteData() {
	int idToDelete;
	cout << "������Ҫɾ�������ű�ţ�";
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
		saveData(); // ɾ�����ź󱣴�
		cout << "����ɾ���ɹ���" << endl;

		CAction action;
		action.deleteByClubID(idToDelete);

		CSource source;
		source.deleteByClubID(idToDelete);

		//���ﻹҪ��ɳ�Ա������ɾ��
	}
	else {
		cout << "δ�ҵ��ñ�ŵ����š�" << endl;
	}

	_getch();
}


void CMassOrg::changeData() {
	int id;
	cout << "������Ҫ�޸ĵ����ű�ţ�";
	cin >> id;

	bool found = false;
	for (auto& data : aData) {
		if (data.nId == id) {
			cout << "��ǰ��Ϣ��" << endl;
			cout << data;

			cout << "�������µ��������ƣ�";
			cin >> data.sName;

			cout << "�޸ĳɹ���" << endl;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "δ�ҵ����Ϊ " << id << " �����š�" << endl;
	}

	cout << "�����������..." << endl;
	_getch();
}

void CMassOrg::findData() {
	int id;
	cout << "������Ҫ���ҵ����ű�ţ�";
	cin >> id;

	bool found = false;
	for (const auto& data : aData) {
		if (data.nId == id) {
			cout << "�ҵ����ţ�" << endl;
			cout << data;
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "δ�ҵ����Ϊ " << id << " �����š�" << endl;
	}

	cout << "�����������..." << endl;
	_getch();
}


CMassOrg::CMassOrg() {
	sFileName = "orgdata.txt";

	readData();
}