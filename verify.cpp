#include <iostream>
#include "interval_map.hpp"  // Include the header file of interval_map

// Function to print a message if a test case fails
void printTestResult(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << testName << " passed" << std::endl;
    } else {
        std::cout << testName << " failed" << std::endl;
    }
}

// Test case for empty interval
void testEmptyInterval() {
    interval_map<int, char> M('A');
    M.assign(1, 2, 'B');
    if (M.m_map.size() == 1 && M.m_map[1] == 'B')
        std::cout << "EmptyInterval passed" << std::endl;
    else
        std::cout << "EmptyInterval failed" << std::endl;

    M.assign(1, 1, 'C');
    if (M.m_map.size() == 0)
        std::cout << "EmptyInterval passed" << std::endl;
    else
        std::cout << "EmptyInterval failed" << std::endl;
}

// Test case for overlapping intervals
void testOverlappingIntervals() {
    interval_map<int, char> M('A');
    M.assign(1, 3, 'B');
    M.assign(2, 4, 'C');
    if (M.m_map.size() == 2 &&
        M.m_map[1] == 'B' && M.m_map[2] == 'C' &&
        M.m_map[3] == 'B' && M.m_map[4] == 'C')
        std::cout << "OverlappingIntervals passed" << std::endl;
    else
        std::cout << "OverlappingIntervals failed" << std::endl;
}

// Test case for assigning a value to a single key
void testSingleKey() {
    interval_map<int, char> M('A');
    M.assign(1, 1, 'B');
    if (M.m_map.size() == 1 && M.m_map[1] == 'B')
        std::cout << "SingleKey passed" << std::endl;
    else
        std::cout << "SingleKey failed" << std::endl;
}

// Test case for assigning a value to a key outside the existing intervals
void testKeyOutsideIntervals() {
    interval_map<int, char> M('A');
    M.assign(1, 3, 'B');
    M.assign(3, 6, 'A');
    M.assign(7, 8, 'C');
    if (M.m_map.size() == 3 &&
        M.m_map[1] == 'B' && M.m_map[2] == 'A' &&
        M.m_map[3] == 'A' && M.m_map[4] == 'A' &&
        M.m_map[5] == 'A' && M.m_map[6] == 'A' &&
        M.m_map[7] == 'C' && M.m_map[8] == 'C')
        std::cout << "KeyOutsideIntervals passed" << std::endl;
    else
        std::cout << "KeyOutsideIntervals failed" << std::endl;
}

// Test case for assigning a value to a key inside an existing interval
void testKeyInsideInterval() {
    interval_map<int, char> M('A');
    M.assign(1, 3, 'B');
    M.assign(3, 6, 'A');
    M.assign(2, 4, 'C');
    if (M.m_map.size() == 3 &&
        M.m_map[1] == 'B' && M.m_map[2] == 'C' &&
        M.m_map[3] == 'A' && M.m_map[4] == 'C')
        std::cout << "KeyInsideInterval passed" << std::endl;
    else
        std::cout << "KeyInsideInterval failed" << std::endl;
}

int main() {
    // Run test cases
    testEmptyInterval();
    testOverlappingIntervals();
    testSingleKey();
    testKeyOutsideIntervals();
    testKeyInsideInterval();

    return 0;
}
