#include <iostream>
#include "si_vector.h"
#include "si_map.h"
#include "si_list.h"
#include <vector>
#include <map>
#include <list>
#include <time.h>

using namespace std;

float t(clock_t t1, clock_t t2) {
    return (t2 - t1) * 1.0 / CLOCKS_PER_SEC;
}
void log(string descrip, int N, clock_t t1, clock_t t2) {
    cout << "\t" << descrip << " ";
    float tm = t(t1, t2)/N;
    if (tm <= 1e-6)
        cout << tm*1e9 << "ns" << endl;
    else if (tm <= 1e-3)
        cout << tm*1e6 << "us" << endl;
    else if (tm <= 1)
        cout << tm*1e3 << "ms" << endl;
    else
        cout << tm << "s" << endl;
}
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
    cout << "my vector:" << endl;
    log("push_back N size 10 vector", 1, t1, t2);
    cout << "std vector:" << endl;
    log("push_back N size 10 vector", 1, t2, t3);
}

void test_list(int N) {
    // si::vector<int> nums1(10, 0);
    // std::vector<int> nums2(10, 0);
    // si::list<si::vector<int> > nums3;
    // list<vector<int> > nums4;
    si::list<int> nums3;
    list<int> nums4;
    clock_t t1 = clock();
    for (int i = 0; i < N; i++) {
        nums3.push_back(i);
    }
    clock_t t2 = clock();
    for (int i = 0; i < N; i++) {
        nums4.push_back(i);
    }
    clock_t t3 = clock();
    cout << "my list:" << endl;
    log("push_back", 1, t1, t2);
    cout << "std list:" << endl;
    log("push_back", 1, t2, t3);
}

void test_map(int N) {
    si::map<int, int> dict1;
    std::map<int, int> dict2;
    int sum1 = 0, sum2 = 0;
    clock_t t1 = clock();
    for (int i = 0; i < N; i++) {
        dict1[i] = i;
    }
    clock_t t2 = clock();
    si::map<int, int>::iterator it = dict1.begin();
    for (; it != dict1.end(); ++it) {
        // cout << (*it).second << " ";
        sum1 += (*it).second;
    }
    clock_t t3 = clock();
    for (int i = 0; i < N; i++)
        dict2[i] = i;
    clock_t t4 = clock();
    std::map<int, int>::iterator it2 = dict2.begin();
    for (; it2 != dict2.end(); ++it2) {
        // cout << (*it).second << " ";
        sum2 += (*it2).second;
    }
    clock_t t5 = clock();
    if (sum1 != sum2)
        cout << "traverse error" << endl;
    cout << "my map:" << endl;
    log("build tree: ", 1, t1, t2);
    log("traverse per element: ", N, t2, t3);
    cout << "std map:" << endl;
    log("build tree: ", 1, t3, t4);
    log("traverse per element: ", N, t4, t5);
    // si::map<int, int>::iterator it;
    // for (; it != dict1.end(); ++it)
    //     cout << (*it).second << " ";
}
int main() {
    int N = 1000000;
    cout << "input scale N = " << N << endl;
    // test_vector(N);
    // test_map(N);
    test_list(N);
}