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

Position TwoHashTable::search(UPCEntry& item) {
	auto hashResult = getHash(item, _size);
	if (!hashResult.hasValue()) {
		return Position::notFound();
	}

	for (size_t hash : std::array<size_t, 2>{hashResult.value().h1, hashResult.value().h2}) {
		for (size_t i = 0; i < _buckets[hash].size(); ++i) {
			if (_buckets[hash][i].upc == item.upc) {
				return {static_cast<int>(hash), static_cast<int>(i)};
			}
		}
	}
	return Position::notFound();
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

double TwoHashTable::getStdDev() {
	double sum = 0;
	for (size_t i = 0; i < _size; ++i) {
		sum += _buckets[i].size();
	}
	double average = sum / _size;

	double deviationSum = 0;
	for (size_t i = 0; i < _size; ++i) {
		deviationSum += (_buckets[i].size() - average) * (_buckets[i].size() - average);
	}

	return std::sqrt(deviationSum / _size);
}
