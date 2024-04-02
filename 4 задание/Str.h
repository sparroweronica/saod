#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>

using namespace std;
class Str
{
	char* m_pszText;
public:
	Str(const char *p)
	{
		if(p) {
			m_pszText = new char[strlen(p) + 1];
			strcpy(m_pszText, p);
		}
		else
			m_pszText = new char[1]{0};
	}
	Str(const Str &s){
		m_pszText = new char[strlen(s.m_pszText) + 1];
		strcpy(m_pszText, s.m_pszText);
	}

	const Str& operator = (const Str& s) //Константная ссылка на объект
	{
		if (&s == this) return *this;
		delete[] m_pszText;	 //Освобождаем текущие данные	//Дальше просто копирование
		m_pszText = new char[strlen(s.m_pszText) + 1];
		strcpy_s(m_pszText,
			strlen(s.m_pszText) + 1,
			s.m_pszText);
		return *this;
	}

	Str& operator +=(const char* sz) 
	{
		const int lens = strlen(m_pszText) + strlen(sz);
		char* mass = new char[lens + 1];
		for (int i = 0; i < strlen(m_pszText); i++) 
		{
			mass[i] = m_pszText[i];
		}
		for (int i = strlen(m_pszText); i < lens; i++)
		{
			mass[i] = sz[i-strlen(m_pszText)];
		}
		mass[lens] = 0;
		delete[] m_pszText;
		m_pszText = mass;
		return*this;
	}

	Str operator +(const char* sz) const
	{
		int len1 = strlen(m_pszText);
		int len2 = strlen(sz);
		cout << len1 << len2 << endl;
		int lens = len1 + len2;
		char* mass = new char[lens + 1];
		for (int i = 0; i < len1; i++)
		{
			mass[i] = m_pszText[i];
		}
		for (int i = len1; i < lens; i++)
		{
			mass[i] = sz[i - len1];
		}
		mass[lens] = 0;

		Str answ(mass);
		delete[] mass;
		return answ;
	}


	~Str() { delete[]m_pszText; }

	operator const char* ()const { return m_pszText; }
};


