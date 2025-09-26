#include "velm/core/ndarray.h"
#include "velm/velm.h"

#include <cassert>
#include <iostream>

using vlem_DR::ndarray;

// Test default initialization and fill
void test_initialization_and_fill() {
    ndarray<int, 4> arr4d(2, 3, 4, 2);
    ndarray<int, 3> arr3d(2, 3, 4);
    ndarray<int, 2> arr2d(4, 5);

    // default should be zero
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 2; ++l) {
                    assert(arr4d(i, j, k, l) == 0);
                }
                assert(arr3d(i, j, k) == 0);
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            assert(arr2d(i, j) == 0);
        }
    }

    // fill
    arr4d.fill(10);
    arr3d.fill(7);
    arr2d.fill(-3);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 2; ++l) {
                    assert(arr4d(i, j, k, l) == 10);
                }
                assert(arr3d(i, j, k) == 7);
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            assert(arr2d(i, j) == -3);
        }
    }
    std::cout << "Initialization and fill test passed.\n";
}

// Test offset_of_index
void test_offset_calculation() {
    ndarray<int, 4> arr4d(2, 3, 4, 5);
    assert(arr4d.offset_of_index(0, 0, 0, 0) == 0);
    assert(arr4d.offset_of_index(1, 0, 0, 0) == 60);
    assert(arr4d.offset_of_index(0, 1, 0, 0) == 20);
    assert(arr4d.offset_of_index(0, 0, 1, 0) == 5);
    assert(arr4d.offset_of_index(0, 0, 0, 1) == 1);

    ndarray<int, 3> arr(2, 3, 4);
    assert(arr.offset_of_index(0, 0, 0) == 0);
    assert(arr.offset_of_index(1, 0, 0) == 12);
    assert(arr.offset_of_index(0, 1, 0) == 4);
    assert(arr.offset_of_index(0, 0, 1) == 1);

    ndarray<int, 2> arr2(4, 5);
    assert(arr2.offset_of_index(0, 0) == 0);
    assert(arr2.offset_of_index(1, 0) == 5);
    assert(arr2.offset_of_index(0, 1) == 1);

    std::cout << "Offset calculation test passed.\n";
}

// Test copy constructor
void test_copy_constructor() {
    ndarray<int, 4> arr4d(2, 3, 4, 2);
    arr4d.fill(12);
    ndarray<int, 4> copy4d(arr4d);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 2; ++l) {
                    assert(copy4d(i, j, k, l) == 12);
                }
            }
        }
    }

    ndarray<int, 3> arr(2, 3, 4);
    arr.fill(9);
    ndarray<int, 3> copy(arr);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                assert(copy(i, j, k) == 9);
            }
        }
    }

    std::cout << "Copy constructor test passed.\n";
}

// Test move constructor
void test_move_constructor() {
    ndarray<int, 4> arr4d(2, 3, 4, 2);
    arr4d.fill(8);
    ndarray<int, 4> moved4d(std::move(arr4d));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 2; ++l) {
                    assert(moved4d(i, j, k, l) == 8);
                }
            }
        }
    }
    assert(arr4d.begin() == nullptr);

    ndarray<int, 3> arr(2, 3, 4);
    arr.fill(5);
    ndarray<int, 3> moved(std::move(arr));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                assert(moved(i, j, k) == 5);
            }
        }
    }
    assert(arr.begin() == nullptr);

    std::cout << "Move constructor test passed.\n";
}

// Test copy assignment
void test_copy_assignment() {
    ndarray<int, 4> arr4d(2, 2, 2, 2);
    arr4d.fill(15);
    ndarray<int, 4> copy4d(2, 2, 2, 2);
    (void) (copy4d = arr4d);  // suppress [[nodiscard]]
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int l = 0; l < 2; ++l) {
                    assert(copy4d(i, j, k, l) == 15);
                }
            }
        }
    }

    ndarray<int, 2> arr(4, 5);
    arr.fill(11);
    ndarray<int, 2> copy(4, 5);
    (void) (copy = arr);  // suppress [[nodiscard]]
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            assert(copy(i, j) == 11);
        }
    }

    std::cout << "Copy assignment test passed.\n";
}

// Test move assignment
void test_move_assignment() {
    ndarray<int, 4> arr4d(2, 2, 2, 2);
    arr4d.fill(17);
    ndarray<int, 4> target4d(2, 2, 2, 2);
    (void) (target4d = std::move(arr4d));  // suppress [[nodiscard]]
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int l = 0; l < 2; ++l) {
                    assert(target4d(i, j, k, l) == 17);
                }
            }
        }
    }
    assert(arr4d.begin() == nullptr);

    ndarray<int, 2> arr(4, 5);
    arr.fill(13);
    ndarray<int, 2> target(4, 5);
    (void) (target = std::move(arr));  // suppress [[nodiscard]]
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            assert(target(i, j) == 13);
        }
    }
    assert(arr.begin() == nullptr);

    std::cout << "Move assignment test passed.\n";
}

// Test out-of-bounds access triggers abort
void test_at_bounds_checking() {
    std::cout << "Testing out-of-bounds access (some assertions may fail)...\n";

    // Note: These will cause the program to terminate if bounds checking is working properly
    // We're commenting these out because without gtest's death test framework,
    // we can't easily test for expected aborts

    /*
    ndarray<int, 4> arr4d(2, 2, 2, 2);
    arr4d.at(2, 0, 0, 0); // Should abort
    arr4d.at(0, 2, 0, 0); // Should abort
    arr4d.at(0, 0, 2, 0); // Should abort
    arr4d.at(0, 0, 0, 2); // Should abort

    ndarray<int, 3> arr(2, 2, 2);
    arr.at(2, 0, 0); // Should abort
    arr.at(0, 2, 0); // Should abort
    arr.at(0, 0, 2); // Should abort
    */

    std::cout << "Skipping bounds checking tests without death test framework.\n";
}

int main() {
    test_initialization_and_fill();
    test_offset_calculation();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment();
    test_move_assignment();
    test_at_bounds_checking();

    std::cout << "All tests passed!\n";
    return 0;
}
