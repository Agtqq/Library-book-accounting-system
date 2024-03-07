#include "book.h"

std::istream& operator>>(std::istream& in, book& bk)
{
	if (in.gcount() == cin.gcount())
		cout << "Номер книги: ";
	in >> bk.book_number;
	if (in.gcount() == cin.gcount())
		cout << "Название: ";
	rewind(stdin);
	//in.getline(bk.book_name, 100);
	in.ignore(100, '\n');
	getline(in, bk.book_name);
	if (in.gcount() == cin.gcount())
		cout << "Автор: ";
	rewind(stdin);
	//in.getline(bk.author_name, 100);
	getline(in, bk.author_name);
	if (in.gcount() == cin.gcount())
		cout << "Количество: ";
	in >> bk.book_count;
	if (in.gcount() == cin.gcount())
		cout << "Наличие: ";
	in >> bk.availible;
	return in;
}

std::ostream& operator<<(std::ostream& out, const book& bk)
{
	out << bk.book_number << endl << bk.book_name << endl << bk.author_name << endl << bk.book_count << endl << bk.availible << endl;
	return out;
}