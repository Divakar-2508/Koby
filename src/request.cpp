#include <sstream>
#include <string>

#include "koby.h"

namespace Koby {

Method parse_method(const std::string &str) {
    if (str == "GET") {
        return Method::GET;
    } else if (str == "POST") {
        return Method::POST;
    } else {
        return Method::INVALID;
    }
}

Request::Request(std::string_view content)
    : Request(parse(std::string(content))) {}

Request::Request(std::string_view path, Method method,
                 std::string_view http_version, Headers headers)
    : path(path), method(method), http_version(http_version), headers(headers) {
}

Request Request::parse(const std::string &chunk) {
    std::stringstream ss(chunk);
    std::string buffer;

    ss >> buffer;
    Method method = parse_method(buffer);

    ss >> buffer;
    std::string path(buffer);

    ss >> buffer;
    std::string http_version(buffer);

    std::getline(ss, buffer);

    Headers headers;

    return Request(path, method, http_version, headers);
}

std::string Request::to_string() const {
    std::ostringstream oss;
    oss << "Method: " << method_to_string(this->method);
    oss << "\nPath: " << this->path;
    oss << "\nVersion: " << this->http_version;

    return oss.str();
}
} // namespace Koby

/*
GET /hello/world?name=divakar&lang=rust HTTP/1.1
Host: example.com
User-Agent: Mozilla/5.0 (X11; Linux x86_64)
Accept: text/html,application/xhtml+xml
Accept-Language: en-US,en;q=0.5
Connection: keep-alive
*/
