/**
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/swap-nodes-algo
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

#include <cstdio>
#include <cstdlib>

#include <vector>
#include <iostream>

class Node {
    public:
    
    int left;
    int right;
};

std::vector<Node> tree;

void inOrder(const std::vector<Node> &tree, int rootIdx) {
    if (tree[rootIdx].left != -1)
        inOrder(tree, tree[rootIdx].left);
    
    std::cout << rootIdx << " ";
    
    if (tree[rootIdx].right != -1)
        inOrder(tree, tree[rootIdx].right);
}

void atDepth(std::vector<size_t> &nodesAtDepth, 
             const std::vector<Node> &tree,
             size_t curIdx,
             size_t depthRemaining) { 
    
    if (depthRemaining == 1) {
        nodesAtDepth.push_back(curIdx);
        return;
    }
    
    if (tree[curIdx].left != -1)
        atDepth(nodesAtDepth, tree, tree[curIdx].left, depthRemaining - 1);
        
    if (tree[curIdx].right != -1)
        atDepth(nodesAtDepth, tree, tree[curIdx].right, depthRemaining -1);

}

int main() {

    size_t N;
    std::cin >> N;
    
    tree.reserve(N + 1);
    
    for (size_t i = 1; i <= N; ++i) {
        int left, right;
        std::cin >> left;
        std::cin >> right;
        
        tree[i].left = left;
        tree[i].right = right;
    }
    
    size_t T;
    std::cin >> T;
    
    for (size_t i = 0; i < T; ++i) {
        size_t startDepth;
        std::cin >> startDepth;
        
        for (
            size_t multiplier = 1, depth = startDepth;
            depth < N; 
            depth = startDepth * ++multiplier
        ) {
            std::vector<size_t> nodesAtDepth;
            
            atDepth(nodesAtDepth, tree, 1, depth);
            
            for (auto index : nodesAtDepth) {
                int tmp = tree[index].left;
                tree[index].left = tree[index].right;
                tree[index].right = tmp;
            }
        }

        inOrder(tree, 1);
        std::cout << std::endl;
    }
    
    return 0;
}

