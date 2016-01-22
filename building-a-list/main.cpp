/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 * 
 * Problem statement:
 *  https://www.hackerrank.com/challenges/building-a-list
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
#include <iostream>
#include <algorithm>

void print(const std::string &prefix, /* Output prefix for the current recursion */ 
           const std::string &input,  /* Input character array */
           const std::string::const_iterator start /* Start location of the char array */
          ) {
    for (auto iter = start; iter != input.end(); ++iter) {  
        std::string temp (prefix + *iter);

        std::cout << temp << std::endl;

        print(temp, input, iter + 1);
    }
}

int handle_test_case(size_t test_num) {
    size_t size;
    std::cin >> size;

    std::string input;
    std::cin >> input;
    assert(size == input.size());

    /* Treat input like a vector<char> and sort it */ 
    std::sort(input.begin(), input.end());

    print("", input, input.begin());
    return 0;
}

int main() {
    size_t test_cases;
    std::cin >> test_cases;

    for (size_t i = 0; i < test_cases; ++i) {
        if (handle_test_case(i))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
