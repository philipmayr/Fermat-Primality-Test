// Fermat Primality Test

#include <stdio.h>
#include <stdlib.h>

int get_random_integer(int exclusive_lower_bound, int exclusive_upper_bound)
{
    return rand() % (exclusive_upper_bound - exclusive_lower_bound + 1) + exclusive_lower_bound;
}

int exponentiate_modularly(int base, int index, int modulus)
{
    int residue = 1;
    
    base %= modulus;
    
    if (base == 0) return 0;
    
    while (index > 0)
    {
        if (index & 1) residue = (residue * base) % modulus;
        
        base = (base * base) % modulus;
        index >>= 1;
    }
    
    return residue;    
}

int test_primality(int prime_candidate)
{
    // 1 < a < p - 1
    int witness_candidate = get_random_integer(1, prime_candidate);
    
    // p is prime if aᵖ⁻¹ ≡ 1 (mod p)
    if (exponentiate_modularly(witness_candidate, prime_candidate - 1, prime_candidate) == 1) return 1;
    else return 0;
}

int main(int argc, char *argv[])
{
    int prime_candidate;
    
    if (argc > 1)
    {
        for (int argument = 1; argument < argc; argument++)
        {
            prime_candidate = atoi(argv[argument]);
            
            if (test_primality(prime_candidate)) printf("%d is a prime number.", prime_candidate);
            else printf("%d is not a prime number.", prime_candidate);

            printf("\n\n");
        }
    }
    
    for (;;)
    {    
        printf("Enter an odd candidate integer to test for primality: ");
        
        // integer input validation
        // https://jackstromberg.com/2013/02/how-to-validate-numeric-integer-input-in-c/
        
        int input, status, temp;

    	status = scanf("%d", &input);
    	
    	while(status != 1)
    	{
            while((temp = getchar()) != EOF && temp != '\n');
            
            printf("Invalid input.");
            printf("\n\n");
            printf("Enter an odd candidate integer to test for primality: ");
            
            status = scanf("%d", &input);
    	}
    
    	prime_candidate = input;
    	
    	if (test_primality(prime_candidate)) printf("%d is a prime number.", prime_candidate);
        else printf("%d is not a prime number.", prime_candidate);
        
        printf("\n\n");
    }
    
    return 0;
}
