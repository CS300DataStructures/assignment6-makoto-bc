#ifndef ASSIGNMENT_6__OPTIONAL_H_
#define ASSIGNMENT_6__OPTIONAL_H_

#include <stdexcept>
#include <ostream>

/**
 * An optional value.
 */
template<class T>
class Option {
public:
	Option()
		: _valid(false) {}

	Option(T value) // NOLINT(google-explicit-constructor)
		: _valid(true)
		, _value(std::move(value)) {}

	/**
	 * @return The value
	 * @throws std::runtime_error This does not contain a value
	 */
	T& value() {
		return const_cast<T&>(const_cast<const Option*>(this)->value());
	}

	/**
	 * @return The value
	 * @throws std::runtime_error This does not contain a value
	 */
	const T& value() const {
		if (!_valid) {
			throw std::runtime_error("does not contain a value");
		}

		return _value;
	}

	/**
	 * @return true if this contains a value
	 */
	bool hasValue() const {
		return _valid;
	}

	bool operator==(const Option& rhs) const {
		return (!_valid && !rhs._valid) || (_valid == rhs._valid && _value == rhs._value);
	}
private:
	bool _valid;
	T _value;
};

#endif //ASSIGNMENT_6__OPTIONAL_H_
