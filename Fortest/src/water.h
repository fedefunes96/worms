#ifndef WATER_H
#define WATER_H

class Water {
private:
	float water_level;
public:
	Water(const float water_level);

	void set_water_level(const float water_level);
	float get_water_level();
};

#endif
