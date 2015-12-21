/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/time-conversion  
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

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cstring>

//  07:05:45PM

int main() {
    std::string input;
    std::cin >> input;
    
    /* copy into a c string */
    char inputc[32];
    strncpy(inputc, input.c_str(), sizeof(inputc));
    inputc[sizeof(inputc) - 1] = 0;
    
    char *tokenized = strtok(inputc, ":");
    if (!tokenized)
        return -1;
    
    unsigned long first = atol(tokenized);
    
    tokenized = strtok(NULL, ":");
    if (!tokenized)
        return -1;
    
    unsigned long second = atol(tokenized);
    
    tokenized = strtok(NULL, ":");
    if (!tokenized)
        return -1;
    
    unsigned long third = atol(tokenized);
    
    if (strstr(tokenized, "PM") != NULL) {
        if (first != 12)
            first += 12;
    }
    else if (strstr(tokenized, "AM") != NULL) {
        if (first == 12)
            first =0;
    }
    
    std::cout << std::setfill('0') << std::setw(2) << first;
    std::cout << ":";
    std::cout << std::setfill('0') << std::setw(2) << second;
    std::cout << ":";
    std::cout << std::setfill('0') << std::setw(2) << third;
    std::cout << std::endl;
    
    return 0;
}
