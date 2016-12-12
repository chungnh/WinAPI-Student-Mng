#pragma once
#include<string>
using namespace std;
class Student
{
private:
	int id;
	string name;
public:
	void setID(int);
	int getID();
	void setName(string);
	string getName();
	Student(int, string);
	Student();
	~Student();
};
