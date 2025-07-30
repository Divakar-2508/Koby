#include "koby.h"
#include <iostream>

int main() {
    Koby::Server my_server(8088);

    my_server.get("/", [](Koby::Request &req) -> Koby::Response {
        std::cout << "Got an " << req.path << "\n";
        return Koby::Response(200, "Baka Baka");
    });

    my_server.get("/html", [](Koby::Request &req) -> Koby::Response {
        std::cout << "Got an " << req.path << "\n";
        return Koby::Response::load_html("some.html");
    });

    my_server.post("/some", [](Koby::Request &req) -> Koby::Response {
        std::cout << "Got an " << req.path << "\n";
        return Koby::Response(200, "hello world");
    });

    my_server.post("/some_thing", [](Koby::Request &req) -> Koby::Response {
        std::cout << "Got an " << req.path << "\n";
        Koby::Json json = {
            {"name", "morbius"},
            {"IsMarried", false},
            {"Body Count", 20000},
            {"Height", 6.12},
            {"Hobbies", Koby::Json{{"morning", {"waking", "sleeping"}},
                                   {"evening", {"Eating", "killing"}}}}};
        return Koby::Response::json(json);
    });

    std::cout << "Koby is running in localhost:" << my_server.port << "\n";
    my_server.run();
}
