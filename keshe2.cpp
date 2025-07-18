// KeShe.cpp : 定义控制台应用程序的入口点。
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

// 对字符串进行简单的异或加密/解密
// sSrc: 需要加密或解密的字符串（加密和解密过程相同）
// sKey: 密钥字符串
void code(std::string& sSrc, const std::string& sKey) {
	int nKey = static_cast<int>(sKey.length());   // 密钥长度
	int nSrc = static_cast<int>(sSrc.length());   // 源字符串长度
	for (int i = 0; i < nSrc; ++i) {
		// 逐字符与密钥循环异或，实现加密或解密
		sSrc[i] ^= sKey[i % nKey];
	}
}

// ========================
// 读取加密密码文件并解密
// 参数：key - 解密用的密钥
// 返回：解密后的密码字符串
// ========================
string readDecryptedPassword(const string& key)
{
	// 以二进制方式打开密码文件
	ifstream fin("admincode.txt", ios::in | ios::binary);
	if (!fin) {
		// 文件打开失败，抛出异常
		throw "密码文件读取失败！请检查 admincode.txt 是否存在";
	}

	// 读取整个文件内容到字符串
	string encryptedPwd((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
	fin.close();

	// 使用密钥对内容进行解密
	code(encryptedPwd, key);
	return encryptedPwd; // 返回解密后的密码
}

// ========================
// 主程序入口
// ========================
int main()
{
	//// 只需运行一次，用于设置初始密码并写入加密文件
	//void writeEncryptedPassword(const string & pwd, const string & key) {
	//	string encryptedPwd = pwd;
	//	code(encryptedPwd, key); // 加密
	//	ofstream fout("admincode.txt", ios::out | ios::binary);
	//	fout.write(encryptedPwd.c_str(), encryptedPwd.size());
	//	fout.close();
	//}

	cout << "欢迎使用社团管理系统" << endl << endl;
	cout << "按任意键开始" << endl;
	_getch();

	// 读取解密后的密码
	string correctPwd;
	try {
		correctPwd = readDecryptedPassword("3.1415926");  // 这个 key 要跟加密时一致
	}
	catch (const char* errMsg) {
		cout << errMsg << endl;
		_getch();
		return -1;
	}

	// 菜单初始化
	CMassOrg massorg;
	CAction caction;
	CSource csource;
	CMember cmember;

	vector<string> aMainMenu;
	aMainMenu.push_back("+------------------------+");
	aMainMenu.push_back("|   社团管理系统主菜单   |");
	aMainMenu.push_back("|========================|");
	aMainMenu.push_back("| 请输入相应数字选择功能 |");
	aMainMenu.push_back("| 1、社团管理            |");
	aMainMenu.push_back("| 2、成员管理            |");
	aMainMenu.push_back("| 3、活动管理            |");
	aMainMenu.push_back("| 4、资源管理            |");
	aMainMenu.push_back("| Esc、退出程序          |");
	aMainMenu.push_back("+------------------------+");


	while (true) {
		CMenu::showMenu(aMainMenu);
		int nKey = _getch(); // 获取键盘按键
		CMenu::clearScr();

		try {
			switch (nKey) {
			case '1': {
				cout << "请输入管理员访问密码：";
				string inputPwd;
				cin >> inputPwd;

				if (inputPwd == correctPwd) {
					massorg.control();  // 密码正确，进入社团管理
				}
				else {
					cout << "密码错误，访问被拒绝。" << endl;
					_getch();
				}
				break;
			}
			case '2':
				cmember.SumMenu(caction, massorg);  // 无需密码
				break;

			case '3': {
				cout << "请输入管理员访问密码：";
				string inputPwd;
				cin >> inputPwd;

				if (inputPwd == correctPwd) {
					caction.control();  // 密码正确，进入活动管理
				}
				else {
					cout << "密码错误，访问被拒绝。" << endl;
					_getch();
				}
				break;
			}
			case '4': {
				cout << "请输入管理员访问密码：";
				string inputPwd;
				cin >> inputPwd;

				if (inputPwd == correctPwd) {
					csource.control();  // 密码正确，进入资源管理
				}
				else {
					cout << "密码错误，访问被拒绝。" << endl;
					_getch();
				}
				break;
			}
			case 27: // Esc
				return 0;

			default:
				cout << "无效选项，请重新输入" << endl;
				int pause = _getch();
				break;
			}

		}
		catch (const char* sError) {
			cout << "出错啦：" << sError << endl;
			_getch();
		}
	}

	return 0;
}
