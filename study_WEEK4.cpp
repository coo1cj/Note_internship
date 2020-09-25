// Test_shared_ptr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int& foo() {
	int a = 2;
	return a;
}


class Intvec
{
public:
	explicit Intvec(size_t num = 0)
		: m_size(num), m_data(new int[m_size])
	{
		log("constructor");
	}

	~Intvec()
	{
		log("destructor");
		if (m_data) {
			delete[] m_data;
			m_data = 0;
		}
	}

	Intvec(const Intvec& other)
		: m_size(other.m_size), m_data(new int[m_size])
	{
		log("copy constructor");
		for (size_t i = 0; i < m_size; ++i)
			m_data[i] = other.m_data[i];
	}

	Intvec& operator=(const Intvec& other)
	{
		log("copy assignment operator");
		Intvec tmp(other);
		std::swap(m_size, tmp.m_size);
		std::swap(m_data, tmp.m_data);
		return *this;
	}
private:
	void log(const char* msg)
	{
		cout << "[" << this << "] " << msg << "\n";
	}

	size_t m_size;
	int* m_data;
};


class myString {
	size_t length;
	char* data;
public:
	myString(): length(0), data(nullptr) { cout << "[" << this << "]" << "Defaut Constructer is called " << endl; }

	myString(const char* str) {
		cout << "[" << this << "]" << "Constructer is called " << endl;
		/*int i = 0;
		while (!str) {
			data[i] = *str;
			i++;
			str++;
		}
		length = i;*/

		length = strlen(str);
		data = new char[length + 1];
		memcpy(data, str, length);
		data[length] = '\0';
	}

	// Copy
	myString(const myString& str) {
		cout << "[" <<  this << "]" << "Copy constructer is called " << endl;
		
		this->length = str.length;
		this->data = new char[this->length + 1];
		memcpy(this->data, str.data, length);
		data[length] = '\0';
	}

	myString& operator=(const myString& str) {
		cout <<  "[" << this << "]" << "Copy assignment constructer is called " << endl;
		if (this != &str) {
			if (this->data) {
				delete data;
				this->data = nullptr;
			}
			this->length = str.length;
			this->data = new char[str.length + 1];
			memcpy(this->data, str.data, this->length);
			data[length] = '\0';
		}
		return *this;
	}

	// Move
	myString(myString&& str) {
		cout << "[" << this << "]" << "Move constructer is called " << endl;
		this->data = str.data;
		this->length = str.length;
		str.data = nullptr;
	}

	myString& operator=(myString&& str) {
		cout << "[" << this << "]" << "Move assignment is called " << endl;
		if (this != &str) {
			this->data = str.data;
			this->length = str.length;
			str.data = nullptr;
		}
		return *this;
	}

	~myString() {
		cout << "[" << this << "]" << "Destructer is called " << endl;
		if(data)
			delete[] data; 
		data = 0; 
	}

	char& operator[](int pos) const {
		return *(data + pos);
	}

	char* getData() {
		return data;
	}


	friend ostream& operator<<(ostream& out, myString& str) {
		for (int i = 0; i < str.length; i++) {
			cout.put(str[i]);
		}

		return out;
	}


};


const char* ff() {
	return "hello world";
}

class Solution {
public:
	int superEggDrop(int K, int N) {
		return dp(K, N);
	}
private:
	unordered_map<int, int> memo;

	int dp(int K, int N) {
		if (memo.find(N * 100 + K) == memo.end()) {
			int ans;
			if (N == 0) ans = 0;
			else if (K == 1) ans = N;
			else {
				int low = 1, high = N;
				while (low + 1 < high) {
					int mid = (low + high) / 2;
					if (dp(K, N - mid) > dp(K - 1, mid - 1))
						low = mid;
					else if (dp(K, N - mid) < dp(K - 1, mid - 1))
						high = mid;
					else
						low = high = mid;
				}
				ans = 1 + min(max(dp(K, N - low), dp(K - 1, low - 1)), max(dp(K, N - high), dp(K - 1, high - 1)));
			}
			memo[N * 100 + K] = ans;
		}

		return memo[N * 100 + K];
	}

};



class Song {
public:
	string artist;
	string title;

	Song(const string& w, const string& s): artist(w), title(s){}
};




void SongVector()
{
	vector<unique_ptr<Song>> songs;

	// Create a few new unique_ptr<Song> instances
	// and add them to vector using implicit move semantics.
	songs.push_back(make_unique<Song>("B'z", "Juice"));
	songs.push_back(make_unique<Song>("Namie Amuro", "Funky Town"));
	songs.push_back(make_unique<Song>("Kome Kome Club", "Kimi ga Iru Dake de"));
	songs.push_back(make_unique<Song>("Ayumi Hamasaki", "Poker Face"));

	// Pass by const reference when possible to avoid copying.
	for (const auto& song : songs)
	{
		cout << "Artist: " << song->artist << "   Title: " << song->title << endl;
	}
}





int main()
{

	//SongVector();



	vector<shared_ptr<Song>> v;

	v.push_back(make_shared<Song>("Bob Dylan", "The Times They Are A Changing"));
	v.push_back(make_shared<Song>("Aretha Franklin", "Bridge Over Troubled Water"));
	v.push_back(make_shared<Song>("Thala", "Entre El Mar y Una Estrella"));

	vector<shared_ptr<Song>> v2;
	remove_copy_if(v.begin(), v.end(), back_inserter(v2), [](shared_ptr<Song> s)
	{
		return s->artist.compare("Bob Dylan") == 0;
	});

	for (const auto& s : v2)
	{
		cout << s->artist << ":" << s->title << endl;
	}
	/*Solution s;
	cout << s.superEggDrop(2, 100) << endl;*/

	/*Intvec v1(20);
	Intvec v2;

	cout << "assigning lvalue...\n";
	v2 = v1;
	cout << "ended assigning lvalue...\n";


	std::string x1 = "hello, world!";
	std::string x2 = std::move(x1);
	cout << "x1 = " << x1 << endl;
	cout << "x2 = " << x2 << endl;*/

	//myString s("qsdqsd"); // constructer is called
	//myString s1(move(s)); // Move constructer is called

	//myString s2;  // defaut constructer is called
	//s2 = move(s1); // Move assignment constructer is called
	//myString s3;  //defaut constructer is called 
	//s3 = s2;  // copy assignment constructer is called 
	//myString s4(s3); // copy constructer is called
	//s4[0] = 'a';
	//
	//cout << (s.getData() == nullptr) << endl;
	//
	//cout << s2 << endl;
	//cout << s3 << endl;
	//cout << s4 << endl;

	//shared_ptr<myString> p(new myString("qbcd"));
	//shared_ptr<myString> p1 = move(p);
	////cout << (p == nullptr) << endl;
	//cout << p1->getData() << endl;
	//cout << p1.use_count() << endl;

	//unique_ptr<myString> up(new myString("qqqqq"));
	//unique_ptr<myString> up1 = move(up);

	//auto up3 = make_unique<myString>("123456798");
	//cout << up3->getData()[3] << endl;
	////cout << up->getData() << endl;
	//cout << up1->getData() << endl;
	//up1.reset();
	//cout << (up1 == nullptr) << endl;


}

