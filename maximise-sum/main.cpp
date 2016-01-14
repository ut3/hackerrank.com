/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/maximise-sum
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

#include <assert.h>
#include <stdint.h>

#include <iostream>
#include <vector>

void handle_testcase(const size_t c) {
    std::cout << "Test case #" << c << std::endl;

    size_t N, M;
    std::cin >> N; /* count */
    std::cin >> M; /* modulo */

    typedef double storage_type;
    std::vector<double> A(N, 0f);

    for (size_t i = 0; i < N; ++i) { 
        std::cin >> A.at(i); 
    }


}

int main(int argc, char **argv) { 
    size_t T;
    std::cin >> T;

    for (size_t i = 0; i < T; ++i) { 
        handle_testcase(i);
    }

}
