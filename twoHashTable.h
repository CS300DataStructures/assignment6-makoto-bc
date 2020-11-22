#include "position.h"
#include "UPCEntry.h"
#include "LinkedList.h"
#include "Option.h"
#include <cmath>
#include <string>
#include <vector>
#include <ostream>
#include <algorithm>

class TwoHashTable {
public:
	TwoHashTable()
		: TwoHashTable(0)
	{}

	explicit TwoHashTable(size_t size)
		: _buckets(std::make_unique<List<UPCEntry>[]>(size))
		, _size(size)
	{}

	TwoHashTable(const TwoHashTable& other) : TwoHashTable(other._size) {
		for (auto& entry : other.entries()) {
			insert(entry);
		}
	}

	TwoHashTable(TwoHashTable&& other) noexcept : TwoHashTable() {
		_buckets = std::move(other._buckets);
		_size = other._size;
	}

	TwoHashTable(const std::initializer_list<UPCEntry>& list) : TwoHashTable(list.size()) {
		for (const auto& entry : list) {
			insert(entry);
		}
	}

	TwoHashTable(const std::initializer_list<UPCEntry>& list, size_t size) : TwoHashTable(size) {
		for (const auto& entry : list) {
			insert(entry);
		}
	}

//    TwoHashTable(const std::string& filename, size_t size);

    bool insert(UPCEntry item);     // returns true if successful, false otherwise.

    std::vector<UPCEntry> entries() const;

//    Position search(UPCEntry &item); // if not found, return the default position with both indices set as -1

//    float getStdDev();

	bool operator==(const TwoHashTable& rhs) const {
		auto cmp = [](const UPCEntry& a, const UPCEntry& b) {
			return a.upc < b.upc;
		};
		auto entries0 = entries();
		std::sort(entries0.begin(), entries0.end(), cmp);
		auto entries1 = rhs.entries();
		std::sort(entries1.begin(), entries1.end(), cmp);
		return entries0 == entries1;
	}

	friend std::ostream& operator<<(std::ostream& os, const TwoHashTable& table);

private:
	std::unique_ptr<List<UPCEntry>[]> _buckets;
	size_t _size;
};

class Hash {
public:
	size_t h1;
	size_t h2;

	bool operator==(const Hash& rhs) const {
		return std::tie(h1, h2) == std::tie(rhs.h1, rhs.h2);
	}
};

Option<Hash> getHash(const UPCEntry& entry, size_t tableSize);
