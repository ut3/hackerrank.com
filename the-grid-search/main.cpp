/*
 * Copyright 2015 J. Rick Ramstetter
 * rick.ramstetter[at]gmail.[tld]
 *
 * Problem statement:
 *  https://www.hackerrank.com/challenges/the-grid-search
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
#include <cstdio>
#include <iostream>
#include <string>
#include <errno.h>
#include <cstring>
#include <ctype.h>

class Grid { 
    public:

    typedef char DataType;
    
    Grid(const size_t xr, const size_t xc, const std::string &name) :
      m_nrows(xr), m_ncols(xc), m_matrix(NULL), m_name(name)
    { }
    
    ~Grid() {
        free(m_matrix);
        m_matrix = NULL;
    }
    
    int Fill() {
      std::cerr << m_name << "::Fill()" << std::endl;
      
      if (m_matrix)
        return 0;
      
      const size_t alloc_size =   
         m_nrows * sizeof(*m_matrix) + /* Pointers */
         m_nrows * m_ncols * sizeof(**m_matrix) /* Data */
        ;
          
      errno = 0;
      m_matrix = (DataType **) malloc(alloc_size);   
          
      if (!m_matrix) {
          std::cerr << m_name << ": -ENOMEM; " << errno << ": "
              << strerror(errno) << " ; bytes: " << alloc_size << std::endl;
          return 0;
      }
  
      DataType *offs = (DataType *) &m_matrix[m_nrows]; // Start of data 
      for (size_t i = 0; i < m_nrows; ++i, offs += m_ncols) {
          m_matrix[i] = offs;
      }
          
      for (size_t r = 0; r < m_nrows; ++r) {      
         for (size_t c = 0; c < m_ncols; ++c) { 
           DataType tmp;
           
           while(std::cin >> tmp && isspace(tmp));
           
           if (std::cin.eof()) {
               std::cerr << m_name << ": EOF for row,col= " << r << ", " << c << std::endl;
               return 0;
           }
           
           m_matrix[r][c] = tmp;
         }
      }
        
      return 1;
    }
    
    void Dump() const { 
        for (size_t r = 0; r < m_nrows; ++r) {
            size_t c = 0;
            for (; c < m_ncols; ++c) {
                std::cerr << m_matrix[r][c];
            }
            std::cerr << std::endl;
        }
    }
  
    int Search(const Grid *const needle, const int debug = 0) const {
      std::cerr << m_name << "::Search()" << std::endl;
      
      if (!m_matrix)
        return 0;
      
      const size_t needle_rows = needle->Rows();
      const size_t needle_cols = needle->Cols();
      
      /* If I have 10 rows (#0-9), and the needle has 3 rows (#0-2), then
         a successful search cannot start beyond row 7 (#6) */
      const size_t haystack_max_row = m_nrows - needle_rows;
      const size_t haystack_max_col = m_ncols - needle_cols;
      
      for (size_t hrs = 0; hrs < haystack_max_row; ++hrs) {
        
        for (size_t hcs = 0; hcs < haystack_max_col; ++hcs) {
          size_t nr = 0;
          size_t nc;
          for (; nr < needle_rows; ++nr) { 
            nc = 0;
            for (; nc < needle_cols; ++nc) {
              const size_t mr = hrs + nr;
              const size_t mc = hcs + nc;
              
              if (debug)
                std::cerr << "(m[" << mr << "][" << mc << "]="
                  << m_matrix[mr][mc] 
                  << ") =? (n[" << nr << "][" << nc << "]="
                  << needle->At(nr, nc) << ")"<< std::endl;
              
              if (m_matrix[mr][mc] != needle->At(nr, nc))
                goto next_haystack_column;
              
            } // nc = needle col
            
          } //nr = needle row 
          
          if (nr == needle_rows && nc == needle_cols)
            goto out_success;
          
next_haystack_column:;
        } // hcs = haystack col start
        
      } //hrs = haystrack row start

      return 0;
      
out_success:
      return 1;
    }
  
    size_t Rows() const { return m_nrows; }
    size_t Cols() const { return m_ncols; }
    DataType At(const size_t r, const size_t c) const {
      return m_matrix[r][c];
    }
    
    private:
    const size_t m_nrows;
    const size_t m_ncols;
    DataType **m_matrix;
    
    const std::string m_name;
};


Grid* fetchGrid (const std::string &name) { 
    size_t rows = 0, cols = 0;
    std::cin >> rows;
    std::cin >> cols;
    
    std::cerr << "Got " << name << " dimensions: " << rows << ", " << cols << std::endl;
    if (rows <= 0 || cols <= 0) {
        std::cerr << "Bad input." << std::endl; 
        return NULL;
    }
  
    Grid *grid = new Grid(rows, cols, name);
    if (!grid) {
      return NULL;
    }
  
    if (!grid->Fill()) {
      delete grid;
      return NULL;
    }
   
    return grid;
}


int handle_test_case(size_t tc) { 
  int rv = 0;
  
  Grid *haystack = fetchGrid("haystack");
  if (!haystack) {
    std::cerr << "Didn't allocate haystack for test case " << tc << std::endl;
    return 0;
  }
  
  Grid *needle = fetchGrid("needle");   
  if (!needle) {
    std::cerr << "Didn't allocate needle for test case " << tc << std::endl;
    return 0;
  }
  
  if (haystack->Search(needle, tc == 3))
    rv = 1;

  delete haystack;
  delete needle;
  return rv;
}


int main() {
    size_t test_cases;
    std::cin >> test_cases; 
    
    for (size_t i = 0; i < test_cases; ++i) {
        std::cerr << "============================" << std::endl;
        std::cerr << "Test case #" << i << std::endl;
        int rv = handle_test_case(i);
        if (rv < 0) {
            std::cerr << "ERROR: during test case: " << i << std::endl;
        } else if (rv > 0) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
        
    }
     
    return 0;
}
