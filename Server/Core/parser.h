#ifndef PARSER
#define PARSER

#include "worm.h"
#include "ubicable.h"
#include "usable.h"
#include "stage.h"
#include <vector>
#include <map>

class Parser
{
public:
	Parser();
	~Parser();

	static void loadWorms(std::string& file, std::string &config, 
		std::vector<Worm*>& worms, Stage& stage, Game* game);

    static void loadGirder(std::string& file,std::string &config,Stage& stage, 
    	std::vector<Ubicable*> &girders);

    static void loadWeapon(std::string& file, std::string &config,Stage& stage,
    	std::vector<Usable*> &usable);

    static float waterLvl(std::string& file);

    static int cantidad(std::string& file);

    static float airMinSpeed(std::string& file);

    static float airMaxSpeed(std::string& file);

    static std::string loadBackground(const std::string& file);
	
};

#endif