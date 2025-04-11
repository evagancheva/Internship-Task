#include "Flight.h"

void Flight::setOrigin(const std::string& origin)
{
	if (origin.empty() || !isValidCityCode(origin))
	{
		throw std::invalid_argument("Origin cannot be empty");
	}

	this->origin = origin;
}

void Flight::setDestination(const std::string& destination)
{
	if (destination.empty() || !isValidCityCode(destination))
	{
		throw std::invalid_argument("Destination cannot be empty");
	}

	this->destination = destination;
}

void Flight::setPrice(int price)
{
	if (price < 0)
	{
		throw std::invalid_argument("Price cannot be negative");
	}
	this->price = price;
}

bool Flight::isValidCityCode(const std::string& cityCode) 
{

	if (cityCode.length() != 3) 
	{
		throw std::invalid_argument("City code must be exactly 3 characters long.");
	}

	std::set<char> charSet;
	for (char c : cityCode) 
	{
		if (!std::isupper(c)) 
		{  
			throw std::invalid_argument("City code must contain only uppercase letters.");
		}
		if (charSet.find(c) != charSet.end()) 
		{ 
			throw std::invalid_argument("City code must not contain duplicate characters.");
		}
		charSet.insert(c);
	}

	return true;
}

Flight::Flight(const std::string& origin, const std::string& destination, int price)
{
	if (origin == destination)
	{
		throw std::invalid_argument("Origin and Destination need to be different");
	}

	setOrigin(origin);
	setDestination(destination);
	setPrice(price);
}

std::string Flight::getOrigin() const
{
	return origin;
}

std::string Flight::getDestination() const
{
	return destination;
}

int Flight::getPrice() const
{
	return price;
}

void Flight::printFlight() const
{
	std::cout << "," << origin << "," << destination << "," << price << std::endl;
}

