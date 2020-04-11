/*
 * Copyright 2020 J. Rick Ramstetter
 * rick.ramstetter@gmail.com
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

#include <bits/stdc++.h>
#include <limits>
#include <stdexcept>
#include <numeric>

using namespace std;

vector<string> split_string(string);

// return swaps made
int selectionSort(vector<int>&  arr, const int depth, const int startIdx)
{
    auto log = [&depth, &startIdx] (vector<int>& arr) -> ostream&
    { 
        for (int i = 0; i < depth; ++i)
        {
            cerr << "-";
        }
        cerr << "[startIdx=" << to_string(startIdx) + ", arr={";
        for (int a : arr)
            cerr << to_string(a) + ", ";
        cerr << "}] ";
        return cerr;
    };
    auto swap = [](vector<int> &arr, int one, int two)
    {
        int tmp = arr[two];
        arr[two] = arr[one];
        arr[one] = tmp;
    };
    auto isSorted = [](vector<int> &arr, int endIdx) -> bool
     {
        // --[Depth=2, arr={1, 2, 4, 3, 5, }] Valid solution till idx 3
        for (int i = 1; i <= endIdx; ++i)
            if (arr.at(i - 1) > arr.at(i))
                return false;
        return true;
    };
    
    
    // base case
    if (startIdx >= arr.size())
    {
        //log(arr) << "Base case" << endl;
        return 0;
    }

    // Find any potentital swap candidate
    vector<int> ltIdx;
    for (int i = startIdx; i < arr.size(); ++i)
    {
        if (arr.at(i) < arr.at(startIdx))
        {
         
           // log(arr) <<  "arr(" << i << ")=" << arr.at(i)<< " LT arr(" << startIdx << ")=" << arr.at(startIdx) << endl;
            ltIdx.push_back(i); 
        }
    }
    
    // The array is sorted from 0..startIdx
    if (ltIdx.empty())
    {
        //log(arr) <<  "Empty LT" <<endl;
        return selectionSort(arr, depth + 1, startIdx + 1);
    }
    
    // For each ltIdx, see if it can be swapped to startIdx for a valid solution
    map<int, vector<int> > swapMap;
    for (auto i = ltIdx.begin(); i != ltIdx.end(); ++i)
    {
        const int& idx = *i;
        vector<int> arrCopy (arr);

        //log(arrCopy) << "Swap " << idx << " and " << startIdx << endl;
        swap(arrCopy, idx, startIdx);
        int swaps = selectionSort(arrCopy, depth + 1, startIdx + 1);
            
        if (swaps != -1 && isSorted(arrCopy, startIdx + 1))
        {   
            //log(arrCopy) << "Valid solution till idx " << startIdx + 1<< endl;
            swapMap.insert(std::make_pair(swaps, arrCopy));
            continue;
        }
        
               
       // log(arrCopy) << "Invalid; discard" << endl;
    }

    if (swapMap.empty())
    {
        // No ltIdx can be swapped to startIdx to cretae a valid solution
        return -1;
    }
    
      arr = swapMap.begin()->second;
    //log(arr) << "Return swaps " << 1 + swapMap.begin()->first << endl;
    return 1 + swapMap.begin()->first;
}


// Complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {
    int swaps = selectionSort(arr, 0, 0);
    return swaps;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);
    
    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int res = minimumSwaps(arr);

    fout << res << "\n";
    
    
    fout.close();

    return 0;
}

vector<string> split_string(string input_string)
 {

string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());
       while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';
    
    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }
    
    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
        
