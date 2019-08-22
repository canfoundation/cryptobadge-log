#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
#include <eosio/crypto.hpp>

using namespace eosio;

CONTRACT cryptobaglog : public contract
{
public:
  using contract::contract;
  cryptobaglog(eosio::name receiver, eosio::name code, datastream<const char *> ds) : contract(receiver, code, ds) {}

  /**
     * Push log of certification on blockchain
     * 
     * @param certid: Certification id
     * @param hash: The hash value of certification content
     * @param uri: The link of proof certification 
     * 
     */
  ACTION logcrecert(const std::string& cert_id, const checksum256 &hash, const std::string &uri);

  /**
   * Update log
   */
  ACTION logupdcert(const checksum256 &old_hash, const checksum256 &new_hash, const std::string &new_uri);

  private : TABLE log_cert
  {
    uint64_t id;
    std::string cert_id;
    checksum256 hash;
    std::string uri;

    uint64_t primary_key() const { return id; }
    checksum256 by_hash() const { return hash; }
  };

  typedef eosio::multi_index<"logcert"_n, log_cert,
  indexed_by<"hash"_n, const_mem_fun<log_cert, checksum256, &log_cert::by_hash>>> logcerts;
};
