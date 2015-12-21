/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 * 
 * Problem statements:
 *  https://www.hackerrank.com/challenges/tree-preorder-traversal
 *  https://www.hackerrank.com/challenges/tree-inorder-traversal
 *  https://www.hackerrank.com/challenges/tree-postorder-traversal
 * These do not form standalone code.
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

void Preorder(node *root) {
    std::cout << root->data << " ";
    
    if (root->left)
        Preorder(root->left);
    
    if (root->right)
        Preorder(root->right);
}

void Inorder(node *root) {
    if (root->left)
        Inorder(root->left);
    
    std::cout << root->data << " ";
    
    if (root->right)
        Inorder(root->right);
}

void Postorder(node *root) {
    if (root->left)
        Postorder(root->left);
    
    if (root->right)
        Postorder(root->right);
    
    std::cout << root->data << " ";
}
