/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/maximizing-xor/
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <assert.h>

#include <iostream>

// Constraints:
// L ≤ A ≤ B ≤ R
// 1 ≤ L ≤ R ≤ 1000
    
int maxXor(const int l, const int r) {
    int value = l ^ r;

    if (value < 0)
	value = ~value;
    
    value |= value >> 1;
    value |= value >> 2; 
    value |= value >> 4; 
    value |= value >> 8; 
    value |= value >> 16; 

    return value;	
}

int main() {
    int res;
    int _l;
    std::cin >> _l;
    
    int _r;
    std::cin >> _r;
    
    res = maxXor(_l, _r);
    std::cout << res;
    
    return 0;
}

