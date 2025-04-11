#pragma once
#include <iostream>
#include <string>
#include <optional>
#include "json.hpp"
using json = nlohmann::json;

namespace JsonFields 
{
	inline constexpr auto ORIGIN = "origin";
	inline constexpr auto DESTINATION = "destination";
	inline constexpr auto MAX_FLIGHTS = "maxFlights";
}
class FlightJsonParser
{
public:
	struct Request
	{
		std::string origin;
		std::string destination;
		std::optional<int> maxFlights;
	};
	struct Route 
	{
		std::vector<std::string> route;
		double price;
	};
	
	static Request parseRequest(const std::string& jsonStr);
	static std::string createResponse(const std::vector<Route>& routes);
};

