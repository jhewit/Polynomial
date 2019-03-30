//-----------------------------poly.cpp----------------------------------
//Johnathan Hewit - CSS343
//Created:  01-09-2019
//Modified: 01-17-2019
//-----------------------------------------------------------------------
//Purpose: Create, store and modify a polynomial using basic math
//         operations.
//-----------------------------------------------------------------------
//Notes: Implementation file for the polynomial program.
//-----------------------------------------------------------------------
#include <iostream>
#include "poly.h"
using namespace std;

//------------------------------Poly-------------------------------------
//Description: Empty constructor
//-----------------------------------------------------------------------
Poly::Poly()
{
  this->size = 0;
} //end of Poly()

//---------------------------Poly(coeff)---------------------------------
//Description: Single Coefficient Partial Constructor
//-----------------------------------------------------------------------
Poly::Poly(int coeff)
{
  polynomial = new int[1];
  polynomial[0] = coeff;
  this->size = 1;
} //end of Poly(coeff)

//------------------------Poly(coeff, expon)-----------------------------
//Description: Coefficient & Exponent Full Constructor
//-----------------------------------------------------------------------
Poly::Poly(int coeff, int expon)
{
  this->size = expon + 1;
  polynomial = new int[this->size];
  initializeArray(polynomial, this->size);
  polynomial[expon] = coeff;
} //end of Poly(coeff, expon)

//-----------------------------Poly(poly)--------------------------------
//Description: Copy Constructor - Makes copy of another polynomial object
//-----------------------------------------------------------------------
Poly::Poly(const Poly &poly)
{
  if (poly.size > 0)
  {
    this->size = poly.size;
    polynomial = new int[this->size];
    copy(poly.polynomial, this->size);
  }
  else
  {
    this->size = 0;
  }
} //end of Poly(poly)

//--------------------------------~Poly()--------------------------------
//Description: Deconstructor - frees up allocated memory for array
//-----------------------------------------------------------------------
Poly::~Poly()
{
  delete[] polynomial;
} //end of ~Poly()

//-------------------------------getCoeff--------------------------------
//Description: Returns the coefficient of a given exponent, if in bounds
//-----------------------------------------------------------------------
int Poly::getCoeff(int expon) const
{
  if (expon < 0 || expon > this->size - 1 || this->size == 0) //If the exponent
  {                                                           // is out of
    return 0;                                                 //bounds, return 0
  }
  return polynomial[expon];
} //end of getCoeff

//------------------------------setCoeff---------------------------------
//Description: Set a coefficient to the given exponent in an array,
//             resizing if necessary.
//-----------------------------------------------------------------------
bool Poly::setCoeff(int coeff, int expon)
{
  if (expon < 0) //If the exponent is negative, it's out of bounds
  {
    return false;
  }
  if (this->size == 0) //If this is empty, create the array and set the polynomial
  {              //to the new term
    this->size = expon + 1;
    polynomial = new int[this->size];
    initializeArray(polynomial, this->size);
    polynomial[expon] = coeff;
    return true;
  }
  if (expon > size - 1) //If the term is larger than this polynomial,
  {                     //resize and set the new term
    int *temp = polynomial;
    polynomial = new int[expon + 1];
    initializeArray(polynomial, expon + 1);
    copy(temp, this->size);
    delete[] temp;
    this->size = expon + 1;
    polynomial[expon] = coeff;
    return true;
  }
  polynomial[expon] = coeff; //If no other conditions, then all that's left is
  return true;               //to replace existing term
} //end of setCoeff

//------------------------------operator+--------------------------------
//Description: Overload of the + operator; adds 2 polynomials and returns
//             a new poly object
//-----------------------------------------------------------------------
Poly Poly::operator+(const Poly &poly) const
{
  Poly temp(*this);
  temp += poly;
  return temp;
} //end of operator+

//-----------------------------operator+=--------------------------------
//Description: Overload of the += operator; adds 2 polynomials and returns
//             same poly object.
//-----------------------------------------------------------------------
Poly& Poly::operator+=(const Poly &poly)
{
  if (poly.size == 0) //If incoming polynomial is empty, return as is
  {
    return *this;
  }
  if (this->size == 0) //If this is empty, return a copy of the incoming polynomial
  {
    this->size = poly.size;
    polynomial = new int[this->size];
    copy(poly.polynomial, this->size);
    return *this;
  }
  int larger;
  if (this->size >= poly.size) //Determine which polynomial is larger for purposes of
  {                      //iterating in loop
    larger = this->size;
  }
  else
  {
    larger = poly.size;
  }
  for (int i = larger - 1; i >= 0; i--)
  {
    setCoeff(getCoeff(i) + poly.getCoeff(i), i); //Add the two terms together
  }                                              //and set them
  return *this;
} //end of operator+=

//-----------------------------operator(-)-------------------------------
//Description: Overload of the - operator; subtracts 2 polynomials and
//             returns a new poly object.
//-----------------------------------------------------------------------
Poly Poly::operator-(const Poly &poly) const
{
  Poly temp(*this);
  temp -= poly;
  return temp;
} //end of operator-

//-----------------------------operator-=--------------------------------
//Description: Overload of the -= operator; subtracts 2 polynomials and
//             returns the same poly object.
//-----------------------------------------------------------------------
Poly& Poly::operator-=(const Poly &poly)
{
  if (poly.size == 0) //If incoming polynomial is empty, return as is
  {
    return *this;
  }
  if (this->size == 0) //If this is empty, create the array and return a copy of
  {                    //the incoming polynomial
    this->size = poly.size;
    polynomial = new int[this->size];
    copy(poly.polynomial, this->size);
    return *this;
  }
  int larger;
  if (this->size >= poly.size) //Determine which polynomial is larger for
  {                            //purposes of iterating in loop
    larger = this->size;
  }
  else
  {
    larger = poly.size;
  }
  for (int i = larger - 1; i >= 0; i--)
  {
    setCoeff(getCoeff(i) - poly.getCoeff(i), i); //Subtract the two terms
  }                                              //and set them
  return *this;
} //end of operator-=

//-----------------------------operator*---------------------------------
//Description: Overload of the * operator; multiplies 2 polynomials and
//             returns a new poly object.
//-----------------------------------------------------------------------
Poly Poly::operator*(const Poly &poly) const
{
  Poly temp(*this);
  temp *= poly;
  return temp;
} //end of operator*

//-----------------------------operator*=--------------------------------
//Description: Overload of the *= operator; multiplies 2 polynomials and
//             returns the same poly object.
//-----------------------------------------------------------------------
Poly& Poly::operator*=(const Poly &poly)
{
  if (poly.size == 0) //If incoming polynomial is 0, this will also be 0
  {                   //because x * 0 = 0
    delete polynomial;
    this->size = 0;
    return *this;
  }
  if (this->size == 0) //If this is 0, it remains 0 because 0 * x = 0
  {
    return *this;
  }
  int maxSize = this->size + poly.size - 1; //Create a temp array to store summed
  int *tempArr = new int[maxSize];          //values of two polynomials - their
  initializeArray(tempArr, maxSize);        //maximum possible size is the sum of
  for (int j = 0; j < this->size; j++)      //both sizes - 1
  {
    for (int k = 0; k < poly.size; k++) //Nested loop allows FOILing of both
    {                                   //polynomials
      if (getCoeff(j) != 0 && poly.getCoeff(k) != 0) //Only consider terms
      {                                              //that don't multiply by 0
        tempArr[j + k] += polynomial[j] * poly.polynomial[k];
      }
    }
  }
  int *temp = polynomial;   //Assign a pointer to the old polynomial array
  this->size = maxSize + 1; //and reassign the size and polynomial pointer
  polynomial = tempArr;     //to the new array, then delete the old array
  delete[] temp;
  return *this;
} //end of operator*=

//------------------------------operator=--------------------------------
//Description: Overload of the = operator; assigns current polynomial to
//             the value(s) of the one being passed in.
//-----------------------------------------------------------------------
Poly& Poly::operator=(const Poly &poly)
{
  if (this->size == 0) //Assign the polynomial the correct size, and copy the incoming
  {
    this->size = poly.size;
    polynomial = new int[this->size];
    copy(poly.polynomial, this->size);
    return *this;
  }
  if (*this == poly) //If the incoming polynomial is this polynomial, do nothing
  {
    return *this;
  }
  delete[] polynomial;     //Otherwise, delete this polynomial and copy the
  this->size = poly.size;  //incoming polynomial
  polynomial = new int[this->size];
  initializeArray(polynomial, this->size);
  copy(poly.polynomial, this->size);
  return *this;
}

//-----------------------------operator==--------------------------------
//Description: Overload of the == operator; checks for equality of 2
//             poly objects.
//-----------------------------------------------------------------------
bool Poly::operator==(const Poly &poly) const
{
  if (this->size != poly.size) //If they aren't the same size, they're unequal
  {
    return false;
  }
  for (int i = 0; i < this->size; i++) //Otherwise, check if each element is identical
  {
    if (polynomial[i] != poly.polynomial[i])
    {
      return false; //If not the same, return false
    }
  }
  return true; //Otherwise, they're the same
}
//-----------------------------operator!=--------------------------------
//Description: Overload of the != operator; checks for inequality of 2
//             poly objects.
//-----------------------------------------------------------------------
bool Poly::operator!=(const Poly &poly) const //Inverse logic of ==
{
  if (this->size != poly.size)
  {
    return true;
  }
  for (int i = 0; i < this->size; i++)
  {
    if (polynomial[i] != poly.polynomial[i])
    {
      return true;
    }
  }
  return false;
} //end of operator!=

//------------------------------operator<<-------------------------------
//Description: Overload of the << operator; formats an output to the
//             console for a poly object.
//-----------------------------------------------------------------------
ostream& operator<<(ostream &print, const Poly &poly)
{
  if (poly.size == 0) //If it's empty, simply print a 0
  {
    print << "0";
    return print;
  }
  for (int i = poly.size - 1; i > 1; i--) //Otherwise, start from the back or
  {                                       //highest order term in the polynomial
    if (poly.polynomial[i] != 0)          //until there are no terms with
    {                                     //exponents
      print << poly.sign(poly.polynomial[i]) << poly.polynomial[i] << "x^" << i;
    }
  }
  if (poly.polynomial[1] != 0) //Check if there is a term in the x position
  {
    print << poly.sign(poly.polynomial[1]) << poly.polynomial[1] << "x";
  }
  if (poly.polynomial[0] != 0) //Check if there is a constant
  {
    print << poly.sign(poly.polynomial[0]) << poly.polynomial[0];
  }
  return print;
} //end of operator<<

//--------------------------------operator>>-----------------------------
//Description: Overload of the >> operator; accepts a coefficient and an
//             exponent from console input, and sets it in the poly object.
//-----------------------------------------------------------------------
istream& operator>>(istream &input, Poly &poly)
{
  int coeff, expon;
  while (!(coeff == -1 && expon == -1)) //Continue until -1 is entered twice
  {
    input >> coeff >> expon;
    if (coeff == -1 && expon == -1) //Check again after accepting input and
    {                               //break if -1 is entered twice
      break;
    }
    poly.setCoeff(coeff, expon); //If it isn't, set the term in the polynomial
  }
  return input;
} //end of operator>>

//-----------------------------------copy--------------------------------
//Description: Deep copies all terms from the polynomial being passed #include
//             to this polynomial.
//-----------------------------------------------------------------------
bool Poly::copy(const int *poly, int size)
{
  if (size == 0) //Unable to copy if the poly is empty
  {
    return false;
  }
  int coeff;
  for (int i = 0; i < size; i++) //Otherwise, deep copy all data to
  {                              //this polynomial
    coeff = poly[i];
    polynomial[i] = coeff;
  }
  return true;
} //end of copy

//----------------------------------sign---------------------------------
//Description: Determines whether or not the coefficient will have a +.
//-----------------------------------------------------------------------
string Poly::sign(int coeff) const
{
  if (coeff >= 0)
  {
    return " +";
  }
  return " ";
} //end of sign

//----------------------------initializeArray----------------------------
//Description: Initializes all elements in the array to 0 to avoid
//             garbage or unexpected data.
//-----------------------------------------------------------------------
void Poly::initializeArray(int *poly, int size)
{
  for (int i = 0; i < size; i++)
  {
    poly[i] = 0;
  }
} //end of initializeArray
