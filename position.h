#ifndef ASSIGNMENT_6__POSITION_H_
#define ASSIGNMENT_6__POSITION_H_

#include <tuple>
#include <ostream>

class Position {
public:
    int indexInTable = -1; //position in the table.
    int indexInBin = -1;   // position in the linked list.

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