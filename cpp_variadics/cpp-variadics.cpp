#include <iostream>
#include <assert.h>
using namespace std;

/*
https://www.hackerrank.com/challenges/cpp-variadics
A template parameter pack is a template parameter that accepts zero or more template arguments (non-types, types, or templates). To read more about parameter pack, click here.

Create a template function named reversed_binary_value. It must take an arbitrary number of bool values as template parameters. These booleans represent binary digits in reverse order. Your function must return an integer corresponding to the binary value of the digits represented by the booleans. For example: reversed_binary_value<0,0,1>() should return 4.
*/

template <int>
unsigned int do_reverse()
{
	return 0;
}

/* 
 * A key piece of insight for me when dealing with variadic templates is
 * ensuring the recursive base case is non ambiguous. Hence depth as a
 * template param.
 *   do_reverse<one boolean>()
 */
template <int depth, bool current, bool... bools>
unsigned int do_reverse()
{
	return (current << depth) + do_reverse<depth + 1, bools...>();
}

template <bool... bools>
unsigned int reversed_binary_value()
{
	return do_reverse<0, bools...>();
}

int main(int argc, char **argv)
{
	std::cout << reversed_binary_value<1>() << std::endl;
	std::cout << reversed_binary_value<1,1>() << std::endl; // 
	std::cout << reversed_binary_value<1,0,1>() << std::endl; // 5: 1*2^0 + 0*2^1 + 1*2^2 
	std::cout << reversed_binary_value<0,0,0,1>() << std::endl;
	std::cout << reversed_binary_value<0,0,0,0,0,0,0,0,1>() << std::endl; // 2^8 = 256
}
