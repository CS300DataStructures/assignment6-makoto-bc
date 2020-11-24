#include "twoHashTable.h"
#include <fstream>

TwoHashTable TwoHashTable::parse(std::istream& file, size_t size) {
	TwoHashTable result(size);
	while (true) {
		file.peek();
		if (file.eof()) {
			return result;
		}

		if (!result.insert(UPCEntry::parse(file))) {
			throw std::runtime_error("invalid entry");
		}
	}
}

TwoHashTable::TwoHashTable(const std::string& filename, size_t size) : TwoHashTable(size) {
	std::ifstream file(filename);
	if (!file.good()) {
		throw std::runtime_error("file does not exist");
	}
	std::string s;
	std::getline(file, s); // Skip header
	*this = parse(file, size);
}

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
	if (tableSize == 0) {
		return {};
	}

	std::array<char, 3> firstThreeChars{};
	switch (entry.description.size()) {
	case 1:
		firstThreeChars = {entry.description[0], '\0', '\0'};
		break;
	case 2:
		firstThreeChars = {entry.description[0], entry.description[1], '\0'};
		break;
	default:
		firstThreeChars = {
			entry.description[0],
			entry.description[1],
			entry.description[2],
		};
	}

	return {{
		entry.upc % tableSize,
		(firstThreeChars[0] + 27 * firstThreeChars[1] + 729 * firstThreeChars[2]) % tableSize,
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

Position TwoHashTable::search(const UPCEntry& item) const {
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
