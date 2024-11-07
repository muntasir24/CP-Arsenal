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

## 3.Sieve of Eratosthenes has a time complexity of O(n log log n), which is efficient for finding all prime numbers up to a given limit n :

```cpp
vector<int> sieve_of_eratosthenes(int n) {
    // Create a boolean vector "prime[0..n]" and initialize all entries as true.
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false; // 0 and 1 are not prime numbers

    for (int p = 2; p * p <= n; ++p) {
        // If prime[p] is still true, it is a prime number
        if (prime[p]) {
            // Mark all multiples of p as false (non-prime)
            for (int i = p * p; i <= n; i += p) {
                prime[i] = false;
            }
        }
    }

    // Collecting all prime numbers
    vector<int> primes;
    for (int p = 2; p <= n; ++p) {
        if (prime[p]) {
            primes.push_back(p);
        }
    }

    return primes;
}
```
```cpp
int main(){

    int n = 10000000; // Example: find primes up to 10 million
    // Get the list of primes
    vector<int> primes = sieve_of_eratosthenes(n);

```
## Find GCD and LCM
```cpp
long long gcd(long long int a, long long int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

// Function to return LCM of two numbers 
long long lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}
```