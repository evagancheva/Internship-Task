#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include "httplib.h"

using json = nlohmann::json;

json load_json_file(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Cannot open file: " + path);
    json j;
    file >> j;
    return j;
}

bool compare_routes(const json& res1, const json& res2) {
    if (res1.size() != res2.size()) return false;
    for (size_t i = 0; i < res1.size(); ++i) {
        if (res1[i]["route"] != res2[i]["route"] || res1[i]["price"] != res2[i]["price"]) {
            return false;
        }
    }
    return true;
}

int main() {
    httplib::Client cli("localhost", 9999);
    auto requests = load_json_file("FlightAPI_Requests.json");
    auto expected = load_json_file("FlightAPI_StructuredResponses.json");

    int passed = 0;
    for (size_t i = 0; i < requests.size(); ++i) {
        auto req_body = requests[i].dump();
        auto res = cli.Post("/search", req_body, "application/json");
        if (!res || res->status != 200) {
            std::cout << "❌ Test " << i + 1 << " failed: No response or bad status.\n";
            continue;
        }

        try {
            json got = json::parse(res->body);
            if (compare_routes(got, expected[i])) {
                std::cout << "✅ Test " << i + 1 << " passed\n";
                ++passed;
            }
            else {
                std::cout << "❌ Test " << i + 1 << " failed: response mismatch.\n";
            }
        }
        catch (...) {
            std::cout << "❌ Test " << i + 1 << " failed: invalid JSON in response.\n";
        }
    }

    std::cout << "\nSummary: " << passed << "/" << requests.size() << " tests passed.\n";
    return 0;
}