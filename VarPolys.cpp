
#include <iostream>
#include <chrono>
#include "MultiPolynomStorage.h"
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;

json termsToJson(const std::vector<std::pair<double, std::map<char, int>>>& terms) {
    json result = json::array();
    for (const auto& [coeff, vars] : terms) {
        json term;
        term["coefficient"] = coeff;
        term["variables"] = json::object();
        for (const auto& [var, exp] : vars) {
            term["variables"][std::string(1, var)] = exp;
        }
        result.push_back(term);
    }
    return result;
}

void createPolynomFromJson(MultiPolynomStorage& poly, const json& terms) {
    for (const auto& term : terms) {
        double coeff = term["coefficient"];
        std::map<char, int> vars;
        for (const auto& [key, value] : term["variables"].items()) {
            vars[key[0]] = value;
        }
        poly.addTerm(coeff, vars);
    }
}

int main() {
    httplib::Server server;

    server.Post("/process", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json input = json::parse(req.body);

            MultiPolynomStorage p1, p2;
            createPolynomFromJson(p1, input["p1"]);
            createPolynomFromJson(p2, input["p2"]);

            MultiPolynomStorage sum = p1 + p2;
            MultiPolynomStorage diff = p1 - p2;
            MultiPolynomStorage prod = p1 * p2;

            json response;
            std::vector<std::string> storageTypes = {
                "avlTree", "collisionResolution", "hashChain",
                "orderedMap", "unorderedList", "unorderedMapArray"
            };

            for (const auto& type : storageTypes) {
                response["terms"][type] = {
                    {"p1", termsToJson(p1.getTermsFrom(type))},
                    {"p2", termsToJson(p2.getTermsFrom(type))},
                };

                response["operations"][type] = {
                    {"sum", termsToJson(sum.getTermsFrom(type))},
                    {"difference", termsToJson(diff.getTermsFrom(type))},
                    {"product", termsToJson(prod.getTermsFrom(type))}
                };
            }

            res.set_content(response.dump(2), "application/json");
            res.status = 200;

        }
        catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            res.set_content(error.dump(), "application/json");
            res.status = 400;
        }
        });

    std::cout << "Server started on port 8080..." << std::endl;
    server.listen("localhost", 8080);

    return 0;
}
