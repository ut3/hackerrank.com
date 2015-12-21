/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 * 
 * Problem statement:
 *  https://www.hackerrank.com/challenges/tree-huffman-decoding
 *  This problem statement handles text processing for the user;
 *  the following is not standalone code.
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

void decode_huff(node * root, string s)
{
    std::cerr << s << std::endl;
    std::string rv;
    
    node *last = root;
    for (auto iter = s.begin(); iter != s.end(); ++iter) {
        const char hchar = *iter;
        
        assert(hchar == '1' || hchar == '0');
        
        if (hchar == '0') {
            assert(last->left);
            last = last->left;
        }
        else if (hchar == '1') {
            assert(last->right);
            last = last->right;
        } 
        
        if (!last->right && !last->left) {
            rv.push_back(last->data);
            last = root;
        }
    }    
    
    std::cout << rv << std::endl;
}
