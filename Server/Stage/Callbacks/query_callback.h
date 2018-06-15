#ifndef QUERY_CALLBACK_H
#define QUERY_CALLBACK_H

#include <Box2D/Box2D.h>
#include <vector>

class QueryCallback : public b2QueryCallback {
public:
	std::vector<b2Body*> foundBodies;

	bool ReportFixture(b2Fixture* fixture) {
		foundBodies.push_back(fixture->GetBody()); 
		return true;
	}
};

#endif
