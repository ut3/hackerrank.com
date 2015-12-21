/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/quicksort1
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
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <assert.h>

void partition(const int pivot, std::vector <int>  &ar) {
    std::vector<int> lesser;
    std::vector<int> greater;
    size_t pivot_copies = 0;
    
    std::vector<int>::const_iterator it = ar.begin();
    for (; it != ar.end(); ++ it) { 
        if (*it < pivot) {
            lesser.push_back(*it);
            continue;
        }
        
        if (*it > pivot) {
            greater.push_back(*it);
            continue;
        }
        
        if (*it == pivot) {
            ++pivot_copies;
            continue;
        }
        
        assert(0 && "Invalid case for *it");
    }
    
    ar.clear();
    ar.insert(ar.begin(), lesser.begin(), lesser.end());
    ar.insert(ar.end(), pivot_copies, pivot);
    ar.insert(ar.end(), greater.begin(), greater.end());
}

int main(void) {
    size_t count;
    std::cin >> count;
    
    std::vector<int> array;
    
    for (size_t i = 0; i < count; ++ i) { 
        int tmp;
        std::cin >> tmp;
        
        array.push_back(tmp);
    }
    
    if (array.empty())
        return EXIT_FAILURE;
    
    partition(array[0], array);
    
    decltype(array)::const_iterator iter = array.begin();
   
    for (; iter != array.end(); ++ iter) {
        std::cout << *iter << " ";
    }
    
    return 0;
}
