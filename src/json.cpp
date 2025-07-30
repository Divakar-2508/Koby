#include "koby.h"
#include <initializer_list>

namespace Koby {

Json::Json(std::initializer_list<std::pair<const std::string, JsonValue>> list)
    : value(list) {}

std::string Json::to_string() const {
    std::ostringstream iss;
    iss << "{";
    for (auto it = this->value.begin(); it != this->value.end(); ++it) {
        iss << "\"" << it->first << "\":" << it->second.to_string();
        if (std::next(it) != this->value.end()) {
            iss << ",";
        }
    }
    iss << "}";

    return iss.str();
}

JsonValue::JsonValue(int val) : value(val) {}
JsonValue::JsonValue(bool val) : value(val) {}
JsonValue::JsonValue(double val) : value(val) {}
JsonValue::JsonValue(const std::string &val) : value(val) {}
JsonValue::JsonValue(const char *val) : value(std::string(val)) {}
JsonValue::JsonValue(const JsonArray &val) : value(val) {}
JsonValue::JsonValue(const Json &val) : value(val) {}
JsonValue::JsonValue(std::initializer_list<JsonValue> list)
    : value(JsonArray(list)) {}

std::string JsonValue::to_string() const {
    return std::visit(
        [](auto &&val) -> std::string {
            using T = std::decay_t<decltype(val)>;
            if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double>) {
                return std::to_string(val);
            } else if constexpr (std::is_same_v<T, bool>) {
                return (val ? "true" : "false");
            } else if constexpr (std::is_same_v<T, std::string>) {
                return "\"" + val + "\"";
            } else if constexpr (std::is_same_v<T, Json>) {
                return val.to_string();
            } else {
                std::string buffer = "[";
                for (int i = 0; i < val.size() - 1; ++i) {
                    buffer.append(val[i].to_string());
                    buffer.append(", ");
                }
                buffer.append(val.back().to_string());
                buffer.append("]");
                return buffer;
            }
        },
        value);
}

// Json Json::parse(const std::string &content) {}

} // namespace Koby
