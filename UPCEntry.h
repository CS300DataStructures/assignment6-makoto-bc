#ifndef UPC_ENTRY
#define UPC_ENTRY
#include <string>
#include <utility>
#include <tuple>
#include <ostream>

class UPCEntry
{
public:
    unsigned long long upc;
    std::string name;

	UPCEntry()
		: upc(0)
	{}

    UPCEntry(unsigned long long upc, std::string name)
    	: upc(upc)
    	, name(std::move(name)) {}

	explicit UPCEntry(const std::string& row);

	static UPCEntry parse(std::istream& file);

	bool operator==(const UPCEntry& rhs) const {
		return std::tie(upc, name) == std::tie(rhs.upc, rhs.name);
	}

	friend std::ostream& operator<<(std::ostream& os, const UPCEntry& entry) {
		os << "{ upc: " << entry.upc << ", name: " << entry.name << " }";
		return os;
	}
};
#endif
