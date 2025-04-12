#include "FlightGraph.h"

void FlightGraph::processFlightLine(const std::string& line)
{
    std::istringstream ss(line);
    std::string origin, destination;
    int price;

    if (std::getline(ss, origin, ',') && std::getline(ss, destination, ',') && (ss >> price))
    {
        try 
        {
            Flight flight(origin, destination, price);
            addFlight(flight);
        }
        catch (const std::exception& e) 
        {
            std::cout << "Skipping invalid flight: " << e.what() << '\n';
        }
    }
    else
    {
        std::cout << "Invalid line format: " << line << '\n';
    }
}


void FlightGraph::readFromFile(const std::string& filename)
{
	if (filename.empty())
	{
		throw std::invalid_argument("Filename cannot be empty.");
	}
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open file with flights.");
	}
	std::string line;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			processFlightLine(line);
		}
	}

}

void FlightGraph::addFlight(const Flight& flight)
{
    flightsGraph[flight.getOrigin()].push_back(flight);
}

<<<<<<< HEAD
void FlightGraph::findRoutesRecursively(const std::string& current, const std::string& destination, std::set<std::string>& visited, Route& path, size_t currentCost, RouteList& allRoutes, const std::optional<int>& maxFlight, size_t currCount) const
{
    if (maxFlight.has_value() && currCount > maxFlight.value())
=======
void FlightGraph::findRoutesRecursively(const std::string& current, const std::string& destination, std::set<std::string>& visited, Route& path, int currentCost, RouteList& allRoutes, const std::optional<int>& maxFlight) const
{
    if (maxFlight.has_value() && currentCost > maxFlight.value()) 
>>>>>>> afe148e4ea043600816a76ac16bba2f6083d5a60
    {
        return;
    }
    if (current == destination) 
    {
        allRoutes.emplace_back(path, currentCost);
        return;
    }

    auto it = flightsGraph.find(current);
    if (it == flightsGraph.end()) 
    {
        return;
    }

    for (const Flight& flight : it->second) 
    {
        const std::string& next = flight.getDestination();
        if (visited.find(next) == visited.end()) 
        {
            visited.insert(next);
            path.push_back(flight);

<<<<<<< HEAD
            findRoutesRecursively(next, destination, visited, path, currentCost + flight.getPrice(), allRoutes,maxFlight, currCount+1);
=======
            findRoutesRecursively(next, destination, visited, path, currentCost + flight.getPrice(), allRoutes,maxFlight);
>>>>>>> afe148e4ea043600816a76ac16bba2f6083d5a60

            path.pop_back();
            visited.erase(next);
        }
    }
}

FlightGraph::FlightGraph(const std::string& filename)
{
	readFromFile(filename);
}
FlightGraph::RouteList FlightGraph::findAllRoutes(const std::string& origin, const std::string& destination, const std::optional<int> maxFlights) const
{
<<<<<<< HEAD
    
=======
>>>>>>> afe148e4ea043600816a76ac16bba2f6083d5a60
    RouteList allRoutes;
    std::set<std::string> visited;
    Route path;

    visited.insert(origin);
<<<<<<< HEAD
    findRoutesRecursively(origin, destination, visited, path, 0, allRoutes, maxFlights,0);
=======
    findRoutesRecursively(origin, destination, visited, path, 0, allRoutes, maxFlights);
>>>>>>> afe148e4ea043600816a76ac16bba2f6083d5a60

    std::sort(allRoutes.begin(), allRoutes.end(),
        [](const auto& a, const auto& b) {return a.second < b.second; });

    return allRoutes;
}
void FlightGraph::printFlights() const 
{
	for (const auto& pair : flightsGraph) 
	{
		const std::string& origin = pair.first;
		const std::vector<Flight>& flights = pair.second;
		std::cout << "Flights from " << origin << ":\n";
		for (const Flight& flight : flights) 
		{
			flight.printFlight();
		}
	}
}

