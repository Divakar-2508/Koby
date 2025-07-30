# Koby

Koby is a lightweight, modern C++ web server framework with JSON support, inspired by Express.js and built using Asio. It enables you to rapidly create REST APIs and web applications in C++ with a clean, expressive syntax.

## Features

- Simple API for defining routes (`GET`, `POST`, etc.)
- JSON parsing and response utilities
- HTML response support
- Asynchronous networking with Asio
- Custom error pages (e.g., a fun 404 page)
- Modern C++ (C++23) codebase

## Example

```cpp
#include "koby.h"
#include <iostream>

int main() {
    Koby::Server my_server(8088);

    my_server.get("/", [](Koby::Request &req) -> Koby::Response {
        std::cout << "Got an " << req.path << "\n";
        return Koby::Response(200, "Hello from Koby!");
    });

    my_server.get("/html", [](Koby::Request &req) -> Koby::Response {
        return Koby::Response::load_html("some.html");
    });

    my_server.post("/json", [](Koby::Request &req) -> Koby::Response {
        Koby::Json json = {
            {"name", "morbius"},
            {"IsMarried", false},
            {"Body Count", 20000},
            {"Height", 6.12},
            {"Hobbies", Koby::Json{{"morning", {"waking", "sleeping"}}, {"evening", {"Eating", "killing"}}}}
        };
        return Koby::Response::json(json);
    });

    std::cout << "Koby is running at http://localhost:" << my_server.port << std::endl;
    my_server.run();
}
```

## Getting Started

### Prerequisites

- A C++23 compatible compiler (e.g., GCC 13+, Clang 16+, MSVC 2022+)
- CMake 4.0+
- [Asio](https://think-async.com/) (header-only, no Boost required)

### Building

1. Clone the repository:

   ```bash
   git clone https://github.com/Divakar-2508/Koby.git
   cd Koby
   ```

2. Build with CMake:

   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

### Running

```bash
./Koby
```
The server will start on `localhost:8088` by default (customize the port as needed).

## Project Structure

```
include/         # Public headers (API)
src/             # Source code
    main.cpp     # Example server
    server.cpp   # Server implementation
    request.cpp  # HTTP request parsing
    response.cpp # HTTP responses
    util.cpp     # Utilities (e.g., headers, methods, 404 page)
    json.cpp     # JSON handling
CMakeLists.txt   # Build configuration
```

## Contribution

Contributions are welcome! Please open an issue or pull request for bug fixes, new features, or improvements.

1. Fork the repo
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is currently unlicensed. Please open an issue if you’d like to contribute under a specific license.

---

Made with ❤️ by [Divakar-2508](https://github.com/Divakar-2508)
