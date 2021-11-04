#include <conio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>

#define MAX 100

using namespace std;

fstream MyFile;

struct Phone
{
	char mark[15];
	char model[15];
	char color[10];
	unsigned price;
	char ram[10];
	char diagonal[5];
	unsigned sim;
	unsigned brojka;
} phone;


void createPhone();
void createListOfPhones();
void updatePhone();
int reportGeneral();
void PhonesOUTPUT();
void reportPhonesBySmallRam();
void reportPhonesBySim2();

char ch;

int main()
{
	system("cls"); system("color 0F");

	while (1)		//Меню на програмата
	{
		cout << endl << endl
			<< "\t\t*** ---------MENU Phones Store---------***" << endl
			<< "\t\t*** 1. Add new Phone                   ***" << endl
			<< "\t\t*** 2. Add new LIST of Phones          ***" << endl
			<< "\t\t*** 3. UPDATE Phones's Data            ***" << endl
			<< "\t\t*** 4. REPORTS                         ***" << endl
			<< "\t\t*** 5. RESERVE                         ***" << endl
			<< "\t\t*** ---------------------------------- ***" << endl
			<< "\t\t*** 0. EXIT                            ***" << endl
			<< "\t\t*** ---------------------------------- ***" << endl
			<< "\t\t    Enter option: ";

		cin >> ch;
		switch (ch)
		{
		case '0': return 0; break;
		case '1': createPhone(); break;
		case '2': createListOfPhones(); break;
		case '3': updatePhone(); break;
		case '4': reportGeneral(); system("cls"); system("color 0F"); break;
		default: cout << endl << "Invalid ANSWER!"; system("cls"); system("color 0F"); break;
		}
	}
	return 0;
}

void createPhone()
{
	MyFile.open("phone.dat", ios::app);
	if (!MyFile)
	{
		cerr << "File open failed !!!\n";
		system("pause>nul");
		return;
	}
	int n = 1; char temp[20];
	cout << endl << "--- Adding a new Phone in database ---" << endl; cin.ignore();
	while (n != 0)
	{
		cout << endl << "Marka: "; cin.getline(phone.mark, 15);
		cout << endl << "Model: "; cin.getline(phone.model, 15);
		cout << endl << "Color: "; cin.getline(phone.color, 10);
		cout << endl << "Price: "; cin.getline(temp, 10); phone.price = (unsigned)atoi(temp);
		cout << endl << "RAM: "; cin.getline(phone.ram, 10);
		cout << endl << "Diagonal: "; cin.getline(phone.diagonal, 5);
		cout << endl << "Sim Cards: "; cin.getline(temp, 6); phone.sim = (unsigned)atoi(temp);
		cout << endl << "Broj phones: "; cin.getline(temp, 6); phone.brojka = (unsigned)atoi(temp);
		MyFile.write((const char*)&phone, sizeof(Phone));
		cout << endl << "Nov telefon ? (1-da, 0-ne) :"; cin >> n; cin.ignore();
	}
	MyFile.close();
}


int reportGeneral()
{
	system("cls"); system("color 0F");
	while (1)
	{
		cout << endl << endl
			<< "\t\t*** --------  REPORTS ---------- ***" << endl
			<< "\t\t*** 1.REPORT phones by ram small ***" << endl
			<< "\t\t*** 2.REPORT phones by sim=2     ***" << endl
			<< "\t\t*** 3.REPORT phones ALL          ***" << endl
			<< "\t\t*** -----------------------------***" << endl
			<< "\t\t*** 0. EXIT                      ***" << endl
			<< "\t\t*** -----------------------------***" << endl
			<< "\t\t    Enter option: ";
		cin >> ch;
		switch (ch)
		{
		case '0': return 0; break;
		case '1': reportPhonesBySmallRam(); break;
		case '2': reportPhonesBySim2(); break;
		case '3': PhonesOUTPUT(); break;
		default: cout << endl << "Invalid ANSWER!"; system("cls"); system("color 0F"); break;
		}
	}
}

void createListOfPhones()
{
	MyFile.open("phone.dat", ios::app);
	if (!MyFile)
	{
		cerr << "File open failed !!!\n";
		system("pause>nul");
		return;
	}
	//system("cls"); system("color 0F");
	int n;
	cout << endl << "Enter number of phones to be added in database: ";
	cin >> n; char temp[20]; cin.ignore();
	for (int i = 1; i <= n; ++i)
	{
		cout << "----- Phone " << i << " to be added-----";
		cout << endl << "Marka: "; cin.getline(phone.mark, 15);
		cout << endl << "Model: "; cin.getline(phone.model, 15);
		cout << endl << "Color: "; cin.getline(phone.color, 10);
		cout << endl << "Price: "; cin.getline(temp, 10); phone.price = (unsigned)atoi(temp);
		cout << endl << "RAM: "; cin.getline(phone.ram, 10);
		cout << endl << "Diagonal: "; cin.getline(phone.diagonal, 5);
		cout << endl << "Sim Cards: "; cin.getline(temp, 6); phone.sim = (unsigned)atoi(temp);
		cout << endl << "Broj phones: "; cin.getline(temp, 6); phone.brojka = (unsigned)atoi(temp);
		MyFile.write((const char*)&phone, sizeof(Phone));
	}
	cout << endl << "---- Phones ADDED!!! ----";
	MyFile.close();
}


void updatePhone()
{
	int result1, result2, result3; char temp[20];
	unsigned long pos;
	char umarka[15];
	char umodel[15];
	char ucolor[10];
	MyFile.open("phone.dat", ios::in | ios::out);
	if (!MyFile)
	{
		cerr << "File open failed !!!\n";
		system("pause>nul");
		return;
	}
	MyFile.seekg(0, ios::beg);
	cout << endl << "Marka na Phone za promyana => "; scanf_s("%14s", umarka);
	cout << endl << "Model na Phone za promyana => "; scanf_s("%14s", umodel);
	cout << endl << "Color na Phone za promyana => "; scanf_s("%9s", ucolor);

	while (MyFile.read((char*)&phone, sizeof(Phone)))
	{
		result1 = strncmp(phone.mark, umarka, 14);
		result2 = strncmp(phone.model, umodel, 14);
		result3 = strncmp(phone.color, ucolor, 9);
		if (result1 == 0 && result2 == 0 && result3 == 0)
		{
			cout << "---Update data for THAT phone---"; cin.ignore();
			cout << endl << "Old Price: " << phone.price << "New price: "; gets_s(temp); phone.price = (unsigned)atoi(temp);
			cout << endl << "Old RAM: " << phone.ram << "New RAM:"; cin >> phone.ram;
			cout << endl << "Old Diagonal: " << phone.diagonal << "New Diagonal:"; cin >> phone.diagonal;
			cout << endl << "Old Sims: " << phone.sim << "New Sims:"; gets_s(temp); phone.sim = (unsigned)atoi(temp);
			cout << endl << "Old Broj: " << phone.brojka << "New Broj:"; gets_s(temp); phone.brojka = (unsigned)atoi(temp);
			pos = MyFile.tellg();
			pos = pos - sizeof(struct Phone);
			MyFile.seekg(pos);
			MyFile.write((const char*)&phone, sizeof(struct Phone));
			break;
		}
	}
	MyFile.close();
}



void reportPhonesBySmallRam()
{
	int a, b;
	MyFile.open("phone.dat", ios::in);
	if (!MyFile)
	{
		cerr << "File open failed !!!\n";
		system("pause>nul");
		return;
	}
	cout << endl << "--- REPORT for phones with small RAM ---" << endl;
	cout << endl << setw(15) << "Marka";
	cout << setw(15) << "Model";
	cout << setw(10) << "Color";
	cout << setw(10) << "Price";
	cout << setw(10) << "RAM";
	cout << setw(8) << "Diag";
	cout << setw(6) << "Sim";
	cout << setw(6) << "Broj" << endl;
	for (int i = 0; i <= 70; ++i) cout << "-";
	while (MyFile.read((char*)&phone, sizeof(Phone)))
	{
		a = (int)phone.ram[0]; a = a - 48;
		b = (int)phone.ram[1]; b = b - 48;

		if (a == 1 && b == 6 || a == 3 && b == 2)
		{
			cout << endl << setw(15) << phone.mark;
			cout << setw(15) << phone.model;
			cout << setw(10) << phone.color;
			printf("%10d", phone.price);
			cout << setw(10) << phone.ram;
			cout << setw(8) << phone.diagonal;
			cout << setw(6) << phone.sim;
			cout << setw(6) << phone.brojka;
		}
	}
	MyFile.close();
}

void reportPhonesBySim2()
{
	MyFile.open("phone.dat", ios::in);
	if (!MyFile)
	{
		cerr << "File open failed !!!\n";
		system("pause>nul");
		return;
	}
	cout << endl << "--- REPORT for phones with 2 SIMS ---" << endl;
	cout << endl << setw(15) << "Marka";
	cout << setw(15) << "Model";
	cout << setw(10) << "Color";
	cout << setw(10) << "Price";
	cout << setw(10) << "RAM";
	cout << setw(8) << "Diag";
	cout << setw(6) << "Sim";
	cout << setw(6) << "Broj" << endl;
	for (int i = 0; i <= 70; ++i) cout << "-";
	while (MyFile.read((char*)&phone, sizeof(Phone)))
	{
		if (phone.sim == 2)
		{
			cout << endl << setw(15) << phone.mark;
			cout << setw(15) << phone.model;
			cout << setw(10) << phone.color;
			printf("%10d", phone.price);
			cout << setw(10) << phone.ram;
			cout << setw(8) << phone.diagonal;
			cout << setw(6) << phone.sim;
			cout << setw(6) << phone.brojka;
		}
	}
	MyFile.close();
}


void PhonesOUTPUT()
{
	MyFile.open("phone.dat", ios::in);
	if (!MyFile)
	{
		cerr << "File open failed !!!\n";
		system("pause>nul");
		return;
	}
	cout << endl << "--- REPORT for ALL phones ---" << endl;
	cout << endl << setw(15) << "Marka";
	cout << setw(15) << "Model";
	cout << setw(10) << "Color";
	cout << setw(10) << "Price";
	cout << setw(10) << "RAM";
	cout << setw(8) << "Diag";
	cout << setw(6) << "Sim";
	cout << setw(6) << "Broj" << endl;
	for (int i = 0; i <= 80; ++i) cout << "-";
	while (MyFile.read((char*)&phone, sizeof(Phone)))
	{
		cout << endl << setw(15) << phone.mark;
		cout << setw(15) << phone.model;
		cout << setw(10) << phone.color;
		printf("%10d", phone.price);
		cout << setw(10) << phone.ram;
		cout << setw(8) << phone.diagonal;
		cout << setw(6) << phone.sim;
		cout << setw(6) << phone.brojka;
	}
	MyFile.close();
}