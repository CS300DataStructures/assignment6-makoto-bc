#ifndef ASSIGNMENT_6__UPCENTRY_H_
#define ASSIGNMENT_6__UPCENTRY_H_

#include <string>
#include <utility>
#include <tuple>
#include <ostream>

/**
 * An entry in TwoHashTable which contains UPC and description.
 */
class UPCEntry
{
public:
    unsigned long long upc;
    std::string description;

	UPCEntry()
		: upc(0)
	{}

    UPCEntry(unsigned long long upc, std::string name)
    	: upc(upc)
    	, description(std::move(name)) {}

	/**
	 * Parses row.
	 */
	explicit UPCEntry(const std::string& row);

	/**
	 * Reads one row from database file.
	 */
	static UPCEntry parse(std::istream& file);

	bool operator==(const UPCEntry& rhs) const {
		return std::tie(upc, description) == std::tie(rhs.upc, rhs.description);
	}

	friend std::ostream& operator<<(std::ostream& os, const UPCEntry& entry) {
		os << "{ upc: " << entry.upc << ", name: " << entry.description << " }";
		return os;
	}
};

#endif //ASSIGNMENT_6__UPCENTRY_H_
