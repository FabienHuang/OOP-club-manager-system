#ifndef __MEMBER__
#define __MEMBER__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class CMember;
class CAction;
class CMassOrg;

class ActionMemData {
private:
    int memId;
    int actId;
public:
	ActionMemData() : memId(0), actId(0) {}
	friend class CMember;
	// 基本输入输出
	friend ostream& operator<<(ostream& os, const ActionMemData& data);
	friend istream& operator>>(istream& is, ActionMemData& data);
	// 文件输入输出
	friend ofstream& operator<<(ofstream& os, const ActionMemData& data);
	friend ifstream& operator>>(ifstream& is, ActionMemData& data);
};


class Proprieter {
private:
    int clubID;
    int nId;   // 成员编号
    std::string sName;   // 成员姓名
    std::string sSex;    // 性别
    std::string sPhone;  // 电话
    std::string sEmail;  // 邮箱

public:
    Proprieter() : clubID(0), nId(0), sName("未命名"), sSex("未知"), sPhone("无"), sEmail("无") {}

    friend class CMember;

    // 基本输入输出
    friend ostream& operator<<(ostream& os, const Proprieter& data);
    friend istream& operator>>(istream& is, Proprieter& data);

    // 文件输入输出
    friend ofstream& operator<<(ofstream& os, const Proprieter& data);
    friend ifstream& operator>>(ifstream& is, Proprieter& data);
};

class NormalMem {
private:
    int clubID;
    int nId;   // 成员编号
    std::string sName;   // 成员姓名
    std::string sSex;    // 性别
    std::string sPhone;  // 电话
    std::string sEmail;  // 邮箱

public:
    NormalMem() : clubID(0), nId(0), sName("未命名"), sSex("未知"), sPhone("无"), sEmail("无") {}

    friend class CMember;

    // 基本输入输出
    friend ostream& operator<<(ostream& os, const NormalMem& data);
    friend istream& operator>>(istream& is, NormalMem& data);

    // 文件输入输出
    friend ofstream& operator<<(ofstream& os, const NormalMem& data);
    friend ifstream& operator>>(ifstream& is, NormalMem& data);
};

class NonMem {
private:
    int clubID;
    int nId;   // 成员编号
    std::string sName;   // 成员姓名
    std::string sSex;    // 性别
    std::string sPhone;  // 电话
    std::string sEmail;  // 邮箱

    NonMem() : clubID(0), nId(0), sName("未命名"), sSex("未知"), sPhone("无"), sEmail("无") {}

    friend class CMember;

    // 基本输入输出
    friend ostream& operator<<(ostream& os, const NonMem& data);
    friend istream& operator>>(istream& is, NonMem& data);

    // 文件输入输出
    friend ofstream& operator<<(ofstream& os, const NonMem& data);
    friend ifstream& operator>>(ifstream& is, NonMem& data);
};

class CMember {
private:
    vector<Proprieter> aProprieters;  // 所有社长
    vector<NormalMem> aNormalMems;    // 普通成员
    vector<NonMem> aNonMems;          // 非社团成员

    string sProprieterFileName;       // 社长文件名
    string sNormalMemFileName;        // 普通成员文件名

    void showMenu();

public:
    CMember();

    void controlForP(); // 社长菜单
    void controlForN(CAction& action, CMassOrg& massorg); // 普通成员菜单
    void controlForNon(CMassOrg& massorg); // 非社团成员菜单

    void displayMem();  // 显示所有社团成员信息

    void addData();     // 加入社团
    void saveData();    // 保存数据到文件
    void readData();    // 从文件读取数据
    void deleteData();  // 删除成员
    void changeData();  // 修改成员信息
    void findData();    // 查找成员信息
    void deleteByClubID(int clubID); // 删除社团成员


    void showMenuForP();
    void showMenuForN();
    void showMenuForNon();

    void updatePresidentInfo();
    void showPresidentInfo();

    void addDataForP();

    void normalMemberMenu(CAction& action, CMassOrg& massorg);

    void SumMenu(CAction& action, CMassOrg& massorg);
};

#endif
