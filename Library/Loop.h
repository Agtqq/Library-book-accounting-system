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
		iterator(const iterator& it) :Node(it.Node) {};  //����������� �����������

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
void Loop<T>::push(T elem) //������� ���������� ��������, ������������ �� �����, � ������
{
	node<T>* temp = new node<T>;
	temp->element = elem;
	temp->next = 0;
	temp->prev = 0;
	if (!end)
	{
		end = temp; // ������� 1 �������
		end->next = end;
		end->prev = end;
	}
	else
	{
		end->next->prev = temp; //������� ��������� � ���������� ��������
		temp->next = end->next;
		end->next = temp;
		temp->prev = end;
        end = temp;
	}

}

template<class T>
int Loop<T>::pushnew(T elem) //������� ���������� � ������ �� �������
{
	node<T>* temp = new node<T>;
	int num, index, chek = 1;
	temp->element = elem;

	index = temp->element.get_number();

	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //�������� ���������� �� ��� ������� � ����� �������
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
	
	if (chek)   //���� ������ �������� � ����� ������� ��� �� ����������, ���������� ��� � ������
	{
		temp->next = 0;
		temp->prev = 0;
		if (!end)
		{
			end = temp; // �������� 1 �������
			end->next = end;
			end->prev = end;
		}
		else
		{
			end->next->prev = temp; //������� ��������� � ���������� ��������
			temp->next = end->next;
			end->next = temp;
			temp->prev = end;
			end = temp;
		}
	}
	else cout << "������� � ����� ������� ��� ����������";
	return chek;
}

template<class T>
void Loop<T>::print()  //����� ���� ��������� �������
{
	if (!end)
	{
		cout << "������ �����������" << endl;
		return;
	}
	
	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //������� ������� ��������� ������� �� � �������
	{
		++iter;
		p = *iter;
		p.report();
	}
	cout << endl;
}


template<class T>
inline T Loop<T>::getElement(int index) //����� �������� ������� �� ������
{
	node<T>* elem = end;
	for (int i = 0; i < index; i++)
		elem = elem->next;
	return elem->element;
}


template<class T>
int Loop<T>::printElement(int index)  //����� �������� ��������������� ������ index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "������ �����������" << endl;
		return 0;
	}
	
	iterator iter = end;
	T p;
	int i=0;
	while (i++ < getElementsAmount()) //���� ������� � ����� �������
	{
		++iter;
		p = *iter;
	   num =p.get_number();
	   if (num == index)  //���� �����, ������� �������
	   {
		   chek = 1;
		   p.show();
		   break;
	   }
    }
	return chek;
}

template<class T>
int Loop<T>::printfaculty(int index)  //����� ���� ��������� ������������� ����������
{
	int num, chek = 0, chek2=0;
	if (!end)
	{
		cout << "������ �����������" << endl;
		return 0;
	}
	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //������������� ��� ��������
	{
		++iter;
		p = *iter;

		chek=p.findfaculty(index); //��������� � ������ ���������� �������
		if (chek)
		{
			p.report();  //���� �� � ������� ���������� �������
			chek2 = 1;
		}
	};
	
	return chek2;
}

template<class T>
int Loop<T>::findbyname(string name) //����� �������� � ��������� name
{
	int chek = 0;
	string elem_name;
	if (!end)
	{
		cout << "������ �����������" << endl;
		return 0;
	}

	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //������� ���� ���������
	{
		++iter;
		p = *iter;
		elem_name = p.retname();
		if (elem_name == name) //���� ������� ������ - �������
		{
			chek = 1;
			p.show();
			cout << "\n";
		}
	}
	return chek;
}

template<class T>
int Loop<T>::findissuebook(int index) //����� ���� ���������, ������� ����� ����� � ������� index
{
	int num, chek = 0, chek2 = 0;
	if (!end)
	{
		cout << "������ �����������" << endl;
		return 0;
	}
	iterator iter = end;
	T p;
	int i = 0;
	while (i++ < getElementsAmount()) //���������� ���� �������� ������
	{
		++iter;
		p = *iter;
		chek = p.findbook(index); //��������� �������� �� ������� ����� � ������� � ������, ���� � ���� ���� �����
		if(chek) chek2 = 1;
			
	};

	return chek2;
}

template<class T>
int Loop<T>::changeElement(int index) //��������� �������� �������� � ������� index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "������ �����������" << endl;
		return 0;
	}

	node<T>* p = end;
	do //�������� �� ������
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index)      //���� ������ ������� � ����� ������� �������� ������� ��������� ������
		{
			chek = 1;
			p->element.modify();
			break;
		}
	} while (p != end); 

	return chek;
}

template<class T>
int Loop<T>::changeCount(int index) //��������� ���������� ����������� ����� � ������� index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "������ �����������" << endl;
		return 0;
	}

	node<T>* p = end;
	do //�������� �� ������
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index)  //���� ������ ������� � ����� ������� �������� ������� ��������� ����������
		{
			chek = 1;
			p->element.addcount();
			break;
		}
	} while (p != end);

	return chek;
}

template<class T>
int Loop<T>::changefk(int index, int nom) //��������� ���������� � ������� index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "������ �����������" << endl;
		return 0;
	}

	node<T>* p = end;
	do //�������� �� ������
	{
		p = p->next;
		num = p->element.get_number(); 
		if (num == index) //���� ������ ������� � ����� ������� �������� ������� ���������
		{
			chek = 1;
			p->element.changefacult(nom);
			break;
		}
	} while (p != end);

	return chek;
}

template<class T>
int Loop<T>::deleteElement(int index) //������� �������� �������� � ������� index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "������ �����������" << endl;
		return 0;
	}

	node<T>* p = end;
	
	node<T>* temp = new node<T>;
	do//������� �� ������
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index) //���� ������ ������� ������ ���� chek =1
		{
			chek = 1;
			temp = p;
			break;
		}
	} while (p != end);

	if (p->element.candelete() == 0)//��������� ����� �� ������� ���� �������
	{
		cout << "���������� �������, ���������� ������ ������\n��� ������ ������� �����";
		return 2;
	}

	if (temp == end) //�������� ��������, ���� �� ���������
	{
		node<T>* p = end->prev;
		node<T>* temp = p->next;
		p->next->next->prev = p;
		p->next = p->next->next;
		delete temp;
		end = p;
		return chek;
	}


	while (temp->next != p) //�������� ��������, ���� �� �� ���������
	{
		temp = temp->next;
	}
	temp->next = p->next; 
	free(p); 
	return chek;
}


template<class T>
int Loop<T>::getElementsAmount()//����������� ���������� ��������� ������
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
int Loop<T>::getN(int index) //�������� ������������� �������� � ������� index
{
	int num, chek = 0;
	if (!end)
	{
		cout << "������ �����������" << endl;
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
int Loop<T>::getinfS(int index, int type, int nom) //������� ��� ������ �� ���������, ������� �����/���������� �����
{
	int num, chek = 0;
	node<T>* p = end;
	do //�������� �� ������
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index) //���� ������ ������� � ����� �������
		{
			if (type == 1)
			{
				if (p->element.rettoken() < 5) //�������� ����� �� ��� ����� �����
				{
					chek = 1;
				}

			}
			if (type == 2)
			{
				p->element.addtoken(); //���������� ���������� ������ ����
				p->element.getstbno(nom); //���������� ������ ����� � ���� stbno ������ student
				chek = 1;
			}
			if (type == 3)
			{
				chek = p->element.retstbno(nom); //�������� ���� �� ����� � ��������
			}
			if (type == 4)
			{
				p->element.resettoken(); //��������� ���������� ����, ������� ���� �������
				p->element.changestbno(nom); //�������� ������ ����� �� ���� stbno ������ student
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
int Loop<T>::getinfB(int index, int type) //������� ��� ������ � �������, ������� �����/���������� �������
{
	int num, chek = 0;
	node<T>* p = end;
	do //�������� �� ������
	{
		p = p->next;
		num = p->element.get_number();
		if (num == index)//������� ����� � ����� �������
		{

			if (type == 2)
			{
				if (p->element.if_available() == 1) //��������� ���� �� ����� � �������
				{
					chek = 1;
				}
			}
			if (type == 3)
			{
				p->element.minuscount(); //�������� 1 �� ���������� ����
				if (p->element.retcount() == 0) //���� ���� �������� 0, �������� ������ �� ��� � �������
				{
					p->element.not_available();
					chek = 1;
				}


			}
			if (type == 4)
			{
				p->element.pluscount(); //��������� 1 � ���������� ����
				p->element.yes_available(); //�������� ������ �� ���� � �������
				chek = 1;
			}
			break;
		}
	} while (p != end);
	return chek;
}



template<class T>
int Loop<T>::sort()//������� ���������� �� ������
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


