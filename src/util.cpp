#include "koby.h"

namespace Koby {

const std::string NOT_FOUND_HTML = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>404 - Lost in the Void</title>
    <style>
        body { font-family: monospace; background-color: #111; color: #0f0; text-align: center; padding: 50px; }
        .glitch { font-size: 2em; animation: blink 1s infinite; }
        @keyframes blink {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.2; }
        }
    </style>
</head>
<body>
    <div class="glitch">404: Page Not Found</div>
    <p>Like your socks after laundry... it's just gone.</p>
    <p>Maybe it joined a startup in another directory.</p>
    <p><a href="/">Go back before the void notices</a></p>
</body>
</html>
)";

const Response NOT_FOUND_RESPONSE(404, "text/html",
                                  {{"Server", "Koby/1.0"},
                                   {"Content-Type", "text/html"},
                                   {"Connection", "close"}},
                                  NOT_FOUND_HTML);

std::string headers_to_string(const Headers &headers) {
    std::stringstream buffer;
    for (const auto &[key, value] : headers) {
        buffer << key << ": " << value << "\r\n";
    }

    return buffer.str();
}

std::string method_to_string(const Method &method) {
    switch (method) {
    case Koby::Method::GET:
        return "GET";
    case Koby::Method::POST:
        return "POST";
    default:
        return "INVALID";
    }
}
} // namespace Koby
