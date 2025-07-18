// KeShe.cpp : �������̨Ӧ�ó������ڵ㡣
// MassOrg  Member  Action

#include "Menu/menu.h"
#include "MassOrg/MassOrg.h"
#include "Action/Action.h"
#include "Member/Member.h"
#include "Source/Source.h"
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

// ���ַ������м򵥵�������/����
// sSrc: ��Ҫ���ܻ���ܵ��ַ��������ܺͽ��ܹ�����ͬ��
// sKey: ��Կ�ַ���
void code(std::string& sSrc, const std::string& sKey) {
	int nKey = static_cast<int>(sKey.length());   // ��Կ����
	int nSrc = static_cast<int>(sSrc.length());   // Դ�ַ�������
	for (int i = 0; i < nSrc; ++i) {
		// ���ַ�����Կѭ�����ʵ�ּ��ܻ����
		sSrc[i] ^= sKey[i % nKey];
	}
}

// ========================
// ��ȡ���������ļ�������
// ������key - �����õ���Կ
// ���أ����ܺ�������ַ���
// ========================
string readDecryptedPassword(const string& key)
{
	// �Զ����Ʒ�ʽ�������ļ�
	ifstream fin("admincode.txt", ios::in | ios::binary);
	if (!fin) {
		// �ļ���ʧ�ܣ��׳��쳣
		throw "�����ļ���ȡʧ�ܣ����� admincode.txt �Ƿ����";
	}

	// ��ȡ�����ļ����ݵ��ַ���
	string encryptedPwd((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
	fin.close();

	// ʹ����Կ�����ݽ��н���
	code(encryptedPwd, key);
	return encryptedPwd; // ���ؽ��ܺ������
}

// ========================
// ���������
// ========================
int main()
{
	//// ֻ������һ�Σ��������ó�ʼ���벢д������ļ�
	//void writeEncryptedPassword(const string & pwd, const string & key) {
	//	string encryptedPwd = pwd;
	//	code(encryptedPwd, key); // ����
	//	ofstream fout("admincode.txt", ios::out | ios::binary);
	//	fout.write(encryptedPwd.c_str(), encryptedPwd.size());
	//	fout.close();
	//}

	cout << "��ӭʹ�����Ź���ϵͳ" << endl << endl;
	cout << "���������ʼ" << endl;
	_getch();

	// ��ȡ���ܺ������
	string correctPwd;
	try {
		correctPwd = readDecryptedPassword("3.1415926");  // ��� key Ҫ������ʱһ��
	}
	catch (const char* errMsg) {
		cout << errMsg << endl;
		_getch();
		return -1;
	}

	// �˵���ʼ��
	CMassOrg massorg;
	CAction caction;
	CSource csource;
	CMember cmember;

	vector<string> aMainMenu;
	aMainMenu.push_back("+------------------------+");
	aMainMenu.push_back("|   ���Ź���ϵͳ���˵�   |");
	aMainMenu.push_back("|========================|");
	aMainMenu.push_back("| ��������Ӧ����ѡ���� |");
	aMainMenu.push_back("| 1�����Ź���            |");
	aMainMenu.push_back("| 2����Ա����            |");
	aMainMenu.push_back("| 3�������            |");
	aMainMenu.push_back("| 4����Դ����            |");
	aMainMenu.push_back("| Esc���˳�����          |");
	aMainMenu.push_back("+------------------------+");


	while (true) {
		CMenu::showMenu(aMainMenu);
		int nKey = _getch(); // ��ȡ���̰���
		CMenu::clearScr();

		try {
			switch (nKey) {
			case '1': {
				cout << "���������Ա�������룺";
				string inputPwd;
				cin >> inputPwd;

				if (inputPwd == correctPwd) {
					massorg.control();  // ������ȷ���������Ź���
				}
				else {
					cout << "������󣬷��ʱ��ܾ���" << endl;
					_getch();
				}
				break;
			}
			case '2':
				cmember.SumMenu(caction, massorg);  // ��������
				break;

			case '3': {
				cout << "���������Ա�������룺";
				string inputPwd;
				cin >> inputPwd;

				if (inputPwd == correctPwd) {
					caction.control();  // ������ȷ����������
				}
				else {
					cout << "������󣬷��ʱ��ܾ���" << endl;
					_getch();
				}
				break;
			}
			case '4': {
				cout << "���������Ա�������룺";
				string inputPwd;
				cin >> inputPwd;

				if (inputPwd == correctPwd) {
					csource.control();  // ������ȷ��������Դ����
				}
				else {
					cout << "������󣬷��ʱ��ܾ���" << endl;
					_getch();
				}
				break;
			}
			case 27: // Esc
				return 0;

			default:
				cout << "��Чѡ�����������" << endl;
				int pause = _getch();
				break;
			}

		}
		catch (const char* sError) {
			cout << "��������" << sError << endl;
			_getch();
		}
	}

	return 0;
}
