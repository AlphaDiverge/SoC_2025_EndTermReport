#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <numeric>
using namespace std;

/*Problem 1: Prime factorization of each element in an array of numbers*/
vector<vector<int>> primeFactors(vector<int>& queries) {
    vector<vector<int>> result;
    for(int num : queries) {
        vector<int> factors;
        int n = num;

        while((n & 1) == 0) {
            factors.push_back(2);
            n >>= 1;
        }

        for(int i = 3; i*i <= n; i += 2) {
            while(n % i == 0) {
                factors.push_back(i);
                n /= i;
            }
        }
        if(n > 1) factors.push_back(n);
        result.push_back(factors);
    }
    return result;
}




/*Problem 2: Divisors of a */
vector<int> getDivisors(int n) {
    vector<int> divisors;

    for (int i = 1; i * i <= n; ++i) {
        if ((n % i) == 0) {
            divisors.push_back(i);
            if (i != (n / i)) {
                divisors.push_back(n / i);
            }
        }
    }

    sort(divisors.begin(), divisors.end());
    return divisors;
}
//The only place i could implement bit manipulation was in /2 or %2 cases, but this doesnt serve any complete process. Hence I have done this using normal methods.




/*Problem 3: Division of two Integers*/
int divide(int dividend, int divisor) {
    if(dividend == INT_MIN && divisor == -1) return INT_MAX;
    long dvd = labs(dividend), dvs = labs(divisor);
    int res = 0;
    while(dvd >= dvs) {
        long temp = dvs, m = 1;
        while(temp << 1 <= dvd) {
            temp <<= 1;
            m <<= 1;
        }
        dvd -= temp;
        res += m;
    }
    return (dividend > 0) == (divisor > 0) ? res : -res;
}
//This question, I did not do on my own. But it was too interesting to leave out from this report. I found this quite nice and included it still.



/*Problem 4: Minimum number of Bit flips to match two numbers*/
int minFlips(int start, int goal) {
    return __builtin_popcount(start ^ goal);
}
//The _builtin_popcount is a built in function to count the number of 1s in a binary representation




/*Problem 5: Only two integers appear once, rest all twice. Print those 2 nums.*/
//Initially I could only make the standard function w/o bit manipulation, that is a sort and a linear run through the array. I could do a binary search too, with some kind of a odd/even places thing.
//But the solution below is the given solution that I remember that was given, that was quite well made. But, I wrote it from memory.
vector<int> singleNumber(vector<int>& nums) {
    long diff = 0;
    for(int num : nums) diff ^= num;
    diff &= -diff; // Rightmost set bit
    vector<int> res = {0, 0};
    for(int num : nums) {
        if(num & diff) res[0] ^= num;
        else res[1] ^= num;
    }
    sort(res.begin(), res.end());
    return res;
}