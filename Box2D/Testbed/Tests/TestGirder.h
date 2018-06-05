#ifndef TESTGIRDER_H
#define TESTGIRDER_H

#include "../src/ubicable.h"
#include "../src/stage.h"
#include "../src/ubicable.cpp"
#include "../src/stage.cpp"
//#include "movable.h"
//#include "static.h"
#include "../src/girder.h"
#include "../src/throwable.h"
#include "../src/girder.cpp"
#include "../src/throwable.cpp"
#include <chrono>
#include <thread>
#include "../src/contact_listener.h"
#include "../src/game.h"
#include "../src/game.cpp"

enum _moveState {
    MS_STOP,
    MS_LEFT,
    MS_RIGHT,
};
  

class TestGirder : public Test {
public:
    b2Body* dinamicbody;
    b2Body* kinematicbody;
    //_moveState moveState;

    TestGirder() { 
        //Create Floor
        m_world->SetGravity(b2Vec2(0.0f, -9.8f));
        //moveState = MS_STOP;
        std::vector<Player> players;
        Game game(m_world, "hi", std::move(players));

        /*Stage stage(m_world, 1/60, 1, 1, game);

        b2Vec2 velocity(50.0, 10.0);

        Throwable test_mov(stage
            , 5
            , 2
            , 0
            , velocity
            , 30.0
            , 1.0
            , 0.0
            , 75.0);

        Girder test_static(stage
            , 0
            , 10
            , 0
            , 1
            , 1);*/
        /*const float32 k_restitution = 1.0f;

        b2Body* ground;
        {
            b2BodyDef bd;
            bd.position.Set(0.0f, 20.0f);
            ground = m_world->CreateBody(&bd);

            b2PolygonShape shape;

            b2FixtureDef sd;
            sd.shape = &shape;
            sd.density = 0.0f;
            //sd.restitution = k_restitution;

            // Left vertical
            shape.SetAsEdge(b2Vec2(-20.0f, -20.0f), b2Vec2(-20.0f, 20.0f));
            ground->CreateFixture(&sd);

            // Right vertical
            shape.SetAsEdge(b2Vec2(20.0f, -20.0f), b2Vec2(20.0f, 20.0f));
            ground->CreateFixture(&sd);

            // Top horizontal
            shape.SetAsEdge(b2Vec2(-20.0f, 20.0f), b2Vec2(20.0f, 20.0f));
            ground->CreateFixture(&sd);

            // Bottom horizontal
            shape.SetAsEdge(b2Vec2(-20.0f, -20.0f), b2Vec2(20.0f, -20.0f));
            ground->CreateFixture(&sd);
        }    

    	{
    	//Create 1 dynamic
            b2BodyDef myBodyDef;
            myBodyDef.type = b2_dynamicBody;
            myBodyDef.position.Set(-5, 5);
            myBodyDef.angle = 0;
            //b2Body* dinamicbody = m_world->CreateBody(&myBodyDef);
            dinamicbody = m_world->CreateBody(&myBodyDef);

            b2PolygonShape boxShape;
            boxShape.SetAsBox(2, 1);

            b2FixtureDef boxFixtureDef;
            boxFixtureDef.shape = &boxShape;
            boxFixtureDef.density = 1;  
            boxFixtureDef.friction = 0.0;
            //boxFixtureDef.restitution = k_restitution;

            dinamicbody->CreateFixture(&boxFixtureDef); 	
        }
        {
            b2BodyDef myBodyDef;
            myBodyDef.type = b2_staticBody;
            myBodyDef.position.Set(0, 0);
            myBodyDef.angle = -b2_pi/4;

            //b2Body* dinamicbody = m_world->CreateBody(&myBodyDef);
            kinematicbody = m_world->CreateBody(&myBodyDef);

            b2PolygonShape boxShape;
            boxShape.SetAsBox(1, 10);

            b2FixtureDef boxFixtureDef;
            boxFixtureDef.shape = &boxShape;
            //boxFixtureDef.restitution = k_restitution;

            kinematicbody->CreateFixture(&boxFixtureDef);             
        }*/

    } //do nothing, no scene yet
 /*   void Keyboard(unsigned char key)
    {
        switch (key)
        {
          case 'q': //move left
            moveState = MS_LEFT;
            break;
          case 'w': //stop
            moveState = MS_STOP;
            break;
          case 'e': //move right
            moveState = MS_RIGHT;
            break;
          default:
            //run default behaviour
            Test::Keyboard(key);
        }
    }*/
    void Step(Settings* settings) {
        //run the default physics and rendering
        Test::Step(settings); 
    
        //show some text in the main screen
        m_debugDraw.DrawString(5, m_textLine, "Prueba");
        m_textLine += 15;   

       /* b2Vec2 vel = dinamicbody->GetLinearVelocity();
        switch ( moveState )
        {
          case MS_LEFT:  vel.x = -5; break;
          case MS_STOP:  vel.x =  0; break;
          case MS_RIGHT: vel.x =  5; break;
        }
        dinamicbody->SetLinearVelocity( vel );*/

        //b2Vec2 vel = dinamicbody->GetLinearVelocity();
        //dinamicbody->SetLinearVelocity(b2Vec2(0.0, 0.0));
        //b2Vec2 vel = dinamicbody->GetLinearVelocityFromWorldPoint();
        //float32 time = 1/60.0;
        //b2Vec2 vel = m_world->GetGravity();
       // vel *= time;

        //kinematicbody->SetLinearVelocity(vel);
        //const b2Vec2* pos = dinamicbody.GetWorldCenter();

        //ApplyForce (const b2Vec2 &force, const b2Vec2 &point)

       // void    SetLinearVelocity (const b2Vec2 &v)
       // b2Vec2  GetLinearVelocity () const



    }
    
    static Test* Create() {
        return new TestGirder;
    }
};
  
#endif
