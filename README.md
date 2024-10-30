# Prime number check :

```cpp
bool isPrime(int n) {
     if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}
```
__________________________________________________________________

    efficient way to calculate the number of divisors for each number from 1 to 𝑁 using a sieve approach. 

<pre>
const int N = 1e6 + 9; // a number larger than 100 * 100 * 100
int d[N] = {0}; // To store number of divisors for each number
for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
        d[j]++;
    }
</pre>
..................................................................
Time Complexity: O(NlogN), which is efficient for this range.
d[1] = 1  // Divisors: {1}
d[2] = 2  // Divisors: {1, 2}
d[3] = 2  // Divisors: {1, 3}
d[4] = 3  // Divisors: {1, 2, 4}
d[5] = 2  // Divisors: {1, 5}
d[6] = 4  // Divisors: {1, 2, 3, 6}
d[7] = 2  // Divisors: {1, 7}
d[8] = 4  // Divisors: {1, 2, 4, 8}
d[9] = 3  // Divisors: {1, 3, 9}\\\\\
____________________________________________________________________
