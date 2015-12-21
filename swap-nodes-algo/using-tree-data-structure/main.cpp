/*
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

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <assert.h>

#include <vector>
#include <iostream>
#include <stack>

class Node {
    public:
    
    size_t data;
    Node *left;
    Node *right;
};

void InOrder(Node *root) {
    
    if (root->left) 
        InOrder(root->left);
    
    std::cout << root->data << " ";
    
    if (root->right)
        InOrder(root->right);
}

void FindNodesAtDepth(std::vector<Node *> &atDepth, Node *root, const size_t depth) {
    if (depth == 1) {
        atDepth.push_back(root);
        return;
    }
    
    if (root->left)
        FindNodesAtDepth(atDepth, root->left, depth - 1);
    
    if (root->right)
        FindNodesAtDepth(atDepth, root->right, depth - 1);
}

void destroyNodes(Node *root) {
    if (!root)
        return;
    
    if (root->left) {
        destroyNodes(root->left);
        root->left = NULL;
    }
    
    if (root->right) {
        destroyNodes(root->right);
        root->right = NULL;
    }
    
    free(root);
}

class InputNode {
public:
    InputNode(size_t i)
        : index(i)
    { 
        std::cin >> left;
        std::cin >> right;
    }
  
    size_t index;
    int left;
    int right;
};

Node *createTree(const size_t N) {
    /** 
     The input lines are ordered opposite to their usefulness.
     Use a stack to reverse the order of input processing.
     */
    std::stack<InputNode> inputNodes;

    for (size_t i = 1; i <= N; ++i) {
        InputNode inputNode(i);
        inputNodes.push(inputNode);
    }

    std::vector<Node *> nodes;
    nodes.reserve(inputNodes.size() + 1);

    /**
      Translate InputNodes into Nodes by starting
      at the deepest nodes (now at the top of the stack)
      and working back towards root
     */
    Node *newNode = NULL;
    while (!inputNodes.empty()) {
        InputNode &input(inputNodes.top());

        newNode = new Node();
        if (!newNode) {
            assert(0 && "ENOMEM");
            exit(1);
        }

        newNode->data = input.index;

        if (input.left == -1)
            newNode->left = NULL;
        else
            newNode->left = nodes[input.left];

        if (input.right == -1)
            newNode->right = NULL;
        else 
            newNode->right = nodes[input.right];

        nodes[input.index] = newNode;

        inputNodes.pop();
    }

    return newNode;
}

void handleSwaps(Node *root, size_t N) {
    size_t T;
    std::cin >> T;
    
    for (size_t i = 0; i < T; ++i) {
        size_t depth;
        std::cin >> depth;
        
        size_t curDepth = depth;
        size_t multiplier = 1;
        
        while (curDepth < N) {
            std::vector<Node *> atDepth;
            FindNodesAtDepth(atDepth, root, curDepth);
        
            for (auto node : atDepth) {
                Node *tmp = node->left;
                node->left = node->right;
                node->right = tmp;
            }
            
            ++multiplier;
            curDepth = depth * multiplier;
        }

        InOrder(root);
        std::cout << std::endl;
    }
}

int main() {
    size_t N = 0; /* Nodes in the tree */
    std::cin >> N;
 
    Node *root = createTree(N);
        
    handleSwaps(root, N);
    
    destroyNodes(root);
    return 0;
}
