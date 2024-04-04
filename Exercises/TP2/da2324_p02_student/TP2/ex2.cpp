// By: Gonçalo Leão

bool subsetSum(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    // TODO
    bool candidate[20];

    for(int i = 0; i < n; i++) {
        candidate[i] = false;
    }

    while (true) {
        int sum = 0;
        for(int k = 0; k < n; k++) {
            sum += A[k]*candidate[k];
        }
        if(sum == T) {
            subsetSize = 0;
            for(int k = 0; k < n; k++) {
                if(candidate[k]) {
                    subset[subsetSize++] = A[k];
                }
            }
            return true;
        }
        int index = 0;
        while(candidate[index]) {
            index++;
            if(index == n) break;
        }
        if(index == n) break;
        for(int i = 0; i < index; i++) {
            candidate[i] = false;
        }
        candidate[index] = true;
    }
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSum(A,6,T,subset,subsetSize), false);
}