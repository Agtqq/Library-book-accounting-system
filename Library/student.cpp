#include "student.h"

student::student()
{
	ID_number = 0;
	Student_name="";
	strcpy_s(faculty, "");
	for (int i = 0; i < 5; i++)
	{
		stbno[i] = 0;
	}
	
	token=0;
}

std::istream& operator>>(std::istream& in, student& st)
{
	if (in.gcount() == cin.gcount())
		cout << "Номер студ. билета: "; 
	in >> st.ID_number;
	if (in.gcount() == cin.gcount())
		cout << "ФИО: ";
	rewind(stdin);
	in.ignore(100, '\n');
	getline(in, st.Student_name);
	if (in.gcount() == cin.gcount())
		cout << "Факультет: ";
	rewind(stdin);
	//in.ignore(100, '\n');
	in.getline(st.faculty, 100);
	if (in.gcount() == cin.gcount())
		cout << "Номер взятой книги ";
	in >> st.stbno[0];
	in >> st.stbno[1];
	in >> st.stbno[2];
	in >> st.stbno[3];
	in >> st.stbno[4];
	if (in.gcount() == cin.gcount())
		cout << "Долг: ";
	in >> st.token;
	return in;
}

std::ostream& operator<<(std::ostream& out, const student& st)
{
	out << st.ID_number << endl << st.Student_name << endl << st.faculty << endl << st.stbno[0]<<endl << st.stbno[1] << endl << st.stbno[2]
		<< endl << st.stbno[3] << endl << st.stbno[4] << endl << st.token << endl;
	return out;
}
