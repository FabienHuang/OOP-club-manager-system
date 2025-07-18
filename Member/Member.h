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
	// �����������
	friend ostream& operator<<(ostream& os, const ActionMemData& data);
	friend istream& operator>>(istream& is, ActionMemData& data);
	// �ļ��������
	friend ofstream& operator<<(ofstream& os, const ActionMemData& data);
	friend ifstream& operator>>(ifstream& is, ActionMemData& data);
};


class Proprieter {
private:
    int clubID;
    int nId;   // ��Ա���
    std::string sName;   // ��Ա����
    std::string sSex;    // �Ա�
    std::string sPhone;  // �绰
    std::string sEmail;  // ����

public:
    Proprieter() : clubID(0), nId(0), sName("δ����"), sSex("δ֪"), sPhone("��"), sEmail("��") {}

    friend class CMember;

    // �����������
    friend ostream& operator<<(ostream& os, const Proprieter& data);
    friend istream& operator>>(istream& is, Proprieter& data);

    // �ļ��������
    friend ofstream& operator<<(ofstream& os, const Proprieter& data);
    friend ifstream& operator>>(ifstream& is, Proprieter& data);
};

class NormalMem {
private:
    int clubID;
    int nId;   // ��Ա���
    std::string sName;   // ��Ա����
    std::string sSex;    // �Ա�
    std::string sPhone;  // �绰
    std::string sEmail;  // ����

public:
    NormalMem() : clubID(0), nId(0), sName("δ����"), sSex("δ֪"), sPhone("��"), sEmail("��") {}

    friend class CMember;

    // �����������
    friend ostream& operator<<(ostream& os, const NormalMem& data);
    friend istream& operator>>(istream& is, NormalMem& data);

    // �ļ��������
    friend ofstream& operator<<(ofstream& os, const NormalMem& data);
    friend ifstream& operator>>(ifstream& is, NormalMem& data);
};

class NonMem {
private:
    int clubID;
    int nId;   // ��Ա���
    std::string sName;   // ��Ա����
    std::string sSex;    // �Ա�
    std::string sPhone;  // �绰
    std::string sEmail;  // ����

    NonMem() : clubID(0), nId(0), sName("δ����"), sSex("δ֪"), sPhone("��"), sEmail("��") {}

    friend class CMember;

    // �����������
    friend ostream& operator<<(ostream& os, const NonMem& data);
    friend istream& operator>>(istream& is, NonMem& data);

    // �ļ��������
    friend ofstream& operator<<(ofstream& os, const NonMem& data);
    friend ifstream& operator>>(ifstream& is, NonMem& data);
};

class CMember {
private:
    vector<Proprieter> aProprieters;  // �����糤
    vector<NormalMem> aNormalMems;    // ��ͨ��Ա
    vector<NonMem> aNonMems;          // �����ų�Ա

    string sProprieterFileName;       // �糤�ļ���
    string sNormalMemFileName;        // ��ͨ��Ա�ļ���

    void showMenu();

public:
    CMember();

    void controlForP(); // �糤�˵�
    void controlForN(CAction& action, CMassOrg& massorg); // ��ͨ��Ա�˵�
    void controlForNon(CMassOrg& massorg); // �����ų�Ա�˵�

    void displayMem();  // ��ʾ�������ų�Ա��Ϣ

    void addData();     // ��������
    void saveData();    // �������ݵ��ļ�
    void readData();    // ���ļ���ȡ����
    void deleteData();  // ɾ����Ա
    void changeData();  // �޸ĳ�Ա��Ϣ
    void findData();    // ���ҳ�Ա��Ϣ
    void deleteByClubID(int clubID); // ɾ�����ų�Ա


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
