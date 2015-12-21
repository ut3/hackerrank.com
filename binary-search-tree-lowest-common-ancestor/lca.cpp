/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 * 
 * Problem statement:
 *  https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor
 *  This problem statement expects a partial implementation; the work of 
 *  processing input text is solved for the user. The following code is not 
 *  standalone code.
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

#include <stack>

void pathToNode(std::stack<node *> &path, node *root, const int value) {
    node *current = root;
   
    for (;;) {
        path.push(current);
        
        if (value == current->data) 
            return;
        
        if (value < current->data) {
            current = current->left;
            continue;   
        }
        
        if (value > current->data) {
            current = current->right;
            continue;
        }
        
        assert(0 && "Bad value case");
    }
    
    assert(0 && "Bad break from loop");
    return ;
}

void printStack(std::stack<node *> stack /* pass by copy */) {
  
  std::cerr << "Path from " << stack.top()->data << " to root: "; 
    
    
  while (!stack.empty())
  {
     std::cerr << (stack.top())->data << " ";
     stack.pop();
  }
  std::cerr << '\n';
    
}


node *findNode(node *root, const int value1, const int value2) {
    node *current = root;
    
    for (;;) {
        if (value1 < current->data && value2 < current->data) {
            current = current->left;
            continue;
        }
        
        if (value1 > current->data && value2 > current->data) { 
            current = current->right;
            continue;
        }
        
        break;
    }
    
    return current;
}

node *lca(node *root, const int v1, const int v2)
{
    /* Find a node RV in the tree such that V1 and V2 are descendants of RV). */
    
    return findNode(root, v1, v2);
}
