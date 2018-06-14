#ifndef LARGE_GIRDER_H
#define LARGE_GIRDER_H

#include "girder.h"
#include "stage.h"
#include <string>

#define LARGE_GIRDER_TYPE "LargeGirder"

class LargeGirder : public Girder {
public:
	LargeGirder(Stage& stage
		, const float x
		, const float y
		, const float angle_rad
		, const float longitude
		, const float height)
		: Girder(stage, x, y, angle_rad, longitude, height) {}

	virtual std::string get_type() override {
		return LARGE_GIRDER_TYPE;
	}
};

#endif
