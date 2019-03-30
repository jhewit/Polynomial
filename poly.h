//-----------------------------poly.h------------------------------------
//Johnathan Hewit - CSS343
//Created:  01-09-2019
//Modified: 01-17-2019
//-----------------------------------------------------------------------
//Purpose: Create, store and modify a polynomial using basic math
//         operations.
//-----------------------------------------------------------------------
//Notes: Header file containing definitions for the polynomial.
//-----------------------------------------------------------------------
#pragma once
#include <iostream>
using namespace std;

class Poly
{
public:
  //Constructors
  Poly();
  Poly(int coeff);
  Poly(int coeff, int expon);
  Poly(const Poly &poly);
  ~Poly();

  //Getters
  int getCoeff(int expon) const;
  //Setters
  bool setCoeff(int coeff, int expon);

  //Operator Overloads
  //Addition
  Poly operator+(const Poly &poly) const;
  Poly& operator+=(const Poly &poly);
  //Subtraction
  Poly operator-(const Poly &poly) const;
  Poly& operator-=(const Poly &poly);
  //Multiplication
  Poly operator*(const Poly &poly) const;
  Poly& operator*=(const Poly &poly);
  //Assignment
  Poly& operator=(const Poly &poly);
  //Equality
  bool operator==(const Poly &poly) const;
  bool operator!=(const Poly &poly) const;
  //Output & Input
  friend ostream& operator<<(ostream &print, const Poly &poly);
  friend istream& operator>>(istream &input, Poly &poly);

private:
  int size;
  int *polynomial;
  bool copy(const int *poly, int size);
  string sign(int coeff) const;
  void initializeArray(int *poly, int size);
};
