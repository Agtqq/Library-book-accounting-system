#define _CRT_SECURE_NO_WARNINGS
#include "menu.h"
#include<string.h>
#include<iomanip>
#include<iostream>
#include <string> 
#include <stdio.h>
#include <fstream>
#include "book.h"
#include "student.h"
#include "Files.h"
#include "Loop.h"
#include "Exception_input.h"
#include <io.h>

using namespace std;

Loop<book> ringB;
book bk;
Loop<student> ringS;
student st;
char stFile[12] = "student.txt";
char tempSFile[10] = "tempS.txt";
TextFile<student> fs(stFile, tempSFile);
char bkFile[9] = "book.txt";
char tempBFile[10] = "tempB.txt";
TextFile<book> fb(bkFile, tempBFile);

bool checkint(int& number) //������� �������� �� �������� ���� int
{
    try
    {
        rewind(stdin);
        if (cin.fail())
            throw Exception(static_cast<int>(Errors::incorrectType), "�������� ���: int");
        return true;
    }
    catch (Exception_input exp)
    {
        exp.show();
        return false;
    }
    catch (Exception error)
    {
        error.show();
        return false;
    }
    
}



void menu::Start() //������� ������ �� ����� � ������
{
   fs.readFromFile(ringS);
   fb.readFromFile(ringB);
    this->MainMenu();
}


void menu::End() //������� ���������� ���������
{
    fs.writeToFile(ringS); //���������� ������ � ����
    fs.CloseFile(); 
    rename("tempS.txt", "file.txt"); //��������������� �����
    rename("student.txt", "tempS.txt");
    rename("file.txt", "student.txt");
   
    fb.writeToFile(ringB);
    fb.CloseFile();
    rename("tempB.txt", "file.txt");
    rename("book.txt", "tempB.txt");
    rename("file.txt", "book.txt");
    cout << "Information Saved";
}

void menu::MainMenu() //������� �������� ����
{

    int option = 0;
    for (;;)
    {
        intro();
        cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n\t\t������� 1 ����� ����� �����";
        cout << "\n\t\t������� 2 ����� ������� �����";
        cout << "\n\t\t������� 3 ����� �������� �� ����������";
        cout << "\n\t\t������� 4 ����� �������� � �������";
        cout << "\n\t\t������� 5 ����� ����������� ������� ����������";
        cout << "\n\t\t������� 6 ����� �����";
        cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\n\t\t�����: ";
        while(1)
        {
            cin >> option;
            if (checkint(option)) break;
        }
        
        switch (option)
        {
        case 1:system("cls");
            this->issue_book();
            break;
        case 2:system("cls");
            this->book_return();
            break;
        case 3:system("cls");
            this->student_menu();
            break;
        case 4:system("cls");
            this->book_menu();
            break;
        case 5:
            this->rules();
            break;
        case 6:
            this->End();
            exit(0);
            break;
        default:cout << "\a";
            this->End();
            exit(0);
        }
    }
}

void menu:: write_book() //������� ���������� ����� �� ������� � ������
{
    system("cls");
    int amount, check;

    cout << "������� ���������� ����: ";
    while (1) //�������� ���������� ����� �� ��� int
    {
        cin >> amount;
        if (checkint(amount)) break;
    }
    cout << "������� �����: " << endl;
    for (int i = 0; i < amount; i++)
    {
        bk.create_book(); //������ ������ �����
        check=ringB.pushnew(bk); //��������� � ������
        if (check) cout << "\t\t\n\n����� ������� ��������...";
    }
    
    _getch();
}
void menu::write_student()//������� ���������� �������� �� ������� � ������
{
    system("cls");
    int amount, check;
   
    cout << "������� ���������� ���������: ";
    while (1) //�������� ���������� ����� �� ��� int
    {
        cin >> amount;
        if (checkint(amount)) break;
    }
       
    cout << "������� ���������: " << endl;
    for (int i = 0; i < amount; i++)
    {
        st.create_student();//������ ������ ��������
        check=ringS.pushnew(st);//��������� � ������
        if (check) cout << "\t\t\n\n������� ������� �������...";
    }
    _getch();
}

void menu::display_a_book() //������� ������ ����� � �������
{
    system("cls");
    cout << "\n���������� � �����\n";
    int check = 0, n, num, choise, check2=0;
    string name;
    cout << "\n\n\t1. ����� �� �������� 0. ����� �� ������: ";
    while (1)
    {
        cin >> choise;
        if (choise == 1 || choise == 0) break;
    }

    if (choise) //����� �� ��������
    {
        cout << "\n\n\t������� �������� ����� � �������� "": ";
        rewind(stdin);
        getline(cin, name);
        check = ringB.findbyname(name);
    }
    else //����� �� ������ �����
    {
        cout << "\n\n\t������� ����� �����: ";
        while (1) //�������� ���������� ����� �� ����������
        {
            cin >> num;
            if (checkint(num))
            {
                try
                {
                    if (num > 999999 || num < 100000)
                        throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                    break;
                }
                catch (Exception_input exp)
                {
                    exp.show();
                }
            }
            
        }
        
        check = ringB.printElement(num);
    }
    int choise2 = 0;
    if (check == 1&&choise==0) //�������� � ���� ���� ��������� ���� ����� �� �����
    { 

        cout << "����������� ����� ��������� ���� ��������� ����� �� �����? 1. �� 0.���";
        while (1) 
        {
            cin >> choise2;
            if (choise2 == 1 || choise2 == 0) break;
        }
        if (choise2 && choise==0) //����� ������� ��������� ������� �����
        {
            cout << "\n�������� � ����������� �����:\n\n";
            check2 = ringS.findissuebook(num);
            if (check2 == 0) cout << "��� ���������� � ����������";
        }
    }

    if (check == 0) cout << "\n\n����� ����� �� ����������";
    _getch();
}

void menu:: display_a_student() //������� ������ �������� � �������
{
    system("cls");
    cout << "\n���������� � ��������\n";
    int check = 0, n, num, choise;
    string name;
    cout << "\n\n\t1. ����� �� ����� 0. ����� �� ������: ";
    cin >> choise;
    if (choise) //����� �� ���
    {
        cout << "\n\n\t������� ��� ��������: ";
        rewind(stdin);
        getline(cin, name);
        check = ringS.findbyname(name);
    }
    else//����� �� ������ ����. ������
    {
        cout << "\n\n\t������� ����� ����. ������: ";

        while (1)
        {
            cin >> num;
            if (checkint(num))
            {
                try
                {
                    if (num > 999999 || num < 100000)
                        throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                    break;
                }
                catch (Exception_input exp)
                {
                    exp.show();
                }
            }

        }
    
        check = ringS.printElement(num);
    }

       
    if(check==0) cout << "\n\n����� ������� �� ����������";
    _getch();
}

void menu::display_faculty() //����� ���� ��������� ������������� ����������
{
    system("cls");
    int check = 0, n, num, choise;
    string name;
    cout << "\n\n\t������� �����: \n1.����� \n2.���� \n3.��� \n4.��� \n5.��� \n6.��� \n7.��\n�����: ";
    int  fakult;
    while (1) //����� ���������� �� ������
    {
        cin >> fakult;
        if (checkint(fakult))
        {
            if (fakult > 0 && fakult < 8) break;
        }

    }
    system("cls");
    cout << "\n��� �������� ����������\n";
    cout << "==============================================================================================\n";
    cout << "\t����� �������������" << setw(10) << "���" << setw(30) << "��������" << setw(20) << "���� ����\n";
    cout << "==============================================================================================\n";

    check=ringS.printfaculty(fakult); //����� ��������
    if (check == 0) cout << "\n\n��� ��������� ����� ����������";
    _getch();
}

void menu::modify_book() //������� ��������� ���������� � �����
{
    system("cls");
    int n;
    int found = 0;
    int check = 0;
    int choise;
    cout << "\n\n\t�������� ��������� � �����... ";
    cout << "\n\n\t������� ��������������� ����� �����: ";
    while (1)//�������� ����������
    {
        cin >> n;
        if (checkint(n))
        {
            try
            {
                if (n > 999999 || n < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }
    cout << "\n1.�������� ������ 0.�������� ����������" << endl;
    while (1)
    {
        cin >> choise;
        if (choise==1||choise==0) break;
    }
    if (choise)//��������� ��������
    {
        cout << "\n������� ����� ����������" << endl;
        check = ringB.changeElement(n);
    }
    else//��������� ���������� �����������
    {
        cout << "\n������� ����� ���������� ����" << endl;
        check = ringB.changeCount(n);
    }

    if (check == 1)  cout << "\n\n\t ������� ��������...";

    if (check == 0)
        cout << "\n\n ����� �� ������� ";
    _getch();
}


void menu::modify_student() //������� ��������� ���������� � ��������
{
   system("cls");
    int n;
    int found = 0;
    int check = 0;
    cout << "\n\n\t�������� ���������� � ��������... ";
    cout << "\n\n\t������� ����� ������������� ������: ";
    while (1)//�������� ����������
    {
        cin >> n;
        if (checkint(n))
        {
            try
            {
                if (n > 999999 || n < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }
    int choise;
    cout << "\n1.�������� ��� 0.�������� ���������" << endl;
    while (1)
    {
        cin >> choise;
        if (choise == 1 || choise == 0) break;
    }
    if (choise)//��������� ���
    {
        cout << "\n������� ����� ����������" << endl;
        check = ringS.changeElement(n);
    }
    else //��������� ����������
    {
        cout << "\n������� ����� ���������" << endl;
        cout << "\n\n������� �����: \n1.����� \n2.���� \n3.��� \n4.��� \n5.��� \n6.��� \n7.��\n�����:";
        int fakult;
        while (1) //����� ������ ����������
        {
            cin >> fakult;
            if (checkint(fakult))
            {
                if (fakult > 0 && fakult < 8) break;
            }
            
        }
        check = ringS.changefk(n, fakult);
     }
   

     if(check==1)  cout << "\n\n\t ������� ��������...";
  
    if (check == 0)
        cout << "\n\n ������� �� ������ ";
    _getch();
    
}

void menu::delete_student() //�������� ��������
{
   system("cls");
    int n;
    int flag = 0;
    cout << "\n\n\n\t������� ��������";
    cout << "\n\n������� ����� ������������� ������ ��������, �������� �� ������� �������: ";
    while (1) //�������� �� ����������
    {
        cin >> n;
        if (checkint(n))
        {
            try
            {
                if (n > 999999 || n < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }

    flag=ringS.deleteElement(n); //��������

    if(flag==1)
        cout << "\n\n\t������ ������� ..";
    else
        cout << "\n\n������� �� ������";
    _getch();
    
}

void menu::delete_book()//�������� �����
{
    system("cls");
    int n;
    int flag = 0;
    cout << "\n\n\n\t������� �����";
    cout << "\n\n������� ��������������� ����� �����, ������� �� ������� �������: ";
    while (1) //�������� �� ����������
    {
        cin >> n;
        if (checkint(n))
        {
            try
            {
                if (n > 999999 || n < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }

    flag = ringB.deleteElement(n); //�������� �����

    if (flag == 1)
        cout << "\n\n\t������ ������� ..";
    else
        cout << "\n\n����� �� �������";
    _getch();
}

void menu::display_all_students() //����� ���� ���������
{
    system("cls");
    
    cout << "\n\n\t\t������ ���������\n\n";
    cout << "==============================================================================================\n";
    cout << "\t����� �������������" << setw(10) << "���" << setw(30) << "��������" << setw(20) << "���� ����\n";
    cout << "==============================================================================================\n";
    
    ringS.print();
    
    _getch();
}

void menu::display_allb() //����� ���� ����
{
    system("cls");
    
    cout << "\n\n\t\t������ ����\n\n";
    cout << "====================================================================================================\n";
    cout << "����� �����" << setw(20) << "��������" << setw(25) << "�����"<<setw(30) << "�������\n";
    cout << "====================================================================================================\n";
    ringB.print();
    _getch();
}

void menu::issue_book()               //������� ������ ����� ���������
{
    system("cls");
    int bn, sn, av, no;
    int found = 0, flag = 0, k = 0;
    cout << "\t\t\n����� �����";
    cout << "\n\n\t����� ������������� ������ ��������: ";
    while (1)             //�������� �� ����������
    {
        cin >> sn;
        if (checkint(sn))
        {
            try
            {
                if (sn > 999999 || sn < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }


    if (ringS.getN(sn)== 1) //���� �������� �� ������
    {
            found = 1;                             //1 ���� �����
           if (ringS.getinfS(sn,1,0) == 1)         //��������� ����� �� ��� ����� �����
           {
                cout << "\n\n\t������� ����� �����: ";
                while (1)                          //�������� �� ����������
                {
                    cin >> bn;
                    if (checkint(bn))
                    {
                        try
                        {
                            if (bn > 999999 || bn < 100000)
                                throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                            break;
                        }
                        catch (Exception_input exp)
                        {
                            exp.show();
                        }
                    }

                }
               
                    if (ringB.getN(bn) == 1)  //���� ����� �� ������
                    {   
                        flag = 1;              //1 ���� �����
                        if(ringB.getinfB(bn,2) == 1)            //���������� ���� �� ����� � �������
                        {
                            cin.clear();
                            ringB.printElement(bn);            //������� ���������� � �����
                           
                            ringS.getinfS(sn,2, bn);           //����������� ����� � ��������
                            ringB.getinfB(bn, 3);              //��������� ���������� ����������
                           
                            cout << "\n\n\t ����� ������� �����...";
                        }
                        else cout << "����� ��� � �������";
                    
                     }
                if (flag == 0)
                    cout << "����� � ����� ������� �� ����������";
           }
            else
            cout << "������� �� ������ ������� ����� ";
     }
    
    if (found == 0)
        cout << "�������� � ����� ������� �� ����������...";
    _getch();
    system("cls");
   
}

void menu::book_return()
{
  system("cls");
    int bn;
    int sn;
    int found = 0, flag = 0, check=0;
    cout << "\t\t������� �����\n";
    cout << "\n\n\t����� ������������� ������ ��������: ";
    while (1)     //�������� �� ����������
    {
        cin >> sn;
        if (checkint(sn))
        {
            try
            {
                if (sn > 999999 || sn < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }
    
   if (ringS.getN(sn) == 1)             //���� �������� � ����� �������
        {
            found = 1;                   //1 ���� �����
            if (ringS.getinfS(sn, 5, 0) != 0)             //��������� ���� �� � ���� �����
            {
                
                cout << "\n\n\t������� ����� �����: ";
                while (1) //�������� �� ����������
                {
                    cin >> bn;
                    if (checkint(bn))   
                    {
                        try
                        {
                            if (bn > 999999 || bn < 100000)
                                throw Exception_input(static_cast<int>(Errors::outOfRange), "���������������� ����� - 6-������� �����");
                            break;
                        }
                        catch (Exception_input exp)
                        {
                            exp.show();
                        }
                    }

                }
                     
                    check = ringS.getinfS(sn, 3, bn); //���� �� � �������� ��� �����
                   
                    if (ringB.getN(bn) == 1 && check == 1)   //���� ���� �� ����� � ����� ������� � ������� ������� ��� �����
                    {
                        ringB.printElement(bn);  //������� ���������� � �����
                        flag = 1;

                        ringS.getinfS(sn, 4, bn);  //������� ����� ����� � ��������
                        ringB.getinfB(bn, 4);   //����������� ���������� ����������� �� 1
                        cout << "\n\n\t ����� ������� ����������...";
                    }
                     if (flag == 0)
                    cout << "����� � ����� ������� �� ����������";
                     if (check == 0)
                         cout << "� �������� ��� ����� �����";
            }
            else
                cout << "������� �� ���� ����.. ���������!";
    }
    
    if (found == 0)
        cout << "������ �������� �� ����������...";
    _getch();
    system("cls");
   
}

void menu::rules()  //������� ����������� �����������
{
    system("cls");
    cout << "���������� �������: ��������� ����� 150504\n\n\n";
    cout << "\t\t������� ����������� �����������\n\n";
    cout << "1.������ �������� 2 ��������� ��� ����� � ����������� ���������������� ��������.\n ������ �������� ���������������\n\n";
    cout << "2.����� ����. ������ ������� �� 6 ����.\n ��������������� ����� ����� ���� ������� �� 6 ����\n\n";
    cout << "3.������� ����� ����� �� ����� 5 ���� ������������\n\n";
    cout << "4.�������� ����� ������� ������ ���� � ���� ��� �����\n����� ����� ����� ������� � ��� ����� �� ������))\n\n";
    cout << "5.�������� �� ��������� �� ������ 6, ����� ������ ����� �����������\n\n";
    cout << "\n\n\n��������� ����������� �����������!";
    _getch();
}




void menu::intro() 
{
    //system("color 07");
    system("cls");
    cout << "��������� ����� 150504 �/� ������������ ���������� \n";
    cout << "\t\t\t\t*\t*";
    cout << "\t\t\t\t**\t**";
    cout << "\t\t\t\t***\t***";
    cout << "\t\t\t\t****\t****";
    cout << "\t\t\t\t*****\t*****";
    cout << "\t\t\t\t******\t******";
    cout << "\t\t\t\t*******\t*******";
    cout << "\t\t\t\t*******\t*******";
    cout << "\t\t\t\t******\t******";
    cout << "\t\t\t\t*****\t*****";
    cout << "\t\t\t\t****\t****";
    cout << "\t\t\t\t***\t***";
    cout << "\t\t\t\t**\t**";
    cout << "\t\t\t\t*\t*";
}


void menu::book_menu() //���� ��� ������ � �������
{
    int option;
    cout << "��������� ����� 150504 �/� ������������ ���������� \n";
    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\t������� 1 ����� �������� �����";
    cout << "\n\t\t������� 2 ����� ������� ��� �����";
    cout << "\n\t\t������� 3 ����� ����� �����";
    cout << "\n\t\t������� 4 ����� �������� ���������� � �����";
    cout << "\n\t\t������� 5 ����� ������� �����";
    cout << "\n\t\t������� 6 ����� ����������� ����� �� ������";
    cout << "\n\t\t������� 7 ��� ������ � ������� ����";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\n\t\t�����: ";
    while (1)
    {
        cin >> option;
        if (checkint(option)) break;
    }
    switch (option)
    {
    case 1:  system("cls");
        write_book();
        break;
    case 2: display_allb();
        break;
    case 3:
        int num;
        system("cls");
       
        display_a_book();
        break;
    case 4: modify_book(); break;
    case 5: delete_book(); break;
    case 6:
        int n;
        n = ringB.sort();
        if (n == 1) cout << "\n\n\t������� �������������� ";
        else  cout << "\n\n\t������ ���������� ";
        _getch();
        system("cls");
        break;
    case 7: system("cls");
        break;
    default:cout << "\a";
    }
}


void menu::student_menu() //���� ��� ������ �� ����������
{
    int option;
    cout << "��������� ����� 150504 �/� ������������ ���������� \n";
    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\t������� 1 ����� �������� ������ � ��������";
    cout << "\n\t\t������� 2 ����� ������� ���� ���������";
    cout << "\n\t\t������� 3 ����� ����� ��������";
    cout << "\n\t\t������� 4 ����� �������� ���������� � ��������";
    cout << "\n\t\t������� 5 ����� ������� ��������";
    cout << "\n\t\t������� 6 ����� ����������� ��������� �� ������";
    cout << "\n\t\t������� 7 ��� ������ � ������� ����";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\n\t\t�����: ";
    while (1)
    {
        cin >> option;
        if (checkint(option)) break;
    }
    switch (option)
    {
    case 1:  system("cls");
        write_student();
        break;
    case 2: system("cls");
        int choise;
        cout << "\t1.������� ���� ��������� ������������ 0. ������� ���� ��������� ����������";
        while (1)
        {
            cin >> choise;
            if (checkint(choise))
            {
                if (choise == 0 || choise == 1) break;
            }
        }
        if(choise) display_all_students();
        else display_faculty();
        break;
    case 3:
        int num;
        system("cls");
        display_a_student();
        break;
    case 4:system("cls");
        modify_student(); break;
    case 5: system("cls");
        delete_student(); break;
    case 6:
        int n;
         n =ringS.sort();
        if (n == 1) cout << "\n\n\t������� �������������� ";
        else  cout << "\n\n\t������ ���������� ";
        _getch();
        system("cls");
        break;
    case 7:
        break;
    default:cout << "\a";
    }
}