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
#include "smallgirder.h"
#include "largegirder.h"

enum Weapons{
    BAZOOKA = 0,
    MORTAR = 1,
    GREEN_GRENADE = 2,
    RED_GRENADE = 3,
    BANANA = 4,
    HLOY_GRENADE = 5,
    DYNAMITE = 6,
    BASEBALL_BAT = 7,
    AIR_ATTACK = 8,
    TELETRANPORTER = 9
};

void Parser::loadWorms(std::string &file, std::string &config, 
	std::vector<Worm*> &worms, Stage& stage, Game* game)
{
    YAML::Node editor = YAML::LoadFile(file);
    YAML::Node cfg = YAML::LoadFile(config);
    if (editor["Worm"]){
        int i= 0;
        for (YAML::iterator it = editor["Worm"].begin(); it != editor["Worm"].end(); ++it,++i){
            const YAML::Node& worm = *it;
            float x = worm[0].as<float>();
            float y = worm[1].as<float>();
            float health = worm[2].as<float>();
            float angl = cfg["Worm"][0].as<float>();
            float longitud = cfg["Worm"][1].as<float>();
            float height = cfg["Worm"][2].as<float>();
            float restitution = cfg["Worm"][3].as<float>();
            float speed = cfg["Worm"][4].as<float>();
            float fowJumX  = cfg["Worm"][5].as<float>();
            float fowJumY  = cfg["Worm"][6].as<float>();
            std::pair<float,float> forw_jump(fowJumX,fowJumY); 
            float backJumX  = cfg["Worm"][7].as<float>();
            float backJumY  = cfg["Worm"][8].as<float>();
            std::pair<float,float> back_jump(backJumX,backJumY);
            float alturaMax = cfg["Worm"][9].as<float>();
            float dkgPorM = cfg["Worm"][10].as<float>();
            float damgMax = cfg["Worm"][11].as<float>();
            Worm *worm2 = new Worm(*game, stage,x,y,angl,longitud,height, restitution,
            	health,speed,forw_jump,back_jump,damgMax,alturaMax,dkgPorM);
            worms.push_back(worm2);
        }
    }
}

void Parser::loadGirder(std::string &file, std::string &config, Stage& stage,
     std::vector<Ubicable*>& girders)
{
    YAML::Node editor = YAML::LoadFile(file);
    YAML::Node cfg = YAML::LoadFile(config);
    if (editor["Small Girder"]){
    	int i = 0;
        for (YAML::iterator it = editor["Small Girder"].begin();
         it != editor["Small Girder"].end(); ++it, ++i){
            const YAML::Node& girder = *it;
            float x = girder[0].as<float>();
            float y = girder[1].as<float>();
            float angle = girder[2].as<float>();
            float longitud = cfg["Small Girder"][0].as<float>();
            float height = cfg["Small Girder"][1].as<float>();
            Girder *gir = new SmallGirder(stage,x,y,angle,longitud,height);
            girders.push_back(gir);
        }
    }

    if (editor["Big Girder"]){
        int i = 0;
        for (YAML::iterator it = editor["Big Girder"].begin();
         it != editor["Big Girder"].end(); ++it, ++i){
            const YAML::Node& girder = *it;
            float x = girder[0].as<float>();
            float y = girder[1].as<float>();
            float angle = girder[2].as<float>();
            float longitud = cfg["Large Girder"][0].as<float>();
            float height = cfg["Large Girder"][1].as<float>();
            Girder *gir = new LargeGirder(stage,x,y,angle,longitud,height);
            girders.push_back(gir);
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
             if (id == BAZOOKA)
             {
             	float VDisparo = config["Bazooka"][0].as<float>();
                float radius = config["Bazooka"][1].as<float>();
                float max_damg = config["Bazooka"][2].as<float>();
                float max_push = config["Bazooka"][3].as<float>();
                float rad_expl = config["Bazooka"][4].as<float>();
    			Bazooka* bazooka = new Bazooka(stage,ammo,VDisparo,radius,
                    max_damg, max_push,rad_expl);
    			usables.push_back(bazooka);
             }
             if (id == MORTAR){
             	float vel = config["Mortar"][0].as<float>();
                float rad = config["Mortar"][1].as<float>();
                float max_dmg = config["Mortar"][2].as<float>();
                float max_push = config["Mortar"][3].as<float>();
                float rad_expl = config["Mortar"][4].as<float>();
                int cant_frag = config["Mortar"][5].as<int>();
                float vel_frag = config["Mortar"][6].as<float>();
                float rad_frag = config["Mortar"][7].as<float>();
                float max_dmg_frag = config["Mortar"][8].as<float>();
    			Mortar* mor = new Mortar(stage,ammo,vel,rad,max_dmg,max_push,
                    rad_expl,cant_frag,vel_frag,rad_frag,max_dmg_frag);
    			usables.push_back(mor);
             }
             if (id == GREEN_GRENADE){
             	float vel = config["GreenGrenade"][0].as<float>();
                float rad = config["GreenGrenade"][1].as<float>();
                float restitution = config["GreenGrenade"][2].as<float>();
                float max_dmg = config["GreenGrenade"][3].as<float>();
                float max_push = config["GreenGrenade"][4].as<float>();
                float rad_expl = config["GreenGrenade"][5].as<float>();
    			GreenGrenade* gre = new GreenGrenade(stage,ammo,vel,rad,
                    restitution,max_dmg,max_push,rad_expl);
    			usables.push_back(gre);
             }
             if (id == RED_GRENADE){
             	
                float vel = config["RedGrenade"][0].as<float>();
                float rad = config["RedGrenade"][1].as<float>();
                float restitution = config["RedGrenade"][2].as<float>();
                float max_dmg = config["RedGrenade"][3].as<float>();
                float max_push = config["RedGrenade"][4].as<float>();
                float rad_expl = config["RedGrenade"][5].as<float>();
                int cant_frag = config["RedGrenade"][6].as<float>();
                float vel_frag = config["RedGrenade"][7].as<float>();
                float rad_frag = config["RedGrenade"][8].as<float>();
                float max_dmg_frag = config["RedGrenade"][9].as<float>();
    			RedGrenade* gre = new RedGrenade(stage,ammo,vel,rad,restitution,
                    max_dmg,max_push,rad_expl,cant_frag,vel_frag,rad_frag,
                    max_dmg_frag);
    			usables.push_back(gre);
             }
             if (id == BANANA)
             {
             	float vel = config["Banana"][0].as<float>();
                float rad = config["Banana"][1].as<float>();
                float restitution = config["Banana"][2].as<float>();
                float max_dmg = config["Banana"][3].as<float>();
                float max_push = config["Banana"][4].as<float>();
                float rad_expl = config["Banana"][5].as<float>();
    			Banana *us = new Banana(stage,ammo, vel,rad,restitution,
                    max_dmg,max_push,rad_expl);
    			usables.push_back(us);
             }
             if (id == HLOY_GRENADE)
             {
             	float vel = config["HolyGrenade"][0].as<float>();
                float rad = config["HolyGrenade"][1].as<float>();
                float restitution = config["HolyGrenade"][2].as<float>();
                float max_dmg = config["HolyGrenade"][3].as<float>();
                float max_push = config["HolyGrenade"][4].as<float>();
                float rad_expl = config["HolyGrenade"][5].as<float>();
    			HolyGrenade *us = new HolyGrenade(stage,ammo,vel,rad,
                    restitution,max_dmg,max_push,rad_expl);
    			usables.push_back(us);
             }
             if (id == DYNAMITE)
             {
             	float rad = config["Dynimite"][0].as<float>();
                float restitution = config["Dynimite"][1].as<float>();
                float max_dmg = config["Dynimite"][2].as<float>();
                float max_push = config["Dynimite"][3].as<float>();
                float rad_expl = config["Dynimite"][4].as<float>();
    			Dynamite* us = new Dynamite(stage,ammo,rad,restitution,
                    max_dmg,max_push,rad_expl);
    			usables.push_back(us);
             }
             if (id == BASEBALL_BAT)
             {
                float vel = config["Bate"][0].as<float>();
             	float max_damg = config["Bate"][1].as<float>();
             	BaseballBat *us = new BaseballBat(stage,ammo,vel,max_damg);
             	usables.push_back(us);
             }
             if (id == AIR_ATTACK){
             	float vel = config["AirAttack"][0].as<float>();
                float rad =config["AirAttack"][1].as<float>();
                float max_dmg = config["AirAttack"][2].as<float>();
                float from = config["AirAttack"][3].as<float>();
                float max_push = config["AirAttack"][4].as<float>();
                float rad_expl = config["AirAttack"][5].as<float>();
    			AerialAttack *us = new AerialAttack(stage,ammo, vel,rad,max_dmg,
                    from,max_push,rad_expl);
    			usables.push_back(us);
             }
             if (id == TELETRANPORTER){
             	Teleportation * us = new Teleportation(stage,ammo);
             	usables.push_back(us);
             }
         }
    }
}

float Parser::waterLvl(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Water"].as<float>();
}

int Parser::cantidad(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Cantidad"].as<int>();
}

float Parser::airMinSpeed(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Wind"][0].as<float>();
}

float Parser::airMaxSpeed(std::string &file)
{
    YAML::Node config = YAML::LoadFile(file);
    return config["Wind"][1].as<float>();
}


std::string Parser::loadBackground(std::string& file){
    YAML::Node config = YAML::LoadFile(file);
    std::string background = config["Background"].as<std::string>();
    return background;
}
