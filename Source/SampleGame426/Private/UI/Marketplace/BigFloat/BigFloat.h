#pragma once
#include <iostream>
#include <vector>

class BigFloat
{
private:
	std::vector<int> digits;
	bool negativ;
	bool is_float;
	int float_point;
	int float_endpoint;
	int precision;

public:
	//This is the default constructor, which initializes a new BigFloat object to 0.
	BigFloat();

	//This constructor initializes a new BigFloat object from a long long integer.
	BigFloat(long long);

	//This constructor initializes a new BigFloat object from a string.
	BigFloat(const std::string&);

	//This is the copy constructor, which initializes a new BigFloat object from an existing BigFloat object.
	BigFloat(const BigFloat&);

	//This is a friend function that returns true if the given BigFloat object is equal to 0.
	friend bool E0(const BigFloat&);
	friend BigFloat Balance_Point(std::vector<int>&, std::vector<int>&, const BigFloat&, const BigFloat&);

	//This is the assignment operator, which assigns one BigFloat object to another.
	BigFloat& operator = (const BigFloat&);

	//This is the input stream operator, which reads a BigFloat object from an input stream.
	friend std::istream& operator >> (std::istream&, BigFloat&);

	//This is the output stream operator, which writes a BigFloat object to an output stream.
	friend std::ostream& operator << (std::ostream&, const BigFloat&);

	//This is the addition operator, which adds two BigFloat objects together.
	friend BigFloat operator + (const BigFloat&, const BigFloat&);

	//This is the compound assignment operator for addition, which adds a BigFloat object to another BigFloat object and stores the result in the first object.
	friend BigFloat operator += (BigFloat&, const BigFloat&);

	//This is the subtraction operator, which subtracts one BigFloat object from another.
	friend BigFloat operator - (const BigFloat&, const BigFloat&);

	//This is the compound assignment operator for subtraction, which subtracts a BigFloat object from another BigFloat object and stores the result in the first object.
	friend BigFloat operator -= (BigFloat&, const BigFloat&);

	//This is the multiplication operator, which multiplies two BigFloat objects together.
	friend BigFloat operator * (const BigFloat&, const BigFloat&);

	// This is the compound assignment operator for multiplication, which multiplies a BigFloat object by another BigFloat object and stores the result in the first object.
	friend BigFloat operator *= (BigFloat&, const BigFloat&);

	//This is the division operator, which divides one BigFloat object by another.
	friend BigFloat operator / (const BigFloat&, const BigFloat&);

	// This is the compound assignment operator for division, which divides a BigFloat object by another BigFloat object and stores the result in the first object.
	friend BigFloat operator /= (BigFloat&, const BigFloat&);

	//This is the modulus operator, which returns the remainder
	friend BigFloat operator % (const BigFloat&, const BigFloat&);

	// This is the compound modulus operator for division, which divides a BigFloat object by another BigFloat object and stores the remainder in the first object.
	friend BigFloat operator %= (BigFloat&, const BigFloat&);

	//function overloads the prefix ++ operator for the BigFloat class, and returns a reference to the modified object. 
	BigFloat& operator ++ ();

	//function overloads the postfix ++ operator for the BigFloat class, and returns a copy of the object before it was incremented. 
	BigFloat operator ++ (int fictiv);

	//functions work similarly, but for the decrement operator --.
	BigFloat& operator -- ();
	BigFloat operator -- (int fictiv);

	friend bool operator == (const BigFloat&, const BigFloat&);
	friend bool operator != (const BigFloat&, const BigFloat&);
	friend bool operator < (const BigFloat&, const BigFloat&);
	friend bool operator <= (const BigFloat&, const BigFloat&);
	friend bool operator > (const BigFloat&, const BigFloat&);
	friend bool operator >= (const BigFloat&, const BigFloat&);

	int operator [] (const int) const;
	friend void set_precision(BigFloat&, BigFloat&,const int&);
};

