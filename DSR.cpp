
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include <random>
#include <iomanip>
#include<string>
#include <cstdlib>
#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <windows.h>
#include <limits>
using namespace std;
const int n = 50;
struct Apartment
{
	string ID;
	string street;
	int neighbourhood;
	double area;
	double price;
	int rooms;
	int status = 0;
	int inspections = 0;
};
void WriteToFile(Apartment aparts[], int count);
void CreateAnAppartment(Apartment allApartments[], int& sequenceNumber, string& neigh);
void validateStatus(Apartment& created);
void validateNeighbourhood(Apartment& created);
string toUpperCase(string SearchedNeighbourhood);
void displayArray(Apartment aparts[], int seqenceNum);
void displayRoomsByPrice(Apartment arr[], int count);
void displayBestValue(Apartment arr[], int count);
void findNearby(Apartment arr[], int count, Apartment searched);
void validates(int& validated);
void validates(string& validated);
void validates(double& validated);
void sortByArea(Apartment apartments[], int count);
void inNeighbourRooms(Apartment arr[], int count, Apartment searched);
void displayByPriceToArea(Apartment arr[], int count);
void inNeighbour(Apartment arr[], int count);
void findNearby(Apartment arr[], int count, Apartment searched);
void propertyInspection(Apartment arr[], int& count);
void FindUnwantedNeighbourhood(Apartment arr[], int count);
void ReadFile(Apartment aparts[], int& count);
void convertNeighbourhood(int neigh, string& converted);
bool fileExists(const string& name);

bool fileExists(const string& name)
{
	bool exist = false;
	ifstream f(name);
	exist = f.good();
	f.close();
	return exist;
}
void getInput(int& count, Apartment allAparts[])

{
	ReadFile(allAparts, count);
	int input;
	int secondInput;
	int thirdInput;
	do
	{
		cout << endl << "����� 1: �������� �� �����������, " << endl
			<< "����� 2: ��������� �� ������ �����������" << endl
			<< "����� 3: ������� 1" << endl
			<< "����� 4: ��������� �� ������������� �� ����" << endl
			<< "����� 5: ������� 2" << endl
			<< "����� 6: ������� �����" << endl
			<< "����� 7: ������ ���-����� ��������� �������" << endl
			<< "����� 8: ������ ��������� ��� ����" << endl
			<< "����� 9: ������� �� ����" << endl
			<< "����� 10: ����� �� ����������" << endl
			<< "������ �����: ";
		validates(input);
		switch (input)
		{

		case 1:
		{
			int numToAdd;
			do
			{
				cout << "����� ����������� ������ �� �������� (�������� 50)" << endl;
				validates(numToAdd);
				if (numToAdd > 50)
				{
					cout << "��������� ���� ����������� (�������� 50)" << endl;
				}
				if (numToAdd <= 0)
				{
					cout << "��������� ���� ����������� (������� 1)" << endl;
				}
				if (numToAdd + count > 50)
				{
					cout << "��������� ���� ����������� (���������� ��������� 50)" << endl;
				}

			} while (numToAdd > 50 || numToAdd < 0 || numToAdd + count > 50);

			string Neighb;
			for (int i = 1; i <= numToAdd; i++)
			{
				if (!(numToAdd > 50 || numToAdd <= 0 || numToAdd + count > 50))
				{
					CreateAnAppartment(allAparts, count, Neighb);
				}

			}
			if (!(numToAdd > 50 || numToAdd <= 0 || numToAdd + count > 50))
			{
				cout << numToAdd << " �������� �����������";
			}

		}break;
		case 2:
			displayArray(allAparts, count);
			break;
		case 3:
		{
			cout << "1- ������� ����������� �� ������� �������" << endl
				<< "2- �������� �� ����������� � ���-����� ����������� ���� �� ��������� �����" << endl;
			do
			{
				validates(thirdInput);
			} while (!thirdInput == 1 && !thirdInput == 2);
			switch (thirdInput)
			{
			case 1:
				displayBestValue(allAparts, count);//������� ����������� � ���-����� ����������� ���� �� ��������� �����
				break;
			case 2:
				inNeighbour(allAparts, count);//������� ����� �� ���� � ���� ����
				break;
			}
		}
		break;
		case 4:
			sortByArea(allAparts, count);
			break;
		case 5:
		{
			cout << "����� 1- �������� ������������� �� ���� �� ��������� ����� � �� �������" << endl
				<< "����� 2- ������� ����������� �� ���������� ���� � ���� ����" << endl;
			do
			{
				validates(secondInput);
			} while (secondInput != 1 && secondInput != 2);
			switch (secondInput)
			{

			case 1:
				displayByPriceToArea(allAparts, count);
				break;
			case 2:
				displayRoomsByPrice(allAparts, count);
				break;
				if (secondInput != 1 && secondInput != 2)
				{
					cout << "��������� ����� �������� 1 ��� 2" << endl;
				}
			}
		}
		break;
		
		case 6:
			propertyInspection(allAparts, count);
			break;
		case 7:
			FindUnwantedNeighbourhood(allAparts, count);
			break;
		case 8:
			WriteToFile(allAparts, count);
			break;
		case 9:
			ReadFile(allAparts, count);
			break;
		}
	} while (input != 10);
	WriteToFile(allAparts, count);
}

void validates(string& validated)
{
	cin.clear();
	getline(cin, validated);
	cin.clear();


	while (cin.fail())
	{
		cout << "��������";
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		getline(cin, validated);
	}

}
void validates(int& validated)
{
	cin >> validated;
	cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
	while (cin.fail())
	{
		cout << "���� �������� ���� �����" << endl;
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		cin >> validated;
	}
}

void validates(double& validated)
{
	cin >> validated;
	while (cin.fail())
	{
		cout << "���� �������� ������ �����" << endl;
		cin.clear();
		cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		cin >> validated;
	}
}
//overloading � int double � string
void displayArray(Apartment aparts[], int seqenceNum) // ������� ������ �� ����� ��������� �� ����������� �����
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout << left << setw(14) << "ID" << setw(20) << "�����" << setw(23) << "�������" << setw(19) << "����" << setw(9) << "����" << setw(10) << "����" << setw(17) << "������" << setw(28) << "������" << endl;
	for (int i = 0; i < seqenceNum; i++)
	{
		string StatusApartment;
		switch (aparts[i].status)
		{
		case 0:
			StatusApartment = "������:��������";
			break;
		case 1:
			StatusApartment = "������:� ��������";
			break;
		case 2:
			StatusApartment = "������:�������";
			break;
		default:
			StatusApartment = "������ ������, ���� �� ���� ��������";
			break;
		}
		string toDisplay;
		convertNeighbourhood(aparts[i].neighbourhood, toDisplay);
		cout << setw(10) << aparts[i].ID << setw(24)
			<< aparts[i].street << setw(23)
			<< toDisplay << setw(15)
			<< setprecision(2)
			<< aparts[i].area << setw(15)
			<< aparts[i].price << setw(10)
			<< aparts[i].rooms << setw(10)
			<< aparts[i].inspections << setw(10)
			<< StatusApartment;

		cout << endl;
	}
}
//������ � ������ �� ����
void WriteToFile(Apartment aparts[], int count)
{
	ofstream outfile("DataFile.bin", ios_base::binary);
	int sizeStreet;

	for (int i = 0; i < count; i++)
	{
		sizeStreet = aparts[i].street.size();
		outfile.write((char*)aparts[i].ID.c_str(), 7);
		outfile.write((char*)&aparts[i].neighbourhood, sizeof(int));
		outfile.write((char*)&sizeStreet, sizeof(int));
		outfile.write((char*)aparts[i].street.c_str(), sizeStreet + 1);
		outfile.write((char*)&aparts[i].area, sizeof(double));
		outfile.write((char*)&aparts[i].price, sizeof(double));
		outfile.write((char*)&aparts[i].rooms, sizeof(int));
		outfile.write((char*)&aparts[i].status, sizeof(int));
		outfile.write((char*)&aparts[i].inspections, sizeof(int));
	}
	outfile.flush();
	outfile.close();
}
void ReadFile(Apartment aparts[], int& count)
{
	string fileName = "DataFile.bin";
	ifstream read;
	if (fileExists(fileName))
	{

	}
	else
	{
		cout << "������ �� ����������" << endl;
		return;
	}
	ifstream readFile("DataFile.bin", ios_base::binary | ios_base::beg);
	int sizeStreet;
	char* ID;
	char* street;
	//while (!readFile.eof())
	while (readFile.peek() != EOF)
	{
		//if (readFile.peek() == EOF)
			//break;
		sizeStreet = 0;
		ID = (char*)calloc(7, 1);
		readFile.read(ID, 7);
		aparts[count].ID = ID;
		readFile.read((char*)&aparts[count].neighbourhood, sizeof(int));
		readFile.read((char*)&sizeStreet, sizeof(int));
		street = (char*)calloc(sizeStreet + 1, 1);
		readFile.read(street, sizeStreet + 1);
		aparts[count].street = street;
		readFile.read((char*)&aparts[count].area, sizeof(double));
		readFile.read((char*)&aparts[count].price, sizeof(double));
		readFile.read((char*)&aparts[count].rooms, sizeof(int));
		readFile.read((char*)&aparts[count].status, sizeof(int));
		readFile.read((char*)&aparts[count].inspections, sizeof(int));
		count++;
	}
}
void sortByArea(Apartment apartments[], int count)//done
{
	Apartment switcher;
	bool flag = true;
	for (int i = 0; i < count; i++)
	{
		flag = false;
		for (int j = 0; j < count - 1; j++)
		{
			if (apartments[j + 1].area < apartments[j].area)
			{
				switcher = apartments[j];
				apartments[j] = apartments[j + 1];
				apartments[j + 1] = switcher;
				flag = true;
			}
		}
		if (!flag)
		{
			break;
		}
	}
}
string genID()
{
	short max = 122;
	short min = 48;
	short range = max - min;
	string generatedID = "nnnnnn";
	srand(time(0));
	for (int i = 0; i < 6; i++)
	{
		int rnd = 0;
		while (!(rnd >= 48 && rnd <= 57 || rnd >= 65 && rnd <= 90 || rnd >= 97 && rnd <= 122))
		{

			rnd = rand() % range + min;
			generatedID[i] = rnd;
		}
	}
	return generatedID;
}
void CreateAnAppartment(Apartment allApartments[], int& sequenceNumber, string& neigh)
{
	Apartment created;
	cout << "�������� �����:";
	validates(created.street);
	cout << "\n" << "�������� ������� (1-�����, 2-������, 3-������, 4-������, 5-�������):";
	validateNeighbourhood(created);
	cout << "\n" << "�������� ���� �� �����:";
	validates(created.area);
	cout << "\n" << "�������� ���� �� �����:";
	validates(created.price);
	cout << "\n" << "�������� ����� ���� ��� �����:";
	validates(created.rooms);
	cout << "\n" << "�������� ������ �� ����������� 0- �������� 1- � �������� 2- �������:";
	validateStatus(created);
	cout << "\n";
	string id = genID();
	bool isSame = false;
	do
	{
		for (int i = 0; i < n; i++)
		{
			if (allApartments[i].ID == id)
			{
				id = genID();
				isSame = true;
			}
		}

	} while (isSame);

	created.ID = id;
	allApartments[sequenceNumber] = created;
	sequenceNumber++;


}
void validateStatus(Apartment& created)
{
	do
	{
		validates(created.status);
		if (!(created.status != 0 && created.status != 1 && created.status != 2))
		{
			return;
		}
		cout << "������ ������ 0-��������� 1- � �������� 2- �������: " << endl;
	} while (created.status != 0 && created.status != 1 && created.status != 2);
}
void validateNeighbourhood(Apartment& created)
{
	do
	{
		validates(created.neighbourhood);
		if (!(created.neighbourhood > 5 || created.neighbourhood < 1))
		{
			return;
		}
		cout << "��������� ������� ���� �������� ���� ���� �����: ";
	} while (created.neighbourhood > 5 || created.neighbourhood < 0);
}
string toUpperCase(string converted)// ����� ������� ����� �������
{
	for (int i = 0; i < converted.length(); i++)
	{
		if (converted[i] > 96 && converted[i] < 123)
		{
			converted[i] -= 32;
		}
	}
	return converted;
}
void convertNeighbourhood(int neigh, string& converted) // �������� ������� �� (1 �� 5) �� ����������� � ������
{
	switch (neigh)
	{
	case 1:
		converted = "Chaika";
		break;
	case 2:
		converted = "Levski";
		break;
	case 3:
		converted = "Centur";
		break;
	case 4:
		converted = "Grycka";
		break;
	case 5:
		converted = "Mladost";
		break;
	default:
		cout << "Nevaliden kvartal" << endl;
	}
}
void inNeighbour(Apartment arr[], int count) {//������� ������ �� ��������� �������
	cout << "�������� ������� ��, ����� ������ �� ������ ����� (1-����� 2- ������ 3-������ 4-������ 5-�������):" << endl;
	int SearchedNeighbourhood;
	validates(SearchedNeighbourhood);
	if (SearchedNeighbourhood < 0 || SearchedNeighbourhood > 5)
	{
		cout << "��������� �������" << endl;
	}
	for (int i = 0; i < count; i++)
	{
		if (arr[i].neighbourhood == SearchedNeighbourhood)
		{
			displayArray(&arr[i], 1);
		}
	}
}
void inNeighbourRooms(Apartment arr[], int count, Apartment searched) {//������� ������ � ������� �������� � ���� ����

	for (int i = 0; i < count; i++)
	{
		if (searched.neighbourhood == arr[i].neighbourhood && searched.rooms == arr[i].rooms)
		{
			displayArray(&arr[i], 1);
		}
	}
}
void displayRoomsByPrice(Apartment arr[], int count)//������� ����������� �� ���������� ���� � ���� ����
{
	cout << "�������� ���������� ����, ����� ����� ������� �� ����������" << endl;
	int value;
	validates(value);
	cout << "�������� ����� ����� ���������� ������" << endl;
	int numOfRooms;
	validates(numOfRooms);
	int numToDisplay = 1;
	Apartment max;
	for (int i = 0; i < count; i++)
		if (arr[i].rooms == numOfRooms && arr[i].price <= value)
			displayArray(&arr[i], numToDisplay);

}
void displayBestValue(Apartment arr[], int count) // ������� ����������� � ���-����� ����������� ���� �� ��������� �����
{
	Apartment max = arr[0];
	for (int i = 1; i < count; i++)
	{
		double ratio = max.area / max.price;
		double isBetter = arr[i].area / arr[i].price;
		if (ratio < isBetter)
			max = arr[i];
	}
	// Display the best value apartment
	displayArray(&max, 1);
}
void displayByPriceToArea(Apartment arr[], int count)//done
{
	Apartment display[n];
	int countDisplay = 0;
	int toDisplay = 1;
	for (int i = 0; i < count; i++)
	{
		if (arr[i].status == 1)
		{
			display[countDisplay] = arr[i];
			countDisplay++;
		}
	}
	bool flag = true;
	Apartment swap;
	for (int i = 0; i < countDisplay; i++)
	{
		flag = false;
		for (int j = 0; j < countDisplay - 1; j++)
		{
			if (display[j].price / display[j].area > display[j + 1].price / display[j + 1].area)
			{
				swap = display[j];
				display[j] = display[j + 1];
				display[j + 1] = swap;
				flag = true;
			}
		}
		if (!flag)
		{
			break;
		}
	}
	for (int i = 0; i < countDisplay; i++)
	{
		displayArray(&display[i], toDisplay);
	}
}
void fillArray(Apartment arr1[], Apartment arr2[], const int& count)
{
	for (int i = 0; i < count; i++)
		arr2[i] = arr1[i];
}
void findNearby(Apartment arr[], int count, Apartment searched)//��������� ����� �� ������� ��������
{
	for (int i = 0; i < count; i++)
	{
		int neigh = searched.neighbourhood;
		bool isClose;
		if ((neigh + 1 == arr[i].neighbourhood || neigh - 1 == arr[i].neighbourhood) && arr[i].rooms == searched.rooms)
		{
			displayArray(&arr[i], 1);
		}
	}
}
void propertyInspection(Apartment arr[], int& count) //������ �� �����
{
	cout << "�������� ���������������� ����� ��, ����� ������ �� ��������� �����" << endl;
	string refNum;
	validates(refNum);
	refNum = regex_replace(refNum, regex("^\\s+|\\s+$"), "");
	bool found = false;
	Apartment searched;
	for (int i = 0; i < count; i++)
	{
		string input = "ne";
		if (toUpperCase(refNum) == toUpperCase(arr[i].ID))
		{
			found = true;
			searched = arr[i];
			if (arr[i].status != 1)
			{
				cout << "����� �� � � ��������" << endl;
			}
			else
			{
				arr[i].inspections++;
				cout << "�� �� ������� �� ������� �� ����� \"da\" ��� \"ne\")" << endl;
				validates(input);
				if (input == "da" && arr[i].status == 1)
				{
					cout << "����� ������ �� � ������ ��������� �� ����������� 0- �������� � 2- �������" << endl;
					int option;
					do {
						validates(option);
						switch (option)
						{
						case 0:
						{
							arr[i].status = 0;
							arr[i].inspections = 0;
						}
						break;

						case 2:
							arr[i].status = 2;
							break;
						default:
							cout << "��������� �����" << endl;
							break;
						}
					} while (option != 0 && option != 1 && option != 2);
				}
				if (input == "ne") {
					cout << "������ �� �� �� ������� ����� ��� ����� ���� ���� �� ����� �������" << endl;
					input = "";
					validates(input);
					if (input == "da")
					{
						inNeighbourRooms(arr, count, searched);

					}
					else
					{
						cout << "������ �� �� �� ������� ����� �� ������� �������� ��� ����� ���� ����" << endl;
						validates(input);
						if (input == "da")
						{
							findNearby(arr, count, searched);
						}
					}
				}
			}
		}


	}
	if (!found)
	{
		cout << "��������� ���������������� �����" << endl;
	}
}
void FindUnwantedNeighbourhood(Apartment arr[], int count) // ������ ���-��������� �������
{
	Apartment Chaika;
	Chaika.neighbourhood = 1;
	Apartment Levski;
	Levski.neighbourhood = 2;
	Apartment Center;
	Center.neighbourhood = 3;
	Apartment Grucka;
	Grucka.neighbourhood = 4;
	Apartment Mladost;
	Mladost.neighbourhood = 5;
	Apartment findMax[5];

	for (int i = 0; i < count; i++)
	{
		if (arr[i].status != 0 && arr[i].status != 2)
		{
			switch (arr[i].neighbourhood)
			{
			case 1:
				Chaika.inspections += arr[i].inspections;
				break;
			case 2:
				Levski.inspections += arr[i].inspections;
				break;
			case 3:
				Center.inspections += arr[i].inspections;
				break;
			case 4:
				Grucka.inspections += arr[i].inspections;
				break;
			case 5:
				Mladost.inspections += arr[i].inspections;
				break;
			}
		}
	}
	findMax[0] = Chaika;
	findMax[1] = Levski;
	findMax[2] = Center;
	findMax[3] = Grucka;
	findMax[4] = Mladost;
	Apartment max = Chaika;
	for (int i = 0; i < 5; i++)
	{
		if (max.inspections < findMax[i].inspections)
		{
			max = findMax[i];
		}
	}
	string convertNeighbourhood1;
	convertNeighbourhood(max.neighbourhood, convertNeighbourhood1);
	cout << "�������� � ���-������ ��������� ����� �:" << convertNeighbourhood1 << endl;
}

int main()
{
	setlocale(LC_ALL, "Bulgarian");
		//std::ios::sync_with_stdio(false);
		//std::locale::global(std::locale(""));
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	Apartment arr[n];
	int sequenceNum = 0;
	getInput(sequenceNum, arr);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to c new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
