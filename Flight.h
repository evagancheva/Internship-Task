#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <set>


class Flight
{
	std::string origin;
	std::string destination;
	int price;

	void setOrigin(const std::string& origin);
	void setDestination(const std::string& destination);
	void setPrice(int price);

	bool isValidCityCode(const std::string& cityCode) const;
public:
	Flight(const std::string& origin, const std::string destination, int price);

	std::string getOrigin() const;
	std::string getDestination() const;
	int getPrice() const;

	void printFlight() const;
};

