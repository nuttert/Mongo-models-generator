#include "base-model.hpp"

namespace models {

BaseModel::BaseModel() {}
BaseModel::~BaseModel() {}

std::string BaseModel::toString(const bool val) { return std::to_string(val); }
std::string BaseModel::toString(const float val) { return std::to_string(val); }
std::string BaseModel::toString(const double val) {
  return std::to_string(val);
}
std::string BaseModel::toString(const int32_t val) {
  return std::to_string(val);
}
std::string BaseModel::toString(const int64_t val) {
  return std::to_string(val);
}
std::string BaseModel::toString(const uint32_t val) {
  return std::to_string(val);
}
std::string BaseModel::toString(const uint64_t val) {
  return std::to_string(val);
}
std::string BaseModel::toString(const std::string &val) { return val; }

std::string BaseModel::toString(const JsonValue &val) { return val.str(); }

void BaseModel::toJson(JsonValueRef jval, bool value) { jval = value; }
void BaseModel::toJson(JsonValueRef jval, float value) { jval = value; }
void BaseModel::toJson(JsonValueRef jval, double value) { jval = value; }
void BaseModel::toJson(JsonValueRef jval, int32_t value) { jval = value; }
void BaseModel::toJson(JsonValueRef jval, int64_t value) { jval = value; }
void BaseModel::toJson(JsonValueRef jval, uint32_t value) { jval = value; }
void BaseModel::toJson(JsonValueRef jval, uint64_t value) { jval = value; }
void BaseModel::toJson(JsonValueRef jval, const std::string &value) {
  jval = value;
}

bool BaseModel::fromString(const std::string &val, bool &outVal) {
  if (val == "false") {
    outVal = false;
  } else if (val == "true") {
    outVal = true;
  } else {
    return false;
  }
  return true;
}
bool BaseModel::fromString(const std::string &val, float &outVal) {
  bool success = true;
  try {
    outVal = std::stof(val);
  } catch (...) {
    success = false;
  }
  return success;
}
bool BaseModel::fromString(const std::string &val, double &outVal) {
  bool success = true;
  try {
    outVal = std::stod(val);
  } catch (...) {
    success = false;
  }
  return success;
}
bool BaseModel::fromString(const std::string &val, int32_t &outVal) {
  bool success = true;
  try {
    outVal = std::stoi(val);
  } catch (...) {
    success = false;
  }
  return success;
}
bool BaseModel::fromString(const std::string &val, int64_t &outVal) {
  bool success = true;
  try {
    outVal = std::stol(val);
  } catch (...) {
    success = false;
  }
  return success;
}
bool BaseModel::fromString(const std::string &val, uint32_t &outVal) {
  bool success = true;
  try {
    outVal = std::stoul(val);
  } catch (...) {
    success = false;
  }
  return success;
}
bool BaseModel::fromString(const std::string &val, uint64_t &outVal) {
  bool success = true;
  try {
    outVal = std::stoul(val);
  } catch (...) {
    success = false;
  }
  return success;
}
bool BaseModel::fromString(const std::string &val, std::string &outVal) {
  outVal = val;
  return true;
}

bool BaseModel::fromJson(const ConstJsonValue &val, bool &outVal) {
  if (!val.is_bool()) {
    return false;
  }
  outVal = val.as_bool();
  return true;
}
bool BaseModel::fromJson(const ConstJsonValue &val, float &outVal) {
  if (!val.is_double()) {
    return false;
  }
  outVal = static_cast<float>(val.as_double());
  return true;
}
bool BaseModel::fromJson(const ConstJsonValue &val, double &outVal) {
  if (!val.is_double()) {
    return false;
  }
  outVal = val.as_double();
  return true;
}
bool BaseModel::fromJson(const ConstJsonValue &val, int32_t &outVal) {
  if (!val.is_int()) {
    return false;
  }
  outVal = val.as_int();
  return true;
}
bool BaseModel::fromJson(const ConstJsonValue &val, int64_t &outVal) {
  if (!val.is_int64()) {
    return false;
  }
  outVal = val.as_int64();
  return true;
}
bool BaseModel::fromJson(const ConstJsonValue &val, uint32_t &outVal) {
  if (!val.is_uint()) {
    return false;
  }
  outVal = val.as_uint();
  return true;
}
bool BaseModel::fromJson(const ConstJsonValue &val, uint64_t &outVal) {
  if (!val.is_uint64()) {
    return false;
  }
  outVal = val.as_uint64();
  return true;
}
bool BaseModel::fromJson(const ConstJsonValue &val, std::string &outVal) {
  if (!val.is_string()) {
    return false;
  }
  outVal = val.as_string();
  return true;
}

} // namespace models
