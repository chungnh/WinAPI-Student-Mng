#include <windows.h>
#include <string>
#include <iostream>
#include "DAO.h"
#include "Student.h"
using namespace std;
HWND button1, button2, button3, textfield1, textfield2;
list<string> result;
list<string>::iterator it;
int selectrow = 33;
TCHAR szAppName[] = TEXT("PopPad1");
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	static HWND list;
	fstream f;
	string input1;
	string input2;
	string line;
	string input;
	DAO dao;
	Student st;
	int id;
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		textfield1 = CreateWindow(TEXT("EDIT"), TEXT("Enter ID"),
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			20, 20, 300, 25,
			hwnd, (HMENU)11, NULL, NULL);
		textfield2 = CreateWindow(TEXT("EDIT"), TEXT("Enter Name"),
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			20, 60, 300, 25,
			hwnd, (HMENU)22, NULL, NULL);
		button1 = CreateWindow("BUTTON", "ADD",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			450, 20, 100, 25,
			hwnd, (HMENU)1, NULL, NULL);
		button2 = CreateWindow("BUTTON", "DEL",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			450, 50, 100, 25,
			hwnd, (HMENU)2, NULL, NULL);
		button3 = CreateWindow("BUTTON", "SHOW",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			450, 200, 100, 25,
			hwnd, (HMENU)3, NULL, NULL);
		list = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_BORDER | WS_VSCROLL |LBS_EXTENDEDSEL | LBS_SORT,
			20, 120, 300, 200,
			hwnd, (HMENU)4, NULL, NULL); SendMessage(list, LB_RESETCONTENT, 0, 0);
		SendMessage(list, LB_RESETCONTENT, 0, 0);
		f.open("data.txt", ios::in);
		while (getline(f, line)) {
			SendMessage(list, LB_ADDSTRING, 0, (LPARAM)line.c_str());
		}
		break;
	case WM_SETFOCUS:
		SetFocus(textfield1);
		return 0;
	case WM_COMMAND:	
		switch (LOWORD (wparam)) {
		case 11:
			if (HIWORD(wparam) == EN_ERRSPACE || HIWORD(wparam) == EN_MAXTEXT) {
				MessageBox(hwnd, "xxx", szAppName, MB_OK | MB_ICONSTOP);
				return 0;
			}
			break;
		case 1://add
			GetWindowText(GetDlgItem(hwnd, 11), reinterpret_cast <char*> ((char *)input1.c_str()), 100);
			GetWindowText(GetDlgItem(hwnd, 22), reinterpret_cast <char*> ((char *)input2.c_str()), 100);	
			try
			{
				id = stoi(input1);
				st = Student(id, input2.c_str());
			}
			catch (const std::exception&)
			{
				MessageBox(hwnd, "Must not be blank ID or Name, ID must be number", "Warning", 0);
				return 0;
			}		
			if (dao.checkID(id)) {
				MessageBox(hwnd, "Already Exist", "Warning", 0);
			}
			else {
				dao.writeFile(st, "data.txt");
				input = input1 + input2;
				SendMessage(list, LB_RESETCONTENT, 0, 0);
				f.open("data.txt", ios::in);
				while (getline(f, line)) {
					SendMessage(list, LB_ADDSTRING, 0, (LPARAM)line.c_str());
				}
				SetWindowText(textfield1, "");
				SetWindowText(textfield2, "");
			}
			break;
		case 2://del
			result = dao.readList("data.txt");
			if (result.empty()) {
				MessageBox(hwnd, "Empty", "Warning", 0);
				break;
			}
			if(selectrow == 33) {//dm may
				MessageBox(hwnd, "choice one", "Warning", 0);
				break;
			}
			else {
				it = result.begin();
				for (int i = 0; i < selectrow; i++) {
					it++;
				}
				it = result.erase(it);
				remove("data.txt");
				for (it = result.begin(); it != result.end(); it++) {
					dao.writeFile2((*it), "data.txt");
				}
				SendMessage(list, LB_DELETESTRING, selectrow, 0);
				/*SendMessage(list, LB_RESETCONTENT, 0, 0);
				f.open("data.txt", ios::in);
				while (getline(f, line)) {
				SendMessage(list, LB_ADDSTRING, 0, (LPARAM)line.c_str());
				}*/
			}
			break;
		case 3://show
			SendMessage(list, LB_RESETCONTENT, 0, 0);
			f.open("data.txt", ios::in);
			while (getline(f, line)) {
				SendMessage(list, LB_ADDSTRING, 0, (LPARAM)line.c_str());
			}
			break;
		case 4:
			if (HIWORD(wparam) == LBN_SELCHANGE) {
				selectrow = (int)SendMessage(list, LB_GETCURSEL, 0, 0);
			}
			break;	
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_HREDRAW; // khi keo tha thi cua so dc ve lai
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0; //cac byte bo sung, ko dung nn cho = 0
	wc.lpszClassName = TEXT("Student Mng");  // ten cua class
	wc.hInstance = hInstance; 
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE); // tao mau nen
	wc.lpszMenuName = NULL;   //ko su dung menu
	wc.lpfnWndProc = WndProc;  //goi ham WndProc

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);  
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // dat bieu tuong con tro vao icon ung dung
	RegisterClass(&wc); //dk lop cua so voi window

	hwnd = CreateWindow(wc.lpszClassName, TEXT("Student Mng"), 
		WS_SYSMENU | WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		200, 200, 600, 400, 
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);   // Display windows
	UpdateWindow(hwnd);   // Update windows
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
