/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/tree-height-of-a-binary-tree
 *  This problem statement handles text processing for the user.
 *  The following code does not form an executable.
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

int height(node *node)
{
  size_t lheight = 0;
  size_t rheight = 0;
    
    if (node->left)
       lheight += 1 + height(node->left);
    
    if (node->right)
       rheight += 1 + height(node->right);
    
    if (!node->left && !node->right)
        return 1;
    
    return lheight > rheight ? lheight : rheight;
}
