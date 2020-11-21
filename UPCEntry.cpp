#include "UPCEntry.h"
#include <sstream>

UPCEntry::UPCEntry(const std::string& row) : UPCEntry() {
	std::stringstream ss(row);
	*this = parse(ss);
}

UPCEntry UPCEntry::parse(std::istream& file) {
	unsigned long long upc = 0;
	file >> upc;
	if (file.fail()) {
		throw std::runtime_error("invalid row");
	}

	char c = '\0';
	file >> c;
	if (c != ',') {
		throw std::runtime_error("invalid row");
	}

	std::string name;
	std::getline(file, name);
	return UPCEntry(upc, std::move(name));
}