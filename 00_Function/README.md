 ## 1. Prime number check :
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

## 2. Calculate the  number of divisors for each number from 1 to 𝑁 using a sieve approach :
```cpp
int divisors[n + 1] = {0}; // Initialize the array to store divisor counts with 0s

for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
        divisors[j]++;
    }
}
```
<pre style="font-size: 0.9em;">
Time Complexity: <mark>O(NlogN)</mark>
d[1] = 1  // Divisors: {1}
d[2] = 2  // Divisors: {1, 2}
d[3] = 2  // Divisors: {1, 3}
d[4] = 3  // Divisors: {1, 2, 4}
d[5] = 2  // Divisors: {1, 5}
d[6] = 4  // Divisors: {1, 2, 3, 6}
d[7] = 2  // Divisors: {1, 7}
d[8] = 4  // Divisors: {1, 2, 4, 8}
d[9] = 3  // Divisors: {1, 3, 9}
</pre>
