#include"Member.h"
#include "../Menu/Menu.h"
#include"../Action/Action.h"
#include "../Member/Member.h"
#include "../Source/Source.h"
#include "../MassOrg/MassOrg.h"


// 加密/解密函数，原地修改
void code(char* sSrc, const char* sKey) {
    int nKey = strlen(sKey);
    int nSrc = strlen(sSrc);
    for (int i = 0; i < nSrc; ++i) {
        sSrc[i] ^= sKey[i % nKey];
    }
}
// 读取加密密码文件并解密，返回解密后的密码
void readPasswordFromFile(const char* filename, const char* key, char* outPwd, int maxLen) {
    ifstream fin(filename);
    if (!fin) {
        throw "密码文件读取失败！";
    }
    fin.getline(outPwd, maxLen); // 读取一行
    fin.close();
    code(outPwd, key); // 解密
}
// 写入加密密码到文件
void writePasswordToFile(const char* filename, const char* key, const char* plainPwd) {
    char buf[64];
    strcpy_s(buf, plainPwd);
    code(buf, key); // 加密
    ofstream fout(filename);
    fout << buf << endl;
    fout.close();
}


ostream& operator<<(ostream& os, const ActionMemData& data) {
    os << data.memId << "\t" << data.actId << endl;
    return os;
}

istream& operator>>(istream& is, ActionMemData& data) {
    is >> data.memId >> data.actId;
    return is;
}

// 文件流输出：写入活动报名数据
ofstream& operator<<(ofstream& os, const ActionMemData& data) {
    os << data.memId << '\t' << data.actId << '\n';
    return os;
}

// 文件流输入：从文件读取活动报名数据
ifstream& operator>>(ifstream& is, ActionMemData& data) {
    is >> data.memId >> data.actId;
    return is;
}


//////////////////////社长输入输出重载函数
ostream& operator<<(ostream& os, const Proprieter& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName.c_str() << "\t" << data.sSex.c_str() << "\t"
        << data.sPhone.c_str() << "\t" << data.sEmail.c_str() << endl;
    return os;
}

istream& operator>>(istream& is, Proprieter& data) {
    is >> data.clubID;
    is >> data.nId;
    if (data.nId <= 0) {//输入的编号 <= 0 表示结束输入
        return is;
    }
    is >> data.sName >> data.sSex >> data.sPhone >> data.sEmail;
    return is;
}

ofstream& operator<<(ofstream& os, const Proprieter& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName << "\t" << data.sSex << "\t"
        << data.sPhone << "\t" << data.sEmail << endl; //实际是写 文件
    return os;
}

ifstream& operator>>(ifstream& is, Proprieter& data) {
    is >> data.clubID >> data.nId >> data.sName >> data.sSex >> data.sPhone >> data.sEmail; //读取文件数据 到 data 中
    return is;
}



/// /////////////////普通成员输出重载函数
ostream& operator<<(ostream& os, const NormalMem& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName.c_str() << "\t" << data.sSex.c_str() << "\t"
        << data.sPhone.c_str() << "\t" << data.sEmail.c_str() << endl;
    return os;
}

istream& operator>>(istream& is, NormalMem& data) {
    is >> data.clubID;
    is >> data.nId;
    if (data.nId <= 0) {//输入的编号 <= 0 表示结束输入
        return is;
    }
    is >> data.sName >> data.sSex >> data.sPhone >> data.sEmail;
    return is;
}

ofstream& operator<<(ofstream& os, const NormalMem& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName << "\t" << data.sSex << "\t"
        << data.sPhone << "\t" << data.sEmail << endl; //实际是写 文件
    return os;
}

ifstream& operator>>(ifstream& is, NormalMem& data) {
    is >> data.clubID >> data.nId >> data.sName >> data.sSex >> data.sPhone >> data.sEmail; //读取文件数据 到 data 中
    return is;
}



//////////////非会员输出重载函数

ostream& operator<<(ostream& os, const NonMem& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName.c_str() << "\t" << data.sSex.c_str() << "\t"
        << data.sPhone.c_str() << "\t" << data.sEmail.c_str() << endl;
    return os;
}

istream& operator>>(istream& is, NonMem& data) {
    is >> data.clubID;
    is >> data.nId;
    if (data.nId <= 0) {//输入的编号 <= 0 表示结束输入
        return is;
    }
    is >> data.sName >> data.sSex >> data.sPhone >> data.sEmail;
    return is;
}

ofstream& operator<<(ofstream& os, const NonMem& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName << "\t" << data.sSex << "\t"
        << data.sPhone << "\t" << data.sEmail << endl; //实际是写 文件
    return os;
}

ifstream& operator>>(ifstream& is, NonMem& data) {
    is >> data.clubID >> data.nId >> data.sName >> data.sSex >> data.sPhone >> data.sEmail; //读取文件数据 到 data 中
    return is;
}





//---------------------------------
/**********************************
   CMember 开始定义
***********************************/
//---------------------------------
//根据菜单项 调用 对应的函数
void CMember::controlForP() {
    CSource source;
    CAction action;
    CMassOrg massorg;
    while (true) {
        showMenuForP(); //显示菜单
        int nKey = _getch(); //等候用户选择
        CMenu::clearScr(); //清屏
        switch (nKey) {
        case '1':
            displayMem(); //显示所有社团成员信息
            break;
        case '2':
            action.control(); //可以进行所有的社团活动操作
            break;
        case '3':
            source.control(); //可以进行所有的社团资源操作
            break;
        case '4':
            massorg.control(); //可以进行所有的社团操作
            break;
        case '5':
            updatePresidentInfo();
            break;
        case '0': //返回上一级菜单
            return;
        default:
            cout << "无效的选项，请重新选择。" << endl;
            int pause = _getch();
            break;
        }
    }
}
void CMember::controlForN(CAction& action, CMassOrg& massorg) {
    while (true) {
        showMenuForN(); //显示菜单
        int nKey = _getch(); //等候用户选择
        CMenu::clearScr(); //清屏
        switch (nKey) {
        case '1': //显示社团的基本信息
        {
            massorg.display();
            break;
        }
        
		case '2': //显示所有的社团活动
        {
            action.display();
			break;
        }
        
        case '3':  //活动报名
        {
            cout << "请输入你的成员编号：";
            int memId;
            cin >> memId;
            cout << "请输入要参加的活动编号：";
            int actId;
            cin >> actId;

            ActionMemData amd;
            amd.memId = memId;
            amd.actId = actId;

            ofstream fout("cactionmemdata.txt", ios::app);
            if (fout.is_open()) {
                fout << amd;
                fout.close();
                cout << "参加活动成功，信息已保存到文件！" << endl;
            }
            else {
                cout << "文件写入失败！" << endl;
            }
            _getch();
            break;
        }

        
        case '4':  // 退出活动
        {
            cout << "请输入你的成员编号：";
            int memId;
            cin >> memId;
            cout << "请输入要退出的活动编号：";
            int actId;
            cin >> actId;

            // 读取所有报名信息
            vector<ActionMemData> allData;
            ifstream fin("cactionmemdata.txt");
            ActionMemData temp;
            while (fin >> temp) {
                // 跳过要删除的记录
                if (!(temp.memId == memId && temp.actId == actId)) {
                    allData.push_back(temp);
                }
            }
            fin.close();

            // 重新写入文件
            ofstream fout("cactionmemdata.txt");
            for (const auto& d : allData) {
                fout << d;
            }
            fout.close();

            cout << "退出活动成功，信息已从文件中移除！" << endl;
            _getch();
            break;
        }
        
        case '5':  // 退出社团
        {
            cout << "请输入你的成员编号以退出社团：";
            int id;
            cin >> id;
            bool found = false;
            for (auto it = aNormalMems.begin(); it != aNormalMems.end(); ++it) {
                if (it->nId == id) {
                    aNormalMems.erase(it);
                    found = true;
                    break;
                }
            }
            saveData();
            if (found) {
                cout << "已成功退出社团！" << endl;
            }
            else {
                cout << "未找到该编号的成员，退出失败。" << endl;
            }
            _getch();
            break;
        }

        case '0': //返回上一级菜单
            return;
        default:
            cout << "无效的选项，请重新选择。" << endl;
            int pause = _getch();
            break;
        }
    }
}
void CMember::controlForNon(CMassOrg& massorg)
{
    while (true) {
        showMenuForNon(); //显示菜单
        int nKey = _getch(); //等候用户选择
        CMenu::clearScr(); //清屏
        switch (nKey) {
        case '1':
            massorg.display(); //显示所有社团信息
            break;
        case '2': {
            // 加入社团
            addData();
            break;
        }

        case '0': //返回上一级菜单
            return;
        default:
            cout << "无效的选项，请重新选择。" << endl;
            int pause = _getch();
            break;
        }
    }
}



void CMember::updatePresidentInfo() {
    system("cls");
    cout << "=== 完善社长个人信息 ===" << endl;

    Proprieter president;
    cout << "请输入所在的社团编号：";
    cin >> president.nId;
    cout << "请输入社长姓名：";
    cin >> president.sName;
    cout << "请输入社长性别：";
    cin >> president.sSex;
    cout << "请输入社长电话：";
    cin >> president.sPhone;
    cout << "请输入社长邮箱：";
    cin >> president.sEmail;

    // 把社长信息写入文件
    ofstream fout("president_info.txt");
    if (fout.is_open()) {
        fout << president;
        fout.close();
        cout << "社长信息已保存成功！" << endl;
    }
    else {
        cout << "保存失败！无法打开文件。" << endl;
    }

    system("pause");
}

void CMember::showPresidentInfo() {
    ifstream fin("president_info.txt");
    if (fin.is_open()) {
        Proprieter president;
        fin >> president;
        fin.close();
        cout << "所在的社团编号：" << president.nId << endl;
        cout << "姓名：" << president.sName << endl;
        cout << "性别：" << president.sSex << endl;
        cout << "电话：" << president.sPhone << endl;
        cout << "邮箱：" << president.sEmail << endl;
    }
    else {
        cout << "暂无社长信息，请先完善个人信息。" << endl;
    }
}


void CMember::showMenuForP()
{
    cout << "1. 显示所有社团成员信息" << endl;
    cout << "2. 社团活动管理" << endl;
    cout << "3. 社团资源管理" << endl;
    cout << "4. 社团管理" << endl;
    cout << "5. 完善社长个人信息" << endl;
    cout << "0. 返回上一级菜单" << endl;
    cout << "请选择操作：";
}

void CMember::showMenuForN()
{
    cout << "1. 显示社团的基本信息" << endl;
    cout << "2. 显示所有社团活动" << endl;
    cout << "3. 活动报名" << endl;
	cout << "4. 退出活动" << endl;
    cout << "5. 退出社团" << endl;
    cout << "0. 返回上一级菜单" << endl;
    cout << "请选择操作：";
}

void CMember::showMenuForNon()
{
    cout << "1. 显示社团的基本信息" << endl;
    cout << "2. 选择加入社团" << endl;
    cout << "0. 返回上一级菜单" << endl;
    cout << "请选择操作：";
}

void CMember::SumMenu(CAction& action, CMassOrg& massorg)
{
    // 初始化密码文件（只需运行一次，实际使用时可注释掉）
    //writePasswordToFile("proprietercode.txt", "mykey123", "567468");
    //writePasswordToFile("normalmemcode.txt", "mykey123", "970975");

    while (true) {
        const char* key = "mykey123";
        const int maxPwdLen = 64;

        vector<string> aMenu;
        aMenu.push_back("1、社长");
        aMenu.push_back("2、普通成员");
        aMenu.push_back("3、非会员");
        aMenu.push_back("0、返回主菜单");
        CMenu::showMenu(aMenu);

        cout << "请选择你的身份：";
        char choice = _getch();
        CMenu::clearScr();

        CMember member;

        try {
            switch (choice) {
            case '1': {
                cout << "请输入社长密码：";
                char inputPwd[maxPwdLen];
                cin >> inputPwd;
                char truePwd[maxPwdLen];
                readPasswordFromFile("proprietercode.txt", key, truePwd, maxPwdLen);
                if (strcmp(inputPwd, truePwd) == 0) {
                    member.controlForP();
                }
                else {
                    cout << "密码错误，无法进入社长界面！" << endl;
                    _getch();
                }
                break;
            }
            case '2': {
                cout << "请输入普通成员密码：";
                char inputPwd[maxPwdLen];
                cin >> inputPwd;
                char truePwd[maxPwdLen];
                readPasswordFromFile("normalmemcode.txt", key, truePwd, maxPwdLen);
                if (strcmp(inputPwd, truePwd) == 0) {
                    CAction action;
                    CMassOrg massorg;
                    member.controlForN(action, massorg);
                }
                else {
                    cout << "密码错误，无法进入普通成员界面！" << endl;
                    _getch();
                }
                break;
            }
            case '3': {
                member.controlForNon(massorg);
                break;
            }
            case '0':
                return;
            default:
                cout << "无效选项，请重新输入。" << endl;
                break;
            }
        }
        catch (const char* e) {
            cerr << "错误：" << e << endl;
            _getch();
        }
    }
}



// 显示所有社团成员信息
void CMember::displayMem() {
    cout << "【社长信息】" << endl;
    showPresidentInfo();
    cout << "【普通成员信息】" << endl;
    for (const auto& m : aNormalMems) {
        cout << m;
    }
    cout << "按任意键返回..." << endl;
    _getch();
}

// 加入社团（添加普通成员）
void CMember::addData() {
    NormalMem newMem;
    cout << "请输入你想加入的社团编号：" << endl;
    cin >> newMem.clubID;
    
    cout << "请输入成员编号：";
    cin >> newMem.nId;
    // 检查编号是否已存在
    for (const auto& m : aNormalMems) {
        if (m.nId == newMem.nId) {
            cout << "该成员编号已存在，不能重复加入！" << endl;
            _getch();
            return;
        }
    }
    cout << "请输入姓名：";
    cin >> newMem.sName;
    cout << "请输入性别：";
    cin >> newMem.sSex;
    cout << "请输入电话：";
    cin >> newMem.sPhone;
    cout << "请输入邮箱：";
    cin >> newMem.sEmail;
    aNormalMems.push_back(newMem);
    saveData();
    cout << "加入社团成功！" << endl;
    _getch();
}

// 保存数据到文件
void CMember::saveData() {
    // 保存社长
    ofstream f1(sProprieterFileName);
    for (const auto& p : aProprieters) {
        f1 << p;
    }
    f1.close();
    // 保存普通成员
    ofstream f2(sNormalMemFileName);
    for (const auto& m : aNormalMems) {
        f2 << m;
    }
    f2.close();
}

// 从文件读取数据
void CMember::readData() {
    aProprieters.clear();
    aNormalMems.clear();
    // 读取社长
    ifstream f1(sProprieterFileName);
    Proprieter p;
    while (f1 >> p) {
        if (p.nId > 0)
            aProprieters.push_back(p);
    }
    f1.close();
    // 读取普通成员
    ifstream f2(sNormalMemFileName);
    NormalMem m;
    while (f2 >> m) {
        if (m.nId > 0)
            aNormalMems.push_back(m);
    }
    f2.close();
}

// 删除成员
void CMember::deleteData() {
    cout << "请输入要删除的成员编号：";
    int id;
    cin >> id;
    int count = 0;
    for (auto it = aNormalMems.begin(); it != aNormalMems.end(); ) {
        if (it->nId == id) {
            it = aNormalMems.erase(it);
            count++;
        }
        else {
            ++it;
        }
    }
    saveData();
    if (count > 0)
        cout << "已删除 " << count << " 个成员。" << endl;
    else
        cout << "未找到该编号的成员。" << endl;
    _getch();
}

// 修改成员信息
void CMember::changeData() {
    cout << "请输入要修改的成员编号：";
    int id;
    cin >> id;
    bool found = false;
    for (auto& m : aNormalMems) {
        if (m.nId == id) {
            cout << "找到成员：" << m;
            cout << "请输入新的姓名：";
            cin >> m.sName;
            cout << "请输入新的性别：";
            cin >> m.sSex;
            cout << "请输入新的电话：";
            cin >> m.sPhone;
            cout << "请输入新的邮箱：";
            cin >> m.sEmail;
            found = true;
            break;
        }
    }
    if (found) {
        saveData();
        cout << "修改成功。" << endl;
    }
    else {
        cout << "未找到该编号的成员。" << endl;
    }
    _getch();
}

// 查找成员信息
void CMember::findData() {
    cout << "请输入要查找的成员编号：";
    int id;
    cin >> id;
    bool found = false;
    for (const auto& m : aNormalMems) {
        if (m.nId == id) {
            cout << "找到成员：" << m;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "未找到该编号的成员。" << endl;
    }
    _getch();
}

// 删除社团时同时删除该社团所有成员信息
void CMember::deleteByClubID(int clubID) {
    int count = 0;
    for (auto it = aNormalMems.begin(); it != aNormalMems.end(); ) {
        // 假设 NormalMem 有 clubID 字段
        if (it->clubID == clubID) {
            it = aNormalMems.erase(it);
            count++;
        }
        else {
            ++it;
        }
    }
    saveData();
    cout << "已删除社团编号为 " << clubID << " 的 " << count << " 个成员。" << endl;
    _getch();
}


CMember::CMember()
{
    sProprieterFileName = "proprieter.txt"; //社长文件名
    sNormalMemFileName = "normalmem.txt"; //普通成员文件名
    //可以在这里读取已有的社长和普通成员数据
    readData();
}