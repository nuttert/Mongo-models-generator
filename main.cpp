#include "Models/CategoryCollection.hpp"
#include "Models/Pet.hpp"
#include "configs/configs.hh"
#include "databases/mongodb/client.hh"
#include "databases/mongodb/manager.hh"
#include "json/base-model.hpp"
#include <iostream>

#include "databases/mongodb/manager.hh"
#include <chrono>

int main() {

  // 1. Example of serialization/deserialization
  auto model = std::make_shared<models::Pet>(); // create model
  if (!models::BaseModel::fromString(
          R"""({
      "_id": {"$oid": "12345"},
      "id": 4,
      "category": {
        "id": 0,
        "name": "string"
      },
      "name": "doggie",
      "photoUrls": [
        "string"
      ],
      "tags": [
        {
          "id": 5,
          "name": "string"
        }
      ],
      "status": "available"
    })""",
          model)) {
    std::cerr << "Parsing error" << std::endl;
  } // parse model

  std::cout << models::BaseModel::toString(model) << std::endl; // print model

  // 2. Example of listening collections
  db::mongodb::MongoManager mongo_manager;
  mongo_manager.loadAll();
  auto cat_coll =
      mongo_manager
          .getCollection<db::mongodb::collections::CategoryCollection>();

  std::cout << models::BaseModel::toString(cat_coll->getByName("abc"))
            << std::endl;

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1000s);
}
