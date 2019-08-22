Smart contract for logging certification on blockchain 
----------------------------------------------------------

Version 1.0.0

**1. Why we need this smart contract**

The smart contract is wrriten for logging all hash or user's certification to blockchain.

**2. Functionality**

***Push new log to blockchain `logcrecert`**

To push new log to blockchain

- `@param cert_id`: The id of certificate 
- `@param hash`: The hash of certificate's content
- `@param uri`: The uri which is a link to detail of this certificate

***Update hash, uri value for existed log `logudpcert`**

To update new hash, or new uri for existed log on bloclchain

- `@param old_hash`: Old value of hash which we are wanting to find to update
- `@param new_hash`: The new value of hash which we want to update
- `@param new_uri`: The new value of uri which we want to update

### Get started 
----------------------------------------------------------

#### Setup environment

* Create an account name to deploy smart contract : crptbadgelog

* Endpoint network for testing

````bash
https://jungle2.cryptolions.io:443 
````

##### Build & deploy smart contract

**Go to crypto_log directory then do flowing steps:**

1.  Build smart contract

````bash
$ eosio-cpp -abigen -I include -contract cryptobaglog -o cbadgelog.wasm src/cbadgelog.cpp
````

2. Deploy to jungle test net

````bash
$ cleos -u https://jungle2.cryptolions.io:443 set contract crptbadgelog . cryptobaglog.wasm cryptobaglog.abi
````

3. Deploy to mainnet

* On your terminal

  - Create a wallet

````bash
$ cleos -u https://jungle2.cryptolions.io:443  wallet create -n [your wallet name] --to-console
````

  - Push your private key of to this wallet

````bash
$ cleos wallet import --private-key=[your private key]  -n [your wallet name] --to-console
````

  - Create keys for log permission

````bash
$ cleos -u https://jungle2.cryptolions.io:443  wallet create_key -n [your wallet name]
````

  - Add `pushlog` permision to your account

````bash
$ cleos -u https://jungle2.cryptolions.io:443  set account permission [your account] pushlog '{"threshold": 1,"keys": [{"key": "[your pushlog public key]","weight": 1}]}' "active" -p [your account]

$ cleos -u https://jungle2.cryptolions.io:443  set action permission [your account] [your account] logcrecert pushlog

$ cleos -u https://jungle2.cryptolions.io:443  set action permission [your account] [your account] logupdcert pushlog

````

* Deploy smart contract to EOS mainnet

  - Buy RAM for your smart contract

````bash
$ cleos -u https://jungle2.cryptolions.io:443  system buyram [your account name] [your account name] "[number of EOS] EOS"
````

  - Push to mainet

````bash
$ cleos -u https://jungle2.cryptolions.io:443  set contract [your account name] . cryptobaglog.wasm cryptobaglog.abi -p [your account name]@pushlog
````

#### Testing on testnet only

**1. Prepare input**

This is a certification in JSON format

```
{
  "id": "Q2VydGlmaWNhdGU6MDAwMDAwMDAwMDAwMTAwOA==",
  "state": "CERTIFIED",
  "winnerName": "winnerName",
  "issuedAt": "2019-02-14T10:33:50+00:00",
  "expiresAt": null,
  "evidence": "CryptoBadge verified that winnerName owns a/an Branch Name email on 02/14/2019",
  "revokedAt": null,
  "revocationReason": null,
  "resourceUrl": "https://cryptobadge.app/@CryptoBadge/0000000000001013/0000000000001008",
  "badge": {
    "id": "QmFkZ2U6MDAwMDAwMDAwMDAwMTAxMw==",
    "name": "Branch Name",
    "imageUrl": "https://s3-us-west-2.amazonaws.com/crypto-badge-static-prod/assets/university-imgs/Univ_battle_0000227_Korea%20University.png",
    "expiredImageUrl": null,
    "revokedImageUrl": null,
    "resourceUrl": "https://cryptobadge.app/@CryptoBadge/0000000000001013",
    "path": "0000000000001013",
    "description": "This badge is presented to the school email holders of Branch Name.",
    "criteria": "Students, alumni, or faculty members who have a Branch Name email address can win the badge. Verify your Branch Name email by clicking on the Claim button.",
    "creatorName": "CryptoBadge"
}
```

The hash value

```
572bf16949ce9e77b9ccb68b3d41250cc63b9485cd728c5ca6422a1bb826ae06
```
The uri

```
https://cryptobadge.app/@CryptoBadge/0000000000001013/0000000000001008

```

The certification Id
```
0000000000001008
```

**2. Push log to blockchain**

````bash
$ cleos -u https://jungle2.cryptolions.io:443 push action crptbadgelog logcrecert '["0000000000001007","572bf16949ce9e77b9ccb68b3d41250cc63b9485cd728c5ca6422a1bb826ae06","https://cryptobadge.app/@CryptoBadge/0000000000001013/0000000000001008"]' -p crptbadgelog

$ cleos -u https://jungle2.cryptolions.io:443 push action crptbadgelog logcrecert '["Q2VydGlmaWNhdGU6aW5jcmVtZW50YWwgaWQ=","fe1f00d963d14536e7b1c5c5a0551e7f394c8fc19315341338d2d98138abcbeb","https://cryptobadgeapp.firebaseapp.com/@CryptoBadge/0000000000000638/0000000000003052"]' -p crptbadgelog

$ cleos -u https://jungle2.cryptolions.io:443 push action crptbadgelog logcrecert '["K2TydGlmaWNhdGU6aW5jcmVtZW50YWwgaWZ=","572bf16949ce9e77b9ccb68b3d41250cc63b9485cd728c5ca6422a1bb826ae05","https://cryptobadge.app/@CryptoBadge/0000000000001014/0000000000001009"]' -p crptbadgelog

$ cleos -u https://jungle2.cryptolions.io:443 push action crptbadgelog logcrecert '["AQlydGlmaWNhdGU6aW5jcmVtZW50YWwgaW==","1a49ab2eb8416ed8a2645173f89fcea2a0232615baa5dab86340f58b5d40c221","https://cryptobadgeapp.firebaseapp.com/@CryptoBadge/0000000000000635/0000000000003051"]' -p crptbadgelog


Push the same hash

$ cleos -u https://jungle2.cryptolions.io:443 push action crptbadgelog logcrecert '["0000000000001007","572bf16949ce9e77b9ccb68b3d41250cc63b9485cd728c5ca6422a1bb826ae06","https://cryptobadge.app/@CryptoBadge/0000000000001013/0000000000001008"]' -p crptbadgelog

`
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: This hash has been existed!
pending console output:
`

````

**3. Update a log**

````bash
cleos -u https://jungle2.cryptolions.io:443 push action crptbadgelog logupdcert '["572bf16949ce9e77b9ccb68b3d41250cc63b9485cd728c5ca6422a1bb826ae05","dc95f0879f8eff302317a1407916ccff97abf8c9bc7f3fa03b66384ef6497c5d","https://cryptobadgeapp.firebaseapp.com/@CryptoBadge/0000000000000734/0000000000004051"]' -p crptbadgelog
````

**4. Check the result**

Go to block explorer 

```
https://jungle.bloks.io/account/cryptobaglog?loadContract=true&tab=Tables&table=logcert&account=crptbadgelog&scope=crptbadgelog&limit=100


$ cleos -u https://jungle2.cryptolions.io:443 get table crptbadgelog crptbadgelog logcert
{
  "rows": [{
      "id": 0,
      "cert_id": "0000000000001007",
      "hash": "572bf16949ce9e77b9ccb68b3d41250cc63b9485cd728c5ca6422a1bb826ae06",
      "uri": "https://cryptobadge.app/@CryptoBadge/0000000000001013/0000000000001008"
    },{
      "id": 1,
      "cert_id": "Q2VydGlmaWNhdGU6aW5jcmVtZW50YWwgaWQ=",
      "hash": "fe1f00d963d14536e7b1c5c5a0551e7f394c8fc19315341338d2d98138abcbeb",
      "uri": "https://cryptobadgeapp.firebaseapp.com/@CryptoBadge/0000000000000638/0000000000003052"
    },{
      "id": 2,
      "cert_id": "K2TydGlmaWNhdGU6aW5jcmVtZW50YWwgaWZ=",
      "hash": "dc95f0879f8eff302317a1407916ccff97abf8c9bc7f3fa03b66384ef6497c5d",
      "uri": "https://cryptobadgeapp.firebaseapp.com/@CryptoBadge/0000000000000734/0000000000004051"
    },{
      "id": 3,
      "cert_id": "AQlydGlmaWNhdGU6aW5jcmVtZW50YWwgaW==",
      "hash": "1a49ab2eb8416ed8a2645173f89fcea2a0232615baa5dab86340f58b5d40c221",
      "uri": "https://cryptobadgeapp.firebaseapp.com/@CryptoBadge/0000000000000635/0000000000003051"
    }
  ],
  "more": false
}
```

**5. Example for get by hash manually**

Format using little endian format

```
fe1f00d963d14536e7b1c5c5a0551e7f 394c8fc19315341338d2d98138abcbeb

--> convert to little endian
7f1e55a0c5c5b1e73645d163d9001ffe ebcbab3881d9d23813341593c18f4c39

get table second index by 7f1e55a0c5c5b1e73645d163d9001ffeebcbab3881d9d23813341593c18f4c39

$ cleos -u https://jungle2.cryptolions.io:443 get table crypbadgelom crypbadgelom logcert --index 2 --key-type sha256 --upper 7f1e55a0c5c5b1e73645d163d9001ffeebcbab3881d9d23813341593c18f4c39 --lower 7f1e55a0c5c5b1e73645d163d9001ffeebcbab3881d9d23813341593c18f4c39
{
  "rows": [{
      "id": 1,
      "cert_id": "0000000000001008",
      "hash": "fe1f00d963d14536e7b1c5c5a0551e7f394c8fc19315341338d2d98138abcbeb",
      "uri": "https://cryptobadgeapp.firebaseapp.com/@CryptoBadge/0000000000000638/0000000000003052"
    }
  ],
  "more": false
}
```