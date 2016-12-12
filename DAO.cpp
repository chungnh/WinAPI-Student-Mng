#include "DAO.h"
#include <fstream>

bool DAO::writeFile(Student st, string path)
{
	fstream f;
	f.open(path, ios::out | ios::app);
	f << st.getID() << "    " << st.getName() << endl;
	f.close();
	return true;
}

bool DAO::writeFile2(string data, string path)
{
	fstream f;
	f.open(path, ios::out | ios::app);
	f << data << endl;
	f.close();
	return true;
}

string DAO::readFile(string path)
{
	string out, line;
	fstream f;
	f.open(path, ios::in);
	while (getline(f, line)) {
		out += line + "\n";
	}
	f.close();
	return out;
}

list<string> DAO::readList(string path)
{
	list<string> list;
	Student st;
	string line;
	fstream f;
	f.open(path, ios::in);
	while (getline(f, line)) {
		bool flag = true;
		try
		{
			list.push_back(line);
		}
		catch (const std::exception&)
		{
			flag = false;
		}
		if (flag == false) {
			continue;
		}
	}
	f.close();
	return list;
}

list<Student> DAO::readObj(string path)
{
	list<Student> list;
	Student st;
	string line;
	fstream f;
	f.open(path, ios::in);
	int id;
	string name;
	while (getline(f, line)) {
		bool flag = true;
		try
		{
			int p = line.find("    ");
			id = stoi(line.substr(0, p)); st.setID(id);
			line = line.substr(p + 1);
			name = line.substr(0, p).c_str(); st.setName(name);
			line = line.substr(p + 1);
			list.push_back(st);
		}
		catch (const std::exception&)
		{
			flag = false;
		}
		if (flag == false) {
			continue;
		}
	}
	return list;
}

bool DAO::checkID(int id)
{
	list<Student> list1 = readObj("data.txt");
	list<Student>::iterator it;
	for(it = list1.begin(); it != list1.end(); it++) {
		if ((*it).getID() == id) {
			return true;
		}
	}
	return false;
}

DAO::DAO()
{
}

DAO::~DAO()
{
}