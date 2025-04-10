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
            std::cerr << "Skipping invalid flight: " << e.what() << '\n';
        }
    }
    else
    {
        std::cerr << "Invalid line format: " << line << '\n';
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

void FlightGraph::findRoutesRecursively(const std::string& current, const std::string& destination, std::set<std::string>& visited, Route& path, int currentCost, RouteList& allRoutes) const
{
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

            findRoutesRecursively(next, destination, visited, path, currentCost + flight.getPrice(), allRoutes);

            path.pop_back();
            visited.erase(next);
        }
    }
}

FlightGraph::FlightGraph(const std::string& filename)
{
	readFromFile(filename);
}
FlightGraph::RouteList FlightGraph::findAllRoutes(const std::string& origin, const std::string& destination) const
{
    RouteList allRoutes;
    std::set<std::string> visited;
    Route path;

    visited.insert(origin);
    findRoutesRecursively(origin, destination, visited, path, 0, allRoutes);

    std::sort(allRoutes.begin(), allRoutes.end(),
        [](const auto& a, const auto& b) 
        {
            return a.second < b.second;
        });

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

