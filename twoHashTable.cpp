#include "twoHashTable.h"
#include <algorithm>

bool TwoHashTable::insert(UPCEntry item) {
	auto hashResult = getHash(item, _size);
	if (!hashResult.hasValue()) {
		return false;
	}

	size_t bucketIndex = 0;
	Hash& hash = hashResult.value();
	if (_buckets[hash.h1].size() <= _buckets[hash.h2].size()) {
		bucketIndex = hash.h1;
	} else {
		bucketIndex = hash.h2;
	}
	_buckets[bucketIndex].insert(0, std::move(item));
	return true;
}

Option<Hash> getHash(const UPCEntry& entry, size_t tableSize) {
	if (entry.name.size() < 3 || tableSize == 0) {
		return {};
	}

	return {{
		entry.upc % tableSize,
		(entry.name[0] + 27 * entry.name[1] + 729 * entry.name[2]) % tableSize,
	}};
}

std::vector<UPCEntry> TwoHashTable::entries() const {
	std::vector<UPCEntry> result;
	for (size_t bucketIndex = 0; bucketIndex < _size; ++bucketIndex) {
		for (size_t listIndex = 0; listIndex < _buckets[bucketIndex].size(); ++listIndex) {
			result.push_back(_buckets[bucketIndex][listIndex]);
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const TwoHashTable& table) {
	os << "{ ";
	auto entries = table.entries();
	for (size_t i = 0; i < entries.size(); ++i) {
		os << entries[i];

		if (i < entries.size() - 1) {
			os << ", ";
		}
	}
	os << " }";
	return os;
}

float stddev(int *binLengths, int tableSize)
{
	float sum = 0;
	for (int i = 0; i < tableSize; i++)
		sum += binLengths[i];

	float avarage = sum / tableSize;

	float dev_sum = 0;
	for (int i = 0; i < tableSize; i++)
	{
		dev_sum = dev_sum + (binLengths[i] - avarage) * (binLengths[i] - avarage);
	}

	float variance = dev_sum / tableSize;
	return sqrt(variance);
}
