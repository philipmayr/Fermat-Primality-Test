// Fermat Primality Test

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long integer;

integer find_greatest_common_divisor(integer a, integer b)
{
    return b ? find_greatest_common_divisor(b, a % b) : a;
}

integer get_random_integer(integer inclusive_lower_bound, integer inclusive_upper_bound)
{
    if (inclusive_upper_bound < inclusive_lower_bound) return inclusive_lower_bound;

    integer range = inclusive_upper_bound - inclusive_lower_bound + 1;
    return (integer) (rand() % range) + inclusive_lower_bound;
}

integer exponentiate_modularly(integer base, integer index, integer modulus)
{
    if (modulus < 2) return 0;
    if (index == 0) return 1 % modulus;
    
    base %= modulus;
    
    // if (base < 0) base += modulus;
    if (index == 1) return base;
    
    integer modular_power = 1;
    
    while (index)
    {
        if (index & 1) modular_power = (modular_power * base) % modulus;
        
        base = (base * base) % modulus;
        index >>= 1;
    }
    
    return modular_power;
}

integer test_primality(integer prime_candidate, integer rounds)
{
    if (prime_candidate == 2) return 1;
    if (~prime_candidate & 1 || prime_candidate < 2) return 0;
    
    integer prime_candidate_less_one = prime_candidate - 1;
    
    while (rounds)
    {
        // 1 < a < p - 1
        // if (prime_candidate_less_one < 3) return 0;
        integer witness_candidate = get_random_integer(2, prime_candidate_less_one);
        
        if (find_greatest_common_divisor(prime_candidate, witness_candidate) != 1 ||
            // p is prime if aᵖ⁻¹ ≡ 1 (mod p)
            // p is composite if aᵖ⁻¹ ≢  1 (mod p)
            exponentiate_modularly(witness_candidate, prime_candidate_less_one, prime_candidate) != 1)
            return 0;
            
        rounds--;
    }
    
    return 1;
}

integer main(integer argugment_count, char *arguments[])
{
    srand((unsigned)time(NULL));
    
    integer prime_candidate;
    
    if (argugment_count > 1)
    {
        for (integer argument = 1; argument < argugment_count; argument++)
        {
            prime_candidate = strtoull(arguments[argument], NULL, 10);
            
            if (test_primality(prime_candidate, 12)) printf("%llu is a prime number.", prime_candidate);
            else printf("%llu is not a prime number.", prime_candidate);
            
            printf("\n\n");
        }
    }
    
    for (;;)
    {
        printf("Enter a candidate integereger to test its primality: ");
        
        // integereger input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integereger-input-in-c/
        
        integer input, status, buffer;
        
        status = scanf("%llu", & input);
        
        while (status != 1)
        {
              while ((buffer = getchar()) != EOF && buffer != '\n');
              
              printf("Invalid input.");
              printf("\n\n");
              printf("Enter a candidate integereger to test its primality: ");
              
              status = scanf("%llu", & input);
        }
        
        prime_candidate = input;
        
        if (test_primality(prime_candidate, 12)) printf("%llu is a prime number.", prime_candidate);
        else printf("%llu is not a prime number.", prime_candidate);
        
        printf("\n\n");
    }
    
    return 0;
}
