#include <asio.hpp>
#include <asio/write.hpp>
#include <cstddef>
#include <string>
#include <unordered_map>

#include "koby.h"

namespace Koby {

Server::Server(int port)
    : port(port), context(), endpoint(asio::ip::tcp::v4(), port),
      acceptor(context, endpoint) {}

void Server::run() {
    using asio::ip::tcp;

    for (;;) {
        tcp::socket socket(context);
        acceptor.accept(socket);

        std::string request;
        char buffer[1024];

        for (;;) {
            std::size_t len = (int)socket.read_some(asio::buffer(buffer));
            request.append(buffer, len);

            // if (request.find("\r\n\r\n") != std::string::npos) {
            if (request.contains("\r\n\r\n")) {
                break;
            }
        }

        Request req(request);
        std::string response;

        if (route_map.contains(req.path)) {
            std::unordered_map<Method, RouteHandler> &handlers =
                route_map[req.path];

            if (!handlers.contains(req.method)) {
                response = "Method not supported";
            } else {
                RouteHandler &handler = handlers[req.method];
                Response resp = handler(req);
                response = resp.to_string();
            }

        } else {
            response = Koby::NOT_FOUND_RESPONSE.to_string();
        }

        asio::write(socket, asio::buffer(response));
        socket.close();
    }
}

void Server::get(std::string route, RouteHandler handle) {
    if (route_map[route].contains(Method::GET)) {
        Koby::route_error("GET", route);
    }
    route_map[route][Method::GET] = handle;
}

void Server::post(std::string route, RouteHandler handle) {
    if (route_map[route].contains(Method::POST)) {
        Koby::route_error("POST", route);
    }
    route_map[route][Method::POST] = handle;
}

} // namespace Koby
