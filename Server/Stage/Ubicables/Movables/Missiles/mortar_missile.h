#ifndef MORTAR_MISSILE_H
#define MORTAR_MISSILE_H

#include "throwable.h"

#define MORTAR_TYPE "Mortar"

class MortarMissile : public Throwable {
private:
	const int ammount_fragments;
	const float velocity_frag;
	const float radius_frag;
	const float max_dmg_frag;
	const float max_pushback;
	const float radius_expl;

	void create_fragments();

public:
	MortarMissile(Stage& stage
	, Worm* owner
	, const float x
	, const float y
	, const float angle_rad
	, const b2Vec2 velocity
	, const float radius
	, const float max_dmg
	, const float max_pushback
	, const float radius_expl
	, const int ammount_fragments
	, const float velocity_frag
	, const float radius_frag
	, const float max_dmg_frag	
	);

	virtual std::string get_type() override;
	virtual bool is_affected_by_wind() override;
	virtual void explode() override;
};

#endif
