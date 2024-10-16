#include "BigFloat.h"
#include <vector>
#include <string>
#include<iostream>
using namespace std;

BigFloat::BigFloat()
{
	//Default constructor
	digits = std::vector<int>();
	negativ = false;
	is_float = false;
	float_point = {};
	float_endpoint = {};
	precision = {};
}

// Constructor for BigFloat class that takes a long long integer as input
BigFloat::BigFloat(long long n)
{
	// Initialize instance variables
	is_float = false;
	float_point = {};
	float_endpoint = {};
	precision = {};
	long long m;
	string  str;
	negativ = false;
	
	// If the input integer is negative
	if (n < 0)
	{
		// Set negativ flag to true
		negativ = true;
		
		// Convert integer to string and remove the negative sign
		str = to_string(n);
		str.erase(str.begin());
		
		// Convert string back to integer
		m = stoi(str);
	}
	
	// If the input integer is zero
	if (n == 0)
	{
		// Add 0 to the digits vector and return
		digits.push_back(0);
		return;
	}
	
	// If the input integer is positive
	if (n > 0)
	{
		// Divide integer by 10 until it becomes 0
		while (n > 0)
		{
			// Add the remainder of the division by 10 to the digits vector
			digits.push_back(n % 10);
			
			// Divide the integer by 10
			n /= 10;
		}
	}
}


// This constructor takes a string as input and creates a BigFloat object
// to represent its value
BigFloat::BigFloat(const std::string& str)
{
	precision = {};
	float_point = {};
	is_float = false;
	int i;
	string s_str = str;
	if (s_str.find('.')==string::npos)
	{
		s_str.push_back('.');
		s_str.push_back('0');
	}
	if (s_str.front() == '-') // check if the number is negative
	{
		int m;
		negativ = true;
		s_str.erase(s_str.begin());
		for (i = 0; i < s_str.size(); i++) // find the position of the decimal point, if any
		{
			if (s_str[i] == '.')
			{
				is_float = true;
				float_point = i;
				break;
			}
		}
		if (is_float)
		{
			s_str.erase(s_str.begin() + i); // remove the decimal point from the string
		}
		m = stoi(s_str); // convert the remaining string to an integer
		while (m > 0) // extract the digits of the integer and store them in digits vector
		{
			digits.push_back(m % 10);
			m /= 10;
		}
	}
	else // case when the number is positive or zero
	{
		for (i = 0; i < s_str.size(); i++) // find the position of the decimal point, if any
		{
			if (s_str[i] == '.')
			{
				is_float = true;
				float_point = i;
				break;
			}
		}
		if (is_float)
		{
			s_str.erase(s_str.begin() + i); // remove the decimal point from the string
		}
		for (i = s_str.size() - 1; i >= 0; i--) // extract the digits of the integer and store them in digits vector
		{
			if (isdigit(s_str[i]))
			{
				digits.push_back(s_str[i] - '0');
			}
			else
			{
				throw("The string of digits contains unaccepted characters"); // throw an exception if the string contains unaccepted characters
			}
		}
		negativ = false;
	}
	if (is_float)
	{
		float_endpoint = s_str.size() - float_point; // calculate the number of digits after the decimal point
	}
	else
	{
		float_point = s_str.size();
		float_endpoint = 0;
	}
}

BigFloat::BigFloat(const BigFloat& ob)
{
	//copy constructor
	digits = ob.digits;
	negativ = ob.negativ;
	is_float = ob.is_float;
	float_point = ob.float_point;
	precision = ob.precision;

}


bool E0(const BigFloat& ob)
{
	//checking if a given object has only one digit and that digit is 0.
	return ob.digits.size() == 1 && ob.digits[0] == 0;
}

// This function takes two vectors of integers and two BigFloat objects as input, and returns a BigFloat object.
BigFloat Balance_Point(vector<int>& V1, vector<int>& V2, const BigFloat& ob1, const BigFloat& ob2)
{
	// Initialize a BigFloat object to hold the result.
	BigFloat result;

	// Check if either of the input BigFloat objects has a decimal point, and only proceed if at least one of them does.
	if (ob1.is_float || ob2.is_float)
	{
		// Add trailing zeros to the end of the first input vector until it aligns with the decimal point of the second input.
		int i = 0;
		while (i < ob2.float_point - ob1.float_point)
		{
			V1.push_back(0);
			i++;
		}

		// Add leading zeros to the beginning of the first input vector until it aligns with the end of the decimal portion of the second input.
		i = 0;
		while (i < ob2.float_endpoint - ob1.float_endpoint)
		{
			V1.insert(V1.begin(), 0);
			i++;
		}

		// Add trailing zeros to the end of the second input vector until it aligns with the decimal point of the first input.
		i = 0;
		while (i < ob1.float_point - ob2.float_point)
		{
			V2.push_back(0);
			i++;
		}

		// Add leading zeros to the beginning of the second input vector until it aligns with the end of the decimal portion of the first input.
		i = 0;
		while (i < ob1.float_endpoint - ob2.float_endpoint)
		{
			V2.insert(V2.begin(), 0);
			i++;
		}

		// Set the "is_float" flag of the result object to true to indicate that it has a decimal portion.
		result.is_float = true;

		// Set the decimal point of the result object to the maximum of the decimal points of the two input objects.
		ob1.float_point > ob2.float_point ?
			result.float_point = ob1.float_point :
			result.float_point = ob2.float_point;
	}

	// Return the result object.
	return result;
}



// Assignment operator for BigFloat class
BigFloat& BigFloat::operator=(const BigFloat& ob)
{
	// Check for self-assignment
	if (this != &ob)
	{
		int sz = 1;

		// Resize and copy the integer part of the number
		for (int i = 0; i < ob.digits.size(); i++)
		{
			digits.resize(sz++);
			digits[i] = ob.digits[i];
		}
	}

	// Copy the rest of the number's properties
	digits = ob.digits;
	negativ = ob.negativ;
	is_float = ob.is_float;
	float_point = ob.float_point;
	precision = ob.precision;

	// Return the modified object
	return *this;
}


std::istream& operator>>(std::istream& in, BigFloat& ob)
{
	// Declare a string variable to store the input
	std::string str;
	// Read the input from the input stream
	in >> str;
	// Clear the digits of the BigFloat object
	ob.digits.clear();
	// Loop through the input string from right to left
	for (int i = str.size() - 1; i >= 0; i--)
	{
		// If the current character is a digit, convert it to an integer and store it as a digit of the BigFloat object
		if (isdigit(str[i]))
		{
			ob.digits.push_back(str[i] - '0');
		}
	}
	// Return the input stream
	return in;
}


ostream& operator<<(ostream& out, const BigFloat& ob)
{
	// If the BigFloat object is negative, output a negative sign
	if (ob.negativ)
		out << '-';

	// Loop through the digits of the BigFloat object from right to left
	for (int i = ob.digits.size() - 1; i >= 0; i--)
	{
		// Output the current digit
		out << ob.digits[i];

		// If the BigFloat object represents a floating-point number and we have output the appropriate number of digits, output a decimal point
		if (ob.is_float)
		{
			if (ob.float_point == ob.digits.size() - i)
				out << '.';
		}
	}

	// Return the output stream
	return out;
}

BigFloat operator+(const BigFloat& ob1, const BigFloat& ob2)
{
	// Extract the digits from the input BigFloats and create an empty vector for the result.
	vector<int>V1 = ob1.digits;
	vector<int>V2 = ob2.digits;
	vector<int>aux;
	BigFloat result = Balance_Point(V1,V2,ob1,ob2);
	
	int transport = 0;

	// If both input BigFloats are positive, add them normally.
	if (ob1.negativ == false && ob2.negativ == false)
		for (int i = 0; i < V1.size() || i < V2.size() || transport > 0; i++)
		{
			if (i < V1.size())
				transport += V1[i];
			if (i < V2.size())
				transport += V2[i];
			result.digits.push_back(transport % 10);
			transport /= 10;
		}
	// If both input BigFloats are negative, add them normally and set the result to negative.
	if (ob1.negativ == true && ob2.negativ == true)
		for (int i = 0; i < V1.size() || i < V2.size() || transport > 0; i++)
		{
			if (i < V1.size())
				transport += V1[i];
			if (i < V2.size())
				transport += V2[i];
			result.digits.push_back(transport % 10);
			transport /= 10;
			result.negativ = true;
		}
	// If one input BigFloat is positive and the other is negative, subtract the smaller number from the larger number.
	if (ob1.negativ == false && ob2.negativ == true)
	{
		int borrow = 0;
		for (size_t i = 0; i < V1.size(); i++)
		{
			int diff = V1[i] - borrow;
			if (i < V2.size())
			{
				diff -= V2[i];
			}
			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else 
			{
				borrow = 0;
			}
			result.digits.push_back(diff);
		}
		// remove leading zeros
		while (result.digits.size() > 1 && result.digits.back() == 0)
		{
			result.digits.pop_back();
		}
		// If ob1 is greater than ob2, the result is positive; otherwise, it is negative.
		if (ob1 > ob2)
			result.negativ = false;

		// If ob2 is greater than ob1, swap the two vectors and add them normally. The result is negative.
		if (ob2 > ob1)
		{
			aux = V1;
			V1 = V2;
			V2 = aux;
			for (int i = 0; i < V1.size() || i < V2.size() || transport > 0; i++)
			{
				if (i < V1.size())
					transport += V1[i];
				if (i < V2.size())
					transport += V2[i];
				result.digits.push_back(transport % 10);
				transport /= 10;
			}
			result.negativ = true;
		}
	}
	// Check if ob1 is negative and ob2 is positive
	if (ob1.negativ == true && ob2.negativ == false)
	{
		int borrow = 0; // Initialize the borrow variable to 0
		for (size_t i = 0; i < V1.size(); i++) // Loop through the digits of V1
		{
			int diff = V1[i] - borrow; // Subtract the borrow from the current digit of V1
			
			// If V2 has more digits, subtract the i-th digit of V2 from diff
			if (i < V2.size()) 
			{
				diff -= V2[i];
			}
			// If diff is negative, add 10 to it and set borrow to 1
			if (diff < 0) 
			{
				diff += 10;
				borrow = 1;
			}
			// Otherwise, set borrow to 0
			else 
			{
				borrow = 0;
			}
			// Add the difference to the result vector
			result.digits.push_back(diff);
		}
		// remove leading zeros
		while (result.digits.size() > 1 && result.digits.back() == 0)
		{
			result.digits.pop_back();
		}
		// Set the sign of the result based on the sign of the larger number
		if (ob1 > ob2)
			result.negativ = true;
		if (ob2 > ob1)
		{
			// Swap V1 and V2, so that V1 is the larger number
			aux = V1;
			V1 = V2;
			V2 = aux;
			for (int i = 0; i < V1.size() || i < V2.size() || transport > 0; i++)
			{
				// Add the i-th digits of V1 and V2, as well as the transport, and store the result in transport
				if (i < V1.size())
					transport += V1[i];
				if (i < V2.size())
					transport += V2[i];
				// Add the last digit of transport to the result vector
				result.digits.push_back(transport % 10);
				// Remove the last digit of transport
				transport /= 10;
			}
			// The result is positive in this case
			result.negativ = false;
		}
	}
	return result;
}
BigFloat operator+=(BigFloat& ob1, const BigFloat& ob2)
{
	// This function overloads the += operator for BigFloat objects.
	// It adds ob2 to ob1 using the + operator, and assigns the result back to ob1.
	ob1 = ob1 + ob2;
	return ob1;
}

BigFloat operator-(const BigFloat& ob1, const BigFloat& ob2)
{
	// Store the digit vectors of both operands in V1 and V2.
	vector<int>V1 = ob1.digits;
	vector<int>V2 = ob2.digits;

	// Define some variables for later use.
	vector<int>aux;
	BigFloat a, b;
	BigFloat result = Balance_Point(V1, V2, ob1, ob2);

	// If both operands are positive, do subtraction as usual.
	if (ob1.negativ == false && ob2.negativ == false)
	{
		if (ob1 < ob2)
		{
			result.negativ = true;
		}
		else
			result.negativ = false;

		if (result.negativ)
		{
			aux = V1;
			V1 = V2;
			V2 = aux;
		}

		// Iterate over the digit vectors, subtracting each digit from the corresponding digit in the other vector.
		// If the result is negative, borrow from the next digit and add 10.
		int borrow = 0;
		for (size_t i = 0; i < V1.size(); i++) 
		{
			int diff = V1[i] - borrow;
			if (i < V2.size())
			{
				diff -= V2[i];
			}
			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else
			{
				borrow = 0;
			}
			result.digits.push_back(diff);
		}
		// remove leading zeros
		while (result.digits.size() > 1 && result.digits.back() == 0)
		{
			result.digits.pop_back();
		}
	}

	// If the first operand is negative and the second is positive, add the absolute values and set the result to negative.
	else if (ob1.negativ == true && ob2.negativ == false)
	{
		a = ob1;
		b = ob2;
		a.negativ = false;
		b.negativ = false;
		result = a + b;
		result.negativ = true;
	}

	// If the first operand is positive and the second is negative, add the absolute values and set the result to positive.
	else if (ob1.negativ == false && ob2.negativ == true)
	{
		a = ob1;
		b = ob2;
		a.negativ = false;
		b.negativ = false;
		result = a + b;
		result.negativ = false;

	}

	// If both operands are negative, subtract the absolute values and set the result to negative or positive based on which operand is larger.
	else if (ob1.negativ == true && ob2.negativ == true)
	{
		if (ob2 < ob1)
		{
			a = ob1;
			b = ob2;
			a.negativ = false;
			b.negativ = false;
			result = a - b;
			result.negativ = true;
		}
		if (ob1 <= ob2)
		{
			a = ob1;
			b = ob2;
			a.negativ = false;
			b.negativ = false;
			result = a - b;
			result.negativ = false;
		}
	}
	
	return result;
}

BigFloat operator-=(BigFloat& ob1, const BigFloat& ob2)
{
	// This function overloads the -= operator for BigFloat objects.
	// It substract ob2 to ob1 using the - operator, and assigns the result back to ob1.
	ob1 = ob1 - ob2;
	return ob1;
}

BigFloat operator*(const BigFloat& ob1, const BigFloat& ob2)
{
	// If either operand is zero, return the other operand
	if (E0(ob1))
	{
		return ob1;
	}
	if (E0(ob2))
	{
		return ob2;
	}
	// Initialize a result object to zero
	BigFloat result;
	
	// Multiply each digit of ob1 by each digit of ob2 and add the products
	// to the result object, taking care to carry over any remainders from 
	// the previous multiplication
	for (int i = 0; i < ob1.digits.size(); i++)
	{
		int carry = 0;
		BigFloat current(0);
		for (int j = 0; j < ob2.digits.size(); j++)
		{
			int product = ob1.digits[i] * ob2.digits[j] + carry;
			current.digits.push_back(product % 10);
			carry = product / 10;
		}
		if (carry > 0)
		{
			current.digits.push_back(carry);
		}
		
		// Insert zeros into the current result object to shift it to the left
		// by i digits, since we are computing a partial product
		for (int j = 0; j < i; j++)
		{
			current.digits.insert(current.digits.begin(), 0);
		}
		// Add the current partial product to the overall result
		result = result + current;

	// Set the sign of the result based on the signs of the operands
	}
	if (ob1.negativ && ob2.negativ)
	{
		result.negativ = false;
	}
	else if (ob1.negativ || ob2.negativ)
	{
		result.negativ = true;
	}

	// Set the position of the decimal point in the result, if either operand is a float
	if (ob1.is_float || ob2.is_float)
	{
		result.float_point = result.digits.size() - (static_cast<unsigned long long>(ob1.float_endpoint) + ob2.float_endpoint) - 1;
		result.is_float = true;
	}

	// Remove any leading zeros from the result and return it
	result.digits.erase(result.digits.begin());
	return result;
}
BigFloat operator*=(BigFloat& ob1, const BigFloat& ob2)
{
	// It multiply ob2 to ob1 using the * operator, and assigns the result back to ob1.
	ob1 = ob1 * ob2;
	return ob1;
}

BigFloat operator/(const BigFloat& ob1, const BigFloat& ob2)
{
	// Create a new BigFloat variable to store the result of the division
	BigFloat result;

	// If the divisor is 0, throw an exception
	if (ob2 == 0)
	{
		throw("Division by zero is not allowed");
	}
	// Calculate the difference in floating point positions between the two operands
	int dif = ob1.float_point - ob2.float_point;
	// Determine the sign of the result based on the signs of the operands
	result.negativ = (ob1.negativ != ob2.negativ);
	// Create a new BigFloat variable to store the current value of the dividend
	BigFloat divident ;
	BigFloat _ob1 = ob1;
	// If the divisor has a floating point component
	if (ob2.is_float)
	{
		// Shift the digits of the dividend to the left to align the decimal points
		for (int i = 0; i < ob2.float_endpoint; i++)
			_ob1.digits.insert(_ob1.digits.begin(), 0);
	}
	// Set the initial value of the dividend to the last digit of the dividend
	divident.digits.push_back(_ob1.digits.back());
	// Create a copy of the divisor to modify
	BigFloat divisor = ob2;
	// Initialize a counter for the number of digits in the result after the decimal point
	int precision = 0;
	// If the dividend has a floating point component
	if (ob1.is_float)
	{
		// Shift the digits of the divisor to the left to align the decimal points
		for (int i = 0; i < ob1.float_endpoint; i++)
			divisor.digits.insert(divisor.digits.begin(), 0);
	}
	// Initialize an index for iterating over the digits of the dividend from right to left
	int k = _ob1.digits.size() - 1;
	while(1) // Loop indefinitely until the division is complete
	{
		bool flag_point = false; // Flag to indicate if the decimal point has been reached
		BigFloat cat = 0; // Create a new BigFloat variable to store the current value of the quotient
		BigFloat produs = 0; // Create a new BigFloat variable to store the current value of the product
		do
		{
			while (divident <= divisor) // While the current value of the dividend is less than or equal to the divisor
			{
				
				if(k) // If there are still digits in the dividend
				{
					// Decrement the index to move to the next digit
					k--;
					// Add the next digit to the left of the dividend
					divident.digits.insert(divident.digits.begin(), _ob1.digits[k]);
					if (!k) // If the first digit of the dividend has been reached
					{
						// Set the flag to indicate that the decimal point has been reached
						flag_point = true;
					}

					// If the last digit of the dividend is 0
					if (divident.digits.size() > 1 && divident.digits[divident.digits.size() - 1] == 0)
					{
						divident.digits.pop_back(); // Remove the trailing 0
						break; // Exit the loop
					}
				}
				else // If all the digits of the dividend have been processed
				{
					divident.digits.insert(divident.digits.begin(), 0);
					if (divident.digits.size() > 1 && divident.digits[divident.digits.size() - 1] == 0)
						divident.digits.pop_back(); // Remove the trailing 0
					break; // Exit the loop
				}
			}
			// Calculate the product of the quotient digit and the divisor
			produs += divisor;

			// If the product is greater than the remaining dividend, break the loop
			if (produs > divident)
				break;

			// Increment the quotient digit
			cat++;
		} while (1);

		// If the dividend is greater than the divisor, subtract the product of the divisor and the quotient from the dividend.
		// This step is necessary to ensure that the next quotient digit is as large as possible while still ensuring that the result is correct.
		if (divident > divisor)
		{
			BigFloat prod = cat * divisor;
			divident = divident - prod;
		}
		//computing the result
		for (int i = cat.digits.size() - 1; i >= 0; i--)
		{
			result.digits.insert(result.digits.begin(), cat.digits[i]);
		}

		//checks whether the result has a floating point
		if (flag_point && divident == 0)
			break;
		if (flag_point)
		{
			result.is_float = true;
			result.float_point = result.digits.size();
			if (ob1.is_float)
				result.float_point ;
			if(ob2.is_float)
				result.float_point ;
		}
		if(result.is_float)
			if (divident == 0)
				break;
		//If the precision is exceeded, the function breaks out of the loop. 
		//If the precision is not specified in the input BigFloat objects, the default precision is 10 digits.
		if (ob1.precision)
		{
			if (precision > ob1.precision)
				break;
		}
		else
			if (precision > 10)
				break;
	
		if (!k)
			precision++;
	}
	//if the division ended with the dividend being smaller than the divisor, 
	// a zero digit is appended to the result
	if (_ob1 < ob2)
	{
		result.digits.push_back(0);
		result.is_float = true;
		result.float_point = result.digits.back()+1;
	}
	
	return result;
}


BigFloat operator/=(BigFloat& ob1, const BigFloat& ob2)
{
	// It make divison ob1 to ob2 using the / operator, and assigns the result back to ob1.
	ob1 = ob1 / ob2;
	return ob1;
}

BigFloat operator%(const BigFloat& ob1, const BigFloat& ob2)
{
	// <EXPERIMENTAL>
	//Use this just for integers
	BigFloat result;
	if (ob2 == 0)
	{
		throw("Division by zero is not allowed");
	}
	if (ob2 > ob1)
	{
		result = 0;
		return result;
	}
	BigFloat _ob1 = ob1;
	if (ob2.is_float)
	{
		for (int i = 0; i < ob2.float_point; i++)
			_ob1.digits.insert(_ob1.digits.begin(), 0);
	}
	
	result.negativ = (ob1.negativ != ob2.negativ);
	BigFloat divident;
	divident.digits.push_back(_ob1.digits.back());
	BigFloat divisor = ob2;
	int k = _ob1.digits.size() - 1;
	while (1)
	{
		BigFloat cat = 0;
		BigFloat produs = divisor;
		do
		{
			while (divident <= divisor)
			{
				k--;
				divident.digits.insert(divident.digits.begin(), _ob1.digits[k]);
			}
			produs += divisor;
			cat++;
		} while (produs <= divident);
		BigFloat prod = cat * divisor;
		divident = divident - prod;
		if (divident == 0)
			break;
		if (!k)
			break;
	}
	result = divident;
	//// Remove leading zeros from the result
	/*while (result.digits.size() > 0 && result.digits.back() == 0)
	{
		result.digits.pop_back();
	}*/
	return result;
}

BigFloat operator%=(BigFloat& ob1, const BigFloat& ob2)
{
	// <EXPERIMENTAL>
	//Use this just for integers
	ob1 = ob1 % ob2;
	return ob1;
}
BigFloat& BigFloat::operator++()
{
	// <EXPERIMENTAL>
	//Use this just for integers
	*this = *this + 1;
	return *this;
}
BigFloat BigFloat::operator++(int fictiv)
{
	// <EXPERIMENTAL>
	//Use this just for integers
	BigFloat temp;
	temp = *this;
	++(*this);
	return temp;
}
BigFloat& BigFloat::operator--()
{
	// <EXPERIMENTAL>
	//Use this just for integers
	*this = *this - 1;
	return *this;
}
BigFloat BigFloat::operator--(int fictiv)
{
	// <EXPERIMENTAL>
	//Use this just for integers
	BigFloat temp;
	temp = *this;
	--(*this);
	return temp;
}

bool operator==(const BigFloat& ob1, const BigFloat& ob2)
{
	// If any two digits are not equal, then the loop terminates and the function returns false. 
	int i;
	if (ob1.digits.size() != ob2.digits.size())
		return false;
	for (i = 0; i < ob1.digits.size() && ob1.digits[i] == ob2.digits[i]; i++);
	return i == ob1.digits.size();
}

bool operator!=(const BigFloat& ob1, const BigFloat& ob2)
{
	//Reverse of the == operator
	return !(ob1 == ob2);
}

bool operator<(const BigFloat& ob1, const BigFloat& ob2)
{
	// Check the number of digits in the two objects
	// If ob1 has fewer digits than ob2, then ob1 is smaller
	int i = 0;
	if (ob1.digits.size() < ob2.digits.size())
		return true;
	// If ob1 has more digits than ob2, then ob1 is larger
	if (ob1.digits.size() > ob2.digits.size())
		return false;
	// If both objects have the same number of digits, then compare them digit by digit
	// Start with the most significant digit and work towards the least significant
	for (i = ob1.digits.size() - 1; i >= 0 && ob1.digits[i] == ob2.digits[i]; i--);
	// If all digits are equal, then the objects are not less than each other
	if (i == -1)
		return false;
	// If the i-th digit of ob1 is less than the i-th digit of ob2, then ob1 is smaller
	if (ob1.digits[i] < ob2.digits[i])
		return true;
	// Otherwise, ob1 is not less than ob2
	return false;

}
bool operator>(const BigFloat& ob1, const BigFloat& ob2)
{
	//Reverse of the < operator
	return ob2 < ob1;
}
bool operator<=(const BigFloat& ob1, const BigFloat& ob2)
{
	//Not the operator >
	return !(ob1 > ob2);
}

bool operator>=(const BigFloat& ob1, const BigFloat& ob2)
{
	//Not the operator <
	return !(ob1 < ob2);
}

void set_precision(BigFloat& ob1, BigFloat& ob2, const int& n)
{
	ob1.precision = n-1;
}
int BigFloat::operator[](const int poz) const
{

	if (poz < 0)
		throw("Range Error");
	return digits[poz];
}

