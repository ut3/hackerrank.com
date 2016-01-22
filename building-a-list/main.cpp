#include <assert.h>
#include <iostream>
#include <sstream>
#include <algorithm>

void print(const std::string &prefix, /* Output prefix for the current recursion */ 
           const std::string &input,  /* Input character array */
           const std::string::const_iterator start /* Start location of the char array */
          ) {
    for (auto iter = start; iter != input.end(); ++iter) {  
        std::string temp (prefix + *iter);

        std::cout << temp << std::endl;

        print(temp, input, iter + 1);
    }
}

int handle_test_case(size_t test_num) {
    size_t size;
    std::cin >> size;

    std::string input;
    std::cin >> input;
    assert(size == input.size());

    /* Treat input like a vector<char> and sort it */ 
    std::sort(input.begin(), input.end());

    print("", input, input.begin());
}

int main() {
    size_t test_cases;
    std::cin >> test_cases;

    for (size_t i = 0; i < test_cases; ++i) {
        if (handle_test_case(i))
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
