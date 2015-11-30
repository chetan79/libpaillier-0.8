 #include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include<paillier.h>

int main(void)
{

paillier_pubkey_t* pub;//The public key
paillier_prvkey_t* prv;//The private key 

paillier_keygen(1024, &pub, &prv,paillier_get_rand_devurandom);

paillier_ciphertext_t* ca;
paillier_ciphertext_t* cb;
paillier_ciphertext_t* res;

paillier_plaintext_t* a;
paillier_plaintext_t* b;
paillier_plaintext_t* sum;

a=paillier_plaintext_from_ui(45);
b=paillier_plaintext_from_ui(100);

//This is the encryption function 
ca=paillier_enc(0, pub, a, paillier_get_rand_devurandom);
cb=paillier_enc(0, pub, b, paillier_get_rand_devurandom);

res=paillier_create_enc_zero();

paillier_mul(pub, res,ca, cb);

sum=paillier_dec(0, pub, prv, res);

gmp_printf("The sum is : %Zd\n",sum);

return 0;

}
