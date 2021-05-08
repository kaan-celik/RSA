# RSA
Implementation of 1024 Bit RSA
If you want the use or debug the code, you should have MPIR/GMP library. If you haven't, you can download from links given below;

For MPIR : https://mpir.org/downloads.html

For GMP: https://gmplib.org/


# Tips
In the progam, 512 bit p and q values randomly generates until they pass the MillerRabin Primality test (for 512 iteration). Therefore it might be take a while. If you have your own prime values. You can modify the code and remove the prime generation partition. If you want to reduce the time of prime generation you can modify "iteration count" or "seed" variables.

If you interest only integer values for encryption and decryption, you can remove the encode decode methods from the program.


