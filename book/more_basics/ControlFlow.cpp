#include "luanics/logging/Contract.hpp"
#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <iostream>

//*******************************************************************
// Selection
//*******************************************************************

bool isOn() {
	return true;
}

void turnOff() {
	std::cout << "turning off" << std::endl;
}

enum class Tempo {
	LARGO,
	ADAGIO,
	ANDANTE,
	MODERATO,
	ALLEGRO
};

std::ostream & operator<<(std::ostream & out, Tempo const tempo) {
	switch (tempo) {
		case Tempo::LARGO:
			out << "LARGO";
			break;
		case Tempo::ADAGIO:
			out << "ADAGIO";
			break;
		case Tempo::ANDANTE:
			out << "ANDANTE";
			break;
		case Tempo::MODERATO:
			out << "MODERATO";
			break;
		case Tempo::ALLEGRO:
			out << "ALLEGRO";
			break;
		default: out << "UNKNOWN";
	}
	return out;
}

Tempo tempoFromBpm(int const bpm) {
	Tempo tempo;
	if (bpm <= 60) {
		tempo = Tempo::LARGO;
	}
	else if (bpm <= 76) {
		tempo = Tempo::ADAGIO;
	}
	else if (bpm <= 108) {
		tempo = Tempo::ANDANTE;
	}
	else if (bpm <= 120) {
		tempo = Tempo::MODERATO;
	}
	else {
		tempo = Tempo::ALLEGRO;
	}
	return tempo;
}

int bpmFromTempo(Tempo const tempo) {
	int result;
	switch (tempo) {
		case Tempo::LARGO: result = 50; break;
		case Tempo::ADAGIO: result = 70; break;
		case Tempo::ANDANTE: result = 90; break;
		case Tempo::MODERATO: result = 110; break;
		case Tempo::ALLEGRO: result = 130; break;
		default: UNREACHABLE("Invalid Tempo");
	}
	return result;
}

class Guitar {
public:
	Guitar() = default;

	bool hasBasics() const {return _hasBasics;}
	bool hasGoldHardware() const {return _hasGoldHardware;}
	bool hasDiamondInlays() const {return _hasPearlInlays;}

	void addBasics() {_hasBasics = true;}
	void addGoldHardware() {_hasGoldHardware = true;}
	void addPearlInlays() {_hasPearlInlays = true;}

private:
	bool _hasBasics = false;
	bool _hasGoldHardware = false;
	bool _hasPearlInlays = false;
};

enum class Trim {BASE, DELUXE, LUXURY};

void applyTrim(Trim const trim, Guitar & guitar) {
	switch (trim) {
		case Trim::LUXURY:
			guitar.addPearlInlays();
			[[fallthrough]]
		case Trim::DELUXE:
			guitar.addGoldHardware();
			[[fallthrough]]
		case Trim::BASE:
			guitar.addBasics();
			break;
	}
}

double costOfPearlPerOunce() {
	return 100.0;
}

double costOfGoldPerOunce() {
	return 100.0;
}

//*******************************************************************
// Iteration
//*******************************************************************

/// @returns number of mistakes made
int practiceWarmupsAt(int const bpm) {
	std::cout << "practiceWarmupsAt(" << bpm << ");" << std::endl;
	return 1;
}

void singMeasureWith(int const numVoices) {
	std::cout << "singMeasureWith(" << numVoices << ");" << std::endl;
}

void play(int const measure, int const beat) {
	std::cout << "play(" << measure << "," << beat << ");" << std::endl;
}

void strum(char const chord) {
	std::cout << "strum(" << chord << ");" << std::endl;
}

bool isAudienceHappy() {
	return false;
}

void playSong() {
	std::cout << "playSong()" << std::endl;
}

//*******************************************************************
// Jump Statements
//*******************************************************************

int timeRemaining() {
	return 1;
}

Tempo tempoFromBpm2(int const bpm) {
	if (bpm <= 60) return Tempo::LARGO;
	else if (bpm <= 76) return Tempo::ADAGIO;
	else if (bpm <= 108) return Tempo::ANDANTE;
	else if (bpm <= 120) return Tempo::MODERATO;
	else return Tempo::ALLEGRO;
}

bool unpackGuitar(bool isSuccessful = true) {
	std::cout << "unpackGuitar(): " << isSuccessful << std::endl;
	return isSuccessful;
}
bool plugInGuitar(bool isSuccessful = true) {
	std::cout << "plugInGuitar(): " << isSuccessful << std::endl;
	return isSuccessful;
}
bool turnOnAmp(bool isSuccessful = true) {
	std::cout << "turnOnAmp(): " << isSuccessful << std::endl;
	return isSuccessful;
}
void playGuitar() {
	std::cout << "playGuitar()" << std::endl;
}
void turnOffAmp() {
	std::cout << "turnOffAmp()" << std::endl;
}
void unplugGuitar() {
	std::cout << "unplugGuitar()" << std::endl;
}
void packGuitar() {
	std::cout << "packGuitar()" << std::endl;
}

struct SetupError {};

struct GuitarUnpacker {
	GuitarUnpacker(bool isSuccessful = true) {
		if (not unpackGuitar(isSuccessful)) throw SetupError{};
	}
	~GuitarUnpacker() {packGuitar();}
};
struct GuitarPlugger {
	GuitarPlugger(bool isSuccessful = true) {
		if (not plugInGuitar(isSuccessful)) throw SetupError{};
	}
	~GuitarPlugger() {unplugGuitar();}
};
struct AmpPowerer {
	AmpPowerer(bool isSuccessful = true) {
		if (not turnOnAmp(isSuccessful)) throw SetupError{};
	}
	~AmpPowerer() {turnOffAmp();}
};

//*******************************************************************
// Main
//*******************************************************************

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"ControlFlow"};

	//*******************************************************************
	// Instruction Pointer
	//*******************************************************************
	int volume = 8;
	volume = 9;
	volume = 10;

	//*******************************************************************
	// Selection
	//*******************************************************************

	if (isOn()) {
		turnOff();
	}

	assert(tempoFromBpm(50) == Tempo::LARGO);
	assert(tempoFromBpm(90) == Tempo::ANDANTE);
	assert(tempoFromBpm(144) == Tempo::ALLEGRO);

	Tempo tempo = Tempo::LARGO;
	std::cout << "The tempo is " << tempo << std::endl;

	Guitar guitar1;
	applyTrim(Trim::DELUXE, guitar1);

	Guitar guitar;
	double price = 0.0;
	Trim trim = Trim::LUXURY;
	switch (trim) {
		case Trim::LUXURY: {
			guitar.addPearlInlays();
			double const premium = 100 + costOfPearlPerOunce() * 0.2;
			price += premium;
		}
		[[fallthrough]]
		case Trim::DELUXE: {
			guitar.addGoldHardware();
			double const premium = 50 + costOfGoldPerOunce() * 0.1;
			price += premium;
		}
		[[fallthrough]]
		case Trim::BASE:
			guitar.addBasics();
			price += 500;
			break;
	}

	//*******************************************************************
	// Iteration
	//*******************************************************************

	for (int bpm = 80; bpm < 120; bpm += 10)
		practiceWarmupsAt(bpm);

	int initialBpm = 120;
	for (int bpm = initialBpm; bpm < 120; bpm += 10)
		practiceWarmupsAt(bpm);

//	for (uint8_t numVoices = 8; numVoices >= 0; --numVoices) {
//		singMeasureWith(numVoices);
//	}

	for (int8_t numVoices = 8; numVoices >= 0; --numVoices) {
		singMeasureWith(numVoices);
	}

	for (uint8_t numVoicesPlusOne = 9; numVoicesPlusOne > 0; --numVoicesPlusOne) {
		uint8_t const numVoices = numVoicesPlusOne - 1;
		singMeasureWith(numVoices);
	}

	for (uint8_t numVoices = 8; numVoices != static_cast<uint8_t>(-1); --numVoices) {
		singMeasureWith(numVoices);
	}


	for (unsigned measure = 1; measure <= 10; ++measure) {
		for (unsigned beat = 1; beat <= 4; ++beat) {
			play(measure, beat);
		}
	}

	std::string chords{'C', 'F', 'G', 'C'};
	for (auto const & chord: chords) {
		strum(chord);
	}

	while (isAudienceHappy()) {
		playSong();
	}

	do {
		playSong();
	}
	while (isAudienceHappy());

	//*******************************************************************
	// Jump Statements
	//*******************************************************************

	for (int bpm = 80; bpm < 120; bpm += 10) {
		int const numMistakes = practiceWarmupsAt(bpm);
		if (numMistakes == 0) continue;
		practiceWarmupsAt(bpm);
		if (timeRemaining() == 0) break;
	}

	int bpm = 80;
	check: if (not (bpm < 120)) goto finish;
	practiceWarmupsAt(bpm);
	bpm += 10;
	goto check;
	finish:

	if (not unpackGuitar())
		goto failed_unpack_guitar;
	if (not plugInGuitar(false))
		goto failed_plug_in_guitar;
	if (not turnOnAmp())
		goto failed_turn_on_amp;

	playGuitar();

		turnOffAmp();
	failed_turn_on_amp:
		unplugGuitar();
	failed_plug_in_guitar:
		packGuitar();
	failed_unpack_guitar:
		;

	try {
		GuitarUnpacker unpacker;
		GuitarPlugger plugger;
		AmpPowerer powerer{false};
		playGuitar();
	}
	catch (SetupError const & error) {
		std::cout << "An error occurred during setup" << std::endl;
	}

	return 0;
}
