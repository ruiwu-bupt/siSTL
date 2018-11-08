#include <iostream>
#include "si_vector.h"
#include "si_map.h"
#include <vector>
#include <map>
#include <time.h>

using namespace std;

// TODO: valgrind checks memory usage
void test_vector(int N) {
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

// void test_list() {
//     int N = 1000;
//     si::vector<int> nums1(10, 0);
//     std::vector<int> nums2(10, 0);
//     si::vector<si::vector<int> > nums3;
//     vector<vector<int> > nums4;
//     clock_t t1 = clock();
//     for (int i = 0; i < N; i++) {
//         nums3.push_back(nums1);
//     }
//     clock_t t2 = clock();
//     for (int i = 0; i < N; i++) {
//         nums4.push_back(nums2);
//     }
//     clock_t t3 = clock();
//     cout << "my vector: " << (t2 - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
//     cout << "std vector: " << (t3 - t2) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
// }

void test_map(int N) {
    si::map<int, int> dict1;
    std::map<int, int> dict2;
    int sum1 = 0, sum2 = 0;
    clock_t t1 = clock();
    for (int i = 0; i < N; i++) {
        dict1[i] = i;
    }
    for (int i = 0; i < N; i++) {
        cout << dict1[i] << " ";
        sum1 += dict1[i];
    }
    cout << endl;
    clock_t t2 = clock();
    for (int i = 0; i < N; i++)
        dict2[i] = i;
    for (int i = 0; i < N; i++)
        sum2 += dict2[i];
    clock_t t3 = clock();
    cout << "my map: " << (t2 - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    cout << "std map: " << (t3 - t2) * 1.0 / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    // si::map<int, int>::iterator it;
    // for (; it != dict1.end(); ++it)
    //     cout << (*it).second << " ";
}
int main() {
    int N = 3;
    // test_vector(N);
    test_map(N);
}