/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/diagonal-difference/ 
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

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    unsigned long N;
    std::cin >> N;
    
    long first_sum = 0;
    long second_sum = 0;
    
    for (int i = 0; i < N; ++i) {
        std::vector<long> vals;
        long tmp;
        
        for (int j = 0; j < N; ++j) {
            /* read in the row */
            std::cin >> tmp;
            vals.push_back(tmp);
        }
        
        /* care about i, N-1-i */
        first_sum += vals[i];
        second_sum += vals[N-1-i];
    }
    
    unsigned long rv = (first_sum > second_sum ? first_sum - second_sum : second_sum - first_sum);
    
    std::cout << rv;
}
