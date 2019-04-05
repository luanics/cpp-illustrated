#pragma once

#include <iosfwd>

namespace luanics::grid {

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @class Grid
///
/// @brief Represents a fixed-size, two-dimensional grid of elements.
///
/// Standard way to display is with origin (0,0) at bottom left.
///
/// ^ y
/// |
/// |
/// *----> x
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class Grid {
public:
	//////////////////////////////////////////////////////////////////
	/// @name Definitions
	//////////////////////////////////////////////////////////////////
	//@{
	static constexpr char EmptyValue = ' ';
	using ValueType = char;
	//@}

	//////////////////////////////////////////////////////////////////
	/// @name Management
	//////////////////////////////////////////////////////////////////
	//@{
	virtual ~Grid() = default;
	//@}

	//////////////////////////////////////////////////////////////////
	/// @name Attributes
	//////////////////////////////////////////////////////////////////
	//@{
	virtual unsigned width() const = 0;
	virtual unsigned height() const = 0;
	//@}

	//////////////////////////////////////////////////////////////////
	/// @name Access
	//////////////////////////////////////////////////////////////////
	//@{
	/// @pre x < width and y < height
	virtual ValueType & operator()(unsigned const x, unsigned const y) = 0;
	/// @pre x < width and y < height
	virtual ValueType const & operator()(unsigned const x, unsigned const y) const = 0;
	//@}

	//////////////////////////////////////////////////////////////////
	/// @name Modification
	//////////////////////////////////////////////////////////////////
	//@{
	/// Fills with EmptyValue
	virtual void clear() = 0;
	virtual void fillWith(ValueType const value) = 0;
	//@}

	//////////////////////////////////////////////////////////////////
	/// @name Io
	//////////////////////////////////////////////////////////////////
	//@{
	/// Default implementation provided using operator()
	virtual void writeTo(std::ostream & out) const = 0;
	/// Default implementation provided using operator()
	virtual void readFrom(std::istream & in) = 0;
	//@}

}; // class Grid

std::ostream & operator<<(std::ostream & out, Grid const & grid);
std::istream & operator>>(std::istream & in, Grid & grid);

} // namespace luanics::grid
