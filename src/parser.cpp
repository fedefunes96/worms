#include "parser.h"
#include "girder.h"
#include "bazooka.h"
#include "mortar.h"
#include "green_grenade.h"
#include "banana.h"
#include "red_grenade.h"
#include "holy_grenade.h"
#include "dynamite.h"
#include "baseball_bat.h"
#include "aerial_attack.h"
#include "teleportation.h"
#include <yaml-cpp/yaml.h>
#include <string>

/*void Parser::loadWorms(std::string &file, std::string &config, 
	std::vector<Worm*> &worms, Stage& stage, Game& game)
{
    YAML::Node editor = YAML::LoadFile(file);
    YAML::Node cfg = YAML::LoadFile(config);
    if (editor["Worm"]){
        int i= 0;
        for (YAML::iterator it = editor["Worm"].begin(); it != editor["Worm"].end(); ++it,++i){
            const YAML::Node& worm = *it;
            int x = worm[0].as<int>();
            int y = worm[1].as<int>();
            int health = worm[2].as<int>();
            float angl = cfg["Worm"][0].as<float>();
            int longitud = cfg["Worm"][1].as<int>();
            int height = cfg["Worm"][2].as<int>();
            int restitution = cfg["Worm"][3].as<int>();
            float speed = cfg["Worm"][4].as<float>();
            float fowJumX  = cfg["Worm"][5].as<float>();
            float fowJumY  = cfg["Worm"][6].as<float>();
            std::pair<float,float> forw_jump(fowJumX,fowJumY); 
            float backJumX  = cfg["Worm"][7].as<float>();
            float backJumY  = cfg["Worm"][8].as<float>();
            std::pair<float,float> back_jump(backJumX,backJumY);
            int alturaMax = cfg["Worm"][9].as<int>();
            //int dkgPorM = cfg["Worm"][10].as<int>();
            int damgMax = cfg["Worm"][11].as<int>();
            worms[i] = new Worm(game, stage,x,y,angl,longitud,height, restitution,
            	health,speed,forw_jump,back_jump,damgMax,alturaMax);
        }
    }
}

void Parser::loadGirder(std::string &file, std::string &config, Stage& stage,
     std::vector<Ubicable*>& girders)
{
    YAML::Node editor = YAML::LoadFile(file);
    YAML::Node cfg = YAML::LoadFile(config);
    if (editor["Girder"]){
    	int i = 0;
        for (YAML::iterator it = editor["Girder"].begin();
         it != editor["Girder"].end(); ++it, ++i){
            const YAML::Node& girder = *it;
            int x = girder[0].as<int>();
            int y = girder[1].as<int>();
            float angle = girder[2].as<float>();
            float longitud = girder[3].as<float>();
            float height = cfg["Girder"][0].as<float>();
            girders[i] = new Girder(stage,x,y,angle,longitud,height);
        }
    }
}

void Parser::loadWeapon(std::string &file,std::string &cfg,Stage& stage,std::vector<Usable*> &usables)
{
    YAML::Node editor = YAML::LoadFile(file);
    YAML::Node config = YAML::LoadFile(cfg);
    if (editor["Usable"]){
         for (YAML::iterator it = editor["Usable"].begin(); it != editor["Usable"].end(); ++it){
             const YAML::Node& usable = *it;
             int id = usable[0].as<int>();
             int ammo = usable[1].as<int>();
             if (id == 0)
             {
             	float radius = config["Bazooka"][0].as<float>();
    			float restitution = config["Bazooka"][1].as<float>();
    			float max_damg = config["Bazooka"][2].as<float>();
    			float VDisparo = config["Bazooka"][3].as<float>();
    			float VAngular = config["Bazooka"][4].as<float>();
    			Bazooka* bazooka = new Bazooka(stage,ammo,VDisparo,VAngular,radius,restitution,max_damg);
    			usables.push_back(bazooka);
             }
             if (id == 1){
             	float radius = config["Mortar"][0].as<float>();
    			float rest = config["Mortar"][1].as<float>();
    			float max_damg = config["Mortar"][2].as<float>();
    			float VDisparo = config["Mortar"][3].as<float>();
    			float VAngular = config["Mortar"][4].as<float>();
    			int cant = config["Mortar"][5].as<float>();
    			float radiusFrag = config["Mortar"][6].as<float>();
    			float restFrag = config["Mortar"][7].as<float>();
    			float max_damgFrag = config["Mortar"][8].as<float>();
    			float VDisparoFrag = config["Mortar"][9].as<float>();
    			float VAngularFrag = config["Mortar"][10].as<float>();
    			Mortar* mor = new Mortar(stage,ammo,VDisparo,VAngular,radius,
    				rest,max_damg,cant,VDisparoFrag,VAngularFrag,radiusFrag,
    				restFrag,max_damgFrag);
    			usables.push_back(mor);
             }
             if (id == 2){
             	float radius = config["GreenGrenade"][0].as<float>();
    			float restitution = config["GreenGrenade"][1].as<float>();
    			float max_damg = config["GreenGrenade"][2].as<float>();
    			float VDisparo = config["GreenGrenade"][3].as<float>();
    			float VAngular = config["GreenGrenade"][4].as<float>();
    			GreenGrenade* gre = new GreenGrenade(stage,ammo,VDisparo,
    				VAngular,radius,restitution,max_damg);
    			usables.push_back(gre);
             }
             if (id == 3){
             	float radius = config["RedGrenade"][0].as<float>();
    			float rest = config["RedGrenade"][1].as<float>();
    			float max_damg = config["RedGrenade"][2].as<float>();
    			float VDisparo = config["RedGrenade"][3].as<float>();
    			float VAngular = config["RedGrenade"][4].as<float>();
    			int cant = config["RedGrenade"][5].as<float>();
    			float radiusFrag = config["RedGrenade"][6].as<float>();
    			float restFrag = config["RedGrenade"][7].as<float>();
    			float max_damgFrag = config["RedGrenade"][8].as<float>();
    			float VDisparoFrag = config["RedGrenade"][9].as<float>();
    			float VAngularFrag = config["RedGrenade"][10].as<float>();
    			RedGrenade* gre = new RedGrenade(stage,ammo,VDisparo,VAngular,
    				radius,rest,max_damg,cant,VDisparoFrag,VAngularFrag,
    				radiusFrag,restFrag,max_damgFrag);
    			usables.push_back(gre);
             }
             if (id == 4)
             {
             	float radius = config["Banana"][0].as<float>();
    			float restitution = config["Banana"][1].as<float>();
    			float max_damg = config["Banana"][2].as<float>();
    			float VDisparo = config["Banana"][3].as<float>();
    			float VAngular = config["Banana"][4].as<float>();
    			Banana *us = new Banana(stage,ammo, VDisparo,VAngular,radius,
    				restitution,max_damg);
    			usables.push_back(us);
             }
             if (id == 5)
             {
             	float radius = config["HolyGrenade"][0].as<float>();
    			float restitution = config["HolyGrenade"][1].as<float>();
    			float max_damg = config["HolyGrenade"][2].as<float>();
    			float VDisparo = config["HolyGrenade"][3].as<float>();
    			float VAngular = config["HolyGrenade"][4].as<float>();
    			HolyGrenade *us = new HolyGrenade(stage,ammo, VDisparo,VAngular,radius,
    				restitution,max_damg);
    			usables.push_back(us);
             }
             if (id == 6)
             {
             	float radius = config["Dynimite"][0].as<float>();
    			float restitution = config["Dynimite"][1].as<float>();
    			float max_damg = config["Dynimite"][2].as<float>();
    			Dynamite* us = new Dynamite(stage,ammo,radius,restitution,max_damg);
    			usables.push_back(us);
             }
             if (id == 7)
             {
             	float max_damg = config["Bate"][2].as<float>();
             	BaseballBat *us = new BaseballBat(stage,ammo,10.0,max_damg);
             	usables.push_back(us);
             }
             if (id == 8){
             	float radius = config["AirAttack"][0].as<float>();
    			float restitution = config["AirAttack"][1].as<float>();
    			float max_damg = config["AirAttack"][2].as<float>();
    			float VDisparo = config["AirAttack"][3].as<float>();
    			float VAngular = config["AirAttack"][4].as<float>();
    			AerialAttack *us = new AerialAttack(stage,ammo, VDisparo,VAngular,radius,
    				restitution,max_damg);
    			usables.push_back(us);
             }
             if (id == 9){
             	Teleportation * us = new Teleportation(stage,ammo);
             	usables.push_back(us);
             }
         }
    }
}

int Parser::waterLvl(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Water"].as<int>();
}

int Parser::cantidad(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Cantidad"].as<int>();
}

float Parser::airMinSpeed(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Wind"][0].as<int>();
}

float Parser::airMaxSpeed(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Wind"][1].as<int>();
}*/