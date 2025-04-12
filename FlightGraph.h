#pragma once
#include "Flight.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <optional>

class FlightGraph
{
public:
	typedef std::vector<Flight> Route;
	typedef std::pair<Route, int> RouteWithCost;
	typedef std::vector<RouteWithCost> RouteList;

private:
	std::unordered_map<std::string, std::vector<Flight>> flightsGraph;

	void processFlightLine(const std::string& line);
	void readFromFile(const std::string& filename);
	void addFlight(const Flight& flight);
	void findRoutesRecursively(const std::string& current, const std::string& destination,
<<<<<<< HEAD
								std::set<std::string>& visited, Route& path, size_t currentCost,
								RouteList& allRoutes, const std::optional<int>& maxFlight, size_t currCount )const;
=======
								std::set<std::string>& visited, Route& path, int currentCost,
								RouteList& allRoutes, const std::optional<int>& maxFlight)const;
>>>>>>> afe148e4ea043600816a76ac16bba2f6083d5a60

public:

	FlightGraph(const std::string& filename);
	RouteList findAllRoutes(const std::string& origin, const std::string& destination, const std::optional<int> maxFlight) const;
	void printFlights() const;
	
};

