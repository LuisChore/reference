#include <bits/stdc++.h>
using namespace std;

typedef long long lli;

const int MOD = 1e9 + 7;
const int N = 1e5 + 5;




vector<lli> fact,inv;
vector<int> sieve;
vector<int> primes;

lli exp_bin(lli b,lli e,lli mod = MOD){
  lli r = 1LL;
  while(e){
    if(e&1){
      r = r * b % mod;
    }
    e>>=1LL;
    b = (b * b) % mod;
  }
  return r;
}


void factorials(int n){
  fact.assign(n+1,1);
  for(lli i=2;i<=n;i++){
    fact[i] = (i * fact[i-1]) % MOD;
  }
}


lli inv_mod(int n){
  return exp_bin(fact[n],MOD - 2);
}


void inverses(int n){
  inv.assign(n+1,1);
  inv[n] = inv_mod(n);
  for(lli i=n-1;i>=0;i--){
    inv[i] = (inv[i+1] * (i+1LL)) % MOD;
  }
}


lli nck(int n,int k){
  return (fact[n] * inv[n-k] % MOD) * inv[k] % MOD;
}














//********************** PRIMES  ************************/
//         π(n) = n /(ln(n) - 1)


void compute_sieve(int n){
  sieve.assign(n+1,0);
  for(int i=4;i<=n;i+=2){
    sieve[i] = 2;
  }
  for(int i=3;i*i<=n;i+=2){
    if(!sieve[i]){
      for(int j=i*i;j<=n;j+=i*2){
        if(!sieve[j])
          sieve[j] = i;
      }
    }
  }
  primes.push_back(2);
  for(int i=3;i<=n;i++){
    if(!sieve[i])
      primes.push_back(i);
  }
}


// <= 10^14
bool is_prime(lli n){
  if(n<=10000000){
    return (sieve[n] == 0);
  }

  for(auto u: primes){
    lli temp = (lli)u*u;
    if(temp>n)
      break;
    if(n%u == 0){
      return false;
    }
  }
  return true;
}

vector<pair<lli,int>> prime_factors(lli n){
  if(n<=10000000){
    vector<pair<lli,int>> ans;
    while(sieve[n]){
      lli number = sieve[n];
      int counter = 0;
      while(n%number == 0){
        counter++;
        n/= number;
      }
      ans.push_back({number,counter});
    }
    if(n != 1){
      ans.push_back({n,1});
    }
    return ans;
  }
  vector<pair<lli,int>> ans;
  for(auto u: primes){
    lli temp = (lli)u*u;
    if(temp>n)
      break;
    if(n%u == 0){
      int counter = 0;
      while(n%u == 0){
        counter++;
        n/=u;
      }
      ans.push_back({u,counter});
    }
  }
  if(n!=1){
    ans.push_back({n,1});
  }
  return ans;
}










lli gcd(lli a,lli b){
  a = abs(a);
  b = abs(b);
  while(b){
    lli r = a%b;
    a = b;
    b = r;
  }
  return a;
}

lli lcm(lli a,lli b){
  return a*(b/gcd(a,b));
}




int main(){

  lli n,m;
  cin >> n >> m;
  cout << gcd(n,m) << "\n";
  cout << lcm(n,m) << "\n";
  cout << __gcd(n,m) << "\n";
}
