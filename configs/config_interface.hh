#pragma once
#include "json/rabbit_json.hpp"
#include <memory>
#include <string>

namespace configs {

class ConfigInterface {
public:
  using JsonObject = rabbit::object;
  using JsonObjectRef = rabbit::value_ref;
  using ConstJsonObject = rabbit::const_object;
  using JsonDocument = rabbit::document;

  virtual const std::string GetName() const = 0;
  virtual const std::string GetPath() const = 0;

  virtual void toJson(JsonObjectRef obj) const = 0;
  virtual bool fromJson(const ConstJsonObject &val) = 0;

  virtual void LoadFile();
};

} // namespace configs
