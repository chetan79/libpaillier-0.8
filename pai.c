#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
#include<paillier.h>
#include <string.h>
#include<math.h>

int main()
{
 int n=4; //degree of polynomial
 paillier_pubkey_t *pub_key=(paillier_pubkey_t *)malloc(sizeof(paillier_pubkey_t));
        paillier_prvkey_t *prv_key=(paillier_prvkey_t *)malloc(sizeof(paillier_prvkey_t));
 //public and private keys generation
 paillier_keygen(4,&pub_key,&prv_key,paillier_get_rand_devrandom);
 long int socalledn= pub_key->n;
 printf("size : %ld\n",socalledn);

 int* myint = (int *)malloc(sizeof(int)*n);
 int i=0;

// generate plaintext and encrypt.
 for(i=0;i<n;i++)
 {  
  unsigned int p=rand()%20;
  paillier_plaintext_t *ptext = paillier_plaintext_from_ui(p);
  
  
  paillier_ciphertext_t *ctext;
  //printf("Starting Encryption");
  ctext = paillier_enc(0, pub_key, ptext, paillier_get_rand_devrandom);
  
  myint[i]= (int *) paillier_ciphertext_to_bytes(n, ctext);
  printf("Ending Encryption");
 }

  printf("\n");
 //print ciphertext
 for (i=0;i<n;i++)
 { 
  printf("Cipher text is %d\n",myint[i]);
 }

printf("\nPart B starting");

// Next part
long int sum;
int j;
for (j=0;j<n;j++)
{
 int x_o = 2;
 int var = pow(x_o,j);
 long int val= pow(myint[j],var);
 printf("val---> %ld\n",val);
 sum = val % ((socalledn)*(socalledn));
}

sum = sum % ((socalledn)*(socalledn));
printf("sum %ld\n",sum);
char* demo = (char*)&sum;
paillier_ciphertext_t *sum_cipher = paillier_ciphertext_from_bytes(demo, 32);

printf("\n Part C starting");
int ran = rand();
paillier_plaintext_t *ptext_ran = paillier_plaintext_from_ui(ran);
paillier_ciphertext_t *ctext_ran;
ctext_ran = paillier_enc(0, pub_key, ptext_ran, paillier_get_rand_devrandom);
paillier_ciphertext_t * result;
result = paillier_create_enc_zero();
paillier_mul(pub_key, result, sum_cipher, ctext_ran);
paillier_plaintext_t * mul;
mul = paillier_dec(0, pub_key, prv_key, result);
gmp_printf("The final answer:%Zd\n", mul);
int final= mul-ran;
printf("-random is %d\n",final);
return 0;
}
