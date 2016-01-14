/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/sherlock-and-array 
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
#include <stdint.h>
#include <assert.h>

#include <iostream>
#include <vector>

void handle_test_case(const size_t c) {
    std::cerr << "On test case #" << c << std::endl;
    
    size_t N;
    std::cin >> N;
    
    std::vector<size_t> A(N, 0);

    for (size_t i = 0; i < N; ++i) { 
        std::cin >> A.at(i);
    }

    
    std::vector<size_t> left_sums(N, 0);
    std::vector<size_t> right_sums(N, 0);

    for (size_t i = 0; i < N; ++i) { 
        size_t left_sum = A.at(i); 
        size_t right_sum = A.at(N - 1 - i);

        if (i != 0) {
            left_sum += left_sums.at(i - 1);
            right_sum += right_sums.at(N - i /* - 1 + 1 */ );
        }

        left_sums.at(i) = left_sum;
        right_sums.at(N - 1 - i) = right_sum;
    }

    
    for (size_t i = 0; i < N; ++i) {
        size_t left_sum = 0;
        size_t right_sum = 0;

        if (i != 0) {
            left_sum = left_sums.at(i - 1);
        }

        if (i != N - 1) {
            right_sum = right_sums.at(i + 1);
        }

        if (left_sum == right_sum) {
            goto out_success;
        }
    }    

    std::cout << "NO" << std::endl;
    return;

out_success:
    std::cout << "YES" << std::endl;
    return;
}


int main() {
    size_t  cases;
    std::cin >> cases;
    
    for (size_t c = 0; c < cases; ++c) {
        handle_test_case(c);
    }
    
    return 0;
}

