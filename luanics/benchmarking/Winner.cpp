#include "luanics/benchmarking/Winner.hpp"

namespace luanics {
namespace benchmarking {

std::ostream & operator<<(std::ostream & out, Winner const winner) {
	switch (winner) {
		case Winner::CHALLENGER: out << "CHALLENGER"; return out;
		case Winner::DEFENDER: out << "DEFENDER"; return out;
		case Winner::TIE: out << "TIE"; return out;
		default: return out;
	}
}

} // namespace benchmarking
} // namespace luanics
