#include "Source.h"
#include "../Menu/Menu.h"

//1�������������
ostream& operator<<(ostream& os, const CSourceData& data) {
	os << data.clubID << "\t" << data.nId << "\t"<<data.sourceNum<< data.measureWord.c_str() << data.sName.c_str() << "\t" << endl;
	return os;
}

istream& operator>>(istream& is, CSourceData& data) {
	is >> data.clubID;
	if (data.clubID <= 0) {//����ı�� <= 0 ��ʾ��������
		return is;
	}
	is >> data.nId;

	is >> data.sourceNum;
	is >> data.measureWord;
	is >> data.sName;

	return is;
}

//2���ļ��������
ofstream& operator<<(ofstream& os, const CSourceData& data) {
	os << data.clubID << "\t" << data.nId << "\t"
		<< data.sourceNum << "\t"
		<< data.measureWord << "\t"
		<< data.sName << endl;
	return os;
}


ifstream& operator>>(ifstream& is, CSourceData& data) {
	is >> data.clubID >> data.nId >> data.sourceNum;

	// ��ȡ����
	is >> ws; // ���ǰ���հ�
	getline(is, data.measureWord, '\t'); // �� tab Ϊ�ָ���

	// ��ȡ��Դ����
	getline(is, data.sName); // ������β

	return is;
}


//---------------------------------
/**********************************
   CAction ��ʼ����
***********************************/
//---------------------------------
//���ݲ˵��� ���� ��Ӧ�ĺ���
void CSource::control() {
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

void CSource::showMenu() {
	vector<string> aMenu;
	aMenu.push_back("1�������Դ��Ϣ");
	aMenu.push_back("2����ʾ��Դ��Ϣ");
	aMenu.push_back("3��������Դ��Ϣ");
	aMenu.push_back("4���޸���Դ��Ϣ");
	aMenu.push_back("5��ɾ����Դ");
	aMenu.push_back("6����������");
	aMenu.push_back("Esc �������˵�");

	CMenu::showMenu(aMenu);
}

void CSource::display() {
	cout << "���������ű�ţ����� 666 ��ʾ������Դ����";
	int clubID;
	cin >> clubID;

	cout << endl;

	vector<CSourceData> toDisplay;

	if (clubID == 666) {
		toDisplay = aData; // ��ʾȫ��
	}
	else {
		// ɸѡ�������ű�Ŷ�Ӧ����Դ
		for (const auto& item : aData) {
			if (item.clubID == clubID) {
				toDisplay.push_back(item);
			}
		}
	}

	if (toDisplay.empty()) {
		cout << "δ�ҵ������ű�ŵ���Դ��¼��" << endl;
	}
	else {
		cout << "���� " << toDisplay.size() << " ����Դ��¼" << endl << endl;
		cout << "�����ҷֱ�Ϊ�����ű�š���Դ��š���Դ����+����+��Դ����" << endl << endl;

		for (const auto& item : toDisplay) {
			cout << item;
		}
	}

	cout << "�����������..." << endl;
	_getch();
}



void CSource::addData() {
	cout << "��ֱ����룺���ű�š���Դ��š���Դ���������ʡ���Դ���ƣ��������ű�� <= 0 ��ֹ���룩" << endl;

	while (true) {
		CSourceData data;
		cin >> data;

		if (data.clubID <= 0) {
			return;
		}

		// �����Դ����Ƿ��Ѵ���
		bool exists = false;
		for (const auto& item : aData) {
			if (item.nId == data.nId) {
				cout << "��Դ��� " << data.nId << " �Ѵ��ڣ�����������һ����ͬ����Դ��š�" << endl;
				exists = true;
				break;
			}
		}

		if (exists) {
			continue; // ��Դ����ظ�����������
		}

		aData.push_back(data);
		cout << "��ӳɹ�����������һ����¼�����������ű�� <= 0 ������ӡ�" << endl;
	}
}


void CSource::saveData() {
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

	cout << "�������� " << aData.size() << " ����Դ���ݵ��ļ���" << endl;
	_getch();
}

void CSource::readData() {
	ifstream file(sFileName.c_str());

	if (!file) {
		string s;
		s = "���ļ�ʧ�ܣ�" + sFileName;
		throw s.c_str();
	}

	CSourceData data;
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
	cout << "����ȡ " << aData.size() << " ����Դ����" << endl;
	_getch();
}

void CSource::deleteData() {
	cout << "������Ҫɾ������Դ��ţ�";
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
		cout << "��ɾ�� " << count << " ����Դ���Ϊ " << nId << " �ļ�¼��" << endl;
	}
	else {
		cout << "û���ҵ�����Դ��ŵļ�¼��" << endl;
	}

	cout << "�����������..." << endl;
	_getch();
}


void CSource::changeData() {
	cout << "������Ҫ�޸ĵ���Դ��ţ�";
	int nId;
	cin >> nId;

	bool found = false;
	for (auto& data : aData) {
		if (data.nId == nId) {
			cout << "�ҵ���¼��" << data;
			cout << "�������µ���Դ������";
			cin >> data.sourceNum;

			cout << "�������µ����ʣ�";
			cin >> data.measureWord;

			cout << "�������µ���Դ���ƣ�";
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
		cout << "δ�ҵ���Ӧ����Դ��š�" << endl;
	}

	cout << "�����������..." << endl;
	_getch();
}


void CSource::findData() {
	cout << "����Ҫ�����ĸ����ŵ���Դ�����������ű�ţ�";
	int clubID;
	cin >> clubID;

	cout << "������Ҫ���ҵ���Դ��ţ�";
	int nId;
	cin >> nId;

	bool found = false;
	for (const auto& data : aData) {
		if (data.clubID == clubID && data.nId == nId) {
			if (!found) {
				cout << "���ҵ�����Դ��¼���£�" << endl;
			}
			cout << data;
			found = true;
		}
	}

	if (!found) {
		cout << "û���ҵ������ű�źͻ��Ŷ�Ӧ����Դ��¼��" << endl;
	}

	cout << "�����������..." << endl;
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
	saveData(); // ���±����ļ�
	cout << "��ɾ�����ű��Ϊ " << clubID << " �� " << count << " ����Դ��¼��" << endl;
}



CSource::CSource() {
	sFileName = "csourcedata.txt";

	readData();
}







