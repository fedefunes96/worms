#ifndef GIRDER_H
#define GIRDER_H

#include "static.h"
#include "stage.h"

class Girder : public Static {
public:
	Girder(Stage& stage
		, const int x
		, const int y
		, const int angle
		, const int longitude
		, const int height);
};

#endif
