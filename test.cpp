#include <iostream>
#include "si_vector.h"
#include "si_iterator.h"
#include <vector>
#include <time.h>

using namespace std;

void test_vector() {
    int N = 1000;
    si::vector<int> nums1(10, 0);
    std::vector<int> nums2(10, 0);
    si::vector<si::vector<int> > nums3;
    vector<vector<int> > nums4;
    clock_t t1 = clock();
    for (int i = 0; i < N; i++) {
        nums3.push_back(nums1);
    }
    clock_t t2 = clock();
    for (int i = 0; i < N; i++) {
        nums4.push_back(nums2);
    }
    clock_t t3 = clock();
    cout << "my vector: " << (t2 - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << "std vector: " << (t3 - t2) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}

int main() {
    test_vector();
}