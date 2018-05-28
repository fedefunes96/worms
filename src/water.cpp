#include "water.h"

Water::Water() {}

void Water::set_water_level(const float water_level) {
	this->water_level = water_level;
}

float Water::get_water_level() {
	return this->water_level;
}