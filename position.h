#ifndef ASSIGNMENT_6__POSITION_H_
#define ASSIGNMENT_6__POSITION_H_

#include <tuple>
#include <ostream>

/**
 * Sequencial index of an item in the hash table.
 */
class Position {
public:
	/**
	 * Position in the table. -1 means not found.
	 */
	int indexInTable = -1;

	/**
	 * Position in the linked list. -1 means not found.
	 */
	int indexInBin = -1;

	/**
	 * @return Position which indicates that an item was not found.
	 */
	static Position notFound() {
		return {-1, -1};
	}

	bool operator==(const Position& rhs) const {
		return std::tie(indexInTable, indexInBin) == std::tie(rhs.indexInTable, rhs.indexInBin);
	}

	friend std::ostream& operator<<(std::ostream& os, const Position& position) {
		os << "{ indexInTable: " << position.indexInTable << ", indexInBin: " << position.indexInBin
		   << " }";
		return os;
	}
};

#endif //ASSIGNMENT_6__POSITION_H_