/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/binary-search-tree-insertion  
 *  This problem statement handles text processing for the user; it
 *  does not expect standalone code. The following is not standaloen code.
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

node *createNode(node *left, node *right, int value) {
    node *rv = (node *) malloc (sizeof(*rv));
    if (!rv) {
        std::cerr << "-ENOMEM" << std::endl;
        exit(1);
    }
    
    rv->data = value;
    rv->left = left;
    rv->right = right;
    
    return rv;
}

node * insert(node * root, int value)
{
    if (!root) {
        root = createNode(NULL, NULL, value);
        return root;
    }
    
   if (value < root->data) {
       if (!root->left) {
            root->left = createNode(NULL, NULL, value);
       } else { 
            insert(root->left, value); 
       }
   } else if (value > root->data) {
       if (!root->right) {
           root->right = createNode(NULL, NULL, value);
       } else { 
           insert(root->right, value);
       }
   } else {
       assert(0 && "Duplicate value in BST");
   }

   return root;
}

