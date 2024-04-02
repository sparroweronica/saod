#pragma once
#include <cmath> 

using namespace std;

class Complex
{
public: double Re, Im;
	
public:
	Complex(double re = 0, double im = 0) {
		Im = im;
		Re = re;
	}

	Complex operator +(const Complex& c)const { return Complex(Re + c.Re, Im + c.Im); }
	Complex operator -(const Complex& c)const { return Complex(Re - c.Re, Im - c.Im); }
	Complex operator *(const Complex& c)const { return Complex(Re * c.Re - Im * c.Im, Re * c.Im + c.Re * Im); }
	Complex operator /(const Complex& c)const { return Complex((Re * c.Re + Im * c.Im) / (c.Re * c.Re + c.Im * c.Im), ((-1) * Re * c.Im + c.Re * Im) / (c.Re * c.Re + c.Im * c.Im)); }
	
	inline Complex Conjugate() { return Complex(Re, (-1) * Im); }

	inline double Mod() { return sqrt(pow(Re, 2.0) + pow(Im, 2.0)); }

	inline double Arg() {
		if (Mod() == 0) return 0;
		else if (Re > 0) return atan(Im / Re);
		else if (Re < 0 && Im >= 0) return acos(-1) + atan(Im / Re);
		else if (Re < 0 && Im < 0) return acos(-1) - atan(Im / Re);
		else if (Im > 0) return acos(0);
		else if (Im < 0) return (-1) * acos(0);
	}
};
inline ostream& operator << (ostream& o, const Complex& c) { return o << '(' << c.Re << ",  " << c.Im << ')'; }


