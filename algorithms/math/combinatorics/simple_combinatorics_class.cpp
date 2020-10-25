/*
* author: pavveu
* task: 
* 		Write simple wrapper for combinatorics objects: 
* 		variation, permutation, combination, 
* 		with and without repetition.
* solution: 
* 		permutation: Precomputed Factorial 
* 		permutation_rep: 
* time:
* 		precomputation: O(N log P)
*	 	permutation_rep: O( | sizes| )
*	 	others: O(1)
* usage: 
* 		combinatorics obj_name( MAX_N, PRIME_MOD );
* 		MAX_N ~ 1'000'000 works fast enough
*
* 		obj_name.combinations(n, k);
* 		obj_name.combinations_rep(n, k);
* 		obj_name.variations(n, k);
* 		obj_name.variations_rep(n, k);
* 		obj_name.permutations(n);
* 		obj_name.permutations_rep({k1, k2, k3, k4, ..., km}); 
* 			where k means size of set of equal elements to i  
* 		obj_name.permutations_rep(n, {k1, k2, k3, .. km});
* 			where |{k1,..}| <= n ( no need to include sets of size 1 in vector )
* 
*/

#include <iostream>
#include <vector>
#include <cassert>

using ll = long long;

class combinatorics {
private:
	int max_n;						// Maximum number that n can be in permutations, calulactions, etc

	ll mod; 						// modulo, all calulations are done modulo mod 
									// MUST BE PRIME

	std::vector<ll> factorial;		// factorial[i] = i * (i - 1) * ... * 1 (mod m)
	std::vector<ll> inv_factorial; 	// inv_factorial = factorial[i]^-1 		(mod m)
public:

	// Constructor
	// O( max_n log prime_mod ) 
	combinatorics(size_t maximum_size, ll prime_modulo) : max_n(maximum_size), 
		mod(prime_modulo), factorial(max_n + 1), inv_factorial(max_n +1) 
	{
		factorial[0] = inv_factorial[0] = 1;
		for (int i = 1; i <= max_n; i++) {
			factorial[i] = (factorial[i - 1] * i) % mod;
			inv_factorial[i] = modular_inverse(factorial[i]);
		}
	}


	// Fermat's Little Theorem   a^(p - 2) == a^-1 ( mod p )
	// O( log n )
	ll modular_inverse(ll a) {
		return bin_pow(a, mod - 2);
	}

	// Calculate a ^ b ( mod m )
	ll bin_pow(ll a, ll b) {
		ll result { 1ll };
		while ( b > 0 ) {
			if ( b & 1 ) result = ( result * a ) % mod;
			a = ( a * a ) % mod;
			b /= 2;
		}
		return result;
	}


	ll permutations(int n) {
		assert(n <= max_n);
		return factorial[n];
	}

	// We pass in vector sizes of repeated groups, sum must be <= n
	ll permutations_rep(int n, const std::vector<int>& sizes) {
		assert(n <= max_n);

		int sum_n = 0;
		for (int k : sizes) sum_n += k;
		assert(sum_n <= n && "sum of repeated sizes is greater than n passed as first argument");

		ll ans = factorial[n];
		for (int k : sizes) ans = ( ans * inv_factorial[k] ) % mod;
		return ans;
	}

	ll permutations_rep(const std::vector<int>& sizes) {
		int sum_n = 0;
		for (int n : sizes) sum_n += n;
		assert(sum_n <= max_n);

		ll ans = factorial[sum_n];

		for (int n : sizes) ans = ( ans * inv_factorial[n] ) % mod;
		return ans;
	}

	ll variations(int n, int k) {
		assert(n <= max_n);
		if ( k > n ) return 0ll;
		else return (factorial[n] * inv_factorial[n - k]) % mod;
	}

	ll variations_rep(int n, int k) {
		assert(n <= max_n);
		return bin_pow(n, k);
	}

	ll combinations(int n, int k) {
		assert(n <= max_n);
		if ( k > n ) return 0ll;
		else return (((factorial[n] * inv_factorial[n - k]) % mod ) * inv_factorial[k]) % mod;
	}

	ll combinations_rep(int n, int k) {
		assert(n <= max_n);
		return combinations(n + k - 1, k); 
	}
};

void go() {
	int max_n = 1'000'000;
	ll prime_mod = 1e9 + 7;
	combinatorics comb(max_n, prime_mod);

	assert(comb.variations(16, 3) == 3360);
	assert(comb.variations(4, 2) == 12);
	assert(comb.variations_rep(2, 8) == 256);
	assert(comb.combinations(16, 3) == 560);
	assert(comb.combinations(5, 166000) == 0);
	assert(comb.combinations_rep(5,3) == 35);
	assert(comb.combinations_rep(3,4) == 15);
	assert(comb.permutations(5) == 120); 
	assert(comb.permutations_rep(3, {2}) == 3); 
	assert(comb.permutations_rep({1, 2}) == 3); 
	assert(comb.permutations_rep(10, {3, 2, 2}) == 151200); 
	assert(comb.permutations_rep({1, 1, 1, 3, 2, 2}) == 151200); 
	assert(comb.permutations_rep(10, {1, 3, 2, 2}) == 151200); 

	std::cout << comb.variations_rep(2, 10) << std::endl;
}

int main() {
	std::ios::sync_with_stdio(false); 
	std::cin.tie(0);
	go();

	return 0;
}
