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

bool checkint(int& number) //функция проверки на введение типа int
{
    try
    {
        rewind(stdin);
        if (cin.fail())
            throw Exception(static_cast<int>(Errors::incorrectType), "Ожидался тип: int");
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



void menu::Start() //функция чтения из файла в кольцо
{
   fs.readFromFile(ringS);
   fb.readFromFile(ringB);
    this->MainMenu();
}


void menu::End() //функция завершения программы
{
    fs.writeToFile(ringS); //записываем данные в файл
    fs.CloseFile(); 
    rename("tempS.txt", "file.txt"); //переименовываем файлы
    rename("student.txt", "tempS.txt");
    rename("file.txt", "student.txt");
   
    fb.writeToFile(ringB);
    fb.CloseFile();
    rename("tempB.txt", "file.txt");
    rename("book.txt", "tempB.txt");
    rename("file.txt", "book.txt");
    cout << "Information Saved";
}

void menu::MainMenu() //функция главного меню
{

    int option = 0;
    for (;;)
    {
        intro();
        cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n\t\tНажмите 1 чтобы ВЗЯТЬ КНИГУ";
        cout << "\n\t\tНажмите 2 чтобы ВЕРНУТЬ КНИГУ";
        cout << "\n\t\tНажмите 3 чтобы РАБОТАТЬ СО СТУДЕНТАМИ";
        cout << "\n\t\tНажмите 4 чтобы РАБОТАТЬ С КНИГАМИ";
        cout << "\n\t\tНажмите 5 чтобы ПРОЧИТАТАТЬ ПРАВИЛА БИБЛИОТЕКИ";
        cout << "\n\t\tНажмите 6 чтобы ВЫЙТИ";
        cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\n\t\tВыбор: ";
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

void menu:: write_book() //функция добавления книги из консоли в кольцо
{
    system("cls");
    int amount, check;

    cout << "Введите количество книг: ";
    while (1) //проверка введенного числа на тип int
    {
        cin >> amount;
        if (checkint(amount)) break;
    }
    cout << "Вводите книги: " << endl;
    for (int i = 0; i < amount; i++)
    {
        bk.create_book(); //вводим данные книги
        check=ringB.pushnew(bk); //добавляем в кольцо
        if (check) cout << "\t\t\n\nКнига успешно добалена...";
    }
    
    _getch();
}
void menu::write_student()//функция добавления студента из консоли в кольцо
{
    system("cls");
    int amount, check;
   
    cout << "Введите количество студентов: ";
    while (1) //проверка введенного числа на тип int
    {
        cin >> amount;
        if (checkint(amount)) break;
    }
       
    cout << "Вводите студентов: " << endl;
    for (int i = 0; i < amount; i++)
    {
        st.create_student();//вводим данные студента
        check=ringS.pushnew(st);//добавляем в кольцо
        if (check) cout << "\t\t\n\nСтудент успешно добален...";
    }
    _getch();
}

void menu::display_a_book() //функция вывода книги в консоль
{
    system("cls");
    cout << "\nИНФОРМАЦИЯ О КНИГЕ\n";
    int check = 0, n, num, choise, check2=0;
    string name;
    cout << "\n\n\t1. Поиск по названию 0. Поиск по номеру: ";
    while (1)
    {
        cin >> choise;
        if (choise == 1 || choise == 0) break;
    }

    if (choise) //вывод по названию
    {
        cout << "\n\n\tВведите название книги в кавычках "": ";
        rewind(stdin);
        getline(cin, name);
        check = ringB.findbyname(name);
    }
    else //вывод по номеру книги
    {
        cout << "\n\n\tВведите номер книги: ";
        while (1) //проверка введенного числа на исключения
        {
            cin >> num;
            if (checkint(num))
            {
                try
                {
                    if (num > 999999 || num < 100000)
                        throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
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
    if (check == 1&&choise==0) //просмотр у кого есть экземпляр этой книги на руках
    { 

        cout << "Посмотретьу каких студентов есть экземпляр книги на руках? 1. да 0.нет";
        while (1) 
        {
            cin >> choise2;
            if (choise2 == 1 || choise2 == 0) break;
        }
        if (choise2 && choise==0) //вывод номеров студентов взявших книгу
        {
            cout << "\nСтуденты с экземпляром книги:\n\n";
            check2 = ringS.findissuebook(num);
            if (check2 == 0) cout << "все экземпляры в библиотеке";
        }
    }

    if (check == 0) cout << "\n\nТакая книга не существует";
    _getch();
}

void menu:: display_a_student() //функция вывода студента в консоль
{
    system("cls");
    cout << "\nИНФОРМАЦИЯ О СТУДЕНТЕ\n";
    int check = 0, n, num, choise;
    string name;
    cout << "\n\n\t1. Поиск по имени 0. Поиск по номеру: ";
    cin >> choise;
    if (choise) //вывод по ФИО
    {
        cout << "\n\n\tВведите ФИО студента: ";
        rewind(stdin);
        getline(cin, name);
        check = ringS.findbyname(name);
    }
    else//вывод по номеру студ. билета
    {
        cout << "\n\n\tВведите номер студ. билета: ";

        while (1)
        {
            cin >> num;
            if (checkint(num))
            {
                try
                {
                    if (num > 999999 || num < 100000)
                        throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
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

       
    if(check==0) cout << "\n\nТакой студент не существует";
    _getch();
}

void menu::display_faculty() //вывод всех студентов определенного факультета
{
    system("cls");
    int check = 0, n, num, choise;
    string name;
    cout << "\n\n\tВведите номер: \n1.ФКСиС \n2.ФИТУ \n3.ФКП \n4.ФИБ \n5.ИЭФ \n6.ФРЭ \n7.ВФ\nВыбор: ";
    int  fakult;
    while (1) //выбор факультета по номеру
    {
        cin >> fakult;
        if (checkint(fakult))
        {
            if (fakult > 0 && fakult < 8) break;
        }

    }
    system("cls");
    cout << "\nВСЕ СТУДЕНТЫ ФАКУЛЬТЕТА\n";
    cout << "==============================================================================================\n";
    cout << "\tНомер студенческого" << setw(10) << "ФИО" << setw(30) << "Факульет" << setw(20) << "Долг книг\n";
    cout << "==============================================================================================\n";

    check=ringS.printfaculty(fakult); //вывод студента
    if (check == 0) cout << "\n\nНет студентов этого факультета";
    _getch();
}

void menu::modify_book() //функция изменения информации о книге
{
    system("cls");
    int n;
    int found = 0;
    int check = 0;
    int choise;
    cout << "\n\n\tИЗМЕНИТЬ ИНФОРМЦИЮ О КНИГЕ... ";
    cout << "\n\n\tВведите регистрационный номер книги: ";
    while (1)//проверка исключений
    {
        cin >> n;
        if (checkint(n))
        {
            try
            {
                if (n > 999999 || n < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }
    cout << "\n1.Изменить данные 0.Изменить количество" << endl;
    while (1)
    {
        cin >> choise;
        if (choise==1||choise==0) break;
    }
    if (choise)//изменение названия
    {
        cout << "\nВведите новую информацию" << endl;
        check = ringB.changeElement(n);
    }
    else//исменение количества экземпляров
    {
        cout << "\nВведите новое количество книг" << endl;
        check = ringB.changeCount(n);
    }

    if (check == 1)  cout << "\n\n\t Успешно изменено...";

    if (check == 0)
        cout << "\n\n Книга не найдена ";
    _getch();
}


void menu::modify_student() //функция изменения информации о студенте
{
   system("cls");
    int n;
    int found = 0;
    int check = 0;
    cout << "\n\n\tИЗМЕНИТЬ ИНФОРМАЦИЮ О СТУДЕНТЕ... ";
    cout << "\n\n\tВведите номер студенческого билета: ";
    while (1)//проверка исключений
    {
        cin >> n;
        if (checkint(n))
        {
            try
            {
                if (n > 999999 || n < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }
    int choise;
    cout << "\n1.Изменить ФИО 0.Изменить факультет" << endl;
    while (1)
    {
        cin >> choise;
        if (choise == 1 || choise == 0) break;
    }
    if (choise)//изменение ФИО
    {
        cout << "\nВведите новую информацию" << endl;
        check = ringS.changeElement(n);
    }
    else //изменение факультета
    {
        cout << "\nВведите новый факультет" << endl;
        cout << "\n\nВведите номер: \n1.ФКСиС \n2.ФИТУ \n3.ФКП \n4.ФИБ \n5.ИЭФ \n6.ФРЭ \n7.ВФ\nВыбор:";
        int fakult;
        while (1) //выбор нового факультета
        {
            cin >> fakult;
            if (checkint(fakult))
            {
                if (fakult > 0 && fakult < 8) break;
            }
            
        }
        check = ringS.changefk(n, fakult);
     }
   

     if(check==1)  cout << "\n\n\t Успешно изменено...";
  
    if (check == 0)
        cout << "\n\n Студент не найден ";
    _getch();
    
}

void menu::delete_student() //удаление студента
{
   system("cls");
    int n;
    int flag = 0;
    cout << "\n\n\n\tУДАЛИТЬ СТУДЕНТА";
    cout << "\n\nВведите номер студенческого билета студента, которого вы желаете удалить: ";
    while (1) //проверка на исключения
    {
        cin >> n;
        if (checkint(n))
        {
            try
            {
                if (n > 999999 || n < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }

    flag=ringS.deleteElement(n); //удаление

    if(flag==1)
        cout << "\n\n\tЗапись удалена ..";
    else
        cout << "\n\nСтудент не найден";
    _getch();
    
}

void menu::delete_book()//удаление книги
{
    system("cls");
    int n;
    int flag = 0;
    cout << "\n\n\n\tУДАЛИТЬ КНИГУ";
    cout << "\n\nВведите регистрационный номер книги, которую вы желаете удалить: ";
    while (1) //проверка на исключения
    {
        cin >> n;
        if (checkint(n))
        {
            try
            {
                if (n > 999999 || n < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }

    flag = ringB.deleteElement(n); //удаление книги

    if (flag == 1)
        cout << "\n\n\tЗапись удалена ..";
    else
        cout << "\n\nКнига не найдена";
    _getch();
}

void menu::display_all_students() //вывод всех студентов
{
    system("cls");
    
    cout << "\n\n\t\tСПИСОК СТУДЕНТОВ\n\n";
    cout << "==============================================================================================\n";
    cout << "\tНомер студенческого" << setw(10) << "ФИО" << setw(30) << "Факульет" << setw(20) << "Долг книг\n";
    cout << "==============================================================================================\n";
    
    ringS.print();
    
    _getch();
}

void menu::display_allb() //вывод всех книг
{
    system("cls");
    
    cout << "\n\n\t\tСПИСОК КНИГ\n\n";
    cout << "====================================================================================================\n";
    cout << "Номер книги" << setw(20) << "Название" << setw(25) << "Автор"<<setw(30) << "Наличие\n";
    cout << "====================================================================================================\n";
    ringB.print();
    _getch();
}

void menu::issue_book()               //функция взятия книги студентом
{
    system("cls");
    int bn, sn, av, no;
    int found = 0, flag = 0, k = 0;
    cout << "\t\t\nВЗЯТЬ КНИГУ";
    cout << "\n\n\tНомер студенческого билета студента: ";
    while (1)             //проверка на исключения
    {
        cin >> sn;
        if (checkint(sn))
        {
            try
            {
                if (sn > 999999 || sn < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }


    if (ringS.getN(sn)== 1) //ищем студента по номеру
    {
            found = 1;                             //1 если нашли
           if (ringS.getinfS(sn,1,0) == 1)         //проверяем можно ли ему брать книгу
           {
                cout << "\n\n\tВведите номер книги: ";
                while (1)                          //проверка на исключения
                {
                    cin >> bn;
                    if (checkint(bn))
                    {
                        try
                        {
                            if (bn > 999999 || bn < 100000)
                                throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
                            break;
                        }
                        catch (Exception_input exp)
                        {
                            exp.show();
                        }
                    }

                }
               
                    if (ringB.getN(bn) == 1)  //ищем книгу по номеру
                    {   
                        flag = 1;              //1 если нашли
                        if(ringB.getinfB(bn,2) == 1)            //проверяяем есть ли книга в наличии
                        {
                            cin.clear();
                            ringB.printElement(bn);            //выводим информацию о книге
                           
                            ringS.getinfS(sn,2, bn);           //записываемм книгу к студенту
                            ringB.getinfB(bn, 3);              //уменьшаем количество эземпляров
                           
                            cout << "\n\n\t Книга успешно взята...";
                        }
                        else cout << "Книги нет в наличии";
                    
                     }
                if (flag == 0)
                    cout << "Книги с таким номером не существует";
           }
            else
            cout << "Студент не вернул прошлые книги ";
     }
    
    if (found == 0)
        cout << "Студента с таким номером не существует...";
    _getch();
    system("cls");
   
}

void menu::book_return()
{
  system("cls");
    int bn;
    int sn;
    int found = 0, flag = 0, check=0;
    cout << "\t\tВЕРНУТЬ КНИГУ\n";
    cout << "\n\n\tНомер студенческого билета студента: ";
    while (1)     //проверка на исключения
    {
        cin >> sn;
        if (checkint(sn))
        {
            try
            {
                if (sn > 999999 || sn < 100000)
                    throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
                break;
            }
            catch (Exception_input exp)
            {
                exp.show();
            }
        }

    }
    
   if (ringS.getN(sn) == 1)             //ищем студента с таким номером
        {
            found = 1;                   //1 если нашли
            if (ringS.getinfS(sn, 5, 0) != 0)             //проверяем есть ли у него книги
            {
                
                cout << "\n\n\tВведите номер книги: ";
                while (1) //проверка на исключения
                {
                    cin >> bn;
                    if (checkint(bn))   
                    {
                        try
                        {
                            if (bn > 999999 || bn < 100000)
                                throw Exception_input(static_cast<int>(Errors::outOfRange), "Идетификационный номер - 6-значное число");
                            break;
                        }
                        catch (Exception_input exp)
                        {
                            exp.show();
                        }
                    }

                }
                     
                    check = ringS.getinfS(sn, 3, bn); //есть ли у студента эта книга
                   
                    if (ringB.getN(bn) == 1 && check == 1)   //ищем есть ли книга с таким номером и студент взявший эту книгу
                    {
                        ringB.printElement(bn);  //выводим информацию о книге
                        flag = 1;

                        ringS.getinfS(sn, 4, bn);  //удаляем номер книги у студента
                        ringB.getinfB(bn, 4);   //увеличиваем количество экземпляров на 1
                        cout << "\n\n\t Книга успешно возвращена...";
                    }
                     if (flag == 0)
                    cout << "Книга с таким номером не существует";
                     if (check == 0)
                         cout << "У студента нет такой книги";
            }
            else
                cout << "Студент не брал книг.. проверьте!";
    }
    
    if (found == 0)
        cout << "Такого студента не существует...";
    _getch();
    system("cls");
   
}

void menu::rules()  //правила пользования библиотекой
{
    system("cls");
    cout << "Приложение создала: Губаревич Агата 150504\n\n\n";
    cout << "\t\tПРАВИЛА ПОЛЬЗОВАНИЯ БИБЛИОТЕКОЙ\n\n";
    cout << "1.Нельзя добавить 2 студентов или книги с одинаковыми индефикационными номерами.\n Номера являются индивидуальными\n\n";
    cout << "2.Номер студ. билета состоит из 6 цифр.\n Регистрационный номер книги тоже состоит из 6 цифр\n\n";
    cout << "3.Студент может взять не более 5 книг одновременно\n\n";
    cout << "4.Студента можно удалять только если у него нет долга\nИначе потом никто никогда о его долге не узнает))\n\n";
    cout << "5.Выходите из программы на кнопку 6, чтобы данные точно сохранились\n\n";
    cout << "\n\n\nПриятного пользования библиотекой!";
    _getch();
}




void menu::intro() 
{
    //system("color 07");
    system("cls");
    cout << "Губаревич Агата 150504 И/С Студенческой Библиотеки \n";
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


void menu::book_menu() //меню для работы с книгами
{
    int option;
    cout << "Губаревич Агата 150504 И/С Студенческой Библиотеки \n";
    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\tНажмите 1 чтобы ДОБАВИТЬ КНИГИ";
    cout << "\n\t\tНажмите 2 чтобы ВЫВЕСТИ ВСЕ КНИГИ";
    cout << "\n\t\tНажмите 3 чтобы НАЙТИ КНИГУ";
    cout << "\n\t\tНажмите 4 чтобы ИЗМЕНИТЬ ИНФОРМАЦИЮ О КНИГЕ";
    cout << "\n\t\tНажмите 5 чтобы УДАЛИТЬ КНИГУ";
    cout << "\n\t\tНажмите 6 чтобы СОРТИРОВАТЬ КНИГИ ПО НОМЕРУ";
    cout << "\n\t\tНажмите 7 для ВЫХОДА В ГЛАВНОЕ МЕНЮ";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\n\t\tВЫбор: ";
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
        if (n == 1) cout << "\n\n\tУспешно отсортированно ";
        else  cout << "\n\n\tОшибка сортировки ";
        _getch();
        system("cls");
        break;
    case 7: system("cls");
        break;
    default:cout << "\a";
    }
}


void menu::student_menu() //меню для работы со студентами
{
    int option;
    cout << "Губаревич Агата 150504 И/С Студенческой Библиотеки \n";
    cout << "\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    cout << "\n\t\tНажмите 1 чтобы ДОБАВИТЬ ЗАПИСЬ О СТУДЕНТЕ";
    cout << "\n\t\tНажмите 2 чтобы ВЫВЕСТИ ВСЕХ СТУДЕНТОВ";
    cout << "\n\t\tНажмите 3 чтобы НАЙТИ СТУДЕНТА";
    cout << "\n\t\tНажмите 4 чтобы ИЗМЕНИТЬ ИНФОРМАЦИЮ О СТУДЕНТЕ";
    cout << "\n\t\tНажмите 5 чтобы УДАЛИТЬ СТУДЕНТА";
    cout << "\n\t\tНажмите 6 чтобы СОРТИРОВАТЬ СТУДЕНТОВ ПО НОМЕРУ";
    cout << "\n\t\tНажмите 7 для ВЫХОДА В ГЛАВНОЕ МЕНЮ";
    cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\n\t\tВыбор: ";
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
        cout << "\t1.Вывести всех студентов университета 0. Вывести всех студентов факультета";
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
        if (n == 1) cout << "\n\n\tУспешно отсортированно ";
        else  cout << "\n\n\tОшибка сортировки ";
        _getch();
        system("cls");
        break;
    case 7:
        break;
    default:cout << "\a";
    }
}