/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/tree-level-order-traversal
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

#include <queue>

void PrintQueue(std::queue<node *> &queue) { 

    while(!queue.empty()) { 
        node *current = queue.front();
        queue.pop();
        
        std::cout << current->data << " ";
        
        if (current->left)
            queue.push(current->left);
        
        if (current->right)
            queue.push(current->right);
    }
}

void LevelOrder(node * root) {

    std::queue<node *> queue;
   
    queue.push(root);
    
    PrintQueue(queue); 
}
