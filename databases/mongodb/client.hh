#pragma once
#include <bsoncxx/builder/stream/document.hpp>
#include <memory>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/pool.hpp>
#include <unordered_map>

#include <utils/singleton.hh>

namespace db::mongodb {

// @brief
// Thread safety mongodb client
class MongoDBClient {
  using PoolPtr = std::shared_ptr<mongocxx::pool>;
  using Pools = std::unordered_map<std::string, PoolPtr>;

public:
  MongoDBClient();

  std::string GetDefaultDatabaseName() const;
  // @brief
  // Get connection for the thread
  mongocxx::pool::entry GetConnectionPtr() const;

private:
  bool connected(mongocxx::database &db) const;

  Pools pools; //
  std::string default_db_name;
};

inline MongoDBClient &mongodb_client() {
  using DB = utils::Single<MongoDBClient>;
  static DB mongo;
  return *DB::instance();
}

} // namespace db::mongodb
