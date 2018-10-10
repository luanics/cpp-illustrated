#include "luanics/utility/Herald.hpp"

#include <cassert>
#include <cmath>
#include <cstring>
#include <experimental/filesystem>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

//*********************************************************
// Tuple and Pair
//*********************************************************

std::tuple<std::string, std::string, int> info() {
	return {"John", "Private", 101};
}

//*********************************************************
// Main
//*********************************************************

int main(int argc, char ** argv) {
	luanics::utility::Herald herald{"Library"};

	//*********************************************************
	// String
	//*********************************************************

	std::string document;
	assert(document.empty());
	assert(document.size() == 0);
	document.append("Prince");
	assert(not document.empty());
	assert(document.size() == 6);
	document.insert(0, "Well, ");
	assert(document.size() == 12);
	assert(document == "Well, Prince");
	assert(document[0] == 'W');
	assert(document.back() == 'e');

	std::string const title{"War and Peace"}; // direct init
	std::string const author = "Tolstoy";     // copy init

	assert(7 == std::strlen("Tolstoy"));

	//*********************************************************
	// Value Semantics
	//*********************************************************

	std::string theBard{"Shakespeare"};
	std::string theFraud = theBard; // value semantics
	theFraud.replace(1, 4, "teak");
	assert(theBard == "Shakespeare");
	assert(theFraud == "Steakspeare");

	//*********************************************************
	// Tuple and Pair
	//*********************************************************

	std::tuple<std::string, char, std::string> x;

	std::tuple ones{1, '1', "one"};
//	assert(ones.size() == 3); // ERROR - no size() method
	static_assert(std::tuple_size<decltype(ones)>::value == 3);
//	assert(ones[0] == 1);     // ERROR - no operator[] method
	assert(std::get<0>(ones) == 1);
	assert(std::get<1>(ones) == '1');
	assert(std::strcmp(std::get<2>(ones),"one")==0);

	auto [name, rank, serialNumber] = info();
	assert(name=="John" and rank=="Private" and serialNumber==101);

	auto const & [one1, one2, one3] = ones;
	assert(one1==1 and one2=='1' and std::strcmp(one3,"one")==0);

	//*********************************************************
	// Array
	//*********************************************************

	std::array<std::string, 4> bookshelf = {
		"War and Peace",
		"The Odyssey",
		"Heidi",
		"Alice in Wonderland"
	};
	assert(bookshelf.size() == 4);
	assert(bookshelf.front() == "War and Peace");
	assert(bookshelf.back() == "Alice in Wonderland");
	assert(bookshelf[1] == "The Odyssey");
	bookshelf[1] = "Tom Sawyer";
	assert(bookshelf[1] == "Tom Sawyer");

	//*********************************************************
	// Vector
	//*********************************************************

	std::vector<std::string> books = {
		"War and Peace",
		"The Odyssey",
		"Heidi",
		"Alice in Wonderland"
	};
	assert(books.size() == 4);
	books.push_back("The Great Gatsby");
	assert(books.size() == 5);
	assert(books.back() == "The Great Gatsby");
	books.pop_back();
	assert(books.size() == 4);
	assert(books.back() == "Alice in Wonderland");

	//*********************************************************
	// List
	//*********************************************************

	std::list<std::string> readingList = {
		"War and Peace",
		"The Odyssey",
		"Heidi"
	};
//	assert(readingList[1] == "The Odyssey"); // ERROR - no operator[]
	assert(readingList.size() == 3);
	readingList.pop_front();
	assert(readingList.size() == 2);
	assert(readingList.front() == "The Odyssey");
	readingList.front() = "Tom Sawyer";
	assert(readingList.front() == "Tom Sawyer");
	readingList.push_back("Alice in Wonderland");
	assert(readingList.size() == 3);
	assert(readingList.back() == "Alice in Wonderland");

	//*********************************************************
	// Set
	//*********************************************************

	std::set<std::string> bookBag = {
		"War and Peace",
		"The Odyssey",
		"Heidi",
		"Alice in Wonderland"
	};
	assert(bookBag.count("The Odyssey") == 1);
	assert(bookBag.count("Tom Sawyer") == 0);
	bookBag.erase("The Odyssey");
	bookBag.insert("Tom Sawyer");
	assert(bookBag.count("The Odyssey") == 0);
	assert(bookBag.count("Tom Sawyer") == 1);

	//*********************************************************
	// Map
	//*********************************************************

	using KeyType = std::string;
	using ValueType = int;
	std::map<KeyType, ValueType> bookCount = {
		{"War and Peace", 9},
		{"The Odyssey", 1},
		{"Heidi", 3},
		{"Alice in Wonderland", 20}
	};
	assert(bookCount["War and Peace"] = 9);
	assert(bookCount.size() == 4);
	assert(bookCount["Tom Sawyer"] == 0);
	assert(bookCount.size() == 5);

	//*********************************************************
	// IO
	//*********************************************************

	//*********************************************************
	// Filesystem
	//*********************************************************

	// Create a temporary directory structure to work in.
	namespace fs = std::experimental::filesystem;
	std::cout << "Temporary directory=" << fs::temp_directory_path() << std::endl;
	fs::path const libraryPath = fs::temp_directory_path() / "library";
	if (exists(libraryPath)) remove_all(libraryPath); // start with a clean slate
	bool const isLibraryNewlyCreated = create_directory(libraryPath);
	assert(isLibraryNewlyCreated);
	assert(is_directory(libraryPath));
	auto const booksPath = libraryPath / "books";
	bool const isBooksCreated = create_directory(booksPath);
	assert(isBooksCreated);
	auto const booksAPath = booksPath / "a";
	bool const isBooksACreated = create_directory(booksAPath);
	assert(isBooksACreated);
	auto const booksBPath = booksPath / "b";
	bool const isBooksBCreated = create_directory(booksBPath);
	assert(isBooksBCreated);
	bool const isBooksBCreatedTwice = create_directory(booksBPath);
	assert(not isBooksBCreatedTwice);

	fs::path const mediaAPath = libraryPath / "media" / "a";
	assert(fs::create_directories(mediaAPath)); // recursive

	// Create some files in the directories.
	auto const alligatorsPath = booksAPath / "Alligators.txt";
	std::ofstream alligatorsFile{alligatorsPath};
	assert(alligatorsFile);
	auto const appalachianPath = booksAPath / "AppalachianAntics.txt";
	std::ofstream appalachinFile{appalachianPath};
	assert(appalachinFile);

	// Verify that we have some files in the books/a directory.
	auto itr = fs::directory_iterator(booksAPath);
	std::size_t const numFiles = std::distance(fs::begin(itr), fs::end(itr));
	assert(numFiles==2);

	//*********************************************************
	// Math
	//*********************************************************

	assert(std::trunc(1.5) == 1.0);
	assert(std::floor(1.5) == 1.0);
	assert(std::ceil(1.5) == 2.0);
	assert(std::trunc(-1.5) == -1.0);
	assert(std::floor(-1.5) == -2.0);
	assert(std::ceil(-1.5) == -1.0);

	return 0;
}
