/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/tree-top-view
 *  This problem handles text input for the user; the following code
 *  does not form a standalone executable.
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

void printLeft(node *root) { 
    if (root->left)
        printLeft(root->left);
    
    std::cout << root->data << " ";
}

void printRight(node *root) { 
    std::cout << root->data << " ";
    
    if (root->right)
        printRight(root->right);
}

void top_view(node *root)
{
    if (root)
        printLeft(root);
    
    if (root->right)
        printRight(root->right);
}

