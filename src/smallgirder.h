#ifndef SMALL_GIRDER_H
#define SMALL_GIRDER_H

#include "girder.h"
#include "stage.h"
#include <string>

#define SMALL_GIRDER_TYPE "SmallGirder"

class SmallGirder : public Girder {
public:
	SmallGirder(Stage& stage
		, const float x
		, const float y
		, const float angle_rad
		, const float longitude
		, const float height)
		: Girder(stage, x, y, angle_rad, longitude, height) {}

	virtual std::string get_type() override {
		return SMALL_GIRDER_TYPE;
	}
};

#endif
