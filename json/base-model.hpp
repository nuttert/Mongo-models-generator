#pragma once
#include <map>
#include <memory>
#include <optional>
#include <vector>

#include "rabbit_json.hpp"

namespace models {
using JsonObject = rabbit::object;
using JsonObjectRef = rabbit::value_ref;
using ConstJsonObject = rabbit::const_object;
using JsonArray = rabbit::array;
using JsonArrayRef = rabbit::value_ref;
using ConstJsonArray = rabbit::const_array;
using JsonValue = rabbit::value;
using JsonValueRef = rabbit::value_ref;
using ConstJsonValue = rabbit::const_value;
using JsonDocument = rabbit::document;
using ConstJsonDocument = rabbit::const_document;

class BaseModel {
public:
  BaseModel();
  virtual ~BaseModel();

  virtual void validate() = 0;

  virtual void toJson(JsonObjectRef obj) const = 0;
  virtual bool fromJson(const ConstJsonObject &json) = 0;
  virtual bool updateFromJson(const ConstJsonObject &val) = 0;

  static std::string toString(const bool val);
  static std::string toString(const float val);
  static std::string toString(const double val);
  static std::string toString(const int32_t val);
  static std::string toString(const int64_t val);
  static std::string toString(const uint32_t val);
  static std::string toString(const uint64_t val);
  static std::string toString(const std::string &val);

  static std::string toString(const JsonValue &val);
  template <typename T> static std::string toString(const T &val);
  template <typename T>
  static std::string toString(const std::shared_ptr<T> &val);
  template <typename T>
  static std::string toString(const std::optional<T> &val);
  template <typename T> static std::string toString(const std::vector<T> &val);
  template <typename T>
  static std::string toString(const std::map<std::string, T> &val);

  static void toJson(JsonValueRef jval, bool val);
  static void toJson(JsonValueRef jval, float val);
  static void toJson(JsonValueRef jval, double val);
  static void toJson(JsonValueRef jval, int32_t val);
  static void toJson(JsonValueRef jval, int64_t val);
  static void toJson(JsonValueRef jval, uint32_t val);
  static void toJson(JsonValueRef jval, uint64_t val);
  static void toJson(JsonValueRef jval, const std::string &val);

  template <typename T>
  static void toJson(JsonValueRef jval, const std::shared_ptr<T> &val);
  template <typename T>
  static void toJson(JsonValueRef jval, const std::optional<T> &val);
  template <typename T>
  static void toJson(JsonArrayRef jval, const std::vector<T> &val);
  template <typename T>
  static void toJson(JsonObjectRef jval, const std::map<std::string, T> &val);

  static bool fromString(const std::string &val, bool &);
  static bool fromString(const std::string &val, float &);
  static bool fromString(const std::string &val, double &);
  static bool fromString(const std::string &val, int32_t &);
  static bool fromString(const std::string &val, int64_t &);
  static bool fromString(const std::string &val, uint32_t &);
  static bool fromString(const std::string &val, uint64_t &);
  static bool fromString(const std::string &val, std::string &);

  template <typename T> static bool fromString(const std::string &val, T &);
  template <typename T>
  static bool fromString(const std::string &val, std::shared_ptr<T> &);
  template <typename T>
  static bool fromString(const std::string &val, std::optional<T> &);
  template <typename T>
  static bool fromString(const std::string &val, std::vector<T> &);
  template <typename T>
  static bool fromString(const std::string &val, std::map<std::string, T> &);

  static bool fromJson(const ConstJsonValue &val, bool &);
  static bool fromJson(const ConstJsonValue &val, float &);
  static bool fromJson(const ConstJsonValue &val, double &);
  static bool fromJson(const ConstJsonValue &val, int32_t &);
  static bool fromJson(const ConstJsonValue &val, int64_t &);
  static bool fromJson(const ConstJsonValue &val, uint32_t &);
  static bool fromJson(const ConstJsonValue &val, uint64_t &);
  static bool fromJson(const ConstJsonValue &val, std::string &);

  template <typename T>
  static bool fromJson(const ConstJsonValue &val, std::shared_ptr<T> &);
  template <typename T>
  static bool fromJson(const ConstJsonValue &val, std::optional<T> &);
  template <typename T>
  static bool fromJson(const ConstJsonArray &val, std::vector<T> &);
  template <typename T>
  static bool fromJson(const ConstJsonObject &val, std::map<std::string, T> &);
};
} // namespace models

namespace models {

template <typename T> std::string BaseModel::toString(const T &val) {
  JsonValue jval;
  val.toJson(jval);
  return jval.str();
}

template <typename T>
std::string BaseModel::toString(const std::shared_ptr<T> &val) {
  JsonValue jval;
  if (val) {
    val->toJson(jval);
    return jval.str();
  }
  return "null";
}

template <typename T>
std::string BaseModel::toString(const std::optional<T> &val) {
  JsonValue jval;
  if (val) {
    val->toJson(jval);
    return jval.str();
  }
  return "null";
}
template <typename T>
std::string BaseModel::toString(const std::vector<T> &val) {
  std::string strArray = "[";
  for (const auto &item : val) {
    strArray.append(toString(item) + ",");
  }
  if (val.size() > 0) {
    strArray.pop_back();
  }
  return strArray + "]";
}
template <typename T>
std::string BaseModel::toString(const std::map<std::string, T> &val) {
  return toJson(val).str();
}

template <typename T>
void BaseModel::toJson(JsonValueRef jval, const std::shared_ptr<T> &val) {
  if (val) {
    val->toJson(jval);
  }
}
template <typename T>
void BaseModel::toJson(JsonValueRef jval, const std::optional<T> &val) {
  if (val) {
    toJson(jval, *val);
  }
}
template <typename T>
void BaseModel::toJson(JsonArrayRef jarr, const std::vector<T> &value) {
  jarr.set(rabbit::array_tag{});
  jarr.resize(value.size());
  for (size_t i = 0; i < value.size(); ++i) {
    toJson(jarr[i], value[i]);
  }
}
template <typename T>
void BaseModel::toJson(JsonObjectRef jobj,
                       const std::map<std::string, T> &val) {
  jobj.set(rabbit::object_tag{});
  for (const auto &[key, value] : val) {
    toJson(jobj[key], value);
  }
}

template <typename T>
bool BaseModel::fromString(const std::string &val, T &outVal) {
  JsonDocument doc;
  doc.parse(val);
  return outVal.fromJson(doc);
}
template <typename T>
bool BaseModel::fromString(const std::string &val, std::shared_ptr<T> &outVal) {
  if (!outVal) {
    outVal = std::make_shared<T>();
  }
  JsonDocument doc;
  doc.parse(val);
  return outVal->fromJson(doc);
}
template <typename T>
bool BaseModel::fromString(const std::string &val, std::optional<T> &outVal) {
  if (!outVal) {
    outVal = std::make_shared<T>();
  }
  JsonDocument doc;
  doc.parse(val);
  return outVal->fromJson(doc);
}

template <typename T>
bool BaseModel::fromString(const std::string &val, std::vector<T> &outVal) {
  JsonDocument doc;
  doc.parse(val);
  return fromJson(doc, outVal);
}

template <typename T>
bool BaseModel::fromString(const std::string &val,
                           std::map<std::string, T> &outVal) {
  JsonDocument doc;
  doc.parse(val);
  return fromJson(doc, outVal);
}

template <typename T>
bool BaseModel::fromJson(const ConstJsonValue &val,
                         std::shared_ptr<T> &outVal) {
  if (!outVal) {
    outVal = std::make_shared<T>();
  }
  return outVal->fromJson(val);
}

template <typename T>
bool BaseModel::fromJson(const ConstJsonValue &val, std::optional<T> &outVal) {
  if (!outVal) {
    outVal = T();
  }
  return outVal->fromJson(val);
}
template <typename T>
bool BaseModel::fromJson(const ConstJsonArray &val, std::vector<T> &outVal) {
  bool ok = true;
  if (val.is_array()) {
    for (const auto &jitem : val) {
      T item;
      ok &= fromJson(jitem, item);
      outVal.push_back(std::move(item));
    }
  } else {
    ok = false;
  }
  return ok;
}

template <typename T>
bool BaseModel::fromJson(const ConstJsonObject &jval,
                         std::map<std::string, T> &outVal) {
  bool ok = true;
  if (jval.is_object()) {
    for (const auto &it : jval) {
      T itemVal;
      ok &= fromJson(it.value(), itemVal);
      outVal.insert(std::pair<std::string, T>(it.name(), itemVal));
    }
  } else {
    ok = false;
  }
  return ok;
}
} // namespace models
