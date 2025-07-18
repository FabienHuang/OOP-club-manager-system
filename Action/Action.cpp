#include "Action.h"
#include "../Menu/Menu.h"

//1�������������
ostream& operator<<(ostream& os, const CActionData& data) {
	os << data.clubID<< "\t"<<  data.nId << "\t" <<data.sName.c_str() << "\t" << endl;
	return os;
}

istream& operator>>(istream& is, CActionData& data) {
	is >> data.clubID;
	if (data.clubID <= 0) {//����ı�� <= 0 ��ʾ��������
		return is;
	}
	is >> data.nId;
	is >> data.sName;	
	
	return is;
}

//2���ļ��������(����ƣ�
ofstream& operator<<(ofstream& os, const CActionData& data) {
	os << data.clubID << "\t" <<data.nId << "\t" << data.sName << "\t" << endl;//ʵ����д �ļ�
	return os;
}

ifstream& operator>>(ifstream& is, CActionData& data) {
	is >> data.clubID>>data.nId >> data.sName;//��ȡ�ļ����� �� data ��
	return is;
}

//�����������
ofstream& operator<<(ofstream& os, const CActionMemData& data) {
	os << data.clubID << "\t" << data.nId << "\t" << data.sName << "\t" << endl;//ʵ����д �ļ�
	return os;
}

ifstream& operator>>(ifstream& is, CActionMemData& data) {
	is >> data.clubID >> data.nId >> data.sName;//��ȡ�ļ����� �� data ��
	return is;
}

//---------------------------------
/**********************************
   CAction ��ʼ����
***********************************/
//---------------------------------
//���ݲ˵��� ���� ��Ӧ�ĺ���
void CAction::control() {
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
		case '4'://�޸�
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

void CAction::showMenu() {
	vector<string> aMenu;
	aMenu.push_back("1����ӻ��Ϣ");
	aMenu.push_back("2����ʾ���Ϣ");
	aMenu.push_back("3�����һ��Ϣ");
	aMenu.push_back("4���޸Ļ��Ϣ");
	aMenu.push_back("5��ɾ���");
	aMenu.push_back("6����������");
	//.........
	aMenu.push_back("Esc �������˵�");

	CMenu::showMenu(aMenu);
}

void CAction::display() {
	cout << "���������ű�ţ�����666��ʾ��ʾȫ�������";
	int clubID;
	cin >> clubID;

	cout << endl;

	if (clubID == 666) {
		cout << "���� " << aData.size() << " �����¼" << endl;
		cout << "�����ҷֱ�Ϊ���ű�š����š������" << endl;
		for (const auto& data : aData) {
			cout << data;
		}
	}
	else {
		int count = 0;
		cout << "���ű��Ϊ " << clubID << " �Ļ��¼���£�" << endl;
		cout << "�����ҷֱ�Ϊ���ű�š����š������" << endl;

		for (const auto& data : aData) {
			if (data.clubID == clubID) {
				cout << data;
				count++;
			}
		}

		if (count == 0) {
			cout << "δ�ҵ������ŵĻ��¼��" << endl;
		}
	}

	cout << endl << "�����������..." << endl;
	_getch();
}


void CAction::displayForN() {    //���������Ϊ��������ͨ��Ա��ʾ�Ͳμӻ��׼��
	cout << "���������ű�ţ�";
	int clubID;
	cin >> clubID;

	cout << endl;

		int count = 0;
		cout << "���ű��Ϊ " << clubID << " �Ļ��¼���£�" << endl;
		cout << "�����ҷֱ�Ϊ���ű�š����š������" << endl;

		for (const auto& data : aData) {
			if (data.clubID == clubID) {
				cout << data;
				count++;
			}
		}

		if (count == 0) {
			cout << "δ�ҵ������ŵĻ��¼��" << endl;
		}

		cout << "��������Ҫ�μӵĻ���:" << endl;
		int getId;
		cin >> getId;

		for (const auto& data : aData) {
			if (data.clubID == clubID && data.nId == getId) {
				CActionMemData memData;
				memData.clubID = clubID;
				memData.nId = getId;
				cout << "����������������";
				cin >> memData.sName;

				ofstream fout("cactionmemdata.txt", ios::app);
				if (fout.is_open()) {
					fout << memData;
					fout.close();
					cout << "������Ϣ�ѱ��浽�ļ���" << endl;
				}
				else {
					cout << "����ʧ�ܣ��޷����ļ���" << endl;
				}


				cout << "���ѳɹ��μӻ��" << data.sName << endl;
				break;
			}
		}

	cout << endl << "�����������..." << endl;
	_getch();
}


void CAction::addData() {
	cout << "��ֱ��������ű�š����š�����ƣ��������ű�� <= 0 ��ֹ���룩" << endl;

	while (true) {
		CActionData data;
		cin >> data;

		if (data.clubID <= 0) {
			return;
		}

		// �������Ƿ��ظ�,ÿ�����Ŷ��Ƕ�һ�޶���
		bool exists = false;
		for (const auto& item : aData) {
			if (item.nId == data.nId) {
				cout << "���� " << data.nId << " �Ѵ��ڣ�����������һ����ͬ�Ļ��š�" << endl;
				exists = true;
				break;
			}
		}

		if (exists) {
			continue; // ����ظ�������������
		}

		aData.push_back(data);
		cout << "��ӳɹ�������������������ű�� <= 0 ������ӡ�" << endl;
	}
}


void CAction::saveData() {
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

	cout << "�������� " << aData.size() << " ������ݵ��ļ���" << endl;
	_getch();
}

void CAction::readData() {
	ifstream file(sFileName.c_str());

	if (!file) {
		string s;
		s = "���ļ�ʧ�ܣ�" + sFileName;
		throw s.c_str();
	}

	CActionData data;
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
	cout << "����ȡ " << aData.size() << " �������" << endl;
}

void CAction::deleteData() {
	cout << "������Ҫɾ���Ļ��ţ�";
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
		saveData(); // ɾ���󱣴�
		cout << "��ɾ�� " << count << " ������Ϊ " << nId << " �ļ�¼��" << endl;
	}
	else {
		cout << "û���ҵ��û��ŵļ�¼��" << endl;
	}

	cout << "�����������..." << endl;
	_getch();
}


void CAction::changeData() {
	cout << "������Ҫ�޸ĵĻ��ţ�";
	int nId;
	cin >> nId;

	bool found = false;
	for (auto& data : aData) {
		if (data.nId == nId) {
			cout << "�ҵ���¼��" << data;
			cout << "�������µĻ���ƣ�";
			cin >> data.sName;
			found = true;
			break;
		}
	}

	if (found) {
		saveData();
		cout << "�޸ĳɹ���" << endl;
	}
	else {
		cout << "δ�ҵ���Ӧ�Ļ��š�" << endl;
	}

	cout << "�����������..." << endl;
	_getch();
}

void CAction::findData() {
	cout << "����Ҫ�����ĸ����ŵ���Դ�����������ű�ţ�";
	int clubID;
	cin >> clubID;

	cout << "������Ҫ���ҵĻ��ţ�";
	int nId;
	cin >> nId;

	bool found = false;
	for (const auto& data : aData) {
		if (data.clubID == clubID && data.nId == nId) {
			if (!found) {
				cout << "���ҵ��Ļ��¼���£�" << endl;
			}
			cout << data;
			found = true;
		}
	}

	if (!found) {
		cout << "û���ҵ������ű�źͻ��Ŷ�Ӧ�ļ�¼��" << endl;
	}

	cout << "�����������..." << endl;
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
	saveData(); // ���±����ļ�
	cout << "��ɾ�����ű��Ϊ " << clubID << " �� " << count << " �����¼��" << endl;
}


CAction::CAction() {
	sFileName = "cactiondata.txt";
	sFileNameForMem = "cactionmemdata.txt"; // �μӻ�ĳ�Ա�����ļ���

	readData();
}






