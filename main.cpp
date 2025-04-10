#include <iostream>
#include "FlightGraph.h"

int main()
{

    try {
        std::string filename = "flights.txt";
        FlightGraph graph(filename);

        std::string origin = "SOF";
        std::string destination = "MLE";

        std::cout << "Origin: " << origin << std::endl;
        std::cout << "Destination: " << destination << std::endl;

        auto routes = graph.findAllRoutes(origin, destination);

        if (routes.empty()) {
            std::cout << "No routes found from " << origin << " to " << destination << std::endl;
        }
        else {
            for (const auto& route : routes) {
                const auto& flights = route.first;
                int totalCost = route.second;

                for (size_t i = 0; i < flights.size(); ++i) {
                    std::cout << flights[i].getOrigin();
                    if (i == flights.size() - 1) {
                        std::cout << "," << flights[i].getDestination();
                    }
                    else {
                        std::cout << ",";
                    }
                }
                std::cout << "," << totalCost << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
    
}

