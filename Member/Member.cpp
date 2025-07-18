#include"Member.h"
#include "../Menu/Menu.h"
#include"../Action/Action.h"
#include "../Member/Member.h"
#include "../Source/Source.h"
#include "../MassOrg/MassOrg.h"


// ����/���ܺ�����ԭ���޸�
void code(char* sSrc, const char* sKey) {
    int nKey = strlen(sKey);
    int nSrc = strlen(sSrc);
    for (int i = 0; i < nSrc; ++i) {
        sSrc[i] ^= sKey[i % nKey];
    }
}
// ��ȡ���������ļ������ܣ����ؽ��ܺ������
void readPasswordFromFile(const char* filename, const char* key, char* outPwd, int maxLen) {
    ifstream fin(filename);
    if (!fin) {
        throw "�����ļ���ȡʧ�ܣ�";
    }
    fin.getline(outPwd, maxLen); // ��ȡһ��
    fin.close();
    code(outPwd, key); // ����
}
// д��������뵽�ļ�
void writePasswordToFile(const char* filename, const char* key, const char* plainPwd) {
    char buf[64];
    strcpy_s(buf, plainPwd);
    code(buf, key); // ����
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

// �ļ��������д����������
ofstream& operator<<(ofstream& os, const ActionMemData& data) {
    os << data.memId << '\t' << data.actId << '\n';
    return os;
}

// �ļ������룺���ļ���ȡ���������
ifstream& operator>>(ifstream& is, ActionMemData& data) {
    is >> data.memId >> data.actId;
    return is;
}


//////////////////////�糤����������غ���
ostream& operator<<(ostream& os, const Proprieter& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName.c_str() << "\t" << data.sSex.c_str() << "\t"
        << data.sPhone.c_str() << "\t" << data.sEmail.c_str() << endl;
    return os;
}

istream& operator>>(istream& is, Proprieter& data) {
    is >> data.clubID;
    is >> data.nId;
    if (data.nId <= 0) {//����ı�� <= 0 ��ʾ��������
        return is;
    }
    is >> data.sName >> data.sSex >> data.sPhone >> data.sEmail;
    return is;
}

ofstream& operator<<(ofstream& os, const Proprieter& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName << "\t" << data.sSex << "\t"
        << data.sPhone << "\t" << data.sEmail << endl; //ʵ����д �ļ�
    return os;
}

ifstream& operator>>(ifstream& is, Proprieter& data) {
    is >> data.clubID >> data.nId >> data.sName >> data.sSex >> data.sPhone >> data.sEmail; //��ȡ�ļ����� �� data ��
    return is;
}



/// /////////////////��ͨ��Ա������غ���
ostream& operator<<(ostream& os, const NormalMem& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName.c_str() << "\t" << data.sSex.c_str() << "\t"
        << data.sPhone.c_str() << "\t" << data.sEmail.c_str() << endl;
    return os;
}

istream& operator>>(istream& is, NormalMem& data) {
    is >> data.clubID;
    is >> data.nId;
    if (data.nId <= 0) {//����ı�� <= 0 ��ʾ��������
        return is;
    }
    is >> data.sName >> data.sSex >> data.sPhone >> data.sEmail;
    return is;
}

ofstream& operator<<(ofstream& os, const NormalMem& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName << "\t" << data.sSex << "\t"
        << data.sPhone << "\t" << data.sEmail << endl; //ʵ����д �ļ�
    return os;
}

ifstream& operator>>(ifstream& is, NormalMem& data) {
    is >> data.clubID >> data.nId >> data.sName >> data.sSex >> data.sPhone >> data.sEmail; //��ȡ�ļ����� �� data ��
    return is;
}



//////////////�ǻ�Ա������غ���

ostream& operator<<(ostream& os, const NonMem& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName.c_str() << "\t" << data.sSex.c_str() << "\t"
        << data.sPhone.c_str() << "\t" << data.sEmail.c_str() << endl;
    return os;
}

istream& operator>>(istream& is, NonMem& data) {
    is >> data.clubID;
    is >> data.nId;
    if (data.nId <= 0) {//����ı�� <= 0 ��ʾ��������
        return is;
    }
    is >> data.sName >> data.sSex >> data.sPhone >> data.sEmail;
    return is;
}

ofstream& operator<<(ofstream& os, const NonMem& data) {
    os << data.clubID << "\t" << data.nId << "\t" << data.sName << "\t" << data.sSex << "\t"
        << data.sPhone << "\t" << data.sEmail << endl; //ʵ����д �ļ�
    return os;
}

ifstream& operator>>(ifstream& is, NonMem& data) {
    is >> data.clubID >> data.nId >> data.sName >> data.sSex >> data.sPhone >> data.sEmail; //��ȡ�ļ����� �� data ��
    return is;
}





//---------------------------------
/**********************************
   CMember ��ʼ����
***********************************/
//---------------------------------
//���ݲ˵��� ���� ��Ӧ�ĺ���
void CMember::controlForP() {
    CSource source;
    CAction action;
    CMassOrg massorg;
    while (true) {
        showMenuForP(); //��ʾ�˵�
        int nKey = _getch(); //�Ⱥ��û�ѡ��
        CMenu::clearScr(); //����
        switch (nKey) {
        case '1':
            displayMem(); //��ʾ�������ų�Ա��Ϣ
            break;
        case '2':
            action.control(); //���Խ������е����Ż����
            break;
        case '3':
            source.control(); //���Խ������е�������Դ����
            break;
        case '4':
            massorg.control(); //���Խ������е����Ų���
            break;
        case '5':
            updatePresidentInfo();
            break;
        case '0': //������һ���˵�
            return;
        default:
            cout << "��Ч��ѡ�������ѡ��" << endl;
            int pause = _getch();
            break;
        }
    }
}
void CMember::controlForN(CAction& action, CMassOrg& massorg) {
    while (true) {
        showMenuForN(); //��ʾ�˵�
        int nKey = _getch(); //�Ⱥ��û�ѡ��
        CMenu::clearScr(); //����
        switch (nKey) {
        case '1': //��ʾ���ŵĻ�����Ϣ
        {
            massorg.display();
            break;
        }
        
		case '2': //��ʾ���е����Ż
        {
            action.display();
			break;
        }
        
        case '3':  //�����
        {
            cout << "��������ĳ�Ա��ţ�";
            int memId;
            cin >> memId;
            cout << "������Ҫ�μӵĻ��ţ�";
            int actId;
            cin >> actId;

            ActionMemData amd;
            amd.memId = memId;
            amd.actId = actId;

            ofstream fout("cactionmemdata.txt", ios::app);
            if (fout.is_open()) {
                fout << amd;
                fout.close();
                cout << "�μӻ�ɹ�����Ϣ�ѱ��浽�ļ���" << endl;
            }
            else {
                cout << "�ļ�д��ʧ�ܣ�" << endl;
            }
            _getch();
            break;
        }

        
        case '4':  // �˳��
        {
            cout << "��������ĳ�Ա��ţ�";
            int memId;
            cin >> memId;
            cout << "������Ҫ�˳��Ļ��ţ�";
            int actId;
            cin >> actId;

            // ��ȡ���б�����Ϣ
            vector<ActionMemData> allData;
            ifstream fin("cactionmemdata.txt");
            ActionMemData temp;
            while (fin >> temp) {
                // ����Ҫɾ���ļ�¼
                if (!(temp.memId == memId && temp.actId == actId)) {
                    allData.push_back(temp);
                }
            }
            fin.close();

            // ����д���ļ�
            ofstream fout("cactionmemdata.txt");
            for (const auto& d : allData) {
                fout << d;
            }
            fout.close();

            cout << "�˳���ɹ�����Ϣ�Ѵ��ļ����Ƴ���" << endl;
            _getch();
            break;
        }
        
        case '5':  // �˳�����
        {
            cout << "��������ĳ�Ա������˳����ţ�";
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
                cout << "�ѳɹ��˳����ţ�" << endl;
            }
            else {
                cout << "δ�ҵ��ñ�ŵĳ�Ա���˳�ʧ�ܡ�" << endl;
            }
            _getch();
            break;
        }

        case '0': //������һ���˵�
            return;
        default:
            cout << "��Ч��ѡ�������ѡ��" << endl;
            int pause = _getch();
            break;
        }
    }
}
void CMember::controlForNon(CMassOrg& massorg)
{
    while (true) {
        showMenuForNon(); //��ʾ�˵�
        int nKey = _getch(); //�Ⱥ��û�ѡ��
        CMenu::clearScr(); //����
        switch (nKey) {
        case '1':
            massorg.display(); //��ʾ����������Ϣ
            break;
        case '2': {
            // ��������
            addData();
            break;
        }

        case '0': //������һ���˵�
            return;
        default:
            cout << "��Ч��ѡ�������ѡ��" << endl;
            int pause = _getch();
            break;
        }
    }
}



void CMember::updatePresidentInfo() {
    system("cls");
    cout << "=== �����糤������Ϣ ===" << endl;

    Proprieter president;
    cout << "���������ڵ����ű�ţ�";
    cin >> president.nId;
    cout << "�������糤������";
    cin >> president.sName;
    cout << "�������糤�Ա�";
    cin >> president.sSex;
    cout << "�������糤�绰��";
    cin >> president.sPhone;
    cout << "�������糤���䣺";
    cin >> president.sEmail;

    // ���糤��Ϣд���ļ�
    ofstream fout("president_info.txt");
    if (fout.is_open()) {
        fout << president;
        fout.close();
        cout << "�糤��Ϣ�ѱ���ɹ���" << endl;
    }
    else {
        cout << "����ʧ�ܣ��޷����ļ���" << endl;
    }

    system("pause");
}

void CMember::showPresidentInfo() {
    ifstream fin("president_info.txt");
    if (fin.is_open()) {
        Proprieter president;
        fin >> president;
        fin.close();
        cout << "���ڵ����ű�ţ�" << president.nId << endl;
        cout << "������" << president.sName << endl;
        cout << "�Ա�" << president.sSex << endl;
        cout << "�绰��" << president.sPhone << endl;
        cout << "���䣺" << president.sEmail << endl;
    }
    else {
        cout << "�����糤��Ϣ���������Ƹ�����Ϣ��" << endl;
    }
}


void CMember::showMenuForP()
{
    cout << "1. ��ʾ�������ų�Ա��Ϣ" << endl;
    cout << "2. ���Ż����" << endl;
    cout << "3. ������Դ����" << endl;
    cout << "4. ���Ź���" << endl;
    cout << "5. �����糤������Ϣ" << endl;
    cout << "0. ������һ���˵�" << endl;
    cout << "��ѡ�������";
}

void CMember::showMenuForN()
{
    cout << "1. ��ʾ���ŵĻ�����Ϣ" << endl;
    cout << "2. ��ʾ�������Ż" << endl;
    cout << "3. �����" << endl;
	cout << "4. �˳��" << endl;
    cout << "5. �˳�����" << endl;
    cout << "0. ������һ���˵�" << endl;
    cout << "��ѡ�������";
}

void CMember::showMenuForNon()
{
    cout << "1. ��ʾ���ŵĻ�����Ϣ" << endl;
    cout << "2. ѡ���������" << endl;
    cout << "0. ������һ���˵�" << endl;
    cout << "��ѡ�������";
}

void CMember::SumMenu(CAction& action, CMassOrg& massorg)
{
    // ��ʼ�������ļ���ֻ������һ�Σ�ʵ��ʹ��ʱ��ע�͵���
    //writePasswordToFile("proprietercode.txt", "mykey123", "567468");
    //writePasswordToFile("normalmemcode.txt", "mykey123", "970975");

    while (true) {
        const char* key = "mykey123";
        const int maxPwdLen = 64;

        vector<string> aMenu;
        aMenu.push_back("1���糤");
        aMenu.push_back("2����ͨ��Ա");
        aMenu.push_back("3���ǻ�Ա");
        aMenu.push_back("0���������˵�");
        CMenu::showMenu(aMenu);

        cout << "��ѡ�������ݣ�";
        char choice = _getch();
        CMenu::clearScr();

        CMember member;

        try {
            switch (choice) {
            case '1': {
                cout << "�������糤���룺";
                char inputPwd[maxPwdLen];
                cin >> inputPwd;
                char truePwd[maxPwdLen];
                readPasswordFromFile("proprietercode.txt", key, truePwd, maxPwdLen);
                if (strcmp(inputPwd, truePwd) == 0) {
                    member.controlForP();
                }
                else {
                    cout << "��������޷������糤���棡" << endl;
                    _getch();
                }
                break;
            }
            case '2': {
                cout << "��������ͨ��Ա���룺";
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
                    cout << "��������޷�������ͨ��Ա���棡" << endl;
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
                cout << "��Чѡ����������롣" << endl;
                break;
            }
        }
        catch (const char* e) {
            cerr << "����" << e << endl;
            _getch();
        }
    }
}



// ��ʾ�������ų�Ա��Ϣ
void CMember::displayMem() {
    cout << "���糤��Ϣ��" << endl;
    showPresidentInfo();
    cout << "����ͨ��Ա��Ϣ��" << endl;
    for (const auto& m : aNormalMems) {
        cout << m;
    }
    cout << "�����������..." << endl;
    _getch();
}

// �������ţ������ͨ��Ա��
void CMember::addData() {
    NormalMem newMem;
    cout << "�����������������ű�ţ�" << endl;
    cin >> newMem.clubID;
    
    cout << "�������Ա��ţ�";
    cin >> newMem.nId;
    // ������Ƿ��Ѵ���
    for (const auto& m : aNormalMems) {
        if (m.nId == newMem.nId) {
            cout << "�ó�Ա����Ѵ��ڣ������ظ����룡" << endl;
            _getch();
            return;
        }
    }
    cout << "������������";
    cin >> newMem.sName;
    cout << "�������Ա�";
    cin >> newMem.sSex;
    cout << "������绰��";
    cin >> newMem.sPhone;
    cout << "���������䣺";
    cin >> newMem.sEmail;
    aNormalMems.push_back(newMem);
    saveData();
    cout << "�������ųɹ���" << endl;
    _getch();
}

// �������ݵ��ļ�
void CMember::saveData() {
    // �����糤
    ofstream f1(sProprieterFileName);
    for (const auto& p : aProprieters) {
        f1 << p;
    }
    f1.close();
    // ������ͨ��Ա
    ofstream f2(sNormalMemFileName);
    for (const auto& m : aNormalMems) {
        f2 << m;
    }
    f2.close();
}

// ���ļ���ȡ����
void CMember::readData() {
    aProprieters.clear();
    aNormalMems.clear();
    // ��ȡ�糤
    ifstream f1(sProprieterFileName);
    Proprieter p;
    while (f1 >> p) {
        if (p.nId > 0)
            aProprieters.push_back(p);
    }
    f1.close();
    // ��ȡ��ͨ��Ա
    ifstream f2(sNormalMemFileName);
    NormalMem m;
    while (f2 >> m) {
        if (m.nId > 0)
            aNormalMems.push_back(m);
    }
    f2.close();
}

// ɾ����Ա
void CMember::deleteData() {
    cout << "������Ҫɾ���ĳ�Ա��ţ�";
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
        cout << "��ɾ�� " << count << " ����Ա��" << endl;
    else
        cout << "δ�ҵ��ñ�ŵĳ�Ա��" << endl;
    _getch();
}

// �޸ĳ�Ա��Ϣ
void CMember::changeData() {
    cout << "������Ҫ�޸ĵĳ�Ա��ţ�";
    int id;
    cin >> id;
    bool found = false;
    for (auto& m : aNormalMems) {
        if (m.nId == id) {
            cout << "�ҵ���Ա��" << m;
            cout << "�������µ�������";
            cin >> m.sName;
            cout << "�������µ��Ա�";
            cin >> m.sSex;
            cout << "�������µĵ绰��";
            cin >> m.sPhone;
            cout << "�������µ����䣺";
            cin >> m.sEmail;
            found = true;
            break;
        }
    }
    if (found) {
        saveData();
        cout << "�޸ĳɹ���" << endl;
    }
    else {
        cout << "δ�ҵ��ñ�ŵĳ�Ա��" << endl;
    }
    _getch();
}

// ���ҳ�Ա��Ϣ
void CMember::findData() {
    cout << "������Ҫ���ҵĳ�Ա��ţ�";
    int id;
    cin >> id;
    bool found = false;
    for (const auto& m : aNormalMems) {
        if (m.nId == id) {
            cout << "�ҵ���Ա��" << m;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "δ�ҵ��ñ�ŵĳ�Ա��" << endl;
    }
    _getch();
}

// ɾ������ʱͬʱɾ�����������г�Ա��Ϣ
void CMember::deleteByClubID(int clubID) {
    int count = 0;
    for (auto it = aNormalMems.begin(); it != aNormalMems.end(); ) {
        // ���� NormalMem �� clubID �ֶ�
        if (it->clubID == clubID) {
            it = aNormalMems.erase(it);
            count++;
        }
        else {
            ++it;
        }
    }
    saveData();
    cout << "��ɾ�����ű��Ϊ " << clubID << " �� " << count << " ����Ա��" << endl;
    _getch();
}


CMember::CMember()
{
    sProprieterFileName = "proprieter.txt"; //�糤�ļ���
    sNormalMemFileName = "normalmem.txt"; //��ͨ��Ա�ļ���
    //�����������ȡ���е��糤����ͨ��Ա����
    readData();
}