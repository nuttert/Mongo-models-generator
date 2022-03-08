#include "config_interface.hh"
#include <fstream>

namespace configs {

void ConfigInterface::LoadFile() {
  try {
    std::ifstream json_root;
    json_root.open(GetPath(), std::ofstream::out);

    std::stringstream stream_json_root;
    stream_json_root << json_root.rdbuf();
    std::string json_str = stream_json_root.str();
    std::cout << json_str;

    JsonDocument doc;
    doc.parse(json_str);
    fromJson(doc);
  } catch (const std::exception &except) {
    throw std::runtime_error("Parse Error:" + GetPath() + " " + except.what());
  }
}
} // namespace configs
