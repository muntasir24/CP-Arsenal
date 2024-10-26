#Prime number check :

bool isPrime(int n) {
     if (n <= 1)
        return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}
______________________________________________________________________
#find all the divisiors of a number in root n :

vector<ll> divisors;
    for(ll i=2;i*i <= n;i++){
        if(n%i == 0){
            divisors.push_back(i);
            if(n/i != i){
                divisors.push_back(n/i);
            }
        }
    }
_____________________________________________________________________
