#ifndef GIRDER_H
#define GIRDER_H

#include "static.h"
#include "stage.h"
#include <string>

#define GIRDER_TYPE "Girder"

class Girder : public Static {
public:
	Girder(Stage& stage
		, const int x
		, const int y
		, const int angle
		, const int longitude
		, const int height);

	virtual std::string get_type() override;
};

#endif
