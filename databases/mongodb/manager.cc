#include <bsoncxx/json.hpp>
#include <iostream>

#include <Models/CategoryCollection.hpp>

#include "client.hh"
#include "manager.hh"

namespace db::mongodb {

MongoManager::MongoManager() : stop_(false), thread_([this]() { listen(); }) {
  using namespace db::mongodb::collections;

  collections_.insert({CategoryCollection::kMongoCollectionName,
                       std::make_shared<CategoryCollection>()});
}
MongoManager::~MongoManager() {
  stop_ = true;
  thread_.join();
}

void MongoManager::loadAll() {
  for (auto &[coll_name, coll_ptr] : collections_) {
    coll_ptr->loadAll();
  }
}

void MongoManager::listen() {
  constexpr auto kTimeToAwait = 10000;
  using ResumeToken = bsoncxx::document::value;
  using OptionalResumeToken = std::optional<ResumeToken>;

  auto client = mongodb_client();
  auto connection_ptr = client.GetConnectionPtr();
  auto database = connection_ptr->database(client.GetDefaultDatabaseName());

  const std::chrono::milliseconds await_time{kTimeToAwait};
  OptionalResumeToken resume_token;
  std::unique_ptr<mongocxx::change_stream> stream;

  while (!stop_) {
    mongocxx::options::change_stream options;
    options.max_await_time(await_time);

    if (resume_token) {
      auto token = resume_token.value();
      options.resume_after(std::move(token));
    }

    try {
      stream =
          std::make_unique<mongocxx::change_stream>(database.watch(options));
      for (const auto &event : *stream) {
        if(stream->get_resume_token()){
           resume_token.emplace(*stream->get_resume_token());
        }
        const auto operationType =
            event["operationType"].get_utf8().value.to_string();
        const auto collection_name =
            event["ns"]["coll"].get_utf8().value.to_string();
        auto coll_it = collections_.find(collection_name);
        if (coll_it == collections_.end()) {
          logError("Collection with name '{}' does not exists",
                   collection_name);
        }

        auto &coll = coll_it->second;
        if (operationType == "insert") {
          const auto &view = event["fullDocument"].get_document().view();
          coll->onInsert(view);
        } else if (operationType == "update") {
          coll->onUpdate(event);
        } else if (operationType == "delete") {
          coll->onDelete(event);
        }
      }

    } catch (const std::exception &e) {
      logError("Mongo error:", e.what());
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
}
} // namespace db::mongodb
