#pragma once
#include<fstream>
#include "Student.h"
#include <list>
#include <iostream>
class DAO
{
public:
	bool writeFile(Student, string);
	bool writeFile2(string, string);
	string readFile(string);
	list<string> readList(string);
	list<Student> readObj(string);
	bool checkID(int);
	DAO();
	~DAO();
};
