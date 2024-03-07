#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<fstream>
#include "Exception_input.h"
#include<string>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>

using namespace std;

class book 
{
protected:
    
    int book_number;
    string book_name;
    string author_name;
    int book_count;
    int availible;
    

  public:
      book() {};
     
      ~book() {};
        void create_book()  //���� ������ �����
        {
            cout << "\n����� �����: ";
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
            book_number=check;
            cout << "\n�������� �����: ";
            //cin.ignore();
            rewind(stdin);
            getline(cin, book_name);
            cout << "\n�����: ";
            //cin.ignore();
            rewind(stdin);
            getline(cin, author_name);
            cout << "\n���������� �����������: ";
            while (1) 
            {
                cin >> book_count;
                if (book_count > 0) break;
                cout << "���������� ���� �� ����� ���� ������ 1";
            }
            
            availible = 1;
            
        }

        void show() //����� ������
        {
            cout << "\n����� �����: " << book_number;
            cout << "\n��������: " << book_name;
            cout << "\n�����: " << author_name;
            cout << "\n���������� ����������: " << book_count;
            if (availible)
            {
                cout << "\n�������: " << "����" << endl;
            }
            else cout << "\n�������: " << "����" << endl;
        }
        void modify() //��������� �������� � ������
        {
            cout << "\n����� �����: " << book_number;
            cout << "\n����� ��������: ";
            rewind(stdin);
            getline(cin, book_name);
            cout << "\n�����: ";
            rewind(stdin);
            getline(cin, author_name);
        }
        int get_number()
        {
            return book_number;
        }

        string retname()
        {
            return book_name;
        }

        void report() //����� � ������
        {
            cout << book_number << setw(30) << book_name << setw(25) << author_name;
            if (availible)
            {
                cout << setw(25) << "����" << endl;
            }
            else cout << setw(25) << "����" << endl;
           
        }

        int if_available()
        {
            return availible;
        }

        int retcount()
        {
            return book_count;
        }

        void minuscount()
        {
            if (book_count == 0)
            {
                cout << "\n����� ����� �����������";
                return;
            }
            book_count--;
        }

        void pluscount()
        {
            book_count++;
        }

        void addcount() //��������� ���������� ����
        {
            int num;
            cout << "\n����� ���������� ����:";
            cin >> num;
            book_count = book_count + num;
        }

        int candelete()
        {
            if (availible > 0) return 1;
            else return 0;
        }

        void not_available()
        {
            availible=0;
        }

        void yes_available()
        {
            availible = 1;
        }

        friend std::ostream& operator<< (std::ostream& out, const book& bk);

        friend std::istream& operator>> (std::istream& in, book& bk);

};

