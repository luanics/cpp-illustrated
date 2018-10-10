#pragma once

// Interface

class Car {
public:
	int speedInMph() const;
	void go();
	void stop();
private:
	int speedInMph_;
};
