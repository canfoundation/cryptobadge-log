#include <cbadgelog.hpp>

ACTION cryptobaglog::logcrecert(const std::string &cert_id,
                                const checksum256 &hash,
                                const std::string &uri)
{
  require_auth(get_self());
  
  logcerts log_table(get_self(), get_self().value);
  auto hash_itr = log_table.get_index<"hash"_n>();
  auto iters = hash_itr.lower_bound(hash);

  check(iters->hash != hash, "This hash has been existed!");

  log_table.emplace(get_self(), [&](auto & c) {
      c.id      = log_table.available_primary_key();;
      c.cert_id = cert_id;
      c.hash    = hash;
      c.uri     = uri;
  });

}
ACTION cryptobaglog::logupdcert(const checksum256 &old_hash,
                            const checksum256 &new_hash,
                            const std::string &new_uri)
{
  require_auth(get_self());

  logcerts log_table(get_self(), get_self().value);
  auto hash_itr = log_table.get_index<"hash"_n>();
  auto iters = hash_itr.lower_bound(old_hash);

  check(iters->hash == old_hash, "Cannot found this hash for certification!");

  while( iters != hash_itr.end()) {
    if(iters->hash == old_hash) {
        log_table.modify(*iters, get_self(), [&](auto &c) {
          c.hash = new_hash;
          c.uri  = new_uri;
        });
      return;
    }
    iters++;
  }
}
EOSIO_DISPATCH(cryptobaglog, (logcrecert)(logupdcert))
