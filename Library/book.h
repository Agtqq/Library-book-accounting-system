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
        void create_book()  //ввод данных книги
        {
            cout << "\nНомер книги: ";
            int check;

            while (1)
            {
                cin >> check;
                try
                {
                    rewind(stdin);
                    if (cin.fail())
                        throw Exception(static_cast<int>(Errors::incorrectType), "Ожидался тип: int");
                    try
                    {
                        if (check > 999999 || check < 100000)
                            throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
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
            cout << "\nНазвание книги: ";
            //cin.ignore();
            rewind(stdin);
            getline(cin, book_name);
            cout << "\nАвтор: ";
            //cin.ignore();
            rewind(stdin);
            getline(cin, author_name);
            cout << "\nКоличесвто экземпляров: ";
            while (1) 
            {
                cin >> book_count;
                if (book_count > 0) break;
                cout << "Количество книг не может быть меньше 1";
            }
            
            availible = 1;
            
        }

        void show() //вывод данных
        {
            cout << "\nНомер книги: " << book_number;
            cout << "\nНазвание: " << book_name;
            cout << "\nАвтор: " << author_name;
            cout << "\nКоличество оставшихся: " << book_count;
            if (availible)
            {
                cout << "\nНаличие: " << "есть" << endl;
            }
            else cout << "\nНаличие: " << "нету" << endl;
        }
        void modify() //изменение названия и автора
        {
            cout << "\nНомер книги: " << book_number;
            cout << "\nНовое название: ";
            rewind(stdin);
            getline(cin, book_name);
            cout << "\nАвтор: ";
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

        void report() //вывод в строку
        {
            cout << book_number << setw(30) << book_name << setw(25) << author_name;
            if (availible)
            {
                cout << setw(25) << "есть" << endl;
            }
            else cout << setw(25) << "нету" << endl;
           
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
                cout << "\nтакие книги закончились";
                return;
            }
            book_count--;
        }

        void pluscount()
        {
            book_count++;
        }

        void addcount() //изменение количества книг
        {
            int num;
            cout << "\nНовое количество книг:";
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

