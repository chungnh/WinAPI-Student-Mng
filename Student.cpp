#include "Student.h"

void Student::setID(int x)
{
	id = x;
}

int Student::getID()
{
	return id;
}

void Student::setName(string x)
{
	name = x;
}

string Student::getName()
{
	return name;
}
Student::Student() {

}

Student::Student(int id1, string name1)
{
	id = id1;
	name = name1;
}

Student::~Student()
{
}