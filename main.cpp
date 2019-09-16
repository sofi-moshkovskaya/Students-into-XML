#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
#include "pugixml.hpp"
using namespace std;



class Address
{
	string _city = "Kherson";
	string _street = "Ushaakova 33";

public:
	Address();
	Address(string city, string street);
	Address(int a);
	~Address();

	void ToScreen();

	void Setcity(string c);
	void Setstreet(string s);
	string Getcity();
	string Getstreet();

	Address operator =(Address ad);

};
class Person
{
	string _name = "No";
	string _surname = "No";
	int _age = 0;
	Address _address;
	bool _smoking = 0;
	string _gender = "female";

public:
	Person();
	Person(string name, string surname, int age, string gender, Address ad, bool smoke);
	Person(int a);
	~Person();

	void ToScreen();

	void Setname(string n);
	void Setsurname(string s);
	void Setage(int a);
	void Setaddress(Address ad);
	void Setsmoking(bool s);
	void Setgender(string g);

	string Getname();
	string Getsurname();
	int Getage();
	Address Getaddress();
	bool Getsmoking();
	string Getgender();
};

void SortbyName(vector<Person> &obj)
{

	int lenght = obj.size();
	for (int i = 0; i < lenght; i++)
	{
		for (int j = 0; j < lenght - 1; j++)
		{
			if (obj[j].Getname() > obj[j + 1].Getname())
			{
				Person temp = Person(obj[j]);
				obj[j] = obj[j + 1];
				obj[j + 1] = temp;
			}
		}
	}
}

void FindbyName(vector <Person>& obj,string name)
{
	int lenght = obj.size();
	for (int i = 0; i < lenght; i++)
	{
		if (obj[i].Getname() == name)
		{
			obj[i].ToScreen();
			cout << endl;
		}
	}
}

void FindbyAge(vector <Person>& obj, int age)
{
	int lenght = obj.size();
	for (int i = 0; i < lenght; i++)
	{
		if (obj[i].Getage() == age)
		{
			obj[i].ToScreen();
			cout << endl;
		}

	}
}

void Addnode(vector<Person> &List);
void Delete(vector<Person>& List);

int main()
{ 
	int stop = 1;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("people.xml");
	pugi::xml_node people = doc.child("People");
	vector<Person> List;
	
	
	
	if (!result)
	{
		cout << "Cannot parse xml: " << result.description() << endl;
		cin.get();
		return  1;
	}

	for (pugi::xml_node person = people.child("Person"); person; person = person.next_sibling("Person"))
	{
		pugi::xml_node address = person.child("address");
		List.push_back(Person(
			person.child("name").text().get(), person.child("surname").text().get(), person.child("age").text().as_int(), person.child("gender").text().get(),
			Address(address.child("city").text().get(), address.child("street").text().get()), person.child("smoking").text().as_bool()));
	}
	int size = List.size();
	
	
	while (true)
	{
		
		cout << "Read and print file -- 1\n" << "Sort objects by name -- 2\n" << "Find an object by age -- 3\n"
			<< "Find an object by name -- 4\n" << "Add a person -- 5\n"<< "Delete an object -- 6\n" << "Exit -- 0" << endl;
		cin >> stop;

		switch (stop)
		{
		case 0:
			return 0;

		case 1:
		{
			for (int i = 0; i < size; i++)
			{
				List[i].ToScreen();
				cout << endl;
			}
			break;
		}

		case 2:
		{
			int size = List.size();
			SortbyName(List);
			for (int i = 0; i < size; i++)
			{
				List[i].ToScreen();
				cout << endl;
			}
			break;
		}

		case 3:
		{
			size = List.size();
			cout << "Enter the age of the person being seeked for:	  ";
			int age;
			cin >> age;
			cout << endl;
			FindbyAge(List, age);
			break;
		}

		case 4:
		{
			size = List.size();
			cout << "Enter the name of the person being seeked for:	  ";
			string name;
			cin >> name;
			cout << endl;
			FindbyName(List, name);
			break;
		}

		case 5:
		{
			Person add = Person(1);
			List.push_back(add);
			Addnode(List);
			break;
		}
		case 6:
		{
			Delete(List);
			break;
		}

		}
	}
	
		
	

	

	int _getch();
}



void Addnode(vector<Person> &List)
{
	pugi::xml_document doc;
	pugi::xml_node people = doc.child("People");
	for (int i = 0; i < List.size(); i++)
	{
		pugi::xml_node person = people.append_child("Person");
		person.prepend_child("Person");
		person.append_child("name").text().set(List[i].Getname().c_str());
		person.append_child("surname").text().set(List[i].Getsurname().c_str());
		person.append_child("age").text().set(List[i].Getage());
		person.append_child("gender").text().set(List[i].Getgender().c_str());
		person.append_child("address");
		person.append_child("city").text().set(List[i].Getaddress().Getcity().c_str());
		person.append_child("street").text().set(List[i].Getaddress().Getstreet().c_str());
		person.append_child("smoking").text().set(List[i].Getsmoking());
	}
	doc.save_file("students.xml");
}

void Delete(vector<Person> &List)
{
	cout << "Input name person to be deleted:   ";
	string name_delete;
	cin >> name_delete;
	for (vector<Person>::iterator it = List.begin(); it != List.end(); it++)
	{
		Person element = *it;
		if (element.Getname() == name_delete)
		{
			List.erase(it);
			return;
		}
	}
	cout << "Element is not found" << endl;
	Addnode(List);
}



Address::Address() {};

Address::Address(string city, string street)
{
	this->Setcity(city); this->Setstreet(street);
};

Address::Address(int k)
{
	string c; int i;
	cout << "Input a city: "; cin >> c; Setcity(c);
	cout << "Input a street: "; cin >> c; Setstreet(c);
}

void Address::Setcity(string c) { _city = c; }

void Address::Setstreet(string s) { _street = s; }

string Address::Getcity() { return _city; }

string Address::Getstreet() { return _street; }


Address::~Address() {}

void Address::ToScreen()
{
	cout << "Address: " << _city << ", " << _street;
}

Address Address::operator =(Address ad)
{
	if (this != &ad)
	{
		this->Setcity(ad.Getcity());
		this->Setstreet(ad.Getstreet());
	}
	return *this;
}








Person::Person() {}

Person::Person(string name, string surname, int age, string gender, Address ad, bool smoke)
{
	_name = name; _surname = surname;
	_age = age; _gender = gender;
	_address = Address(ad); _smoking = smoke;
}

Person::Person(int a)
{
	int b = a;
	cout << "Input name: "; cin >> _name;
	cout << "Input surname: "; cin >> _surname;
	cout << "Input age: "; cin >> _age;
	cout << "Input gender: "; cin >> _gender;
	_address = Address(b);
	cout << "Does person smoke? 1-yes, 0-no  "; cin >> _smoking;
}

Person::~Person() {}

void Person::Setname(string n) { _name = n; }
void Person::Setsurname(string s) { _surname = s; }
void Person::Setage(int a) { _age = a; }
void Person::Setaddress(Address ad) { _address = ad; }
void Person::Setsmoking(bool s) { _smoking = s; }
void Person::Setgender(string g) { _gender = g; }

string Person::Getname() { return _name; }
string Person::Getsurname() { return _surname; }
int Person::Getage() { return _age; }
Address Person::Getaddress() { return _address; }
bool Person::Getsmoking() { return _smoking; }
string Person::Getgender() { return _gender; }


void Person::ToScreen()
{
	cout << "Name: " << _name << endl;
	cout << "Surame: " << _surname << endl;
	cout << "Age: " << _age << endl;
	cout << "Gender: " << _gender << endl;
	_address.ToScreen();
	cout << "\nSmoking: " << _smoking << endl;
}