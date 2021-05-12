#include <mpir.h>
#include <mpirxx.h>

#define PRIME_LENGTH 512
#define RSA_LENGTH 1024


static unsigned long seed = 311;

typedef struct
{
	mpz_t e;
	mpz_t n;
}PublicKey;

typedef struct
{
	mpz_t d;
}PrivateKey;



void InitRandomState(gmp_randstate_t state)
{
	gmp_randinit_mt(state);
	gmp_randseed_ui(state, seed);
}

void GeneratePrimes(mpz_t prime, gmp_randstate_t state)
{
	mpz_rrandomb(prime, state, PRIME_LENGTH);

	while (!(mpz_millerrabin(prime, 512)))
	{
		gmp_randclear(state);
		seed++;
		InitRandomState(state);
		mpz_rrandomb(prime, state, PRIME_LENGTH);
	}
	gmp_randclear(state);
	seed++;
}

void GenerateN(gmp_randstate_t state,mpz_t n, mpz_t p, mpz_t q)
{
	mpz_inits(p,q,NULL);
	InitRandomState(state);
	GeneratePrimes(p, state);
	gmp_printf("p-value:%Zd\n\n", p);
	InitRandomState(state);
	GeneratePrimes(q, state);
	gmp_printf("q-value:%Zd\n\n", q);
	mpz_mul(n, p, q);
}

void GeneratePhi_N(mpz_t phi_n,mpz_t p, mpz_t q)
{
	mpz_t p_minus1, q_minus1;
	mpz_inits(p_minus1, q_minus1,phi_n, NULL);
	mpz_sub_ui(p_minus1, p, 1);
	mpz_sub_ui(q_minus1, q, 1);
	mpz_mul(phi_n, p_minus1, q_minus1);
	gmp_printf("phi_n-value:%Zd\n\n", phi_n);

	mpz_clears(p, q, p_minus1, q_minus1,NULL);
}
void GeneratePublicKey(PublicKey* pubkey, gmp_randstate_t state, unsigned int seed, mpz_t p, mpz_t q)
{
	mpz_set_ui(pubkey->e, 65537);
	GenerateN(state, pubkey->n, p, q);
	gmp_printf("n-value:%Zd\n\n", pubkey->n);
}

void GeneratePrivateKey(PrivateKey*privkey, mpz_t phi_n, mpz_t e)
{
	mpz_invert(privkey->d,e,phi_n);
	gmp_printf("PrivateKey:%Zd\n\n", privkey->d);
}

void RSA_Decode(mpz_t decode,  unsigned char decode_array[])
{
	mpz_import(decode, 128, 1, sizeof(decode_array[0]), 0, 0, decode_array);
}

void RSA_Encryption(mpz_t ciphertext, mpz_t plaintext,PublicKey* pubkey)
{
	mpz_powm(ciphertext, plaintext, pubkey->e, pubkey->n);		
}

void RSA_Encode(mpz_t encode, unsigned char encode_array[])
{
	mpz_export(encode_array, NULL, 1, sizeof(encode_array[0]), 0, 0, encode);
}

void RSA_Decryption(mpz_t message,  mpz_t ciphertext, PrivateKey* privkey, PublicKey* pubkey)
{
	mpz_powm(message, ciphertext, privkey->d,pubkey->n);
}
