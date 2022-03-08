#pragma once
#include <string>
#include <thread>
#include <log.hh>

namespace db::mongodb {

class MongoManager {

  using CollectionInterface =
      db::mongodb::collections::MongoCollectionInterface;
  using CollectionPtr = std::shared_ptr<CollectionInterface>;

public:
  MongoManager();
  ~MongoManager();

  void loadAll();
  void stop() { stop_ = true; }

  void listen();

  template <typename Collection>
  std::shared_ptr<const Collection> getCollection() const {
    auto coll_it = collections_.find(Collection::kMongoCollectionName);
    if (coll_it == collections_.end()) {
      logError("Collection with name '{}' does not exists",
               Collection::kMongoCollectionName);
    }
    auto &coll = coll_it->second;
    return std::dynamic_pointer_cast<const Collection>(coll);
  }

private:
  std::atomic_bool stop_;
  std::thread thread_;
  std::unordered_map<std::string, CollectionPtr> collections_;
};

} // namespace db::mongodb
