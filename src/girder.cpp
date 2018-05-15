#include "girder.h"
#include "static.h"
#include "stage.h"

Girder::Girder(Stage& stage, const int x, const int y, const int angle_rad
, const int longitude, const int height)
 : Static(stage, x, y, angle_rad, longitude, height) {}
