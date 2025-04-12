#include "Solution.h"

void Solution::run()
{
    try
    {
        FlightGraph graph("flights.txt");
        httplib::Server svr;

        svr.Post("/search", [&graph](const httplib::Request& req, httplib::Response& res)
            {
                try
                {
                    auto request = FlightJsonParser::parseRequest(req.body);
                    if (request.maxFlights.has_value() && request.maxFlights.value() < 0)
                    {
                        res.status = 400;
                        json error = { {"error", "maxFlights must be >= 0"} };
                        res.set_content(error.dump(), "application/json");
                        return;
                    }
                    auto routesWithCost = graph.findAllRoutes(
                        request.origin,
                        request.destination,
                        request.maxFlights
                    );

                    std::vector<FlightJsonParser::Route> responseRoutes;
                    for (const auto& [route, cost] : routesWithCost)
                    {
                        std::vector<std::string> cities;
                        for (const auto& flight : route)
                        {
                            if (cities.empty())
                            {
                                cities.push_back(flight.getOrigin());
                            }
                            cities.push_back(flight.getDestination());
                        }
                        responseRoutes.push_back({ cities, static_cast<double>(cost) });
                    }

                    std::string responseJson = FlightJsonParser::createResponse(responseRoutes);
                    res.set_content(responseJson, "application/json");
                }
                catch (const std::exception& e)
                {
                    res.status = 400;
                    res.set_content(std::string("Error:") + e.what(), "application/json");
                }
            });

        svr.listen("0.0.0.0", 9999);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to start server: " << e.what() << std::endl;
        return;
    }
}
