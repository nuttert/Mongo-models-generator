#include "client.hh"

#include <Configs/MongodbConfig.hpp>
#include <configs/configs.hh>

#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <fmt/format.h>
#include <log.hh>
#include <string>

namespace db::mongodb {
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

bool MongoDBClient::connected(mongocxx::database &db) const {
  try {
    document ping;
    ping << "ping" << 1;
    auto result = db.run_command(ping.view());
    if (result.view()["ok"].get_double().value != 1){
       return false;
    }
     
  } catch (const std::exception &e) {
    logWarn("Mongo ping does not work {}", e.what());
    return false;
  }

  return true;
}

MongoDBClient::MongoDBClient() {
  using namespace fmt::literals;

  mongocxx::instance instance{}; // This should be done only once.
  const auto config = config_manager().GetConfig<configs::MongodbConfig>();

  auto databases = config->getDatabases();
  default_db_name = config->getDefaultDb();

  try {
    for (const auto &[name, database] : databases) {
      std::string host = database->getHost();
      const auto port = std::to_string(database->getPort());
      std::string username = database->getUsername();
      std::string password = database->getPassword();
      // clang-format off
      const auto configuration =
          fmt::format("mongodb://{host}:{port}/{name}?"
                      "retryWrites=true&w=majority&minPoolSize=3&maxPoolSize=3",
                      // "username"_a = username,
                      // "password"_a = password,
                      "host"_a = host,
                      "port"_a = port,
                      "name"_a = name);
      // clang-format on
      logInfo("MongoDB connection: {}", configuration);
      auto pool =
          std::make_shared<mongocxx::pool>(mongocxx::uri{configuration});
      auto connection_ptr = pool->acquire();
      auto db = connection_ptr->database(name);
      pools[name] = pool;
      auto ok = connected(db);
      if (!ok)
        throw std::runtime_error("Mongodb auth error! " + name);
    }
  } catch (const std::exception &e) {
    logInfo("Mongodb auth error: {}", e.what());
    throw;
  }
}

std::string MongoDBClient::GetDefaultDatabaseName() const {
  return default_db_name;
}

mongocxx::pool::entry MongoDBClient::GetConnectionPtr() const {
  auto db_iterator = pools.find(default_db_name);
  if (db_iterator == pools.end()) {
    throw std::runtime_error(default_db_name +
                             " mongo db: database not found!");
  }
  auto connection = db_iterator->second->acquire();
  return connection;
}
} // namespace db::mongodb
