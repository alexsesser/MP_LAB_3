#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <clocale> 
#include <stdio.h> 
#include <time.h> 
#include <iterator>
#include <map>
#include <set>
using namespace std;

int hash_metod = 1;

long long simpleHash(string& key)
{
	long long hash = 1;
	for (auto c : key)
	{
		hash *= c;
	}
	return hash;
}


long long complecsHash(string& key)
{
	const int BASE = 26;
	int hash = 0;
	int p = 1;
	for (char ch : key) {
		hash += (ch - 'a' + 1) * p;
		p *= BASE;
	}
	return hash;
}

class Passenger
{
public:
	//сравнение по полям – номер каюты, порт  назначения, ФИО
	string name;
	int cabin;
	int type; //0,1,2,3
	string port;
	long long hash;
	Passenger() {}
	Passenger(string name, int cabin, int type, string port)
	{
		this->name = name;
		this->cabin = cabin;
		this->type = type;
		this->port = port;
		if (hash_metod == 1)
		{
			hash = simpleHash(this->name);
		}
		else
		{
			hash = complecsHash(this->name);
		}

	}
	long long get_hash()
	{
		return this->hash;
	}
	bool operator < (Passenger& b)
	{
		if (this->name == b.name)
		{
			return true;
		}
		else
		{
			int res = this->name.compare(b.name);
			return res < 0;
		}
	}
	bool operator <= (Passenger& b)
	{
		if (this->name == b.name)
		{
			return true;
		}
		else
		{
			int res = this->name.compare(b.name);
			return res <= 0;
		}
	}

	bool operator > (Passenger& b)
	{
		if (this->name == b.name)
		{
			return true;
		}
		else
		{
			int res = this->name.compare(b.name);
			return res > 0;
		}
	}

	bool operator >= (Passenger& b)
	{
		if (this->name == b.name)
		{
			return true;
		}
		else
		{
			int res = this->name.compare(b.name);
			return res >= 0;
		}
	}
};



ostream& operator<<(ostream& out, const Passenger& passagir) {
	return out << passagir.name << ":" << passagir.cabin << "," << passagir.type << "-" << passagir.port;
}



//Passanger

long long hash(string& key)
{
	if (hash_metod == 1)
	{
		return simpleHash(key);
	}
	else
	{
		return complecsHash(key);
	}
}


const int magicNumber = 31;

class HashTable
{
public:
	HashTable() {}
	HashTable(const int a) : algo(a) {}
	void addElement(Passenger& object)
	{
		data.insert(pair<long long, Passenger>(curHash(object), object));
	}
	int countCollisions() const
	{
		auto p0 = data.begin();
		set<long long> myset;
		while (p0 != data.end()) {
			myset.insert(p0->first);
			++p0;
		}
		return data.size() - myset.size();
	}

	void findElement(string& name) const
	{
		//first - lower bound, second - upper bounds
		pair<multimap<long long, Passenger>::const_iterator, multimap<long long, Passenger>::const_iterator> p1;
		p1 = data.equal_range(curHash(name));
		while (p1.first != p1.second) {
			p1.first++;
		}
	}

	long long curHash(const Passenger& object) const
	{
		return object.hash;
	}

	long long curHash(string& name) const
	{
		if (hash_metod == 1)
		{
			return simpleHash(name);
		}
		else
		{
			return complecsHash(name);
		}
	}

private:
	multimap<long long, Passenger> data;
	int algo = 0;
	int collisions = 0;
};



ofstream out_d("D:/учёба/Методы програмирования/Metods_3/graph/ris_grahp.txt");


void handleFile(string fileName, int hashMetod, string key) {
	hash_metod = hashMetod;
	string openPath = "D:/учёба/Методы програмирования/Metods_1/test/" + fileName;
	ifstream file(openPath);
	vector <Passenger> data;
	string line, field;
	while (getline(file, line))
	{
		stringstream ss(line);
		int i = 0;
		string name;
		int cabin;
		int type;
		string port;
		while (getline(ss, field, ','))
		{
			switch (i) {
			case 0:
				name = field;
				break;
			case 1:
				cabin = stoi(field);
				break;
			case 2:
				type = stoi(field);
				break;
			case 3:
				port = field;
				break;
			default:
				break;
			}
			++i;
		}
		Passenger pasn(name, cabin, type, port);
		data.push_back(pasn);
	}
	HashTable hTable(hashMetod);
	for (int i = 0; i < data.size(); i++) {
		hTable.addElement(data[i]);
	}
	//auto begin = std::chrono::steady_clock::now();
	//hTable.findElement(key);
	//auto end = chrono::steady_clock::now();
	//auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
	/*cout << data.size() << "\t" << elapsed_ms.count() << endl;
	out_d << data.size() << "\t" << elapsed_ms.count() << endl;*/
	cout << data.size() << "\t" << hTable.countCollisions() << endl;
	out_d << data.size() << "\t" << hTable.countCollisions() << endl;
}



// сортировки а, в, е Сортировка выбором Сортировка простыми вставками Быстрая сортировка
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Size" << "\t" << "Простая хэш-функция" << "\n";
	out_d << "Size" << "\t" << "Простая хэш-функция" << "\n";
	handleFile("test400.txt", 1, "qahcuckczcvu aitrtkzimtvc cymtrjs");
	handleFile("test800.txt", 1, "bygugwblg krwgopy m");
	handleFile("test4000.txt", 1, "pzsewtkhrwpc aisynksrl s");
	handleFile("test8000.txt", 1, "kvdgtoqbbazt amxlxvofmalh fdfhiakpv");
	handleFile("test40000.txt", 1, "lvlsneciihhga edbs ztyyttzg");
	handleFile("test80000.txt", 1, "iolao ixihcv yhdcre");
	handleFile("test120000.txt", 1, "nbicphpt wjpnwyj mkseqtrnx");
	cout << "Size" << "\t" << "Сложная хэш-функция" << "\n";
	out_d << "Size" << "\t" << "Сложная хэш-функция" << "\n";
	handleFile("test400.txt", 2, "qahcuckczcvu aitrtkzimtvc cymtrjs");
	handleFile("test800.txt", 2, "bygugwblg krwgopy m");
	handleFile("test4000.txt", 2, "pzsewtkhrwpc aisynksrl s");
	handleFile("test8000.txt", 2, "kvdgtoqbbazt amxlxvofmalh fdfhiakpv");
	handleFile("test40000.txt", 2, "lvlsneciihhga edbs ztyyttzg");
	handleFile("test80000.txt", 2, "iolao ixihcv yhdcre");
	handleFile("test120000.txt", 2, "nbicphpt wjpnwyj mkseqtrnx");
	//cout << "Size" << "\t" << "Сортировка + бинарный поиск" << "\n";
	//out_d << "Size" << "\t" << "Сортировка + бинарный поиск" << "\n";
	//handleFile("test400.txt", 3, "qahcuckczcvu aitrtkzimtvc cymtrjs");
	//handleFile("test800.txt", 3, "bygugwblg krwgopy m");
	//handleFile("test4000.txt", 3, "pzsewtkhrwpc aisynksrl s");
	//handleFile("test8000.txt", 3, "kvdgtoqbbazt amxlxvofmalh fdfhiakpv");
	//handleFile("test40000.txt", 3, "lvlsneciihhga edbs ztyyttzg");
	//handleFile("test80000.txt", 3, "iolao ixihcv yhdcre");
	//handleFile("test120000.txt", 3, "ywmbfffplsqq srcfbcxpe fgca");
	//cout << "Size" << "\t" << "Multimap" << "\n";
	//out_d << "Size" << "\t" << "Multimap" << "\n";
	//handleFile("test400.txt", 4, "qahcuckczcvu aitrtkzimtvc cymtrjs");
	//handleFile("test800.txt", 4, "bygugwblg krwgopy m");
	//handleFile("test4000.txt", 4, "pzsewtkhrwpc aisynksrl s");
	//handleFile("test8000.txt", 4, "kvdgtoqbbazt amxlxvofmalh fdfhiakpv");
	//handleFile("test40000.txt", 4, "lvlsneciihhga edbs ztyyttzg");
	//handleFile("test80000.txt", 4, "iolao ixihcv yhdcre");
	//handleFile("test120000.txt", 4, "ywmbfffplsqq srcfbcxpe fgca");
}