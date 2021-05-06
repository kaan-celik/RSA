#include <stdio.h>
#include "rsa.h"
#include <cstring>
#include<time.h>

using namespace std;

mpz_t message, plaintext, ciphertext, phi_n;



void KeyGeneration(PrivateKey*privKey, PublicKey* pubKey)
{		
	gmp_randstate_t state;
	mpz_t p, q;	
	GeneratePublicKey(pubKey,state,seed,p,q);
	GeneratePhi_N(phi_n, p, q);
	GeneratePrivateKey(privKey,phi_n, pubKey->e);

}

int main()
{
	
	PrivateKey privKey; PublicKey pubKey;
	mpz_inits(pubKey.e, pubKey.n, privKey.d, NULL);
	mpz_inits(plaintext, ciphertext, message, NULL);
	string test = "3daygt0fs947lWgfPha15Cs61r6NwjiFP6Gg4WFO3w9H0v15crwdp7dW9Tqu2L4IrCm6b8xjOLXLe1UO2Pv9j2jmi5634g20b0uZT0K6X6zSLAd3p2GCAa5j6VbUqPQq";

	
	unsigned char data_array[128] = { 0 };
	unsigned char message_array[128] = { 0 };
	copy(test.begin(), test.end(), data_array);

	KeyGeneration(&privKey,&pubKey);
	RSA_Decode(plaintext,data_array);
	gmp_printf("Plaintext Value :%Zd\n\n", plaintext);
	RSA_Encryption(ciphertext,plaintext,&pubKey);
	RSA_Decryption(message,ciphertext,&privKey,&pubKey);
	RSA_Encode(message, message_array);

	gmp_printf("Message Value:%Zd\n", message);

	system("Pause");
	return 0;

}
