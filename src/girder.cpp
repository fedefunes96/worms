#include "girder.h"
#include "static.h"
#include "stage.h"
#include <string>

Girder::Girder(Stage& stage, const int x, const int y, const int angle_rad
, const int longitude, const int height)
 : Static(stage, x, y, angle_rad, longitude, height) {
 	this->body->SetUserData(this);
}

std::string Girder::get_type() {
	return GIRDER_TYPE;
}