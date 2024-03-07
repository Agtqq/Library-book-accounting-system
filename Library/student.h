#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<string>
#include<iomanip>
#include<iostream>
#include"list"
#include "Exception_input.h"

using namespace std;


class student
{
protected:
    int ID_number;
    string Student_name;
    char faculty[10];
    int stbno[5];
    int token;

public:
    student();
    void create_student()  //���� ������ � ��������
    {
        cout << "\n������� ����� ����. ������: ";
        int check;
        
        while (1)
        {
            cin >> check;
            try
            {
                rewind(stdin);
                if (cin.fail())
                    throw Exception(static_cast<int>(Errors::incorrectType), "�������� ���: int");
                try
                {
                    if (check > 999999 || check < 100000)
                        throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                    break;
                }
                catch (Exception_input exp)
                {
                    exp.show();
                }
            }
            catch (Exception error)
            {
                error.show();
                
            }
        }
        
        ID_number = check;

        cout << "\n\n��� ��������: ";
        rewind(stdin);
        getline(cin, Student_name);
        cout << "\n\n���������(������� �����): \n1.����� \n2.���� \n3.��� \n4.��� \n5.��� \n6.��� \n7.��\n�����:";
        int fakult;
        while (1)
        {
            cin >> fakult;
            try
            {
                rewind(stdin);
                if (cin.fail())
                    throw Exception(static_cast<int>(Errors::incorrectType), "�������� ���: int");
                if (fakult > 0 && fakult < 8) break;
            }
            catch (Exception error)
            {
                error.show();

            }
        }
        switch (fakult)
        {
        case 1:
            strcpy_s(faculty, "�����");
            break;
        case 2:
            strcpy_s(faculty, "����");
            break;
        case 3:
            strcpy_s(faculty, "���");
            break;
        case 4:
            strcpy_s(faculty, "���");
            break;
        case 5:
            strcpy_s(faculty, "���");
            break;
        case 6:
            strcpy_s(faculty, "���");
            break;
        case 7:
            strcpy_s(faculty, "��");
            break;
        default:
            break;
        }
        token = 0;
        for (int i = 0; i < 5; i++)
        {
            stbno[i] = 0;
        }
        
        
    }
    void show()   //����� ������ � ��������
    {
        cout << "\n����� ����. ������: " << ID_number;
        cout << "\n���: ";
        cout<<Student_name;
        cout << "\n���������: ";
        cout << faculty;
        cout << "\n���������� ������ ����: " << token;
        if (token >0)
            for (int i = 0; i < 5; i++)
            {
                if (stbno[i]!=0)
                cout << "\n����� �����: " << stbno[i];
            }
            
    }
    void modify()  //��������� ���
    {
        cout << "\n����� ����. ������: " << ID_number;
        cout << "\n����� ���: ";
        //cin.ignore();
        rewind(stdin);
        getline(cin,Student_name);
    }
    int get_number()
    {
        return ID_number;
    }
    int retstbno(int bookn)
    {
        for (int i = 0; i < 5; i++)
        {
            if (stbno[i] == bookn)
            {
                return 1;
                break;
            }
        }
        return 0;
    }
    int rettoken()
    {
        return token;
    }
    int findbook(int num) //�����, ���� �� ����� � ��������
    {
        int check = 0;
        for (int i = 0; i < 5; i++)
        {
            if (stbno[i] == num)
            {
                cout << ID_number << "\n";
                check = 1;
            }
        }
        return check;
    }
    int changefacult(int fakult) //��������� ����������
    {
        switch (fakult)
        {
        case 1:
            strcpy_s(faculty, "�����");
            break;
        case 2:
            strcpy_s(faculty, "����");
            break;
        case 3:
            strcpy_s(faculty, "���");
            break;
        case 4:
            strcpy_s(faculty, "���");
            break;
        case 5:
            strcpy_s(faculty, "���");
            break;
        case 6:
            strcpy_s(faculty, "���");
            break;
        case 7:
            strcpy_s(faculty, "��");
            break;
        default:
            break;
        }
        return 1;
    }
    int findfaculty(int fakult)  
    {
        switch (fakult)
        {
        case 1:
            if (strcmp(faculty, "�����")==0) return 1;
            break;
        case 2:
            if (strcmp(faculty, "����")==0) return 1;
            break;
        case 3:
            if (strcmp(faculty, "���")==0) return 1;
            break;
        case 4:
            if (strcmp(faculty, "���")==0) return 1;
            break;
        case 5:
            if (strcmp(faculty, "���")==0) return 1;
            break;
        case 6:
            if (strcmp(faculty, "���")==0) return 1;
            break;
        case 7:
            if (strcmp(faculty, "��")==0) return 1;
            break;
        default:
            break;
        }
        return 0;
    }
    string retname()
    {
        return Student_name;
    }
    void addtoken()
    {
        token++;
    }
    void resettoken()
    {
        token --;
    }
    void getstbno(int t)
    {
        for (int i = 0; i < 5; i++)
        {
            if (stbno[i] == 0)
            {
                stbno[i] = t;
                break;
            }
        }
        
    }
    int changestbno(int bookn) //������ ������ ����� � ��������
    {
        for (int i = 0; i < 5; i++)
        {
            if (stbno[i] == bookn)
            {
                stbno[i]=0;
                return 1;
                break;
            }
        }
        return 0;
    }

    int candelete()
    {
        if (token == 0) return 1;
        else return 0;
    }
    void report() //����� ������ � ���� ������
    {
        cout << "\t" << ID_number << setw(40) << Student_name << setw(15) << faculty << setw(10) << token << endl;
    }

    friend std::ostream& operator<< (std::ostream& out, const student& st);

    friend std::istream& operator>> (std::istream& in, student& st);
};