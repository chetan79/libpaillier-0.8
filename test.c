#include<stdio.h>
#include<stdlib.h>
#include<gmp.h>
#include<paillier.h>
#include <string.h>
#include<malloc.h>

int main()
{
 int n=1; //degree of polynomial
 int i=0;
 char* str;
 str = malloc(200*sizeof(char));
 paillier_pubkey_t *pub_key=(paillier_pubkey_t *)malloc(sizeof(paillier_pubkey_t));
        paillier_prvkey_t *prv_key=(paillier_prvkey_t *)malloc(sizeof(paillier_prvkey_t));
 //public and private keys generation
 paillier_keygen(4,&pub_key,&prv_key,paillier_get_rand_devrandom);

 for(i=0;i<n;i++)
 {  
  unsigned int p=rand()%20;
  paillier_plaintext_t *ptext = paillier_plaintext_from_ui(p);
  
  
  paillier_ciphertext_t *ctext;
  ctext = paillier_enc(0, pub_key, ptext, paillier_get_rand_devrandom);
  
  //ciphers[i]= (char *) paillier_ciphertext_to_bytes(n, ctext);
  str = (char*)paillier_ciphertext_to_bytes(n,ctext);
  printf("str==[%s]\n",str);
  //printf("cipher[%d] == [%s]\n",i,ciphers[i]);
 }

 return 0;
}
