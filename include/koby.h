#include <asio.hpp>
#include <functional>
#include <initializer_list>
#include <map>
#include <string>
#include <string_view>
#include <unordered_map>

#ifndef SERVER_H
#define SERVER_H

namespace Koby {

class Request;
class Response;
class JsonValue;
class Json;

enum class Method { GET, POST, INVALID };

using RouteHandler = std::function<Koby::Response(Koby::Request &)>;
using Headers = std::unordered_map<std::string, std::string>;
using JsonArray = std::vector<JsonValue>;

extern const Response NOT_FOUND_RESPONSE;

std::string headers_to_string(const Headers &headers);
std::string method_to_string(const Method &method);
[[noreturn]] inline void route_error(const std::string &method,
                                     const std::string &route) {
    throw std::runtime_error("[" + method + "] Route Handler for \"" + route +
                             "\" already exists. Mistakes Won’t Be Tolerated.");
}

class Request {
  public:
    const std::string path;
    const std::string http_version;
    const Headers headers;
    const Method method;

    Request(std::string_view content);
    Request(std::string_view path, Method method, std::string_view http_version,
            Headers header);

    static Request parse(const std::string &chunk);

    std::string to_string() const;
};

class Response {
  public:
    Response(int status_code, std::string content);
    Response(int status_code, std::string content, Headers headers,
             std::string content_type);
    Response(int status_code, Headers headers);
    Response(const std::string &file_path);

    static Response load_html(const std::string &file_path);
    static Response json(const Json &json);
    static Response text(const std::string &content);

    std::ostream &operator<<(std::ostream &os);
    std::string to_string() const;

  private:
    int status_code;
    std::string content;
    std::string content_type;
    Headers headers;
};

class Server {
  public:
    const int port;
    Server(int port);
    void run();
    void get(std::string route, RouteHandler handle);
    void post(std::string route, RouteHandler handle);

  private:
    asio::io_context context;
    asio::ip::tcp::endpoint endpoint;
    asio::ip::tcp::acceptor acceptor;
    std::unordered_map<std::string, std::unordered_map<Method, RouteHandler>>
        route_map;
};

class Json {
  public:
    Json(std::initializer_list<std::pair<const std::string, JsonValue>>);
    std::string to_string() const;
    static Json parse(const std::string &content);

  private:
    using JsonMap = std::map<std::string, JsonValue>;
    JsonMap value;
};

class JsonValue {
  public:
    JsonValue(int val);
    JsonValue(bool val);
    JsonValue(double val);
    JsonValue(const char *val);
    JsonValue(const std::string &val);
    JsonValue(const JsonArray &val);
    JsonValue(const Json &val);
    JsonValue(std::initializer_list<JsonValue> list);

    std::string to_string() const;

  private:
    using Value = std::variant<std::string, int, double, bool, JsonArray, Json>;
    Value value;
};

} // namespace Koby

#endif // !server
