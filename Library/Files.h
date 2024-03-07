#pragma once
#include "Loop.h"
#include "Exception_file.h"
#include <fstream>
#include <iostream>

template <class T>
class AbstractFile
{
protected:
	ifstream inputFile;
	ofstream outputFile;
	virtual void readFromFile(Loop<T>&) = 0;
	virtual void writeToFile(Loop<T>&) = 0;
};

template <class T>
class TextFile : public AbstractFile<T>
{
public:
	TextFile(char* inFile, char* outFile);
	void readFromFile(Loop<T>&) override;
	void writeToFile(Loop<T>&) override;
	void CloseFile();
	~TextFile();
};


template <class T>
TextFile<T>::TextFile(char* inputFilename, char* outputFilename)
{
	try
	{
		this->inputFile.open(inputFilename);
		this->outputFile.open(outputFilename);
		if (!this->inputFile.is_open() || !this->outputFile.is_open())
			throw Exception_file(static_cast<int>(Errors::fileIsNotOpen), "Не удалось открыть файл\nВозможно, он не создан");
	}
	catch (Exception_file exc)
	{
		exc.show();
		exit(static_cast<int>(Errors::fileIsNotOpen));
	}
}

template <class T>
void TextFile<T>::readFromFile(Loop<T>& destination) //вывод из файла 
{
	T element;
	char space[10];
	int i = 0;
	char *c=new char;
	while (true)
	{
		if (this->inputFile.eof())
			break;
		this->inputFile >> element;

		try
		{
			if (this->inputFile.fail())
				throw Exception_file(static_cast<int>(Errors::incorrectInput), "Некорректная структура данных в файле");
		}
		catch (Exception_file ex)
		{
			ex.show();
			exit(static_cast<int>(Errors::incorrectInput));
		}
		destination.push(element);
		this->inputFile.getline(space, 10);
		this->inputFile.getline(space, 10);
		this->inputFile >> c;
		if (!c[0])
		{
			break;
		}
		else this->inputFile.seekg(-6, ios::cur);
	}
}

template <class T>
void TextFile<T>::writeToFile(Loop<T>& destination)  //ввод в файл
{
	for (int i = 0; i < destination.getElementsAmount(); i++)
		this->outputFile << destination.getElement(i) << endl;
}


template <class T>
void TextFile<T>::CloseFile() //закрытие файла
{
	this->inputFile.close();
	this->outputFile.close();
}


template <class T>
TextFile<T>::~TextFile()
{
	this->inputFile.close();
	this->outputFile.close();
}