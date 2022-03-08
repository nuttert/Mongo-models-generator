#pragma once
#include <bsoncxx/builder/basic/document.hpp>
#include <string>

namespace db::mongodb::collections {

class MongoCollectionInterface {
public:
  virtual std::string GetCollectionName() const = 0;
  virtual void loadAll() = 0;

  virtual void onDelete(const bsoncxx::document::view &data) = 0;
  virtual void onInsert(const bsoncxx::document::view &data) = 0;
  virtual void onUpdate(const bsoncxx::document::view &data) = 0;
};

} // namespace db::mongodb::collections
