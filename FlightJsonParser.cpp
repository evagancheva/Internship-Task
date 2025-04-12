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
<<<<<<< HEAD
            std::cout << request.maxFlights.value();
=======
>>>>>>> afe148e4ea043600816a76ac16bba2f6083d5a60
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
<<<<<<< HEAD
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
=======
    json j = json::array();

    for (const auto& route : routes)
    {
        j.push_back({ {"route", route.route}, {"price", route.price} });
    }
    return j.dump(4);
>>>>>>> afe148e4ea043600816a76ac16bba2f6083d5a60
}
