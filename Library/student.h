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
    void create_student()  //ввод данных о студенте
    {
        cout << "\nВведите номер студ. билета: ";
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
        
        ID_number = check;

        cout << "\n\nФИО студента: ";
        rewind(stdin);
        getline(cin, Student_name);
        cout << "\n\nФакультет(введите номер): \n1.ФКСиС \n2.ФИТУ \n3.ФКП \n4.ФИБ \n5.ИЭФ \n6.ФРЭ \n7.ВФ\nВыбор:";
        int fakult;
        while (1)
        {
            cin >> fakult;
            try
            {
                rewind(stdin);
                if (cin.fail())
                    throw Exception(static_cast<int>(Errors::incorrectType), "Ожидался тип: int");
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
            strcpy_s(faculty, "ФКСиС");
            break;
        case 2:
            strcpy_s(faculty, "ФИТУ");
            break;
        case 3:
            strcpy_s(faculty, "ФКП");
            break;
        case 4:
            strcpy_s(faculty, "ФИБ");
            break;
        case 5:
            strcpy_s(faculty, "ИЭФ");
            break;
        case 6:
            strcpy_s(faculty, "ФРЭ");
            break;
        case 7:
            strcpy_s(faculty, "ВФ");
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
    void show()   //вывод данных о студенте
    {
        cout << "\nНомер студ. билета: " << ID_number;
        cout << "\nФИО: ";
        cout<<Student_name;
        cout << "\nФакультет: ";
        cout << faculty;
        cout << "\nКоличество взятых книг: " << token;
        if (token >0)
            for (int i = 0; i < 5; i++)
            {
                if (stbno[i]!=0)
                cout << "\nНомер книги: " << stbno[i];
            }
            
    }
    void modify()  //изменение ФИО
    {
        cout << "\nНомер студ. билета: " << ID_number;
        cout << "\nНовое ФИО: ";
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
    int findbook(int num) //поиск, есть ли книга у студента
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
    int changefacult(int fakult) //изменение факультета
    {
        switch (fakult)
        {
        case 1:
            strcpy_s(faculty, "ФКСиС");
            break;
        case 2:
            strcpy_s(faculty, "ФИТУ");
            break;
        case 3:
            strcpy_s(faculty, "ФКП");
            break;
        case 4:
            strcpy_s(faculty, "ФИБ");
            break;
        case 5:
            strcpy_s(faculty, "ИЭФ");
            break;
        case 6:
            strcpy_s(faculty, "ФРЭ");
            break;
        case 7:
            strcpy_s(faculty, "ВФ");
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
            if (strcmp(faculty, "ФКСиС")==0) return 1;
            break;
        case 2:
            if (strcmp(faculty, "ФИТУ")==0) return 1;
            break;
        case 3:
            if (strcmp(faculty, "ФКП")==0) return 1;
            break;
        case 4:
            if (strcmp(faculty, "ФИБ")==0) return 1;
            break;
        case 5:
            if (strcmp(faculty, "ИЭФ")==0) return 1;
            break;
        case 6:
            if (strcmp(faculty, "ФРЭ")==0) return 1;
            break;
        case 7:
            if (strcmp(faculty, "ВФ")==0) return 1;
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
    int changestbno(int bookn) //запись номера книги к студенту
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
    void report() //вывод данных в одну строку
    {
        cout << "\t" << ID_number << setw(40) << Student_name << setw(15) << faculty << setw(10) << token << endl;
    }

    friend std::ostream& operator<< (std::ostream& out, const student& st);

    friend std::istream& operator>> (std::istream& in, student& st);
};