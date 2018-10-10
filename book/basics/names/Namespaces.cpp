#include <iostream>

#include <cstdint>

struct Person {
	std::string firstName;
	std::string lastName;
	uint8_t age;
};

namespace perez {
	Person jane{"Jane", "Perez", 45};
	Person alfonso{"Alfonso", "Perez", 40};
	Person elizabeth{"Elizabeth", "Perez", 10};
}

namespace smith {
	Person jane{"Jane", "Smith", 30};
	Person scott{"Scott", "Smith", 5};
}

namespace hospital {
	Person & chiefSurgeon = ::perez::jane;
	Person & headAdministrator = ::smith::jane;
}

void perezBirthdayParty() {
	using namespace perez;
	++jane.age;
}

void smithBirthdayParty() {
	using namespace smith;
	++jane.age;
}

void kidsBirthdayParty() {
	using namespace perez;
	using namespace smith;
	++elizabeth.age;
	++scott.age;
//	++jane.age; // Won't compile - which jane do you mean?
}

int main(int argc, char ** argv) {

	return 0;
}
