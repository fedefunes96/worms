#ifndef GIRDER_H
#define GIRDER_H

#include "ubicable.h"
#include "stage.h"
#include <string>

#define GIRDER_TYPE "Girder"

class Girder : public Ubicable {
private:
	Stage& stage;
	b2Body* body;
	b2Fixture* fixture;	

	static int id_girders;
    const int id_obj;	
public:
	Girder(Stage& stage
		, const int x
		, const int y
		, const float angle
		, const int longitude
		, const int height);

	virtual std::string get_type() override;
	virtual void delete_myself() override;
	//virtual void start_contacting(Ubicable* ubicable) override;
	virtual void start_contacting() override;
	virtual void stop_contacting() override;

	/*virtual void colision(Girder& girder) override;
	virtual void colision(Worm& worm) override;	
	virtual void colision(Throwable& throwable) override;*/
	virtual int get_id() override;

	//Girder(Girder&&);
};

#endif
