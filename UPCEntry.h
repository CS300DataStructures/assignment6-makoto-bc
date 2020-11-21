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
		  , name("") {}

    UPCEntry(unsigned long long upc, std::string name)
    	: upc(upc)
    	, name(std::move(name)) {}

	UPCEntry(const std::string& row);

	static UPCEntry parse(std::istream& file);

//    int hash1(int tableSize)
//    {
//        return upc % tableSize;
//    }
//
//    int hash2(int tableSize)
//    {
//        return std::abs(desc[0] + 27 * desc[1] + 729 * desc[2]) % tableSize;
//    }

	bool operator==(const UPCEntry& rhs) const {
		return std::tie(upc, name) == std::tie(rhs.upc, rhs.name);
	}

	friend std::ostream& operator<<(std::ostream& os, const UPCEntry& entry) {
		os << "{ upc: " << entry.upc << ", name: " << entry.name << " }";
		return os;
	}
};
#endif
