#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <ctime>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include "random.h"

using namespace std;
using namespace sf;

enum directions { IDLE = 0, UP, DOWN, RIGHT, LEFT };
enum states { MENU = 0, INPUT, INTRO, HOME, OUTDOOR, SKY, CASTLE, STORE, PAUSE, GAME_OVER, SCORE, TUTORIAL, CREDIT };
enum click_states { UNSELECTED = 0, BOUGHT, BYE };
enum boss_phases { STILL = 0, AGGROVATED, PISSED, INFURIATED, MURDEROUS };
enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

//define global variables;
static float viewWidght = 1920.f;
static float viewHeight = 1080.f;
static unsigned int framerateLimit = 60;
static float maxHP = 2000.f;
static float maxMP = 1000.f;
static float maxEnergy = 3000.f;
static float gravity = 3000.f;