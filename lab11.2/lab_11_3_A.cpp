#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
#include <fstream>

using namespace std;

enum Specialty { PROGRAMMER, ENGINEER, PHYSICIAN };
string specStr[] = { "��", "��", "��" };
struct Student
{
    char prizv[64];
    int kurs;
    Specialty spec;
    int physics;
    int math;
    int inform;

};

void Create(char* fname);
void Print(char* fname);
int fRead(fstream& f, const int i);
char SRead(fstream& f, const int i);
int TRead(fstream& f, const int i);
void fChange(fstream& f, const int i, const int j);
void sortBin(char* fname);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char fname[61];
    double MinAve = 0.0;
    int countPhysics = 0;
    int countMathematics = 0;
    int countInformatics = 0;
    int choice;
    do {
        cout << "������ ����� �������:" << endl;
        cout << "[1] - �������� ������ ��������" << endl;
        cout << "[2] - ������� ������ �� �����" << endl;
        cout << "[3] - Գ����� ������������ ����"
            << endl << endl;
        cout << " [0] - ����� �� ��������" << endl << endl;
        cout << "������ ����� �������: "; cin >> choice;
        cout << endl << endl << endl;

        switch (choice)
        {
        case 1:
            cin.get(); cin.sync();
            cout << "������ ��'� �����: "; cin.getline(fname, sizeof(fname));
            Create(fname);
            break;
        case 2:
            cin.get(); cin.sync();
            cout << "������ ��'� �����: "; cin.getline(fname, sizeof(fname));
            Print(fname);
            break;
        case 3:
            cin.get(); cin.sync();
            cout << "������ ��'� �����: "; cin.getline(fname, sizeof(fname));
            sortBin(fname);
            break;
        default:
            cout << "�� ����� ����������� �������" << endl;
            break;
        }
    } while (choice != 0);
}

void Create(char* fname)
{
    ofstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "��������� ������� ���� '" << fname << "'" << endl;
        exit(1);
    }

    Student s;
    int spec;
    char ch;
    int i = 0;
    do {
        cout << endl;
        cout << "������� � " << i + 1 << ":" << endl;
        ++i;
        cin.sync();
        cout << "�������: ";  cin >> s.prizv;
        cout << "����: "; cin >> s.kurs;
        cout << "������������ (0 - ��, 1 - ��, 2 - ��): "; cin >> spec;
        s.spec = (Specialty)spec;
        cout << "��� �� ������: "; cin >> s.physics;
        cout << "��� �� ����������: "; cin >> s.math;
        cout << "��� �� �����������: "; cin >> s.inform;
        if (!f.write((char*)&s, sizeof(Student)))
        {
            cerr << "��������� ������� ����" << endl;
            exit(1);
        }
        cout << "������ ������ �� ������ ��������? (Y/N): "; cin >> ch;

    } while (ch == 'Y' || ch == 'y');

}

void Print(char* fname)
{
    ifstream f(fname, ios::binary);
    if (!f)
    {
        cerr << "��������� ������� ����" << endl;
        exit(1);
    }

    Student s;
    int i = 0;

        cout << "================================================================================"
        << endl;
    cout << "| �  | �������     | ���� | ������������ | Գ���� | ���������� | ����������� |"
        << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    while (f.read((char*)&s, sizeof(Student)))
    {
        cout << "| " << setw(2) << right << i + 1 << " "
            << "| " << setw(13) << left << s.prizv
            << "| " << setw(3) << right << s.kurs << "  "
            << "| " << setw(8) << right << specStr[s.spec] << "      "
            << "| " << setw(4) << right << s.physics << "   "
            << "| " << setw(6) << right << s.math << "      "
            << "| " << setw(6) << right << s.inform << "     |" << endl;
        i++;
    }
    cout << "================================================================================" << endl;
}
void sortBin(char* fname)
{
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f)
    {
        cerr << "��������� ������� ����" << endl;
        exit(1);
    }


    f.seekg(0 * (long)sizeof(Student), ios::end);
    int size = f.tellg() / (sizeof(Student));
    f.seekg(0, ios::beg);
    for (int i0 = 1; i0 < size; i0++)
        for (int i1 = 0; i1 < size - i0; i1++)
        {
            int specialty1 = fRead(f, i1);
            int specialty2 = fRead(f, i1 + 1);
            char prizv1 = SRead(f, i1);
            char prizv2 = SRead(f, i1 + 1);
            int kurs1 = TRead(f, i1);
            int kurs2 = TRead(f, i1 + 1);
            if ((specialty1 > specialty2)
                ||
                (specialty1 == specialty2 && prizv1 < prizv2)
                ||
                (specialty1 == specialty2 && prizv1 == prizv2 && kurs1 > kurs2))
                fChange(f, i1, i1 + 1);
        }
    f.seekp(0, ios::end);
}

int fRead(fstream& f, const int i)
{
    Student student;
    f.seekg(i * (long)sizeof(Student));
    f.read((char*)&student, sizeof(Student));
    int specialty = student.spec;
    return specialty;
}

char SRead(fstream& f, const int i)
{
    Student student;
    f.seekg(i * (long)sizeof(Student));
    f.read((char*)&student, sizeof(Student));
    char prizv[64];
    strcpy_s(prizv, sizeof(prizv), student.prizv);
    return *prizv;
}

int TRead(fstream& f, const int i)
{
    Student student;
    f.seekg(i * (long)sizeof(Student));
    f.read((char*)&student, sizeof(Student));
    int kurs = student.kurs;
    return kurs;
}

void fChange(fstream& f, const int i, const int j)
{
    Student si, sj, temp;
    f.seekg(i * (long)sizeof(Student));
    f.read((char*)&si, sizeof(Student));
    temp = si;
    f.seekg(j * (long)sizeof(Student));
    f.read((char*)&sj, sizeof(Student));
    f.seekp(i * (long)sizeof(Student));
    f.write((char*)&sj, sizeof(Student));
    f.seekp(j * (long)sizeof(Student));
    f.write((char*)&temp, sizeof(Student));
}