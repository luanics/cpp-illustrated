#include "luanics/crypto/Helpers.hpp"
#include "luanics/utility/Herald.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <limits>
#include <random>
#include <vector>

enum CryptoMode {ENCRYPT, DECRYPT};

/// This is the type of the incremental keys produced by the keystreams,
///  *not* the type of they top-level keys provided to the keystream generators.
using IncrementalKeyType = int8_t;

//*********************************************************
// Operator policies
//*********************************************************

template <CryptoMode ModeV>
struct ShiftOperator {
	char operator()(char const ch, IncrementalKeyType const stream) {
		if constexpr (ModeV == ENCRYPT) {
			return luanics::crypto::shift(ch, stream);
		}
		else {
			return luanics::crypto::shift(ch, -stream);
		}
	}
};

template <CryptoMode ModeV>
struct XorOperator {
	char operator()(char const ch, IncrementalKeyType const key) {
		return ch ^ key;
	}
};

//*********************************************************
// Keystream policies
//*********************************************************

struct PseudorandomKeystream {
	using EngineType = std::mt19937;
	using SeedType = EngineType::result_type;

	PseudorandomKeystream(SeedType const seed) :
		_engine{seed},
		_distribution{std::numeric_limits<IncrementalKeyType>::min(), std::numeric_limits<IncrementalKeyType>::max()}
	{}

	IncrementalKeyType operator()() {
		return _distribution(_engine);
	}

	EngineType _engine;
	std::uniform_int_distribution<IncrementalKeyType> _distribution;
};

struct FixedKeystream {
	FixedKeystream(IncrementalKeyType const key) : _incrementalKey{key} {}
	FixedKeystream(char const key) : _incrementalKey{} {}

	IncrementalKeyType operator()() const {return _incrementalKey;}

	IncrementalKeyType _incrementalKey;
};

struct RepeatingKeystream {
	static std::vector<IncrementalKeyType> keyFromString(std::string const & input) {
		std::vector<IncrementalKeyType> result;
		std::transform(
			input.begin(),
			input.end(),
			std::back_inserter(result),
			luanics::crypto::distanceFromA
		);
		return result;
	}

	RepeatingKeystream(std::vector<IncrementalKeyType> key) :
		_sequence{std::move(key)},
		_index{0}
	{}

	IncrementalKeyType operator()() {
		IncrementalKeyType result = _sequence[_index];
		_index += 1;
		_index %= _sequence.size();
		return result;
	}

	std::vector<std::int8_t> _sequence;
	std::size_t _index;
};

//*********************************************************
// Cipher
//*********************************************************


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///
/// @class KeystreamCipher
///
/// @brief Policy-based keystream cipher.
///
/// @tparam ModeV is the mode in which the cipher is operating
/// @tparam OperatorPolicyT governs how the characters are combined with incremental keys.
/// @tparam KeystreamPolicyT governs how the incremental keys are produced.
///
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
template <
	CryptoMode ModeV,
	template <CryptoMode> class OperatorPolicyT,
	typename KeystreamPolicyT
>
class KeystreamCipher {
public:
	template <typename KeyT>
	KeystreamCipher(KeyT && key) :
		_keystream{std::forward<KeyT>(key)},
		_operator{}
	{}

	std::string operator()(std::string text) {
		for (auto & character: text) {
			character = _operator(character, _keystream());
		}
		return std::move(text);
	}

private:
	KeystreamPolicyT _keystream;
	OperatorPolicyT<ModeV> _operator;
};

template <CryptoMode ModeV>
using CaesarCipher = KeystreamCipher<ModeV, ShiftOperator, FixedKeystream>;

template <CryptoMode ModeV>
using VigenereCipher = KeystreamCipher<ModeV, ShiftOperator, RepeatingKeystream>;

template <CryptoMode ModeV>
using PseudorandomXorCipher = KeystreamCipher<ModeV, XorOperator, PseudorandomKeystream>;

int main() {
	luanics::utility::Herald herald{"Policies"};

	{
		using Encrypter = CaesarCipher<CryptoMode::ENCRYPT>;
		using Decrypter = CaesarCipher<CryptoMode::DECRYPT>;

		int8_t const key = 2;
		Encrypter encrypter{key};
		Decrypter decrypter{key};
		std::string plaintext = "goodbye";
		std::string ciphertext = encrypter(plaintext);
		std::cout << plaintext << " -> " << ciphertext << std::endl;
		std::string decrypted = decrypter(ciphertext);
		assert(plaintext == decrypted);
	}

	{
		using Encrypter = VigenereCipher<CryptoMode::ENCRYPT>;
		using Decrypter = VigenereCipher<CryptoMode::DECRYPT>;

		auto key = RepeatingKeystream::keyFromString("hello");
		Encrypter encrypter{key};
		Decrypter decrypter{key};
		std::string plaintext = "goodbye";
		std::string ciphertext = encrypter(plaintext);
		std::cout << plaintext << " -> " << ciphertext << std::endl;
		std::string decrypted = decrypter(ciphertext);
		assert(plaintext == decrypted);
	}

	{
		using Encrypter = PseudorandomXorCipher<CryptoMode::ENCRYPT>;
		using Decrypter = PseudorandomXorCipher<CryptoMode::DECRYPT>;

		std::size_t key = 1;
		Encrypter encrypter{key};
		Decrypter decrypter{key};
		std::string plaintext = "hello";
		std::string ciphertext = encrypter(plaintext);
		std::cout << plaintext << " -> " << ciphertext << std::endl;
		std::string decrypted = decrypter(ciphertext);
		assert(plaintext == decrypted);
	}

	return 0;
}
