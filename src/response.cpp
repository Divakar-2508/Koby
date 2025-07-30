#include "koby.h"
#include <fstream>
#include <string>

namespace Koby {

Response::Response(int code, std::string content)
    : status_code(code), content(content) {}

Response::Response(int code, Headers headers)
    : status_code(code), headers(headers) {}

Response::Response(int code, std::string content_type, Headers headers,
                   std::string content)
    : status_code(code), content(content), headers(headers) {
    this->headers.insert({"Content-Type", content_type});
}

std::ostream &Response::operator<<(std::ostream &os) {
    os << this->to_string();
    return os;
}

std::string Response::to_string() const {
    std::stringstream ss;
    ss << "HTTP/1.1 " << this->status_code << " OK\r\n"
       << Koby::headers_to_string(this->headers) << "\r\n"
       << this->content;

    return ss.str();
}

Response Response::load_html(const std::string &file_path) {
    Response r(200, {{"Content-Type", "text/html"}});
    std::ifstream file(file_path);
    std::string buffer;

    while (std::getline(file, buffer)) {
        r.content.append(buffer);
    }

    return r;
}

Response Response::json(const Json &json) {
    Response r(200, {{"Content-Type", "application/json"}});
    r.content = json.to_string();

    return r;
}

Response Response::text(const std::string &content) {
    return Response(200, content);
}

} // namespace Koby
