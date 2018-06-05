#include "explosion.h"
#include "stage.h"
#include <Box2D/Box2D.h>
#include "query_callback.h"
#include "worm.h"

Explosion::Explosion(Stage& stage, const b2Vec2& pos, const float radius, const float max_dmg) {
	QueryCallback queryCallback;
	b2AABB aabb;
	aabb.lowerBound = pos - b2Vec2(radius, radius);
	aabb.upperBound = pos + b2Vec2(radius, radius);
	stage.get_world().QueryAABB(&queryCallback, aabb);
	  
	//check which of these bodies have their center of mass within the blast radius
	for (int i = 0; i < (int) queryCallback.foundBodies.size(); i++) {
		b2Body* body = queryCallback.foundBodies[i];
		b2Vec2 bodyCom = body->GetWorldCenter();
	      
		//ignore bodies outside the blast range
		if ((bodyCom - pos).Length() >= radius)
			continue;
		
		//Change this later

		Ubicable* ubicable = (Ubicable*) body->GetUserData();

		if (ubicable->get_type().compare("Worm")==0) {
			b2Vec2 blastDir = bodyCom - pos;
			float distance = blastDir.Normalize();

			if (distance == 0) {
				((Worm*) ubicable)->receive_dmg(max_dmg);
         		continue;
			}

			float invDistance = 1 / distance;
			float blastPower = 5.0;
			float impulseMag = blastPower * invDistance * invDistance;
			body->ApplyLinearImpulse(impulseMag * blastDir, bodyCom);
			//Down cast	
			((Worm*) ubicable)->receive_dmg(max_dmg - (distance * max_dmg/radius));
		}
		//applyBlastImpulse(body, center, bodyCom, blastPower );
	}

	/* (int i = 0; i < numRays; i++) {
	float angle = (i / (float)numRays) * 360 * DEGTORAD;
	b2Vec2 rayDir( sinf(angle), cosf(angle) );
	b2Vec2 rayEnd = center + blastRadius * rayDir;
  
	//check what this ray hits
	RayCastClosestCallback callback;//basic callback to record body and hit point
	m_world->RayCast(&callback, center, rayEnd);
	if ( callback.m_body ) 
		applyBlastImpulse(callback.body, center, callback.point, (m_blastPower / (float)numRays));
	}*/
}