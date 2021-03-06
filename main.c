﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eoskeys.h"
#include "eth.h"
#include "etherkeys.h"
#include "bitcoinkeys.h"
#include "bip39.h"
#include "bip32.h"
#include "bignum256.h"
#include "bch.h"

int main(void)
{
	//0、bchaddress test
	btc_to_bch("12c6DSiU4Rq3P4ZxziKxzrL5LmMBrzjrJX");
	
	//1、eth methodId
	char * method_code = (char*)"transfer(address,uint256)";
	char method_id[11] = { 0 };
	get_method_id(method_code, OUT method_id);
	printf("method:%s, methodId:%s\n", method_code, method_id);

	//2、eos address
	const char *priv = "618c79503a3d1476211c8be7876e94e8723596a1e0b0204c050229983c9bfebd";
	char privStr[256] = "PRIV";
	char addrStr[256] = "ADDR";

	eosPrivate2Address(priv, privStr, addrStr);
	printf("private key(%d): %s\nprivate key coded: %s\neos address: EOS%s\n", strlen(priv),priv, privStr, addrStr);

	//3、eth address
	char ethAddrStr[43] = { 0 };
	etherPrivate2Address(priv, ethAddrStr);
	printf("eth address: %s\n", ethAddrStr);

	//4、bitcoin address
	char bitcoinAddr[35] = { 0 };
	bitcoinPrivate2Address(priv, "", bitcoinAddr, 0);
	printf("bitcoin address:%s\n", bitcoinAddr);

	//5、bip39
	const char* words = mnemonic_generate(128);
	printf("generat mnemonic:%s\n",words);

	uint8_t seed[64];
	mnemonic_to_seed(words, "123456", seed, NULL);

	//6、bip32
	HDNode hd;
	hdnode_from_seed(seed, 64, &hd);

	char private_key_hex[67] = {0}, public_key_hex[67] = { 0 };
	bigToHexString(hd.private_key, private_key_hex);
	bigToHexString(hd.public_key, public_key_hex);
	printf("root private key:%s,root public key:%s\n", private_key_hex, public_key_hex);

	for (int i = 0; i < 10; ++i)
	{
		hdnode_private_ckd(&hd, i);
		char private_key_hex[67] = { 0 }, public_key_hex[67] = { 0 };
		bigToHexString(hd.private_key, private_key_hex);
		bigToHexString(hd.public_key, public_key_hex);
		printf("[%d] private key:%s,public key:%s\n", i, private_key_hex, public_key_hex);
	}
	
	getchar();
	return 0;
}
