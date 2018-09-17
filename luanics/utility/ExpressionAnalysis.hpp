#pragma once

#include "luanics/logging/Contract.hpp"

namespace luanics {

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class ValueCategory
///
/// @brief Enumeration for the terminal categories of value category.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
enum class ValueCategory {
	LVALUE,
	XVALUE,
	PRVALUE
};

inline std::ostream & operator<<(std::ostream & out, ValueCategory const value) {
	switch (value) {
		case ValueCategory::LVALUE: out << "LVALUE"; break;
		case ValueCategory::XVALUE: out << "XVALUE"; break;
		case ValueCategory::PRVALUE: out << "PRVALUE"; break;
		default: NEVER_REACHED(static_cast<int>(value));
	}
	return out;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class ExpressionAnalysis
///
/// @brief Contains the *type* and *value category* of an expression.
///
/// Remember that the type of expressions is always *object* type.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <typename T, ValueCategory V>
struct ExpressionAnalysis {
	static constexpr ValueCategory value = V;
	using type = T;

	static void writeTo(std::ostream & out) {
		out << "(";
		writeTypeTo(out);
		out << ",";
		writeValueCategoryTo(out);
		out << ")";
	}
	static void writeValueCategoryTo(std::ostream & out) {
		out << value;
	}
	static void writeTypeTo(std::ostream & out) {
		// typeid doesn't include cv-ness ...
		out << typeid(T).name();
		// ... so we include it ourselves.
		if constexpr (std::is_const_v<T>) {
			out << " const";
		}
		if constexpr (std::is_volatile_v<T>) {
			out << " volatile";
		}
	}

};

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class AnalyzeExpression
///
/// @brief Type metafunction that returns ExpressionAnalysis
///
/// Value category analysis based on idea presented by Luc Danton:
///  https://stackoverflow.com/questions/16637945/empirically-determine-value-category-of-c11-expression
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <typename T>
struct AnalyzeExpression;

/// Primary template matches all types.
template <typename T>
struct AnalyzeExpression {
	///  Since decltype(e) is non-ref for prvalue expression e,
	///   the value category is PRVALUE.
	using type = ExpressionAnalysis<T, ValueCategory::PRVALUE>;
};

/// Universal reference specialization, matches all reference types.
template <typename T>
struct AnalyzeExpression<T &&> {
	/// Since decltype(e) is an rvalue ref for xvalue expression e,
	///  the value category is XVALUE.
	using type = ExpressionAnalysis<T, ValueCategory::XVALUE>;
};

/// Lvalue reference specialization, matches *only* lvalue refs.
template <typename T>
struct AnalyzeExpression<T &> {
	///  Since decltype(e) is an lvalue ref for lvalue expression e,
	///  the value category is LVALUE
	using type = ExpressionAnalysis<T, ValueCategory::LVALUE>;
};

} // namespace luanics

#define VALUE_CATEGORY_OF(x) luanics::AnalyzeExpression<decltype((x))>::type::value
#define TYPE_OF(x) typename luanics::AnalyzeExpression<decltype((x))>::type::type
#define ANALYSIS_OF(x) luanics::AnalyzeExpression<decltype((x))>::type
#define PRINT_ANALYSIS_OF(x) std::cout << "(" << #x << ") -> "; luanics::AnalyzeExpression<decltype((x))>::type::writeTo(std::cout); std::cout << std::endl
