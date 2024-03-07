#pragma once
#include <iostream>
#include "student.h"
#include "book.h"

using namespace std;

template <class T>
struct node
{
	T element;
	node<T>* next;
	node<T>* prev;
};

template <class T>
class Loop
{
	node<T>* end;
public:
	Loop()
	{
		end = 0;
	}
	void push(T number);
	int pushnew(T number);
	void print();
	int deleteElement(int index);
	int printElement(int index);
	int printfaculty(int index);
	int findbyname(string name);
	int findissuebook(int index);
	int getN(int index);
	int getinfB(int index, int type);
	int getinfS(int index, int type, int nom);
	int changeElement(int index);
	int changeCount(int index);
	int changefk(int index, int nom);
	T getElement(int index);
	int getElementsAmount();
	int sort();
	~Loop()
	{
		
	}

	class iterator
	{
	private:
		friend class Loop<T>;
		
	public:
		node<T>* Node;
		iterator() :Node(0) {};
		iterator(node<T>* other) :Node(other) {};
		iterator(const iterator& it) :Node(it.Node) {};  //конструктор копирования

		iterator& operator=(const iterator& it)
		{
			Node = it.Node;
			return *this;
		}


		iterator& operator++()
		{
			Node = Node->next;
			return *this;
		}

		iterator& operator--()
		{
			Node = Node->prev;
			return *this;
		}

		T& operator*()const
		{
			return Node->element;
		}

		~iterator() {}
		friend std::ostream& operator << (std::ostream& os, const iterator& it);
		friend std::istream& operator >> (std::istream& is, const iterator& it);
	};

	friend std::ostream& operator << (std::ostream& os, const iterator& it)
	{
		return os << it.Node->element;
	}

	friend std::istream& operator >> (std::istream& is, const iterator& it)
	{
		return is >> it.Node->element;
	}
};

template<class T>
void Loop<T>::push(T elem) //функция добавления элемента, прочитанного из файла, в кольцо
{
	node<T>* temp = new node<T>;
	temp->element = elem;
	temp->next = 0;
	temp->prev = 0;
	if (!end)
	{
		end = temp; // выбрать 1 элемент
		end->next = end;
		end->prev = end;
	}
	else
	{
		end->next->prev = temp; //выбрать следующий и предыдущий элементы
		temp->next = end->next;
		end->next = temp;
		temp->prev = end;
        end = temp;
	}

}

template<class T>
int Loop<T>::pushnew(T elem) //функция добавления ф кольцо из консоли
{
	node<T>* temp = new node<T>;
	int num, index, chek = 1;
	temp->element = elem;

	index = temp->element.get_number();

	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //проверка существует ли уже элемент с таким номером
	{
		++iter;
		p = *iter;
		num = p.get_number();
		if (num == index)
		{
			chek = 0;
			break;
		}
	}
	
	if (chek)   //если такого элемента с таким номером ещё не существует, записываем его в кольцо
	{
		temp->next = 0;
		temp->prev = 0;
		if (!end)
		{
			end = temp; // выбираем 1 элемент
			end->next = end;
			end->prev = end;
		}
		else
		{
			end->next->prev = temp; //выбрать следующий и предыдущий элементы
			temp->next = end->next;
			end->next = temp;
			temp->prev = end;
			end = temp;
		}
	}
	else cout << "Элемент с таким номером уже существует";
	return chek;
}

template<class T>
void Loop<T>::print()  //вывод всех элементов очереди
{
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return;
	}
	
	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //выводим столько элементов сколько их в очереди
	{
		++iter;
		p = *iter;
		p.report();
	}
	cout << endl;
}


template<class T>
inline T Loop<T>::getElement(int index) //вывод элемента очереди по номеру
{
	node<T>* elem = end;
	for (int i = 0; i < index; i++)
		elem = elem->next;
	return elem->element;
}


template<class T>
int Loop<T>::printElement(int index)  //вывод элемента соответсвуюзего номеру index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}
	
	iterator iter = end;
	T p;
	int i=0;
	while (i++ < getElementsAmount()) //ищем элемент с таким номером
	{
		++iter;
		p = *iter;
	   num =p.get_number();
	   if (num == index)  //если нашли, выводим элемент
	   {
		   chek = 1;
		   p.show();
		   break;
	   }
    }
	return chek;
}

template<class T>
int Loop<T>::printfaculty(int index)  //вывод всех студентов определенного факультета
{
	int num, chek = 0, chek2=0;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}
	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //просмотриваем все элементы
	{
		++iter;
		p = *iter;

		chek=p.findfaculty(index); //проверяем с какого факультета студент
		if (chek)
		{
			p.report();  //если он с нужного факультета выводим
			chek2 = 1;
		}
	};
	
	return chek2;
}

template<class T>
int Loop<T>::findbyname(string name) //поиск элемента с названием name
{
	int chek = 0;
	string elem_name;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}

	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //перебор всех элементов
	{
		++iter;
		p = *iter;
		elem_name = p.retname();
		if (elem_name == name) //если элемент найден - выводим
		{
			chek = 1;
			p.show();
			cout << "\n";
		}
	}
	return chek;
}

template<class T>
int Loop<T>::findissuebook(int index) //поиск всех студентов, которые взяли книгу с номером index
{
	int num, chek = 0, chek2 = 0;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}
	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //перебираем всех элементы кольца
	{
		++iter;
		p = *iter;
		chek = p.findbook(index); //проверяем студента на наличие книги и выводим в случае, если у него есть книга
		if(chek) chek2 = 1;
			
	};

	return chek2;
}

template<class T>
int Loop<T>::changeElement(int index) //изменение названия элемента с номером index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}

	node<T>* p = end;
	do //проходим по кольцу
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index)      //если найден элемент с таким номером вызываем функцию изменения данных
		{
			chek = 1;
			p->element.modify();
			break;
		}
	} while (p != end); 

	return chek;
}

template<class T>
int Loop<T>::changeCount(int index) //изменение количества экземпляров книги с номером index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}

	node<T>* p = end;
	do //проходим по кольцу
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index)  //если найден элемент с таким номером вызываем функцию изменения количества
		{
			chek = 1;
			p->element.addcount();
			break;
		}
	} while (p != end);

	return chek;
}

template<class T>
int Loop<T>::changefk(int index, int nom) //изменение факультета с номером index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}

	node<T>* p = end;
	do //проходим по кольцу
	{
		p = p->next;
		num = p->element.get_number(); 
		if (num == index) //если найден студент с таким номером вызываем функцию изменения
		{
			chek = 1;
			p->element.changefacult(nom);
			break;
		}
	} while (p != end);

	return chek;
}

template<class T>
int Loop<T>::deleteElement(int index) //функция удаления элемента с номером index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}

	node<T>* p = end;
	
	node<T>* temp = new node<T>;
	do//проходи по кольцу
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index) //если найден элемент ставим флаг chek =1
		{
			chek = 1;
			temp = p;
			break;
		}
	} while (p != end);

	if (p->element.candelete() == 0)//проверяем можно ли удалять этот элемент
	{
		cout << "Невозможно удалить, произойдет утечка данных\nДля начала верните книгу";
		return 2;
	}

	if (temp == end) //удаление элемента, если он последний
	{
		node<T>* p = end->prev;
		node<T>* temp = p->next;
		p->next->next->prev = p;
		p->next = p->next->next;
		delete temp;
		end = p;
		return chek;
	}


	while (temp->next != p) //удаление элемента, если он не последний
	{
		temp = temp->next;
	}
	temp->next = p->next; 
	free(p); 
	return chek;
}


template<class T>
int Loop<T>::getElementsAmount()//возвращение количества элементов кольца
{
	int i = 1;
	if (!end)
	{
		i = 0;
		return i;
	}
	node<T>* point = end->next;
	while (point != end)
	{
		i++;
		point = point->next;
	}
	return i;
}


template<class T>
int Loop<T>::getN(int index) //проверка существования элемента с номером index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "данные отсутствуют" << endl;
		return 0;
	}
	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount())
	{
		++iter;
		p = *iter;
		num = p.get_number();
		if (num == index)
		{
			chek = 1;
			break;
		}
	}
	return chek;

}

template<class T>
int Loop<T>::getinfS(int index, int type, int nom) //функция для работы со студентом, который берет/возвращает книгу
{
	int num, chek = 0;
	node<T>* p = end;
	do //проходим по кольцу
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index) //если найден студент с таким номером
		{
			if (type == 1)
			{
				if (p->element.rettoken() < 5) //проверка можно ли ему взять книгу
				{
					chek = 1;
				}

			}
			if (type == 2)
			{
				p->element.addtoken(); //добавление количества взятых книг
				p->element.getstbno(nom); //добавление номера книги в поле stbno класса student
				chek = 1;
			}
			if (type == 3)
			{
				chek = p->element.retstbno(nom); //проверка есть ли книга у студента
			}
			if (type == 4)
			{
				p->element.resettoken(); //изменение количества книг, которые взял студент
				p->element.changestbno(nom); //удаление номера книги из поля stbno класса student
				chek = 1;
			}
			if (type == 5)
			{
				if (p->element.rettoken() == 0)
				{
					chek = 0;
				}
				else chek = 1;
			}
			break;
		}
	} while (p != end);
	return chek;


}

template<class T>
int Loop<T>::getinfB(int index, int type) //функция для работы с книгами, которые берет/возвращает студент
{
	int num, chek = 0;
	node<T>* p = end;
	do //проходим по кольцу
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index)//находим книгу с нуным номером
		{

			if (type == 2)
			{
				if (p->element.if_available() == 1) //проверяем есть ли книга в наличии
				{
					chek = 1;
				}
			}
			if (type == 3)
			{
				p->element.minuscount(); //отнимает 1 от количества книг
				if (p->element.retcount() == 0) //если книг осталось 0, изменяем статус на нет в наличии
				{
					p->element.not_available();
					chek = 1;
				}


			}
			if (type == 4)
			{
				p->element.pluscount(); //добавляем 1 к количеству книг
				p->element.yes_available(); //изменяем статус на есть в наличии
				chek = 1;
			}
			break;
		}
	} while (p != end);
	return chek;
}



template<class T>
int Loop<T>::sort()//функция сортировки по номеру
{

	int n1, n2;


	node<T>* t = end->next;
	node<T>* t1 = NULL;
	
	do
	{

		for (t1=end->next;t1->next !=t; t1=t1->next)
		{ 
			
			n1 = t1->element.get_number();
			n2 = t1->next->element.get_number();
			if (n1 > n2)
			{
				T elem = t1->element;
				t1->element = t1->next->element;
				t1->next->element = elem;
			}
			
		}
		t = t1;

	} while (end->next != t); 
	
	

	return 1;

}


