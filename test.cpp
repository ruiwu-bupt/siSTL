#include <iostream>
#include "si_vector.h"

using namespace std;

int main() {
    test_vector();
}

void test_vector() {
    vector<int> nums(10, 1);
    vector<vector<int> nums2(10, nums);
    vector<vector<int>>::iterator it1;
    vector<int>::iterator it2;
    int sum = 0;
    for (it1 = nums2.begin(); it1 != it1.end(); ++it1) {
        for (it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
            sum += *it2;
        }
    }
    cout << "sum: " << sum << endl;
}