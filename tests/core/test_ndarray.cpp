#include "velm/core/types/ndarray.h"

#include <gtest/gtest.h>

using vlem_DR::ndarray;

// Test default initialization and fill
TEST(NdArrayTest, InitializationAndFill) {
    ndarray<int, 4> arr4d(2, 3, 4, 2);
    ndarray<int, 3> arr3d(2, 3, 4);
    ndarray<int, 2> arr2d(4, 5);

    // default should be zero
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 2; ++l) {
                    EXPECT_EQ(arr4d(i, j, k, l), 0);
                }
                EXPECT_EQ(arr3d(i, j, k), 0);
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            EXPECT_EQ(arr2d(i, j), 0);
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
                    EXPECT_EQ(arr4d(i, j, k, l), 10);
                }
                EXPECT_EQ(arr3d(i, j, k), 7);
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            EXPECT_EQ(arr2d(i, j), -3);
        }
    }
}

// Test offset_of_index
TEST(NdArrayTest, OffsetCalculation) {
    ndarray<int, 4> arr4d(2, 3, 4, 5);
    EXPECT_EQ(arr4d.offset_of_index(0, 0, 0, 0), 0);
    EXPECT_EQ(arr4d.offset_of_index(1, 0, 0, 0), 60);
    EXPECT_EQ(arr4d.offset_of_index(0, 1, 0, 0), 20);
    EXPECT_EQ(arr4d.offset_of_index(0, 0, 1, 0), 5);
    EXPECT_EQ(arr4d.offset_of_index(0, 0, 0, 1), 1);

    ndarray<int, 3> arr(2, 3, 4);
    EXPECT_EQ(arr.offset_of_index(0, 0, 0), 0);
    EXPECT_EQ(arr.offset_of_index(1, 0, 0), 12);
    EXPECT_EQ(arr.offset_of_index(0, 1, 0), 4);
    EXPECT_EQ(arr.offset_of_index(0, 0, 1), 1);

    ndarray<int, 2> arr2(4, 5);
    EXPECT_EQ(arr2.offset_of_index(0, 0), 0);
    EXPECT_EQ(arr2.offset_of_index(1, 0), 5);
    EXPECT_EQ(arr2.offset_of_index(0, 1), 1);
}

// Test copy constructor
TEST(NdArrayTest, CopyConstructor) {
    ndarray<int, 4> arr4d(2, 3, 4, 2);
    arr4d.fill(12);
    ndarray<int, 4> copy4d(arr4d);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 2; ++l) {
                    EXPECT_EQ(copy4d(i, j, k, l), 12);
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
                EXPECT_EQ(copy(i, j, k), 9);
            }
        }
    }
}

// Test move constructor
TEST(NdArrayTest, MoveConstructor) {
    ndarray<int, 4> arr4d(2, 3, 4, 2);
    arr4d.fill(8);
    ndarray<int, 4> moved4d(std::move(arr4d));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 2; ++l) {
                    EXPECT_EQ(moved4d(i, j, k, l), 8);
                }
            }
        }
    }
    EXPECT_EQ(arr4d.begin(), nullptr);

    ndarray<int, 3> arr(2, 3, 4);
    arr.fill(5);
    ndarray<int, 3> moved(std::move(arr));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                EXPECT_EQ(moved(i, j, k), 5);
            }
        }
    }
    EXPECT_EQ(arr.begin(), nullptr);
}

// Test copy assignment
TEST(NdArrayTest, CopyAssignment) {
    ndarray<int, 4> arr4d(2, 2, 2, 2);
    arr4d.fill(15);
    ndarray<int, 4> copy4d(2, 2, 2, 2);
    (void) (copy4d = arr4d);  // suppress [[nodiscard]]
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int l = 0; l < 2; ++l) {
                    EXPECT_EQ(copy4d(i, j, k, l), 15);
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
            EXPECT_EQ(copy(i, j), 11);
        }
    }
}

// Test move assignment
TEST(NdArrayTest, MoveAssignment) {
    ndarray<int, 4> arr4d(2, 2, 2, 2);
    arr4d.fill(17);
    ndarray<int, 4> target4d(2, 2, 2, 2);
    (void) (target4d = std::move(arr4d));  // suppress [[nodiscard]]
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int l = 0; l < 2; ++l) {
                    EXPECT_EQ(target4d(i, j, k, l), 17);
                }
            }
        }
    }
    EXPECT_EQ(arr4d.begin(), nullptr);

    ndarray<int, 2> arr(4, 5);
    arr.fill(13);
    ndarray<int, 2> target(4, 5);
    (void) (target = std::move(arr));  // suppress [[nodiscard]]
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            EXPECT_EQ(target(i, j), 13);
        }
    }
    EXPECT_EQ(arr.begin(), nullptr);
}

// Test out-of-bounds access triggers abort
TEST(NdArrayDeathTest, AtThrowsAbort) {
    ndarray<int, 4> arr4d(2, 2, 2, 2);
    EXPECT_DEATH((void) arr4d.at(2, 0, 0, 0), "");
    EXPECT_DEATH((void) arr4d.at(0, 2, 0, 0), "");
    EXPECT_DEATH((void) arr4d.at(0, 0, 2, 0), "");
    EXPECT_DEATH((void) arr4d.at(0, 0, 0, 2), "");

    ndarray<int, 3> arr(2, 2, 2);
    EXPECT_DEATH((void) arr.at(2, 0, 0), "");
    EXPECT_DEATH((void) arr.at(0, 2, 0), "");
    EXPECT_DEATH((void) arr.at(0, 0, 2), "");
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
