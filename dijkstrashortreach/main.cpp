/**
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/dijkstrashortreach
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

#include <vector>
#include <limits>
#include <iostream>
#include <utility>
#include <queue>
#include <set>
#include <map>

class AdjacencyMatrix { 
  public:
    typedef int16_t Weight; // edge weight type
   
    AdjacencyMatrix(const size_t nodes, const size_t edges) :
        m_nodes(nodes), /* Actual number of nodes */
        m_edges(edges), /* Actual number f edges */
        m_max_edges(nodes * (nodes + 1) / 2 ), /* Mathematical max number of edges */
        m_matrix(NULL)
    {    
            assert(edges <= m_max_edges);
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
            sizeof(**m_matrix) * (m_nodes * m_nodes) /* Space for datums */ 
            ;
      
        errno = 0;
        m_matrix = (Weight **) malloc (alloc_size);
       
        if (!m_matrix) {
            std::cerr << "-ENOMEM: " << errno << " :: " << strerror(errno) << std::endl;
            return -1;
        }
        
        Weight *offset = (Weight *) &m_matrix[m_nodes];
        for (size_t i = 0; i < m_nodes; ++i, offset += m_nodes) {
            m_matrix[i] = offset;
            
            for (size_t j = 0; j < m_nodes; ++j) { 
                m_matrix[i][j] = -1;
            }
          
          m_matrix[i][i] = -2; /* -2 -cost edge to self */ 
        }
        
        return 0;
    }
    
    void SetEdge(const size_t A, const size_t B, const Weight weight) { 
        const size_t UA = A-1;
        const size_t UB = B-1;
        
        if (UA >= m_nodes || UB >= m_nodes) {
            std::cerr << "-EBADIDX :: " << UA << ", " << UB << std::endl;
            return;
        }
      
        // Duplicate edge?
        Weight oldweight = GetEdge(A, B);
        if (oldweight >= 0) { 
          // Edge already exists
          
          if (oldweight < weight)
            return;
        }
        
        //std::cerr << "set [" << UA << "][" << UB << "] to " << weight << std::endl;
        m_matrix[UA][UB] = weight;
        m_matrix[UB][UA] = weight;
    }
    
    Weight GetEdge(const size_t A, const size_t B) const { 
        if (!m_matrix) {
            std::cerr << "-ENOTINIT" << std::endl;
            return 0;
        }
        
        const size_t UA = A-1;
        const size_t UB = B-1;
         
        const Weight tmp = m_matrix[UA][UB];
      
        assert(tmp == m_matrix[UB][UA]);
        return tmp;
    }
    
    size_t NodeCount() const { return m_nodes; }

  void GetNeighbors(const size_t node, std::map<size_t, Weight> &neighbors) const { 
       for (size_t i = 1; i <= m_nodes; ++i) {
           if (i == node)
             continue;
         
           Weight weight = GetEdge(node, i);
           if (weight >= 0)
               neighbors.insert(std::make_pair(i, weight));
       }
  }
  
  
    
  private:
    const size_t m_nodes;
    const size_t m_edges;
    const size_t m_max_edges;
    Weight **m_matrix;
};



class DijkstraGraph { 
    public: 
    typedef AdjacencyMatrix::Weight Weight;

    DijkstraGraph(const size_t start, const AdjacencyMatrix &matrix) :
        m_start(start), m_matrix(matrix), m_distances(NULL) { }
    
    ~DijkstraGraph() {
        free(m_distances);
        m_distances = NULL;
    }
    
    int Setup() { 
        if (m_distances)
            return -1;
       
        const size_t alloc_size = sizeof(Weight) * m_matrix.NodeCount();
        
        m_distances = (Weight *) malloc(alloc_size);
        if (!m_distances) { 
            std::cerr << "-ENOMEM" << std::endl;
            return -1;
        }
        
        for (size_t i = 0; i < m_matrix.NodeCount(); ++i)
            m_distances[i] = -1;
        
        m_distances[m_start - 1] = 0; /* Distance to self is 0 */
      
        return 0;
    }
          
    int Compute() {
      std::map<size_t, Weight> unvisited;
      unvisited.insert(std::make_pair(m_start, 0));
      
      while (!unvisited.empty()) { 
        /* Known & firm min distance to the current node */
        const Weight c_dist = unvisited.begin()->second;
        const size_t c_node = unvisited.begin()->first;
        unvisited.erase(unvisited.begin());
        
        std::map<size_t, Weight> neighbors;
        m_matrix.GetNeighbors(c_node, neighbors);
        
        std::map<size_t, Weight>::const_iterator iter = neighbors.begin();
        for (; iter != neighbors.end(); ++iter) {
          const size_t n_node         = iter->first;
          /* distance to the neighbor node by going through C */
          const Weight n_distThroughC = c_dist + iter->second;
          
          if (m_distances[n_node - 1] == -1 ||
              n_distThroughC < m_distances[n_node - 1])
          {
            m_distances[n_node - 1] = n_distThroughC;
            
            /* Have to update unvisited queue with new info */
            unvisited.erase(n_node);
            unvisited[n_node] = m_distances[n_node - 1];
          }
            
        }
        
      }
      
      return 0;
    }
  
    void Print() const { 
      size_t i = 0;
      
      for (; i < m_matrix.NodeCount(); ++i) { 
        if (i == m_start - 1)
          continue;
        
        std::cout << m_distances[i] << " ";
      }
      
      std::cout << std::endl;
    }
    

    private:
    size_t m_start;
    
    const AdjacencyMatrix &m_matrix;
    
    /* m_distances[R][C] constraint: R <= C (swap them if not) */
    Weight *m_distances;
};

    
int handle_test_case(size_t test_num) { 
    size_t nodes = 0; // constrained: 2 < N < 3000
    size_t edges = 0; // 1 <= M <= (N*(N-1))/2

    std::cin >> nodes;
    std::cin >> edges;
    
    AdjacencyMatrix matrix(nodes, edges);
    if (matrix.Setup()) {
        std::cerr << "Matrix setup failed; aborting test case " << test_num << std::endl;
        return -1;
    }
    
    for (size_t i = 0; i < edges; ++i) {
        size_t A, B;
        AdjacencyMatrix::Weight weight;
        
        std::cin >> A;
        std::cin >> B;
        std::cin >> weight;
        
        matrix.SetEdge(A, B, weight);
    }
    
    size_t start;
    std::cin >> start;
    
    DijkstraGraph dijkstra(start, matrix);
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
