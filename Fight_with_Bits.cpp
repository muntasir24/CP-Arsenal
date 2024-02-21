1.
bool isPowerOfTwo(int n) {
      return n > 0 && (n & n - 1) == 0;
    }
_____________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
2.
long long previous_power_of_two(long long n) {
    int position = 0;

    // Finding the position of the highest set bit
    while (n > 1) {
        n = n >> 1;  // Right shifting the number by 1
        position++; // Incrementing the position
    }

    // Returning the previous power of two
    return (1LL << position);
}
________________________________________________________
.For n = 14, the binary representation is 1110.
.The highest set bit is in position 3 (from the right).
.Therefore, the previous power of two is 2^3 = 8.
___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________________
