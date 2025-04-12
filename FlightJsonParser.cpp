#include "FlightJsonParser.h"

FlightJsonParser::Request FlightJsonParser::parseRequest(const std::string& jsonStr)
{
    try 
    {
        const auto j = json::parse(jsonStr);
        Request request;

        if (!j.contains(JsonFields::ORIGIN) || !j[JsonFields::ORIGIN].is_string()) 
        {
            throw std::runtime_error("Invalid/missing origin field");
        }
        j[JsonFields::ORIGIN].get_to(request.origin);  

        if (!j.contains(JsonFields::DESTINATION) || !j[JsonFields::DESTINATION].is_string()) 
        {
            throw std::runtime_error("Invalid/missing destination field");
        }
        j[JsonFields::DESTINATION].get_to(request.destination); 

        if (j.contains(JsonFields::MAX_FLIGHTS)) 
        {
            if (!j[JsonFields::MAX_FLIGHTS].is_number_integer()) 
            {
                throw std::runtime_error("Field max flights must be integer" );
            }
            int maxFlightsValue;
            j[JsonFields::MAX_FLIGHTS].get_to(maxFlightsValue);  
            request.maxFlights = maxFlightsValue;
            std::cout << request.maxFlights.value();
        }

        return request;
    }
    catch (const json::exception& e) 
    {
        throw std::runtime_error(std::string("JSON parsing error: ") + e.what());
    }
}

std::string FlightJsonParser::createResponse(const std::vector<Route>& routes)
{
    json response;
    response["routes"] = json::array();
    for (const auto& route : routes)
    {
        response["routes"].push_back({
            {"cities", route.cities},
            {"price", route.price}
            });
    }
    return response.dump(2);
}
