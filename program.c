// Fermat Primality Test

#include <stdio.h>
#include <stdlib.h>

int find_greatest_common_divisor(int a, int b)
{
    return b ? find_greatest_common_divisor(b, a % b) : a;
}

int get_random_integer(int exclusive_lower_bound, int exclusive_upper_bound)
{
    return rand() % (exclusive_upper_bound - exclusive_lower_bound + 1) + exclusive_lower_bound;
}

int exponentiate_modularly(int base, int index, int modulus)
{
    if (base == 0) return 0;
    if (index == 0) return 1;

    if (base > modulus) base %= modulus;
    if (index == 1) return base;
    
    int residue = 1;
    
    while (index)
    {
        if (index & 1) residue = (residue * base) % modulus;
        
        base = (base * base) % modulus;
        index >>= 1;
    }
    
    return residue;
}

int test_primality(int prime_candidate, int rounds)
{
    if (prime_candidate == 2) return 1;
    if (~prime_candidate & 1 || prime_candidate < 2) return 0;

    int prime_candidate_less_one = prime_candidate - 1;
    
    while (rounds)
    {
        // 1 < a < p - 1
        int witness_candidate = get_random_integer(1, prime_candidate_less_one);
        
        if (find_greatest_common_divisor(prime_candidate, witness_candidate) != 1 ||
            // p is prime if aᵖ⁻¹ ≡ 1 (mod p)
            // p is composite if aᵖ⁻¹ ≢  1 (mod p)
            exponentiate_modularly(witness_candidate, prime_candidate_less_one, prime_candidate) != 1)
            return 0;
            
        rounds--;
    }
    
    return 1;
}

int main(int argc, char *argv[])
{
    int prime_candidate;
    
    if (argc > 1)
    {
        for (int argument = 1; argument < argc; argument++)
        {
            prime_candidate = atoi(argv[argument]);
            
            if (test_primality(prime_candidate, 12)) printf("%d is a prime number.", prime_candidate);
            else printf("%d is not a prime number.", prime_candidate);
            
            printf("\n\n");
        }
    }
    
    for (;;)
    {
        printf("Enter a candidate integer to test its primality: ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        int input, status, buffer;

        status = scanf("%d", & input);
        
        while (status != 1)
        {
              while ((buffer = getchar()) != EOF && buffer != '\n');
              
              printf("Invalid input.");
              printf("\n\n");
              printf("Enter a candidate integer to test its primality: ");
              
              status = scanf("%d", & input);
        }
        
        prime_candidate = input;
        
        if (test_primality(prime_candidate, 12)) printf("%d is a prime number.", prime_candidate);
        else printf("%d is not a prime number.", prime_candidate);
        
        printf("\n\n");
    }
    
    return 0;
}
