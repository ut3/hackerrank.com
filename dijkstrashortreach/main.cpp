/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/dijkstrashortreach
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

#include <cstdlib>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include <list>
#include <limits>
#include <iostream>
#include <set>
#include <vector>

/**
 * The adjacency matrix is space-optimized for bidirectional graphs.
 *
 * In RAM, the matrix for this input:
 *   n1<->n2 = w24 (a bidrectional edge of weight 24 exists between nodes 1 and 2)
 *   n1<->n4 = w20
 *   n3<->n1 = w3
 *   n4<->n3 = w12
 *
 * ...will look like:
 *   1  2  3  4
 * 1 M  _  _  _
 * 2 24 M  _  _
 * 3 3  M  M  _
 * 4 20 M  12 M
 *
 * where "M" means std::numeric_limits<T>::max() and
 *  a "_" means not-allocated
 *
 * The total allocation size is calculated from the arithmetic sum:
 *   ∑i from 1 to N = N(N+1)/2
 */
template <typename W>
class AdjacencyMatrix {
    public:
        typedef W Weight; // edge weight type

        AdjacencyMatrix(const size_t nodes, const size_t edges) :
            m_nodes(nodes), /* Actual number of nodes */
            m_edges(edges), /* Actual number f edges */
            m_matrix(NULL) {
                /** 
                 * Mathematical max number of edges.  
                 * Graph input (edges and nodes) not sane if this fails.
                 */
                if (edges > nodes * (nodes + 1) / 2) {
                    std::cerr << "Graph input not sane, mismatch between "
                              << "edge (" << edges <<") and node (" 
                              << nodes << ") counts." << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

        ~AdjacencyMatrix() {
            free(m_matrix);
            m_matrix = NULL;
        }

        int Setup() {
            if (m_matrix)
                return -1;

            const size_t alloc_size =
                sizeof(*m_matrix) * m_nodes + /* Space for row pointers */
                sizeof(**m_matrix) * (m_nodes * (m_nodes + 1)) / 2 /* Space for datums */
                ;

            errno = 0;
            m_matrix = (Weight **) malloc (alloc_size);

            if (!m_matrix) {
                std::cerr << "-ENOMEM: " << errno << " :: " << strerror(errno) << std::endl;
                return -1;
            }

            /* offset points to the start of row data (it is preceded by pointers to rows) */
            Weight *offset = (Weight *) &m_matrix[m_nodes];

            for (size_t i = 0; i < m_nodes; ++i, offset += i) {
                m_matrix[i] = offset;

                /* the highest column index in the i-th row is i */
                for (size_t j = 0; j <= i; ++j) {
                    m_matrix[i][j] = std::numeric_limits<Weight>::max();
                }

                m_matrix[i][i] = 0;
            }

            return 0;
        }

        void SetEdge(const size_t A, const size_t B, const Weight weight) {
            const size_t UA = A > B ? A - 1 : B - 1; /* larger - 1 */
            const size_t UB = A < B ? A - 1 : B - 1; /* smaller - 1 */

            if (UA >= m_nodes || UB >= m_nodes) {
                std::cerr << "BAD IDX :: " << UA << ", " << UB << std::endl;
                return;
            }

            /* 
             * If a duplicate edge exists, discard the higher-cost edge.
             * This will cause trouble if the AdjacencyMatrix is ever used as
             * part of a cost-maximization algorithm. 
             */
            Weight oldweight = GetEdge(A, B);
            if (oldweight < weight)
                return;

            m_matrix[UA][UB] = weight;
        }

        Weight GetEdge(const size_t A, const size_t B) const {
            if (!m_matrix) {
                std::cerr << "-ENOTINIT" << std::endl;
                return 0;
            }

            const size_t UA = A > B ? A - 1 : B - 1; /* larger - 1 */
            const size_t UB = A < B ? A - 1 : B - 1; /* smaller - 1 */

            return m_matrix[UA][UB];
        }

        size_t NodeCount() const { return m_nodes; }


        /* "node" param is 1-indexed */
        template <typename T>
        void GetNeighbors(const size_t node, T &neighbors) const {

            if (node > m_nodes) {
                std::cerr << "Node " << node << " out of bounds, max is " << m_nodes << std::endl;
                return;
            }

            /* When i is less than the search node, use i as the row index */
            for (size_t i = 0; i < node; ++i) {
                Weight weight = m_matrix[node - 1 /* 0-indexed */][i];
                if (weight != std::numeric_limits<Weight>::max()) {
                    neighbors.insert(neighbors.end(), std::make_pair(i + 1 /* 1-indexed */, weight));
                }
            }

            /* When i is greater than or equal to the search node, use i as the col index */
            for (size_t i = node; i < m_nodes; ++i) {
                Weight weight = m_matrix[i][node - 1 /* 0-indexed */];
                if (weight != std::numeric_limits<Weight>::max()) {
                    neighbors.insert(neighbors.end(), std::make_pair(i + 1 /* 1-indexed */, weight));
                }
            }
        }

        void Print() {
            std::cerr << "Matrix dump follows: " << std::endl;
            for (size_t x = 1; x <= m_nodes; ++x) {
                std::cerr << x << ": ";
                for (size_t y = 1; y <= x; ++y) {
                    Weight val = m_matrix[x - 1][y - 1];
                    if (val == std::numeric_limits<Weight>::max())
                        std::cerr << y << "=M ";
                    else
                        std::cerr << y << "=" << val << " ";
                }
                std::cerr << std::endl;
            }
        }

    private:
        const size_t m_nodes;
        const size_t m_edges;

        /* This is 0-indexed, but most public methods are 1-indexed */
        Weight **m_matrix;
};



template <typename MatrixT>
class DijkstraGraph {
    public:
        typedef typename MatrixT::Weight Weight;

        /* start is 1-indexed, internal data structures are 0-indexed */
        DijkstraGraph(const size_t start, const MatrixT &matrix) :
            m_start(start), 
            m_matrix(matrix), 
            m_distances(NULL) { 

                /**
                 * Bounds checking on the start node.
                 * Input start node is not sane if this fails.
                 */
                if (start > m_matrix.NodeCount()) { 
                    std::cerr << "Start node " << start 
                              << " exceeds maximum node count " 
                              << m_matrix.NodeCount() << std::endl;
                    exit(EXIT_FAILURE);
                }
            }

        ~DijkstraGraph() {
            free(m_distances);
            free(m_previous);
            m_distances = NULL;
            m_previous = NULL;
        }

        int Setup() {
            if (m_distances)
                return -1;

            /* 
             * 1. Allocate space for the 0-indexed list of weights from start
             */

            const size_t alloc_size = sizeof(Weight) * m_matrix.NodeCount();

            m_distances = (Weight *) malloc(alloc_size);
            if (!m_distances) {
                std::cerr << "-ENOMEM" << std::endl;
                return -1;
            }



            /*
             * 2. Allocate space for the 0-indexed list of prior nodes on
             *    the optimal path from start 
             */ 

            m_previous = (size_t *) malloc(sizeof(size_t) * m_matrix.NodeCount());
            if (!m_previous) {
                std::cerr << "-ENOMEM" << std::endl;
                return -1;
            }

            /* 3. Initialize */

            for (size_t i = 0; i < m_matrix.NodeCount(); ++i) {
                m_distances[i] = std::numeric_limits<Weight>::max();
                m_previous[i]  = std::numeric_limits<size_t>::max(); 
            }

            /* Distance to self from self is 0 */
            m_distances[m_start - 1] = 0;

            /* Previous node from start to start is start, but with indexing issues */
            m_previous[m_start - 1] = m_start; 

            return 0;
        }


        int Compute() {
            /**
             * Mapping 1-idx node number to node's Weight 
             */ 
            typedef std::pair<size_t, Weight> PairT;

            /** 
             * A comparison functor which gives precedence to the second
             * entry of PairT, the Weight. Allows the "unvisited" set to
             * sort based on Weigh.
             */ 
            struct comparator{
                bool operator() (const PairT &lhs, const PairT &rhs) {
                    if (lhs.second == rhs.second)
                        return lhs.first < rhs.first;

                    return lhs.second <= rhs.second;
                }
            } theComparator;

            /** 
             * Nodes which must be traversed. "theComparator" causes
             * this to be sorted by elements' Weight, returning
             * the lowest weight element for .begin()
             */ 
            std::set<PairT, comparator> unvisited(theComparator);

            /**
             * Tracking nodes which have been visited and whose shortest paths
             * are known. This optimization is not necessary.
             */
            std::vector<bool> visited(m_matrix.NodeCount(), false);
            
            unvisited.insert(std::make_pair(m_start, 0));

            while (!unvisited.empty()) 
            {
                /* Node number 1-idx */
                const size_t &n_node = unvisited.begin()->first;

                /* Current node distance from m_start */
                const Weight &n_dist = unvisited.begin()->second;

                if (visited.at(n_node - 1))
                    std::cerr << "Error: already visited " << n_node << std::endl;

                /* The unvisited queue has been mismanaged if this fails */
                assert(false == visited.at(n_node - 1 /* 0-idx */));

                std::vector<PairT> neighbors;
                m_matrix.GetNeighbors(n_node, neighbors); 

                for (auto neighbor : neighbors)
                {
                    const size_t &c_node = neighbor.first;

                    Weight c_distThroughN = n_dist + neighbor.second;

                    /* Optimization: skip nodes we've already firmly calculated */
                    if (visited.at(c_node - 1))
                        continue;

                    if (c_distThroughN < m_distances[c_node - 1]) {

                        Weight oldWeight = m_distances[c_node - 1 /* 0-idx */];

                        m_distances[c_node - 1] = c_distThroughN;
                        m_previous[c_node - 1] = n_node;

                        /** 
                         * Update the distance stored in the queue.
                         */
                        size_t removed = unvisited.erase(std::make_pair(c_node, oldWeight));

                        /* If more than one was removed, the unvisited queue was mismanaged. */
                        assert(removed < 2);

                        unvisited.insert(std::make_pair(c_node, c_distThroughN));
                    }

                }

                unvisited.erase(unvisited.begin());

                visited.at(n_node - 1) = true;
            }

            return 0;
        }



        void Print() const {
            size_t i = 0;

            for (; i < m_matrix.NodeCount(); ++i) {
                if (i == m_start - 1)
                    continue;

                if (m_distances[i] == std::numeric_limits<Weight>::max())
                    std::cout << "-1 ";
                else
                    std::cout << m_distances[i] << " ";
            }

            std::cout << std::endl;
        }


    private:
        /* 1-indexed start node */
        size_t m_start;

        const MatrixT &m_matrix;

        /* 0-indexed list of distances from the start node */
        Weight *m_distances;

        /* 0-indexed list of prior nodes on the optimal path from start */
        size_t *m_previous;
};


int handle_test_case(size_t test_num) {
    size_t nodes = 0; // constrained: 2 < N < 3000
    size_t edges = 0; // 1 <= M <= (N*(N-1))/2

    std::cin >> nodes;
    std::cin >> edges;

    typedef AdjacencyMatrix<uint32_t> MatrixT;
    MatrixT matrix(nodes, edges);
    if (matrix.Setup()) {
        std::cerr << "Matrix setup failed; aborting test case " << test_num << std::endl;
        return -1;
    }

    for (size_t i = 0; i < edges; ++i) {
        size_t A, B;
        MatrixT::Weight weight;

        std::cin >> A;
        std::cin >> B;
        std::cin >> weight;

        //std::cerr << "SetEdge " << A << " " << B << " " << weight << std::endl;

        matrix.SetEdge(A, B, weight);
    }

    //matrix.Print();

    size_t start;
    std::cin >> start;

    DijkstraGraph<MatrixT> dijkstra(start, matrix);
    if (dijkstra.Setup()) {
        std::cerr << "Dijkstra setup() failed; aborting test case " << test_num << std::endl;
        return -1;
    }

    if (dijkstra.Compute()) {
        std::cerr << "Dijkstra compute() failed; aborting test case " << test_num << std::endl;
        return -1;
    }

    dijkstra.Print();

    return 0;
}


int main() {
    size_t num_test_cases = 0; // constrained: 1 < T < 10

    std::cin >> num_test_cases;

    for (size_t i = 0; i < num_test_cases; ++i) {
        if (handle_test_case(i))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
