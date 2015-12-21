/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 * https://www.hackerrank.com/challenges/plus-minus
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

#include <vector>
#include <iostream>

int main() {
    unsigned long count;
    std::cin >> count;
    
    unsigned long negative = 0;
    unsigned long positive = 0;
    unsigned long zero = 0;
    
    std::vector<long> values;
    for (size_t i = 0; i < count; ++i) {
        long tmp;
        std::cin >> tmp;     
        
        if (tmp == 0)
            ++zero;
        else if (tmp > 0)
            ++positive;
        else if (tmp < 0)
            ++negative;
        else 
            std::cout << "ERROR" << std::endl;
    }
    
    
    std::cout << positive / static_cast<double>(count) << std::endl;
    std::cout << negative / static_cast<double>(count) << std::endl;
    std::cout << zero / static_cast<double>(count) << std::endl;

    return 0;
}

