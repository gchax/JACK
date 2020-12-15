#define _CRT_SECURE_NO_WARNINGS
#include "stdfn.h"
#include "player.h"
#include "platform.h"
#include "bitmap.h"
#include "enemy.h"
#include "button.h"
#include "textDisplay.h"
#include "item.h"
#include "textBox.h"

void resizeView(const RenderWindow&, View&);
void showText(Vector2f , string, Font*, int, RenderWindow&);


//main;
int main()
{
	//render window;
	RenderWindow window(VideoMode(viewWidght, viewHeight), "Jack!", Style::Close | Style::Fullscreen);
	View view(Vector2f(0.0f, 0.0f), Vector2f(viewWidght, viewHeight));
	window.setFramerateLimit(framerateLimit);
	Event event;
	srand(time(NULL));


	//define screen size;
	Vector2u ws = window.getSize();
	Vector2f windowSize(static_cast<float>(ws.x), static_cast<float>(ws.y));


	//initialize variables
	bool isPause = false;
	bool isPlayerDead = false;
	bool isUnlocked = false;
	bool isRestarted = false;
	bool isScrolled = false;
	bool playMenuMusic = false;
	bool playIntroMusic = false;
	bool playGameMusic = false;
	bool playBossMusic = false;
	bool playStoreMusic = false;
	bool playEndMusic = false;
	bool playRoar = false;
	bool playLaugh = false;
	bool playYouDie = false;
	bool collisionCheat = false;
	bool gravityCheat = false;
	bool unlimitedEnergyCheat = false;
	bool unlimitedManaCheat = false;
	bool unlimitedHealthCheat = false;
	bool readFile = false;
	int state = MENU;
	int bossPhase = STILL;
	int clickState = UNSELECTED;
	int wandLevel = 0;
	int key = 0;
	int playerScore = 0;
	int playerMoney = 0;
	int hpPotion = 0;
	int mpPotion = 0;
	int pattern = 0;
	int page = 1;
	int typeLimit = 25;
	int lifetime = 0;
	float maxhp = maxHP;
	float maxmp = maxMP;
	float playerHP = maxhp;
	float playerMP = maxmp;
	float playerEnergy = maxEnergy;
	float playerGravity = gravity;
	string name;

	//load from files;
	Music menuMusic;
	menuMusic.openFromFile("resources/audio/lobby.wav");
	menuMusic.setVolume(25);
	menuMusic.setLoop(true);
	menuMusic.play();
	playMenuMusic = true;

	Music introMusic;
	introMusic.openFromFile("resources/audio/intro.wav");
	introMusic.setVolume(50);
	introMusic.setLoop(true);

	Music gameMusic;
	gameMusic.openFromFile("resources/audio/game.wav");
	gameMusic.setVolume(20);
	gameMusic.setLoop(true);

	Music bossMusic;
	bossMusic.openFromFile("resources/audio/boss.wav");
	bossMusic.setVolume(25);
	bossMusic.setLoop(true);

	Music storeMusic;
	storeMusic.openFromFile("resources/audio/shop.wav");
	storeMusic.setVolume(25);
	storeMusic.setLoop(true);

	Music endMusic;
	endMusic.openFromFile("resources/audio/end.wav");
	endMusic.setVolume(25);

	Music die;
	die.openFromFile("resources/audio/gameover.wav");
	die.setVolume(25);

	SoundBuffer ouch;
	ouch.loadFromFile("resources/audio/ouch.ogg");
	Sound hurt;
	hurt.setBuffer(ouch);
	hurt.setVolume(35);

	SoundBuffer fire;
	fire.loadFromFile("resources/audio/fireball.wav");
	Sound shoot;
	shoot.setBuffer(fire);
	shoot.setVolume(10);
	
	SoundBuffer mcoin;
	mcoin.loadFromFile("resources/audio/coin.wav");
	Sound getcoin;
	getcoin.setBuffer(mcoin);
	getcoin.setVolume(50);

	SoundBuffer eiei;
	eiei.loadFromFile("resources/audio/evillaugh.wav");
	Sound evillaugh;
	evillaugh.setBuffer(eiei);
	evillaugh.setVolume(35);
	evillaugh.setPitch(5);

	SoundBuffer bossRoar;
	bossRoar.loadFromFile("resources/audio/roar.wav");
	Sound roar;
	roar.setBuffer(bossRoar);
	roar.setVolume(35);

	SoundBuffer oraora;
	oraora.loadFromFile("resources/audio/ora.wav");
	Sound ora;
	ora.setBuffer(oraora);
	ora.setVolume(20);

	SoundBuffer turnpage;
	turnpage.loadFromFile("resources/audio/turnpage.wav");
	Sound turn;
	turn.setBuffer(turnpage);
	turn.setVolume(40);

	SoundBuffer swallow;
	swallow.loadFromFile("resources/audio/drink.wav");
	Sound drink;
	drink.setBuffer(swallow);
	drink.setVolume(50);

	SoundBuffer kill;
	kill.loadFromFile("resources/audio/kill.ogg");
	Sound dead;
	dead.setBuffer(kill);
	dead.setVolume(35);

	Font font;
	font.loadFromFile("resources/font/8BitDragon.ttf");

	Texture HPP;
	HPP.loadFromFile("resources/picture/hpp.jpg");

	Texture MPP;
	MPP.loadFromFile("resources/picture/mpp.jpg");

	Texture jack;
	jack.loadFromFile("resources/picture/jack.png");

	Texture menubg;
	menubg.loadFromFile("resources/picture/menu.jpg");

	Texture jacklogo;
	jacklogo.loadFromFile("resources/picture/logo.png");

	Texture homebg;
	homebg.loadFromFile("resources/picture/map_home.png");

	Texture outdoorbg;
	outdoorbg.loadFromFile("resources/picture/map_outdoor.png");

	Texture skybg;
	skybg.loadFromFile("resources/picture/map_sky.png");

	Texture mapCastle;
	mapCastle.loadFromFile("resources/picture/map_castle.png");

	Texture storebg;
	storebg.loadFromFile("resources/picture/shopbg.jpg");

	Texture textbox;
	textbox.loadFromFile("resources/picture/textbox.png");

	Texture awand;
	awand.loadFromFile("resources/picture/sparkle.png");

	Texture coins;
	coins.loadFromFile("resources/picture/coin.png");

	Texture fireball;
	fireball.loadFromFile("resources/picture/fireball.png");

	Texture hp;
	hp.loadFromFile("resources/picture/hp.png");

	Texture mp;
	mp.loadFromFile("resources/picture/mp.png");

	Texture keys;
	keys.loadFromFile("resources/picture/key.png");

	Texture gargoyle1;
	gargoyle1.loadFromFile("resources/picture/gargoyle1.png");

	Texture gargoyle1Ball;
	gargoyle1Ball.loadFromFile("resources/picture/ballg1.png");

	Texture gargoyle2;
	gargoyle2.loadFromFile("resources/picture/gargoyle2.png");

	Texture gargoyle2Ball;
	gargoyle2Ball.loadFromFile("resources/picture/ballg2.png");

	Texture titan1;
	titan1.loadFromFile("resources/picture/titan1.png");

	Texture titan2;
	titan2.loadFromFile("resources/picture/titan2.png");

	Texture titan2Ball;
	titan2Ball.loadFromFile("resources/picture/ballt2.png");

	Texture monSeller;
	monSeller.loadFromFile("resources/picture/mon_seller.png");

	Texture minion1;
	minion1.loadFromFile("resources/picture/minion.png");

	Texture theboss;
	theboss.loadFromFile("resources/picture/boss.png");

	Texture torch;
	torch.loadFromFile("resources/picture/torch.png");

	Texture chndlir;
	chndlir.loadFromFile("resources/picture/chandelier.png");

	Texture speeech;
	speeech.loadFromFile("resources/picture/speech.png");

	Texture pg1;
	pg1.loadFromFile("resources/picture/page1.png");

	Texture pg2;
	pg2.loadFromFile("resources/picture/page2.png");

	Texture pg3;
	pg3.loadFromFile("resources/picture/page3.png");

	Texture pg4;
	pg4.loadFromFile("resources/picture/page4.png");

	Texture tutorialpng;
	tutorialpng.loadFromFile("resources/picture/tutorial.png");

	Texture inp;
	inp.loadFromFile("resources/picture/inputscreen.png");

	Texture blackboard;
	blackboard.loadFromFile("resources/picture/blackboard.png");

	Texture jckttr;
	jckttr.loadFromFile("resources/picture/jackTutorial.png");


	//initialize player;
	player wandedJack(&jckttr, Vector2u(6, 2), 0.08f, 600.f, Vector2f(132.f, 150.0f));
	player player(&jack, Vector2u(8, 8), 0.08f, 600.f, Vector2f(71.11f, 120.0f));


	//declare delta time;
	float deltaTime = 0.0f;
	Clock clock[15];


	//initialzie map variables;
	platform background(&menubg, Vector2f(windowSize), Vector2f(windowSize / 2.f));

	platform logo(&jacklogo, Vector2f(750.f, 750.f), Vector2f(windowSize.x / 2.f, windowSize.y / 3.25f));

	platform background1(&homebg, Vector2f(1800.0f, 2070.0f), Vector2f(900.0f, 1035.f));
	vector<bitmap> blockH;
	int home[23][20] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 }
	};
	for (int mapX = 0; mapX < 20; mapX++)
	{
		for (int mapY = 0; mapY < 23; mapY++)
		{
			if (home[mapY][mapX] == 0)
			{
				bitmap outdoor(nullptr, Vector2f(((mapX) * 90.f) + 45.f, ((mapY) * 90.f) + 45.f), Vector2f(90.f, 90.f));
				blockH.push_back(outdoor);
			}
		}
	}

	platform background2(&outdoorbg, Vector2f(4920.0f, 5880.0f), Vector2f(2460.0f, 2940.0f));
	vector<bitmap> blockO0;
	vector<bitmap> blockO2;
	int outdoor[49][41] =
	{
		{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
		{0,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  1,  1,  1,  2,  2,  2,  1,  1,  2,  2,  2,  1,  1,  1,  1,  1,  1,  2,  2,  2,  1,  1,  1,  1,  1,  2,  2,  2,  1,  1},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{2,  2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
	};
	for (int mapX = 0; mapX < 41; mapX++)
	{
		for (int mapY = 0; mapY < 49; mapY++)
		{
			if (outdoor[mapY][mapX] == 0)
			{
				bitmap outdoor(nullptr, Vector2f(((mapX) * 120) + 60, ((mapY) * 120) + 60), Vector2f(120.f, 120.f));
				blockO0.push_back(outdoor);
			}
			if (outdoor[mapY][mapX] == 2)
			{
				bitmap outdoor(nullptr, Vector2f(((mapX) * 120) + 60, ((mapY) * 120) + 60), Vector2f(120.f, 120.f));
				blockO2.push_back(outdoor);
			}
		}
	}

	platform background3(&skybg, Vector2f(7920.0f, 2640.0f), Vector2f(3960.0f, 1320.0f));
	vector<bitmap> blockS0;
	vector<bitmap> blockS2;
	int sky[22][66] =
	{
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  1,  1,  1,  1,  0,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0},
		{0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0},
		{0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  0},
		{0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0},
		{0,  0,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0},
		{0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0},
		{0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
	};
	for (int mapX = 0; mapX < 66; mapX++)
	{
		for (int mapY = 0; mapY < 22; mapY++)
		{
			if (sky[mapY][mapX] == 0)
			{
				bitmap sky(nullptr, Vector2f(((mapX) * 120) + 60, ((mapY) * 120) + 60), Vector2f(120.f, 120.f));
				blockS0.push_back(sky);
			}
		}
		for (int mapY = 0; mapY < 22; mapY++)
		{
			if (sky[mapY][mapX] == 2)
			{
				bitmap sky(nullptr, Vector2f(((mapX) * 120) + 60, ((mapY) * 120) + 60), Vector2f(120.f, 120.f));
				blockS2.push_back(sky);
			}
		}
	}

	platform castle(&mapCastle, Vector2f(5242.72f, 1080.0f), Vector2f(0.f, -100.f));
	platform wall1(nullptr, Vector2f(100.f, 2000.f), Vector2f(0.f, 0.f));
	wall1.body.setPosition(Vector2f(-windowSize.x / 2.f - wall1.body.getSize().x / 2.f, 0.f));
	platform wall2(nullptr, Vector2f(100.f, 2000.f), Vector2f(0.f, 0.f));
	wall2.body.setPosition(Vector2f(windowSize.x / 2.f + wall1.body.getSize().x / 2.f, 0.f));
	vector<platform> ground;
	ground.push_back(platform(nullptr, Vector2f(5242.72f, 1.f), Vector2f(0.f, 450.f)));
	vector<platform> torch1;
	torch1.push_back(platform(nullptr, Vector2f(70.f, 1.f), Vector2f(700.f, 285.f)));
	platform wallTorch1(&torch, Vector2f(92.f, 200.f), Vector2f(700.f, 250.f));
	vector<platform> torch2;
	torch2.push_back(platform(nullptr, Vector2f(70.f, 1.f), Vector2f(450.f, 115.f)));
	platform wallTorch2(&torch, Vector2f(92.f, 200.f), Vector2f(450.f, 80.f));
	vector<platform> torch3;
	torch3.push_back(platform(nullptr, Vector2f(70.f, 1.f), Vector2f(700.f, -55.f)));
	platform wallTorch3(&torch, Vector2f(92.f, 200.f), Vector2f(700.f, -90.f));
	vector<platform> Chandelier;
	Chandelier.push_back(platform(nullptr, Vector2f(350.f, 1.f), Vector2f(350.f, -215.f)));
	platform chandelier(&chndlir, Vector2f(390.f, 400.f), Vector2f(350.f, -380.f));

	platform store(&storebg, Vector2f(1920.f, 1080.f), Vector2f(960.f, 540.f));
	store.body.setFillColor(Color(150, 150, 150, 150));

	platform speech(&speeech, Vector2f(1500.f, 1000.f), Vector2f(windowSize.x / 2.f, windowSize.y + 380.f));

	platform page1(&pg1, Vector2f(windowSize.y, windowSize.y), Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));
	platform page2(&pg2, Vector2f(windowSize.y, windowSize.y), Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));
	platform page3(&pg3, Vector2f(windowSize.y, windowSize.y), Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));
	platform page4(&pg4, Vector2f(windowSize.y, windowSize.y), Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

	platform Tutorial(&tutorialpng, Vector2f(1500.f, 1000.f), Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

	platform inputScreen(&inp, Vector2f(1500.f, 1000.f), Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

	platform board(&blackboard, Vector2f(1200.f, 664.f), Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));


	//initialize warpers;
	RectangleShape warperH;
	warperH.setPosition(Vector2f(1170.f, 2040.f));
	warperH.setSize(Vector2f(180.f, 10.f));

	RectangleShape pickUp;
	pickUp.setPosition(Vector2f(1020.0f, 625.0f));
	pickUp.setSize(Vector2f(90.f, 20.f));

	RectangleShape warperO[2];
	warperO[0].setPosition(Vector2f(3660.f, 4900.f));
	warperO[0].setSize(Vector2f(120.f, 120.f));
	warperO[1].setPosition(Vector2f(840.f, 300.f));
	warperO[1].setSize(Vector2f(480.f, 120.f));

	RectangleShape warperS[3];
	warperS[0].setPosition(Vector2f(1200.f, 2225.f));
	warperS[0].setSize(Vector2f(240.f, 10.f));
	warperS[1].setPosition(Vector2f(840.f, 1000.f));
	warperS[1].setSize(Vector2f(120.f, 10.f));
	warperS[2].setPosition(Vector2f(5420.f, 1800.f));
	warperS[2].setSize(Vector2f(210.f, 10.f));

	RectangleShape skull;
	skull.setPosition(Vector2f(-600.f, 225.f));
	skull.setSize(Vector2f(120.f, 200.f));

	RectangleShape blockade;
	blockade.setPosition(Vector2f(windowSize.x / 2.f + 500.f, windowSize.y / 2.f - 230.f));
	blockade.setSize(Vector2f(120.f, 120.f));


	//initialize items;
	item wand(&awand, Vector2u(1, 1), Vector2f(120.f, 120.f));
	wand.body.setPosition(Vector2f(Vector2f(1030.0f, 600.0f)));

	item coin(&coins, Vector2u(6, 1), Vector2f(60.f, 60.f));
	vector<item>::const_iterator coinIter;
	vector<item> coinArray;

	projectile bullet(&fireball, 1000.f, 100.f);
	vector<projectile>::const_iterator bulletIter;
	vector<projectile> projectileArray;

	item hpp(&hp, Vector2u(1, 1), Vector2f(55.f, 72.5f));
	vector<item>::const_iterator hppIter;
	vector<item> hppArray;

	item mpp(&mp, Vector2u(1, 1), Vector2f(40.f, 77.5f));
	vector<item>::const_iterator mppIter;
	vector<item> mppArray;

	item Key(&keys, Vector2u(1, 1), Vector2f(44.f, 21.5f));
	vector<item>::const_iterator keyIter;
	vector<item> keyArray;


	//initialize enemies;
	enemy normalGargoyle(&gargoyle1, Vector2u(5, 2), Vector2f(360.f, 232.f), Vector2f(generateIntRandom(500, 100), generateIntRandom(2300, 700)), 0.1f, 180.f, 500.f, 15);
	vector<enemy>::const_iterator gargoyle1Iter;
	vector<enemy> gargoyle1Array;
	projectile gargoyle1Bullet(&gargoyle1Ball, 800.f, 5.f);
	vector<projectile>::const_iterator gargoyle1BulletIter;
	vector<projectile> gargoyle1BulletArray;

	enemy advancedGargoyle(&gargoyle2, Vector2u(5, 2), Vector2f(348.f, 372.f), Vector2f(generateIntRandom(500, 100), generateIntRandom(2300, 700)), 0.1f, 250.f, 1500.f, 25);
	vector<enemy>::const_iterator gargoyle2Iter;
	vector<enemy> gargoyle2Array;
	projectile gargoyle2Bullet(&gargoyle2Ball, 1000.f, 20.f);
	vector<projectile>::const_iterator gargoyle2BulletIter;
	vector<projectile> gargoyle2BulletArray;

	enemy normalTitan(&titan1, Vector2u(3, 4), Vector2f(304.f, 400.f), Vector2f(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f)), 0.5f, 240.f, 2500.f, 30);
	vector<enemy>::const_iterator titan1Iter;
	vector<enemy> titan1Array;

	enemy advancedTitan(&titan2, Vector2u(3, 4), Vector2f(304.f, 400.f), Vector2f(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f)), 0.5f, 280.f, 5000.f, 70);
	vector<enemy>::const_iterator titan2Iter;
	vector<enemy> titan2Array;
	projectile titan2Bullet(&titan2Ball, 1200.f, 50.f);
	vector<projectile>::const_iterator titan2BulletIter;
	vector<projectile> titan2BulletArray;

	enemy seller(&monSeller, Vector2u(2, 1), Vector2f(33.f * 16, 49.f * 16), Vector2f(windowSize.x / 2.f + 432.f, windowSize.y / 2.f - 50.f), 0.8, 0.f, 0.f, 0);

	enemy minion(&minion1, Vector2u(5, 2), Vector2f(3 * 96 / 2, 3 * 64 / 2), Vector2f(generateIntRandom(120, 80), generateIntRandom(120, -100)), 0.03f, 300.f, 6000, 30);
	vector<enemy>::const_iterator minionIter;
	vector<enemy> minionArray;
	projectile laser(&gargoyle2Ball, 1200.f, 20.f);
	vector<projectile>::const_iterator laserIter;
	vector<projectile> laserArray;

	enemy boss(&theboss, Vector2u(2, 4), Vector2f(850.f, 900.f), Vector2f(-550.f, 50.f), 1.f, 1, 200000, 300);
	projectile bossBullet(&fireball, 1200.f, 100.f);
	vector<projectile>::const_iterator bossBulletIter;
	vector<projectile> bossBulletArray;

	int entityValue = 0;


	//texts involved;
	textDisplay moneyDp(Color::Yellow);
	moneyDp.text.setFont(font);
	vector<textDisplay>::const_iterator moneyIter;
	vector<textDisplay> moneyArray;

	textDisplay hppDp(Color(255, 155, 0));
	hppDp.text.setFont(font);
	vector<textDisplay>::const_iterator hppPickUpIter;
	vector<textDisplay> hppPickUpArray;

	textDisplay mppDp(Color::Magenta);
	mppDp.text.setFont(font);
	vector<textDisplay>::const_iterator mppPickUpIter;
	vector<textDisplay> mppPickUpArray;

	textDisplay keyDp(Color(255, 239, 84));
	keyDp.text.setFont(font);
	vector<textDisplay>::const_iterator keyPickUpIter;
	vector<textDisplay> keyPickUpArray;

	textDisplay dmgDp(Color::Red);
	dmgDp.text.setFont(font);
	vector<textDisplay>::const_iterator dmgIter;
	vector<textDisplay> dmgArray;

	textBox input(30, Color::White, &font, Vector2f(windowSize / 2.f), true, true, typeLimit);


	//initialize leaderboard info;
	vector<pair<int, string>> highScore;
	FILE* file;
	char temp[25] = {};
	string nameArr[6];
	int scoreArr[6] = {};
	bool collectHS = false;
	file = fopen("resources/leaderboard.txt", "r");
	for (int i = 0;i < 5;i++) 
	{
		fscanf(file, "%s", temp);
		nameArr[i] = temp;
		fscanf(file, "%d", &scoreArr[i]);
		highScore.push_back(make_pair(scoreArr[i], nameArr[i]));
	}
	sort(highScore.begin(), highScore.end());
	fclose(file);


	//loop;
	while (window.isOpen())
	{
		//call delta time;
		deltaTime = clock[0].restart().asSeconds();
		if (deltaTime > 1.f / 20.f) deltaTime = 1.f / 20.f;

		//initialize time variables;
		Time elapse[15];
		elapse[0] = clock[0].getElapsedTime();
		elapse[1] = clock[1].getElapsedTime(); 
		elapse[2] = clock[2].getElapsedTime();
		elapse[3] = clock[3].getElapsedTime();
		elapse[4] = clock[4].getElapsedTime();
		elapse[5] = clock[5].getElapsedTime();
		elapse[6] = clock[6].getElapsedTime();
		elapse[7] = clock[7].getElapsedTime();
		elapse[8] = clock[8].getElapsedTime();
		elapse[9] = clock[9].getElapsedTime();
		elapse[10] = clock[10].getElapsedTime();
		elapse[11] = clock[11].getElapsedTime();
		elapse[12] = clock[12].getElapsedTime();
		elapse[13] = clock[13].getElapsedTime();
		elapse[14] = clock[14].getElapsedTime();

		//check coordinate;
		Vector2i pos = Mouse::getPosition(window);
		Vector2f mousePos(static_cast<float>(pos.x), static_cast<float>(pos.y));

		//textbox;
		platform box(&textbox, Vector2f(680.f, 152.f), Vector2f(player.body.getPosition().x + 10.f, player.body.getPosition().y + windowSize.y / 2.f - 200.f));
		platform winBox(&textbox, Vector2f(680.f, 152.f), Vector2f(0.f, windowSize.y / 2.f - 200.f));
		platform storeBox(&textbox, Vector2f(1700.f, 380.f), Vector2f(windowSize.x / 2.f, 7.f * windowSize.y / 10.f));

		//buttons;
		button startGame(Vector2f(windowSize.x / 2.f, 4.f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 45, "START", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		startGame.setTextOutlineColor(Color::Black);
		startGame.setTextOutlineThickness(3);
		button score(Vector2f(windowSize.x / 2.f, 4.5f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 45, "LEADERBOARD", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		score.setTextOutlineColor(Color::Black);
		score.setTextOutlineThickness(3);
		button tutorial(Vector2f(windowSize.x / 2.f, 5.f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 45, "TUTORIAL", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		tutorial.setTextOutlineColor(Color::Black);
		tutorial.setTextOutlineThickness(3);
		button credit(Vector2f(windowSize.x / 2.f, 5.5f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 45, "CREDITS", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		credit.setTextOutlineColor(Color::Black);
		credit.setTextOutlineThickness(3);
		button exitGame(Vector2f(windowSize.x / 2.f, 6.f * windowSize.y / 7.f), Vector2f(300.f, 45.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 45, "EXIT", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		exitGame.setTextOutlineColor(Color::Black);
		exitGame.setTextOutlineThickness(3);

		button pickItUp(Vector2f(box.body.getPosition().x, box.body.getPosition().y + 10.f), Vector2f(windowSize.x - 200.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, "PRESS 'ENTER' TO PICK UP THE ITEM.", Color::Black, Color::Black, Color::Black);

		button toSky(Vector2f(box.body.getPosition().x, box.body.getPosition().y + 10.f), Vector2f(windowSize.x - 200.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, "PRESS 'ENTER' TO GO UP TO THE SKY.", Color::Black, Color::Black, Color::Black);

		button toBean(Vector2f(box.body.getPosition().x, box.body.getPosition().y + 10.f), Vector2f(windowSize.x - 200.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, "PRESS 'ENTER' TO GO DOWN THE BEANSTALK.", Color::Black, Color::Black, Color::Black);
		string findKey;
		if (key != 5) findKey = ("FIND " + to_string(5 - key) + " MORE KEYS TO OPEN.");
		else findKey = "PRESS 'ENTER' TO ENTER THE CASTLE.";
		button unlock(Vector2f(box.body.getPosition().x, box.body.getPosition().y + 10.f), Vector2f(windowSize.x - 200.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, findKey, Color::Black, Color::Black, Color::Black);

		button welcomeText(Vector2f(storeBox.body.getPosition().x, storeBox.body.getPosition().y + 15.f), Vector2f(windowSize.x, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 55, "What is it that you desire?", Color::Black, Color::Black, Color::Black);
		button healthPotion(Vector2f(windowSize.x / 2.f, 2.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			1.f, &font, 35, "Health Potion                                  60", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		healthPotion.setTextOutlineThickness(1);
		button manaPotion(Vector2f(windowSize.x / 2.f, 3.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			1.f, &font, 35, "Mana Potion                                  25", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		manaPotion.setTextOutlineThickness(1);
		button wandUpgrade(Vector2f(windowSize.x / 2.f, 4.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			1.f, &font, 35, "Upgrade Wand                                200", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		wandUpgrade.setTextOutlineThickness(1);
		button moreMaxHP(Vector2f(windowSize.x / 2.f, 5.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			1.f, &font, 35, "Increase Maximun HP                                500", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		moreMaxHP.setTextOutlineThickness(1);
		button moreMaxMP(Vector2f(windowSize.x / 2.f, 6.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			1.f, &font, 35, "Increase Maximun MP                                100", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		moreMaxMP.setTextOutlineThickness(1);
		button done(Vector2f(windowSize.x / 2.f, 8.f * windowSize.y / 15.f), Vector2f(windowSize.x, 70.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			1.f, &font, 35, "Done.", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		button thxText(Vector2f(storeBox.body.getPosition().x, storeBox.body.getPosition().y + 15.f), Vector2f(3.f * windowSize.x / 4.f, 150.f), Color(186, 186, 186), Color(186, 186, 186), Color(186, 186, 186),
			2.f, &font, 55, "Anything else?", Color::Black, Color::Black, Color::Black);
		button cheap(Vector2f(storeBox.body.getPosition().x, storeBox.body.getPosition().y + 15.f), Vector2f(3.f * windowSize.x / 4.f, 150.f), Color(186, 186, 186), Color(186, 186, 186), Color(186, 186, 186),
			2.f, &font, 55, "Not Enough Money.", Color::Black, Color::Black, Color::Black);
		button byeText(Vector2f(storeBox.body.getPosition().x, storeBox.body.getPosition().y + 15.f), Vector2f(3.f * windowSize.x / 4.f, 75.f), Color(186, 186, 186), Color(186, 186, 186), Color(186, 186, 186),
			2.f, &font, 45, "Gladly looking forward to seeing you again, kind sir.", Color::Black, Color::Black, Color::Black);
		button returnToTheGame(Vector2f(storeBox.body.getPosition().x + 555.f, storeBox.body.getPosition().y + 100.f), Vector2f(windowSize.x / 2.f, 50.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 20, "Return to the game.", Color::Black, Color(69, 69, 69, 255), Color(200, 200, 200, 255));

		button win(Vector2f(winBox.body.getPosition().x, winBox.body.getPosition().y + 10.f), Vector2f(windowSize.x - 200.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, "PRESS 'ENTER' TO CONTINUE.", Color::Black, Color::Black, Color::Black);

		button gameOver(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 150, "GAME OVER", Color::Red, Color::Red, Color::Red);
		button scoreState(Vector2f(windowSize.x / 2.f, 3.5f * windowSize.y / 6.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, "LEADERBOARD", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		button returnToMenu(Vector2f(windowSize.x / 2.f, 9.f * windowSize.y / 10.f), Vector2f(300.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, "RETURN TO MENU", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

		button resume(Vector2f(windowSize.x / 2.f, 2.5f * windowSize.y / 6.f), Vector2f(500.f, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 150, "RESUME", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));
		button toMenu(Vector2f(windowSize.x / 2.f, 9.f * windowSize.y / 10.f), Vector2f(windowSize.x, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 25, "RESTART AND RETURN TO MENU", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

		button Tomenu(Vector2f(windowSize.x - 150.f, 11.f * windowSize.y / 12.f), Vector2f(300, 90.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 20, "Return To Menu", Color::White, Color(150, 150, 150, 255), Color(80, 80, 80, 255));

		button title(Vector2f(windowSize.x / 2.f, 4.f * windowSize.y / 14.f), Vector2f(400, 100.f), Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0),
			2.f, &font, 50, "LEADERBOARD", Color::White, Color::White, Color::White);

		if (state == INPUT || state == CREDIT || state == SCORE || state == TUTORIAL) background.body.setFillColor(Color(150, 150, 150, 111));
		else background.body.setFillColor(Color(255, 255, 255, 255));

		if (state == TUTORIAL) player.body.setScale(2, 2);
		else player.body.setScale(1, 1);

		//player variables;
		Vector2f playerPosition = player.body.getPosition();
		collider playerCollision = player.getCollider();
		player.hp = playerHP;
		if (playerHP >= maxhp) playerHP = maxhp;
		if (maxhp >= 12000) maxhp = 12000;
		player.mp = playerMP;
		if (playerMP >= maxmp) playerMP = maxmp;
		if (maxmp >= 2000) maxmp = 2000;
		if (playerEnergy >= maxEnergy) playerEnergy = maxEnergy;
		player.money = playerMoney;
		if (playerMoney < 0) playerMoney = 0;
		if (wandLevel >= 60) wandLevel = 60;
		player.gravity = playerGravity;
		hpp.gravity = playerGravity;
		mpp.gravity = playerGravity;
		playerGUI gui(&font, &HPP, &MPP, player.hp, maxhp, player.mp, maxmp, playerEnergy, hpPotion, mpPotion, player.money, playerScore, wandLevel, key, boss.hp);
		float atkSpd = 0.4f - wandLevel / 600.f;

		//loop counters;
		int gargoyle1Counter = 0;
		int gargoyle1BulletCounter = 0;
		int gargoyle2Counter = 0;
		int gargoyle2BulletCounter = 0;
		int titan1Counter = 0;
		int titan2Counter = 0;
		int titan2BulletCounter = 0;
		int minionCounter = 0;
		int laserCounter = 0;
		int bossBulletCounter = 0;
		int bulletCounter = 0;
		int coinCounter = 0;
		int hppCounter = 0;
		int mppCounter = 0;
		int keyCounter = 0;
		int moneyCounter = 0;
		int hppPickUpCounter = 0;
		int mppPickUpCounter = 0;
		int keyPickUpCounter = 0;
		int dmgCounter = 0;

		//entities' value;
		int gargoyle1Value = generateIntRandom(10, 20);
		int gargoyle2Value = generateIntRandom(10, 50);
		int titan1Value = generateIntRandom(10, 80);
		int titan2Value = generateIntRandom(10, 150);

		//menu//
		if (state == MENU)
		{
			//set window event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();

				//start game;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && startGame.getGlobalBounds().contains(mousePos))
				{
					window.clear();
					input.setSelected(true);
					state = INPUT;
				}

				//see scores;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && score.getGlobalBounds().contains(mousePos))
				{
					window.clear();
					state = SCORE;
				}

				//tutorial;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && tutorial.getGlobalBounds().contains(mousePos))
				{
					window.clear();
					state = TUTORIAL;
				}

				//credits;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && credit.getGlobalBounds().contains(mousePos))
				{
					window.clear();
					state = CREDIT;
					isScrolled = true;
					speech.body.setPosition(windowSize.x / 2.f, windowSize.y + 380.f);
				}

				//exit game;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && exitGame.getGlobalBounds().contains(mousePos)) window.close();
			}

			//music;
			if (!playMenuMusic)
			{
				menuMusic.play();
				introMusic.stop();
				gameMusic.stop();
				bossMusic.stop();
				storeMusic.stop();
				endMusic.stop();
				die.stop();
				playMenuMusic = true;
				playIntroMusic = false;
				playGameMusic = false;
				playBossMusic = false;
				playStoreMusic = false;
				playYouDie = false;
			}

			//update buttons;
			startGame.update(mousePos);
			score.update(mousePos);
			tutorial.update(mousePos);
			credit.update(mousePos);
			exitGame.update(mousePos);

			//set view;
			view.setCenter(windowSize / 2.f);

			//clear screen;
			window.clear();
			window.setView(view);

			//draw background;
			background.draw(window);

			//draw logo;
			logo.draw(window);

			//draw buttons
			startGame.draw(window);
			score.draw(window);
			tutorial.draw(window);
			credit.draw(window);
			exitGame.draw(window);
		}

		//input;
		if (state == INPUT)
		{
			//set window event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
				if (event.type == Event::TextEntered) input.update(event);
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
				{
					collectHS = false;
					name = input.getInput();
					input.setSelected(false);

					window.clear();
					state = INTRO;
				}
			}

			//set view;
			view.setCenter(windowSize / 2.f);
			window.clear();
			window.setView(view);

			background.draw(window);
			inputScreen.draw(window);
			input.draw(window);
		}

		//the game//
		if (!isPause && state == INTRO || !isPause && state == HOME || !isPause && state == OUTDOOR || 
			!isPause && state == SKY || !isPause && state == CASTLE || !isPause && state == STORE)
		{
			//intro//
			if (state == INTRO)
			{
				//set window event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed) window.close();

					//page up;
					if (event.type == Event::KeyPressed)
					{
						if (page < 4 && event.key.code != Keyboard::Escape) //page up;
						{
							turn.play();
							page++;
						}
						else if (page == 4 && event.key.code == Keyboard::Space) //start game;
						{
							window.clear();
							player.body.setPosition(Vector2f(1125.0f, 560.0f));
							player.setAnimationRow(4);
							state = HOME;
						}
					}
				}

				//music;
				if (!playIntroMusic)
				{
					menuMusic.stop();
					introMusic.play();
					gameMusic.stop();
					bossMusic.stop();
					storeMusic.stop();
					playMenuMusic = false;
					playIntroMusic = true;
					playGameMusic = false;
					playBossMusic = false;
					playStoreMusic = false;
				}

				//set view;
				view.setCenter(windowSize / 2.f);

				//clear screen;
				window.clear();
				window.setView(view);

				if (page == 1) page1.draw(window);
				else if (page == 2) page2.draw(window);
				else if (page == 3) page3.draw(window);
				else if (page == 4) page4.draw(window);
			}

			//stage 1//
			if (state == HOME)
			{
				//music;
				if (!playIntroMusic)
				{
					menuMusic.stop();
					introMusic.play();
					gameMusic.stop();
					bossMusic.stop();
					storeMusic.stop();
					playMenuMusic = false;
					playIntroMusic = true;
					playGameMusic = false;
					playBossMusic = false;
					playStoreMusic = false;
				}

				//update GUI;
				gui.updateStatus(deltaTime, windowSize, playerPosition);
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				player.update(deltaTime);

				//map collision;
				for (int i = 0; i < blockH.size(); i++) if (!collisionCheat) blockH[i].getCollider().checkCollider(playerCollision, 1.0f);

				//set view;
				view.setCenter(playerPosition);

				//clear window;
				window.clear(Color(16, 16, 16));
				window.setView(view);

				//draw map texture;
				background1.draw(window);

				//draw items;
				if (wandLevel == 0)
				{
					wand.draw(window);
					if (player.body.getGlobalBounds().intersects(pickUp.getGlobalBounds()))
					{
						box.draw(window);
						pickItUp.update(mousePos);
						pickItUp.draw(window);
						if (Keyboard::isKeyPressed(Keyboard::Return)) wandLevel = 1;
					}
				}

				//draw player;
				player.draw(window);

				//go outside;
				if (player.body.getGlobalBounds().intersects(warperH.getGlobalBounds()))
				{
					window.clear();
					player.body.setPosition(Vector2f(3720.0f, 5100.0f));
					state = OUTDOOR;
				}
			}

			//stage 2//
			if (state == OUTDOOR)
			{
				//music;
				if (!playGameMusic)
				{
					menuMusic.stop();
					introMusic.stop();
					gameMusic.play();
					bossMusic.stop();
					storeMusic.stop();
					playMenuMusic = false;
					playIntroMusic = false;
					playGameMusic = true;
					playBossMusic = false;
					playStoreMusic = false;
				}

				//update GUI;
				gui.updateStatus(deltaTime, windowSize, playerPosition);
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				player.update(deltaTime);

				//map collision;
				if (!collisionCheat)
				{
					for (int i = 0; i < blockO0.size(); i++) blockO0[i].getCollider().checkCollider(playerCollision, 1.0f);
					for (int i = 0; i < blockO2.size(); i++) blockO2[i].getCollider().checkCollider(playerCollision, 1.0f);
				}

				//set view;
				view.setCenter(playerPosition);

				//clear screen;
				window.clear(Color(127, 231, 255));
				window.setView(view);

				//draw map texture;
				background2.draw(window);

				//draw items;
				coinCounter = 0; //coins;
				for (coinIter = coinArray.begin();coinIter != coinArray.end();coinIter++)
				{
					coinArray[coinCounter].update(deltaTime);
					window.draw(coinArray[coinCounter].body);
					coinArray[coinCounter].lifetime++;
					if (elapse[11].asSeconds() >= 60.f)
					{
						clock[11].restart();
						coinArray[coinCounter].lifetime = 0;
						coinArray[coinCounter].destroy = true;
					}
					coinCounter++;
				}
				hppCounter = 0; //health potions;
				for (hppIter = hppArray.begin();hppIter != hppArray.end();hppIter++)
				{
					hppArray[hppCounter].update(deltaTime);
					window.draw(hppArray[hppCounter].body);
					hppArray[hppCounter].lifetime++;
					if (elapse[12].asSeconds() >= 60.f)
					{
						clock[12].restart();
						hppArray[hppCounter].lifetime = 0;
						hppArray[hppCounter].destroy = true;
					}
					hppCounter++;
				}
				mppCounter = 0; //mana potions;
				for (mppIter = mppArray.begin();mppIter != mppArray.end();mppIter++)
				{
					mppArray[mppCounter].update(deltaTime);
					window.draw(mppArray[mppCounter].body);
					mppArray[mppCounter].lifetime++;
					if (elapse[13].asSeconds() >= 60.f)
					{
						clock[13].restart();
						mppArray[mppCounter].lifetime = 0;
						mppArray[mppCounter].destroy = true;
					}
					mppCounter++;
				}
				keyCounter = 0; //keys;
				for (keyIter = keyArray.begin();keyIter != keyArray.end();keyIter++)
				{
					keyArray[keyCounter].update(deltaTime);
					window.draw(keyArray[keyCounter].body);
					keyArray[keyCounter].lifetime++;
					if (elapse[14].asSeconds() >= 200.f)
					{
						clock[14].restart();
						keyArray[keyCounter].lifetime = 0;
						keyArray[keyCounter].destroy = true;
					}
					keyCounter++;
				}

				//draw entities;
				if (normalGargoyle.isSpawned[0]) //spawn gargoyle1;
				{
					normalGargoyle.isSpawned[0] = false;
					for (int i = 0;i < 7;i++)
					{
						normalGargoyle.body.setPosition(generateIntRandom(500, 100), generateIntRandom(2300, 700));
						gargoyle1Array.push_back(normalGargoyle);
					}
					for (int i = 0;i < 8;i++)
					{
						normalGargoyle.body.setPosition(generateIntRandom(500, 1500), generateIntRandom(2300, 700));
						gargoyle1Array.push_back(normalGargoyle);
					}
				}
				if (normalGargoyle.isRespawned) //respawn gargoyle1;
				{
					int LoR = generateIntRandom(2, 1);
					normalGargoyle.isRespawned = false;
					if (LoR == 1) normalGargoyle.body.setPosition(generateIntRandom(500, 100), generateIntRandom(2300, 700));
					else if (LoR == 2) normalGargoyle.body.setPosition(generateIntRandom(500, 1500), generateIntRandom(2300, 700));
					gargoyle1Array.push_back(normalGargoyle);
				}
				gargoyle1Counter = 0; //gargoyle1 aggroed;
				for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
				{
					if (gargoyle1Array[gargoyle1Counter].isAggroed)
					{
						gargoyle1Array[gargoyle1Counter].action = generateIntRandom(2, 1);
						if (elapse[3].asMilliseconds() >= 10.f)
						{
							clock[3].restart();
							gargoyle1Array[gargoyle1Counter].updateAggroedFly(deltaTime, playerPosition);
						}
					}
					if (gargoyle1Array[gargoyle1Counter].action >= 2)
					{
						if (elapse[4].asSeconds() >= 1.f)
						{
							clock[4].restart();
							if (playerPosition.x < gargoyle1Array[gargoyle1Counter].body.getPosition().x && abs(playerPosition.y - gargoyle1Array[gargoyle1Counter].body.getPosition().y) <= 40)
							{
								gargoyle1Bullet.direction = LEFT;
								gargoyle1Bullet.body.setPosition(gargoyle1Array[gargoyle1Counter].body.getPosition());
								gargoyle1BulletArray.push_back(gargoyle1Bullet);
								gargoyle1Array[gargoyle1Counter].direction = LEFT;
							}
							if (playerPosition.x > gargoyle1Array[gargoyle1Counter].body.getPosition().x && abs(playerPosition.y - gargoyle1Array[gargoyle1Counter].body.getPosition().y) <= 40)
							{
								gargoyle1Bullet.direction = RIGHT;
								gargoyle1Bullet.body.setPosition(gargoyle1Array[gargoyle1Counter].body.getPosition());
								gargoyle1BulletArray.push_back(gargoyle1Bullet);
								gargoyle1Array[gargoyle1Counter].direction = RIGHT;
							}
						}
					}
					gargoyle1Counter++;
				}
				gargoyle1Counter = 0; //gargoyle1 die;
				for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
				{
					if (gargoyle1Array[gargoyle1Counter].isDead)
					{
						coin.body.setPosition(generateIntRandom(480, 840), gargoyle1Array[gargoyle1Counter].body.getPosition().y);
						coinArray.push_back(coin);
						if (chance(29) == 0)
						{
							hpp.body.setPosition(generateIntRandom(480, 840), gargoyle1Array[gargoyle1Counter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(24) == 0)
						{
							mpp.body.setPosition(generateIntRandom(480, 840), gargoyle1Array[gargoyle1Counter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						if (chance(299) == 0)
						{
							Key.body.setPosition(generateIntRandom(480, 840), gargoyle1Array[gargoyle1Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						dead.play();
						entityValue = gargoyle1Value;
						playerScore += 100;
						gargoyle1Array.erase(gargoyle1Iter);
						normalGargoyle.isRespawned = true;
						break;
					}
					gargoyle1Counter++;
				}
				gargoyle1BulletCounter = 0; //gargoyle1's bullets hit player;
				for (gargoyle1BulletIter = gargoyle1BulletArray.begin(); gargoyle1BulletIter != gargoyle1BulletArray.end();gargoyle1BulletIter++)
				{
					if (gargoyle1BulletArray[gargoyle1BulletCounter].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						player.hurt();
						hurt.play();
						int damage = gargoyle1BulletArray[gargoyle1BulletCounter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						playerHP -= gargoyle1Bullet.damage;
						gargoyle1BulletArray.erase(gargoyle1BulletIter);
						break;
					}
					gargoyle1BulletCounter++;
				}
				gargoyle1BulletCounter = 0; //draw gargoyle1's bullets;
				for (gargoyle1BulletIter = gargoyle1BulletArray.begin(); gargoyle1BulletIter != gargoyle1BulletArray.end();gargoyle1BulletIter++)
				{
					gargoyle1BulletArray[gargoyle1BulletCounter].update(deltaTime);
					window.draw(gargoyle1BulletArray[gargoyle1BulletCounter].body);
					gargoyle1BulletCounter++;
				}
				gargoyle1Counter = 0; //draw gargoyle1;
				for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
				{
					gargoyle1Array[gargoyle1Counter].updateFly(deltaTime);
					window.draw(gargoyle1Array[gargoyle1Counter].body);
					gargoyle1Counter++;
				}

				if (advancedGargoyle.isSpawned[0]) //spawn gargoyle1;
				{
					advancedGargoyle.isSpawned[0] = false;
					for (int i = 0;i < 2;i++)
					{
						advancedGargoyle.body.setPosition(generateIntRandom(500, 0), generateIntRandom(2300, 700));
						gargoyle2Array.push_back(advancedGargoyle);
					}
					for (int i = 0;i < 3;i++)
					{
						advancedGargoyle.body.setPosition(generateIntRandom(500, 1600), generateIntRandom(2300, 700));
						gargoyle2Array.push_back(advancedGargoyle);
					}
				}
				if (advancedGargoyle.isRespawned) //respawn gargoyle2;
				{
					int LoR = generateIntRandom(2, 1);
					advancedGargoyle.isRespawned = false;
					if (LoR == 1) advancedGargoyle.body.setPosition(generateIntRandom(500, 0), generateIntRandom(2300, 700));
					else if (LoR == 2) advancedGargoyle.body.setPosition(generateIntRandom(500, 1600), generateIntRandom(2300, 700));
					gargoyle2Array.push_back(advancedGargoyle);
				}
				gargoyle2Counter = 0; //gargoyle2 aggroed;
				for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
				{
					if (gargoyle2Array[gargoyle2Counter].isAggroed)
					{
						gargoyle2Array[gargoyle2Counter].action = generateIntRandom(2, 1);
						if (elapse[7].asMilliseconds() >= 10.f)
						{
							clock[7].restart();
							gargoyle2Array[gargoyle2Counter].updateAggroedFly(deltaTime, playerPosition);
						}
					}
					if (gargoyle2Array[gargoyle2Counter].action >= 2)
					{
						if (elapse[8].asSeconds() >= 0.8f)
						{
							clock[8].restart();
							if (playerPosition.x < gargoyle2Array[gargoyle2Counter].body.getPosition().x && abs(playerPosition.y - gargoyle2Array[gargoyle2Counter].body.getPosition().y) <= 40)
							{
								gargoyle2Bullet.direction = LEFT;
								gargoyle2Bullet.body.setPosition(gargoyle2Array[gargoyle2Counter].body.getPosition());
								gargoyle2BulletArray.push_back(gargoyle2Bullet);
								gargoyle2Array[gargoyle2Counter].direction = LEFT;
							}
							if (playerPosition.x > gargoyle2Array[gargoyle2Counter].body.getPosition().x && abs(playerPosition.y - gargoyle2Array[gargoyle2Counter].body.getPosition().y) <= 40)
							{
								gargoyle2Bullet.direction = RIGHT;
								gargoyle2Bullet.body.setPosition(gargoyle2Array[gargoyle2Counter].body.getPosition());
								gargoyle2BulletArray.push_back(gargoyle2Bullet);
								gargoyle2Array[gargoyle2Counter].direction = RIGHT;
							}
						}
					}
					gargoyle2Counter++;
				}
				gargoyle2Counter = 0; //gargoyle2 die;
				for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
				{
					if (gargoyle2Array[gargoyle2Counter].isDead)
					{
						coin.body.setPosition(generateIntRandom(480, 840), gargoyle2Array[gargoyle2Counter].body.getPosition().y);
						coinArray.push_back(coin);
						if (chance(24) == 0)
						{
							hpp.body.setPosition(generateIntRandom(480, 840), gargoyle2Array[gargoyle2Counter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(19) == 0)
						{
							mpp.body.setPosition(generateIntRandom(480, 840), gargoyle2Array[gargoyle2Counter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						if (chance(99) == 0)
						{
							Key.body.setPosition(generateIntRandom(480, 840), gargoyle2Array[gargoyle2Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						dead.play();
						entityValue = gargoyle2Value;
						playerScore += 250;
						gargoyle2Array.erase(gargoyle2Iter);
						advancedGargoyle.isRespawned = true;
						break;
					}
					gargoyle2Counter++;
				}
				gargoyle2BulletCounter = 0; //gargoyle2's bullets hit player;
				for (gargoyle2BulletIter = gargoyle2BulletArray.begin(); gargoyle2BulletIter != gargoyle2BulletArray.end();gargoyle2BulletIter++)
				{
					if (gargoyle2BulletArray[gargoyle2BulletCounter].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						player.hurt();
						hurt.play();
						int damage = gargoyle2BulletArray[gargoyle2BulletCounter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						playerHP -= damage;
						gargoyle2BulletArray.erase(gargoyle2BulletIter);
						break;
					}
					gargoyle2BulletCounter++;
				}
				gargoyle2BulletCounter = 0; //draw gargoyle2's bullets;
				for (gargoyle2BulletIter = gargoyle2BulletArray.begin(); gargoyle2BulletIter != gargoyle2BulletArray.end();gargoyle2BulletIter++)
				{
					gargoyle2BulletArray[gargoyle2BulletCounter].update(deltaTime);
					window.draw(gargoyle2BulletArray[gargoyle2BulletCounter].body);
					gargoyle2BulletCounter++;
				}
				gargoyle2Counter = 0; //draw gargoyle2;
				for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
				{
					gargoyle2Array[gargoyle2Counter].updateFly(deltaTime);
					window.draw(gargoyle2Array[gargoyle2Counter].body);
					gargoyle2Counter++;
				}

				player.draw(window); //draw player;

				//go back inside the house;
				if (player.body.getGlobalBounds().intersects(warperO[0].getGlobalBounds()))
				{
					window.clear();
					player.body.setPosition(Vector2f(1255.0f, 1970.0f));
					state = HOME;
				}

				//go up to the sky;
				if (player.body.getGlobalBounds().intersects(warperO[1].getGlobalBounds()))
				{
					box.draw(window);
					toSky.update(mousePos);
					toSky.draw(window);
					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						window.clear();
						player.setAnimationRow(2);
						player.body.setPosition(Vector2f(1320.0f, 2160.0f));
						state = SKY;
					}
				}
			}

			//stage 3//
			if (state == SKY)
			{
				//music;
				if (!playGameMusic)
				{
					menuMusic.stop();
					introMusic.stop();
					gameMusic.play();
					bossMusic.stop();
					storeMusic.stop();
					playMenuMusic = false;
					playIntroMusic = false;
					playGameMusic = true;
					playBossMusic = false;
					playStoreMusic = false;
				}

				//update GUI;
				gui.updateStatus(deltaTime, windowSize, playerPosition);
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				player.update(deltaTime);

				//map collision;
				for (int i = 0; i < blockS0.size(); i++) if (!collisionCheat) blockS0[i].getCollider().checkCollider(playerCollision, 1.0f);

				//set view;
				view.setCenter(playerPosition);

				//clear screen;
				window.clear(Color(127, 231, 255));
				window.setView(view);

				//draw map texture;
				background3.draw(window);

				//draw items;
				coinCounter = 0; //coins;
				for (coinIter = coinArray.begin();coinIter != coinArray.end();coinIter++)
				{
					coinArray[coinCounter].update(deltaTime);
					window.draw(coinArray[coinCounter].body);
					coinArray[coinCounter].lifetime++;
					if (elapse[11].asSeconds() >= 60.f)
					{
						clock[11].restart();
						coinArray[coinCounter].lifetime = 0;
						coinArray[coinCounter].destroy = true;
					}
					coinCounter++;
				}
				hppCounter = 0; //health potions;
				for (hppIter = hppArray.begin();hppIter != hppArray.end();hppIter++)
				{
					hppArray[hppCounter].update(deltaTime);
					window.draw(hppArray[hppCounter].body);
					hppArray[hppCounter].lifetime++;
					if (elapse[12].asSeconds() >= 60.f)
					{
						clock[12].restart();
						hppArray[hppCounter].lifetime = 0;
						hppArray[hppCounter].destroy = true;
					}
					hppCounter++;
				}
				mppCounter = 0; //mana potions;
				for (mppIter = mppArray.begin();mppIter != mppArray.end();mppIter++)
				{
					mppArray[mppCounter].update(deltaTime);
					window.draw(mppArray[mppCounter].body);
					mppArray[mppCounter].lifetime++;
					if (elapse[13].asSeconds() >= 60.f)
					{
						clock[13].restart();
						mppArray[mppCounter].lifetime = 0;
						mppArray[mppCounter].destroy = true;
					}
					mppCounter++;
				}
				keyCounter = 0; //keys;
				for (keyIter = keyArray.begin();keyIter != keyArray.end();keyIter++)
				{
					keyArray[keyCounter].update(deltaTime);
					window.draw(keyArray[keyCounter].body);
					keyArray[keyCounter].lifetime++;
					if (elapse[14].asSeconds() >= 200.f)
					{
						clock[14].restart();
						keyArray[keyCounter].lifetime = 0;
						keyArray[keyCounter].destroy = true;
					}
					keyCounter++;
				}

				//draw entities;
				if (normalTitan.isSpawned[0]) //spawn titan1;
				{
					normalTitan.isSpawned[0] = false;
					for (int i = 0;i < 10;i++)
					{
						normalTitan.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
						titan1Array.push_back(normalTitan);
					}
				}
				if (normalTitan.isRespawned) //respawn titan1;
				{
					normalTitan.isRespawned = false;
					titan1Array.push_back(normalTitan);
					normalTitan.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
				}
				titan1Counter = 0; //titan1 hit;
				for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
				{
					collider titan1Collision = titan1Array[titan1Counter].getCollider();
					for (int i = 0; i < blockS0.size(); i++) blockS0[i].getCollider().checkCollider(titan1Collision, 1.0f);
					for (int i = 0; i < blockS2.size(); i++) blockS2[i].getCollider().checkCollider(titan1Collision, 1.0f);

					if (player.body.getGlobalBounds().intersects(titan1Array[titan1Counter].body.getGlobalBounds()) && elapse[1].asSeconds() >= 0.5f)
					{
						clock[1].restart();
						player.hurt();
						hurt.play();
						int damage = titan1Array[titan1Counter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						if (!unlimitedHealthCheat) playerHP -= damage;
					}
					titan1Counter++;
				}
				titan1Counter = 0; //titan1	aggroed;
				for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
				{
					if (elapse[3].asSeconds() >= 0.02f)
					{
						clock[3].restart();
						if (titan1Array[titan1Counter].isAggroed) titan1Array[titan1Counter].action = 1;
					}
					titan1Counter++;
				}
				titan1Counter = 0; //titan1 die;
				for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
				{
					if (titan1Array[titan1Counter].isDead)
					{
						coin.body.setPosition(titan1Array[titan1Counter].body.getPosition());
						coinArray.push_back(coin);
						if (chance(14) == 0)
						{
							hpp.body.setPosition(titan1Array[titan1Counter].body.getPosition().x + 25.f, titan1Array[titan1Counter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(9) == 0)
						{
							mpp.body.setPosition(titan1Array[titan1Counter].body.getPosition().x - 25.f, titan1Array[titan1Counter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						if (chance(69) == 0)
						{
							Key.body.setPosition(titan1Array[titan1Counter].body.getPosition().x, titan1Array[titan1Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						dead.play();
						entityValue = titan1Value;
						playerScore += 500;
						titan1Array.erase(titan1Iter);
						normalTitan.isRespawned = true;
						break;
					}
					titan1Counter++;
				}
				titan1Counter = 0; //draw titan1;
				for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
				{
					if (titan1Array[titan1Counter].isAggroed) titan1Array[titan1Counter].updateAggrovated(deltaTime, player.body.getPosition());
					else titan1Array[titan1Counter].updateWalk(deltaTime);
					window.draw(titan1Array[titan1Counter].body);
					titan1Counter++;
				}

				if (advancedTitan.isSpawned[0]) //spawn titan2;
				{
					advancedTitan.isSpawned[0] = false;
					for (int i = 0;i < 5;i++)
					{
						advancedTitan.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
						titan2Array.push_back(advancedTitan);
					}
				}
				if (advancedTitan.isRespawned) //respawn titan2;
				{
					advancedTitan.isRespawned = false;
					titan2Array.push_back(advancedTitan);
					advancedTitan.body.setPosition(generateIntRandom(2200, 2500.f), generateIntRandom(1150, 900.f));
				}
				titan2Counter = 0; //titan2 hit;
				for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
				{
					collider titan2Collision = titan2Array[titan2Counter].getCollider();
					for (int i = 0; i < blockS0.size(); i++) blockS0[i].getCollider().checkCollider(titan2Collision, 1.0f);
					for (int i = 0; i < blockS2.size(); i++) blockS2[i].getCollider().checkCollider(titan2Collision, 1.0f);

					if (player.body.getGlobalBounds().intersects(titan2Array[titan2Counter].body.getGlobalBounds()))
					{
						if (elapse[1].asSeconds() >= 0.5f)
						{
							clock[1].restart();
							player.hurt();
							hurt.play();
							int damage = titan2Array[titan2Counter].damage;
							dmgDp.text.setString("-" + to_string(damage));
							dmgDp.text.setPosition(playerPosition);
							dmgArray.push_back(dmgDp);
							if (!unlimitedHealthCheat) playerHP -= damage;
						}
					}
					titan2Counter++;
				}
				titan2Counter = 0; //titan2	aggroed;
				for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
				{
					if (titan2Array[titan2Counter].isAggroed)
					{
						titan2Array[titan2Counter].action = generateIntRandom(2, 1);
						if (elapse[3].asSeconds() >= 0.02f)
						{
							clock[3].restart();
							titan2Array[titan2Counter].updateAggrovated(deltaTime, playerPosition);
						}
					}
					if (titan2Array[titan2Counter].action >= 2)
					{
						if (elapse[4].asSeconds() >= 0.5f)
						{
							clock[4].restart();
							if (playerPosition.x < titan2Array[titan2Counter].body.getPosition().x && abs(playerPosition.y - titan2Array[titan2Counter].body.getPosition().y) <= 40)
							{
								titan2Bullet.direction = LEFT;
								titan2Bullet.body.setPosition(titan2Array[titan2Counter].body.getPosition());
								titan2BulletArray.push_back(titan2Bullet);
								titan2Array[titan2Counter].direction = LEFT;
								advancedTitan.shoot = true;
							}
							if (playerPosition.x > titan2Array[titan2Counter].body.getPosition().x && abs(playerPosition.y - titan2Array[titan2Counter].body.getPosition().y) <= 40)
							{
								titan2Bullet.direction = RIGHT;
								titan2Bullet.body.setPosition(titan2Array[titan2Counter].body.getPosition());
								titan2BulletArray.push_back(titan2Bullet);
								titan2Array[titan2Counter].direction = RIGHT;
								advancedTitan.shoot = true;
							}
							if (playerPosition.y < titan2Array[titan2Counter].body.getPosition().y && abs(playerPosition.x - titan2Array[titan2Counter].body.getPosition().x) <= 40)
							{
								titan2Bullet.direction = UP;
								titan2Bullet.body.setPosition(titan2Array[titan2Counter].body.getPosition());
								titan2BulletArray.push_back(titan2Bullet);
								titan2Array[titan2Counter].direction = UP;
								advancedTitan.shoot = true;
							}
							if (playerPosition.y > titan2Array[titan2Counter].body.getPosition().y && abs(playerPosition.x - titan2Array[titan2Counter].body.getPosition().x) <= 40)
							{
								titan2Bullet.direction = DOWN;
								titan2Bullet.body.setPosition(titan2Array[titan2Counter].body.getPosition());
								titan2BulletArray.push_back(titan2Bullet);
								titan2Array[titan2Counter].direction = DOWN;
								advancedTitan.shoot = true;
							}
						}
					}
					titan2Counter++;
				}
				titan2Counter = 0; //titan2 die;
				for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
				{
					if (titan2Array[titan2Counter].isDead)
					{
						coin.body.setPosition(titan2Array[titan2Counter].body.getPosition());
						coinArray.push_back(coin);
						if (chance(9) == 0)
						{
							hpp.body.setPosition(titan2Array[titan2Counter].body.getPosition().x + 25.f, titan2Array[titan2Counter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(4) == 0)
						{
							mpp.body.setPosition(titan2Array[titan2Counter].body.getPosition().x - 25.f, titan2Array[titan2Counter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						if (chance(39) == 0)
						{
							Key.body.setPosition(titan2Array[titan2Counter].body.getPosition().x, titan2Array[titan2Counter].body.getPosition().y + 25.f);
							keyArray.push_back(Key);
						}
						dead.play();
						entityValue = titan2Value;
						playerScore += 1000;
						titan2Array.erase(titan2Iter);
						advancedTitan.isRespawned = true;
						break;
					}
					titan2Counter++;
				}
				titan2BulletCounter = 0; //titan2's bullets hit player;
				for (titan2BulletIter = titan2BulletArray.begin(); titan2BulletIter != titan2BulletArray.end();titan2BulletIter++)
				{
					if (titan2BulletArray[titan2BulletCounter].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						player.hurt();
						hurt.play();
						int damage = titan2BulletArray[titan2BulletCounter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						playerHP -= damage;
						titan2BulletArray.erase(titan2BulletIter);
						break;
					}
					titan2BulletCounter++;
				}
				titan2BulletCounter = 0; //draw titan2's bullets;
				for (titan2BulletIter = titan2BulletArray.begin(); titan2BulletIter != titan2BulletArray.end();titan2BulletIter++)
				{
					titan2BulletArray[titan2BulletCounter].update(deltaTime);
					window.draw(titan2BulletArray[titan2BulletCounter].body);
					titan2BulletCounter++;
				}
				titan2Counter = 0; //draw titan2;
				for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
				{
					titan2Array[titan2Counter].updateWalk(deltaTime);
					window.draw(titan2Array[titan2Counter].body);
					titan2Counter++;
				}

				player.draw(window); //draw player;

				//go down the beanstalk;
				if (player.body.getGlobalBounds().intersects(warperS[0].getGlobalBounds()))
				{
					box.draw(window);
					toBean.update(mousePos);
					toBean.draw(window);
					if (Keyboard::isKeyPressed(Keyboard::Return))
					{
						window.clear();
						player.body.setPosition(Vector2f(1100.0f, 555.0f));
						state = OUTDOOR;
					}
				}

				//go into the store;
				if (player.body.getGlobalBounds().intersects(warperS[1].getGlobalBounds()))
				{
					window.clear();
					player.body.setPosition(windowSize / 2.f);
					clickState = UNSELECTED;
					state = STORE;
				}

				//go inside the castle;
				if (Keyboard::isKeyPressed(Keyboard::Return) && key == 5) isUnlocked = true;
				if (player.body.getGlobalBounds().intersects(warperS[2].getGlobalBounds()))
				{
					if (isUnlocked)
					{
						window.clear();
						player.body.setPosition(Vector2f(700.f, 400.f));
						player.setAnimationRow(6);
						state = CASTLE;
					}
					if (!isUnlocked)
					{
						box.draw(window);
						unlock.update(mousePos);
						unlock.draw(window);
					}
				}
			}

			//stage 4//
			if (state == CASTLE)
			{
				//music;
				if (!playBossMusic)
				{
					menuMusic.stop();
					introMusic.stop();
					gameMusic.stop();
					bossMusic.play();
					storeMusic.stop();
					playMenuMusic = false;
					playIntroMusic = false;
					playGameMusic = false;
					playBossMusic = true;
					playStoreMusic = false;
				}

				//update GUI;
				gui.updateCastle(deltaTime, windowSize);

				//update entities;
				if (!gravityCheat) player.updateBossFight(deltaTime);
				else player.update(deltaTime);
				boss.updateBoss(deltaTime, bossPhase);

				if (player.body.getGlobalBounds().intersects(boss.body.getGlobalBounds()) && !boss.isDead)
				{
					player.hurt();
					if (elapse[1].asSeconds() >= 0.5f)
					{
						clock[1].restart();
						int damage = boss.damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						if (!unlimitedHealthCheat) playerHP -= damage;
					}
				}

				//initialize collider;
				Vector2f direction;
				for (int i = 0; i < ground.size(); i++) platform& platform = ground[i];
				for (platform& platform : ground) if (!gravityCheat) if (platform.getCollider().checkGroundCollision(playerCollision, direction, 1.f)) player.onCollision(direction);
				for (int i = 0; i < torch1.size(); i++) platform& platform = torch1[i];
				for (platform& platform : torch1) if (!gravityCheat) if (platform.getCollider().checkGroundCollision(playerCollision, direction, 1.f)) player.onCollision(direction);
				for (int i = 0; i < torch2.size(); i++) platform& platform = torch2[i];
				for (platform& platform : torch2) if (!gravityCheat) if (platform.getCollider().checkGroundCollision(playerCollision, direction, 1.f)) player.onCollision(direction);
				for (int i = 0; i < torch3.size(); i++) platform& platform = torch3[i];
				for (platform& platform : torch3) if (!gravityCheat) if (platform.getCollider().checkGroundCollision(playerCollision, direction, 1.f)) player.onCollision(direction);
				for (int i = 0; i < Chandelier.size(); i++) platform& platform = Chandelier[i];
				for (platform& platform : Chandelier) if (!gravityCheat) if (platform.getCollider().checkGroundCollision(playerCollision, direction, 1.f)) player.onCollision(direction);

				hppCounter = 0;
				for (hppIter = hppArray.begin();hppIter != hppArray.end();hppIter++)
				{
					collider hpPotionCollision = hppArray[hppCounter].getCollider();
					for (int i = 0; i < ground.size(); i++) platform& platform = ground[i];
					for (platform& platform : ground) if (platform.getCollider().checkGroundCollision(hpPotionCollision, direction, 1.f)) hppArray[hppCounter].onCollision(direction);
					for (int i = 0; i < torch1.size(); i++) platform& platform = torch1[i];
					for (platform& platform : torch1) if (platform.getCollider().checkGroundCollision(hpPotionCollision, direction, 1.f)) hppArray[hppCounter].onCollision(direction);
					for (int i = 0; i < torch2.size(); i++) platform& platform = torch2[i];
					for (platform& platform : torch2) if (platform.getCollider().checkGroundCollision(hpPotionCollision, direction, 1.f)) hppArray[hppCounter].onCollision(direction);
					for (int i = 0; i < torch3.size(); i++) platform& platform = torch3[i];
					for (platform& platform : torch3) if (platform.getCollider().checkGroundCollision(hpPotionCollision, direction, 1.f)) hppArray[hppCounter].onCollision(direction);
					for (int i = 0; i < Chandelier.size(); i++) platform& platform = Chandelier[i];
					for (platform& platform : Chandelier) if (platform.getCollider().checkGroundCollision(hpPotionCollision, direction, 1.f)) hppArray[hppCounter].onCollision(direction);
					hppCounter++;
				}

				mppCounter = 0;
				for (mppIter = mppArray.begin();mppIter != mppArray.end();mppIter++)
				{
					collider mpPotionCollision = mppArray[mppCounter].getCollider();
					for (int i = 0; i < ground.size(); i++) platform& platform = ground[i];
					for (platform& platform : ground) if (platform.getCollider().checkGroundCollision(mpPotionCollision, direction, 1.f)) mppArray[mppCounter].onCollision(direction);
					for (int i = 0; i < torch1.size(); i++) platform& platform = torch1[i];
					for (platform& platform : torch1) if (platform.getCollider().checkGroundCollision(mpPotionCollision, direction, 1.f)) mppArray[mppCounter].onCollision(direction);
					for (int i = 0; i < torch2.size(); i++) platform& platform = torch2[i];
					for (platform& platform : torch2) if (platform.getCollider().checkGroundCollision(mpPotionCollision, direction, 1.f)) mppArray[mppCounter].onCollision(direction);
					for (int i = 0; i < torch3.size(); i++) platform& platform = torch3[i];
					for (platform& platform : torch3) if (platform.getCollider().checkGroundCollision(mpPotionCollision, direction, 1.f)) mppArray[mppCounter].onCollision(direction);
					for (int i = 0; i < Chandelier.size(); i++) platform& platform = Chandelier[i];
					for (platform& platform : Chandelier) if (platform.getCollider().checkGroundCollision(mpPotionCollision, direction, 1.f)) mppArray[mppCounter].onCollision(direction);
					mppCounter++;
				}

				collider leftScreen = wall1.getCollider();
				collider rightScreen = wall2.getCollider();
				leftScreen.checkCollider(playerCollision, 1.f);
				rightScreen.checkCollider(playerCollision, 1.f);

				//set view;
				view.setCenter(0.f, 0.f);

				//claer screen;
				window.clear(Color(32, 48, 32));
				window.setView(view);

				//draw background;
				castle.draw(window);
				wallTorch1.draw(window);
				wallTorch2.draw(window);
				wallTorch3.draw(window);
				chandelier.draw(window);

				//draw items;
				hppCounter = 0; //health potions;
				for (hppIter = hppArray.begin();hppIter != hppArray.end();hppIter++)
				{
					hppArray[hppCounter].updateGravity(deltaTime);
					window.draw(hppArray[hppCounter].body);
					hppArray[hppCounter].lifetime++;
					if (hppArray[hppCounter].lifetime >= 500)
					{
						hppArray[hppCounter].lifetime = 0;
						hppArray[hppCounter].destroy = true;
					}
					hppCounter++;
				}
				mppCounter = 0; //mana potions;
				for (mppIter = mppArray.begin();mppIter != mppArray.end();mppIter++)
				{
					mppArray[mppCounter].updateGravity(deltaTime);
					window.draw(mppArray[mppCounter].body);
					mppArray[mppCounter].lifetime++;
					if (mppArray[mppCounter].lifetime >= 500)
					{
						mppArray[mppCounter].lifetime = 0;
						mppArray[mppCounter].destroy = true;
					}
					mppCounter++;
				}

				if (boss.hp > 100000 && boss.hp < 199400) bossPhase = PISSED;
				else if (boss.hp > 50000 && boss.hp <= 100000) bossPhase = INFURIATED;
				else if (boss.hp > 0 && boss.hp <= 50000) bossPhase = MURDEROUS;
				if (bossPhase == AGGROVATED)
				{
					if (!playRoar)
					{
						roar.play();
						playRoar = true;
						playLaugh = false;
					}
					if (minion.isSpawned[0]) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playRoar = false;
							playLaugh = true;
						}
						minion.isSpawned[0] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
				}
				if (bossPhase == PISSED)
				{
					if (minion.isSpawned[1] && boss.hp <= 190000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[1] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[2] && boss.hp <= 170000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[2] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[3] && boss.hp <= 150000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[3] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[4] && boss.hp <= 130000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[4] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[5] && boss.hp <= 120000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[5] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[6] && boss.hp <= 110000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playRoar = false;
							playLaugh = true;
						}
						minion.isSpawned[6] = false;
						minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
						minionArray.push_back(minion);
						minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
						minionArray.push_back(minion);
						minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
						minionArray.push_back(minion);
					}
				}
				if (bossPhase == INFURIATED)
				{
					if (!playRoar)
					{
						roar.play();
						playRoar = true;
						playLaugh = false;
					}
					if (elapse[13].asSeconds() >= 1.2f)
					{
						pattern++;
						if (pattern > 3) pattern = 1;
						ora.play();
						clock[13].restart();
						if (playerPosition.x > boss.body.getPosition().x)
						{
							bossBullet.direction = RIGHT;
							if (pattern == 1)
							{
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - (3.f * boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - (boss.body.getSize().y / 4.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - (boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
							}
							if (pattern == 2)
							{
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - (boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y);
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y + (boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
							}
							if (pattern == 3)
							{
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y + (boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y + (boss.body.getSize().y / 4.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y + (3.f * boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
							}
						}
					}
				}
				if (bossPhase == MURDEROUS)
				{
					if (!playRoar)
					{
						roar.play();
						playRoar = true;
						playLaugh = false;
					}
					if (elapse[14].asSeconds() >= 1.f)
					{
						pattern++;
						if (pattern > 2) pattern = 1;
						ora.play();
						clock[14].restart();
						if (playerPosition.x > boss.body.getPosition().x)
						{
							bossBullet.direction = RIGHT;
							if (pattern == 1)
							{
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - (boss.body.getSize().y / 2.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - (3.f * boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - (boss.body.getSize().y / 4.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - (boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y);
								bossBulletArray.push_back(bossBullet);
							}
							if (pattern == 2)
							{
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y + (3.f * boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y + (boss.body.getSize().y / 4.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y + (boss.body.getSize().y / 8.f));
								bossBulletArray.push_back(bossBullet);
								bossBullet.body.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y);
								bossBulletArray.push_back(bossBullet);
							}
						}
					}
					if (minion.isSpawned[7]) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[7] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[8] && boss.hp <= 40000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[8] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[9] && boss.hp <= 30000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[9] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[10] && boss.hp <= 20000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[10] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[11] && boss.hp <= 15000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[11] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[12] && boss.hp <= 10000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[12] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[13] && boss.hp <= 5000) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playLaugh = true;
						}
						minion.isSpawned[13] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
					if (minion.isSpawned[14] && boss.hp <= 2500) //spawn minion;
					{
						if (!playLaugh)
						{
							evillaugh.play();
							playRoar = false;
							playLaugh = true;
						}
						minion.isSpawned[14] = false;
						for (int i = 0;i < 3;i++)
						{
							minion.body.setPosition(generateIntRandom(120, 80), generateIntRandom(120, -100));
							minionArray.push_back(minion);
						}
					}
				}
				if (boss.isDead) //boss die;
				{
					if (!playRoar)
					{
						roar.play();
						playRoar = true;
						playLaugh = false;
					}
					bossMusic.stop();

					gargoyle1Counter = 0;
					for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
					{
						gargoyle1Array.erase(gargoyle1Iter);
						break;
					}
					gargoyle2Counter = 0;
					for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
					{
						gargoyle2Array.erase(gargoyle2Iter);
						break;
					}
					titan2Counter = 0;
					for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
					{
						titan2Array.erase(titan2Iter);
						break;
					}
					titan1Counter = 0;
					for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
					{
						titan1Array.erase(titan1Iter);
						break;
					}
					titan2Counter = 0;
					for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
					{
						titan2Array.erase(titan2Iter);
						break;
					}
					minionCounter = 0;
					for (minionIter = minionArray.begin();minionIter != minionArray.end();minionIter++) minionArray[minionCounter].isDead = true;

					bossPhase = STILL;
					if (player.body.getGlobalBounds().intersects(skull.getGlobalBounds()))
					{
						winBox.draw(window);
						win.update(mousePos);
						win.draw(window);
						if (Keyboard::isKeyPressed(Keyboard::Return))
						{
							if (!playEndMusic)
							{
								endMusic.play();
								playEndMusic = true;
							}
							window.clear();
							state = CREDIT;
							isScrolled = true;
						}
					}
				}

				//draw entities;
				boss.draw(window);
				player.draw(window);

				bossBulletCounter = 0; //boss' bullets hit player;
				for (bossBulletIter = bossBulletArray.begin(); bossBulletIter != bossBulletArray.end();bossBulletIter++)
				{
					if (bossBulletArray[bossBulletCounter].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						player.hurt();
						hurt.play();
						int damage = bossBulletArray[bossBulletCounter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						if (!unlimitedHealthCheat) playerHP -= laser.damage;
						bossBulletArray.erase(bossBulletIter);
						break;
					}
					bossBulletCounter++;
				}
				bossBulletCounter = 0; //draw boss' bullets;
				for (bossBulletIter = bossBulletArray.begin(); bossBulletIter != bossBulletArray.end();bossBulletIter++)
				{
					bossBulletArray[bossBulletCounter].update(deltaTime);
					window.draw(bossBulletArray[bossBulletCounter].body);
					bossBulletCounter++;
				}

				minionCounter = 0; //minion hit;
				for (minionIter = minionArray.begin();minionIter != minionArray.end();minionIter++)
				{
					collider minionCollision = minionArray[minionCounter].getCollider();
					leftScreen.checkCollider(minionCollision, 1.0f);
					rightScreen.checkCollider(minionCollision, 1.0f);

					if (player.body.getGlobalBounds().intersects(minionArray[minionCounter].body.getGlobalBounds()))
					{
						if (elapse[1].asSeconds() >= 0.5f)
						{
							clock[1].restart();
							player.hurt();
							hurt.play();
							int damage = minionArray[minionCounter].damage;
							dmgDp.text.setString("-" + to_string(damage));
							dmgDp.text.setPosition(playerPosition);
							dmgArray.push_back(dmgDp);
							if (!unlimitedHealthCheat) playerHP -= damage;
						}
					}
					minionCounter++;
				}
				minionCounter = 0; //minion	attack;
				for (minionIter = minionArray.begin();minionIter != minionArray.end();minionIter++)
				{
					minionArray[minionCounter].action = generateIntRandom(2, 1);
					if (elapse[3].asSeconds() >= 0.02f)
					{
						clock[3].restart();
						minionArray[minionCounter].updateAggrovated(deltaTime, playerPosition);
					}
					if (minionArray[minionCounter].action >= 2)
					{
						if (elapse[4].asSeconds() >= 0.5f)
						{
							clock[4].restart();
							if (playerPosition.x < minionArray[minionCounter].body.getPosition().x && abs(playerPosition.y - minionArray[minionCounter].body.getPosition().y) <= 40)
							{
								laser.direction = LEFT;
								laser.body.setPosition(minionArray[minionCounter].body.getPosition());
								laserArray.push_back(laser);
								minionArray[minionCounter].direction = LEFT;
							}
							if (playerPosition.x > minionArray[minionCounter].body.getPosition().x && abs(playerPosition.y - minionArray[minionCounter].body.getPosition().y) <= 40)
							{
								laser.direction = RIGHT;
								laser.body.setPosition(minionArray[minionCounter].body.getPosition());
								laserArray.push_back(laser);
								minionArray[minionCounter].direction = RIGHT;
							}
							if (playerPosition.y < minionArray[minionCounter].body.getPosition().y && abs(playerPosition.x - minionArray[minionCounter].body.getPosition().x) <= 40)
							{
								laser.direction = UP;
								laser.body.setPosition(minionArray[minionCounter].body.getPosition());
								laserArray.push_back(laser);
								minionArray[minionCounter].direction = UP;
							}
							if (playerPosition.y > minionArray[minionCounter].body.getPosition().y && abs(playerPosition.x - minionArray[minionCounter].body.getPosition().x) <= 40)
							{
								laser.direction = DOWN;
								laser.body.setPosition(minionArray[minionCounter].body.getPosition());
								laserArray.push_back(laser);
								minionArray[minionCounter].direction = DOWN;
							}
						}
					}
					minionCounter++;
				}
				minionCounter = 0; //minion die;
				for (minionIter = minionArray.begin();minionIter != minionArray.end();minionIter++)
				{
					if (minionArray[minionCounter].isDead)
					{
						if (chance(9) == 0)
						{
							hpp.body.setPosition(minionArray[minionCounter].body.getPosition().x + 25.f, minionArray[minionCounter].body.getPosition().y);
							hppArray.push_back(hpp);
						}
						if (chance(4) == 0)
						{
							mpp.body.setPosition(minionArray[minionCounter].body.getPosition().x - 25.f, minionArray[minionCounter].body.getPosition().y);
							mppArray.push_back(mpp);
						}
						dead.play();
						playerScore += 2000;
						minionArray.erase(minionIter);
						break;
					}
					minionCounter++;
				}
				laserCounter = 0; //laser beam hit player;
				for (laserIter = laserArray.begin(); laserIter != laserArray.end();laserIter++)
				{
					if (laserArray[laserCounter].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
					{
						player.hurt();
						hurt.play();
						int damage = laserArray[laserCounter].damage;
						dmgDp.text.setString("-" + to_string(damage));
						dmgDp.text.setPosition(playerPosition);
						dmgArray.push_back(dmgDp);
						if (!unlimitedHealthCheat) playerHP -= laser.damage;
						laserArray.erase(laserIter);
						break;
					}
					laserCounter++;
				}
				laserCounter = 0; //draw laser beam;
				for (laserIter = laserArray.begin(); laserIter != laserArray.end();laserIter++)
				{
					laserArray[laserCounter].update(deltaTime);
					window.draw(laserArray[laserCounter].body);
					laserCounter++;
				}
				minionCounter = 0; //draw minion;
				for (minionIter = minionArray.begin();minionIter != minionArray.end();minionIter++)
				{
					window.draw(minionArray[minionCounter].body);
					minionCounter++;
				}

				//draw boss hp;
				gui.drawBossHpBar(window);
			}

			//store//
			if (state == STORE)
			{
				//set window events;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed) window.close();

					//get items;
					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && healthPotion.getGlobalBounds().contains(mousePos))
					{
						if (playerMoney >= 60)
						{
							clickState = BOUGHT;
							hpPotion++;
							playerMoney -= 60;
						}
						else clickState = BROKE;
					}
					
					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && manaPotion.getGlobalBounds().contains(mousePos))
					{
						if (playerMoney >= 25)
						{
							clickState = BOUGHT;
							mpPotion++;
							playerMoney -= 25;
						}
						else clickState = BROKE;
					}
					
					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && wandUpgrade.getGlobalBounds().contains(mousePos))
					{
						if (playerMoney >= 200)
						{
							clickState = BOUGHT;
							wandLevel++;
							playerMoney -= 200;
						}
						else clickState = BROKE;
					}
					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && moreMaxHP.getGlobalBounds().contains(mousePos) && maxhp < 12000)
					{
						if (playerMoney >= 500)
						{
							clickState = BOUGHT;
							maxhp += 1000;
							playerMoney -= 500;
						}
						else clickState = BROKE;
					}
					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && moreMaxMP.getGlobalBounds().contains(mousePos) && maxmp < 2000)
					{
						if (playerMoney >= 100)
						{
							clickState = BOUGHT;
							maxmp += 100;
							playerMoney -= 100;
						}
						else clickState = BROKE;
					}

					//return to the game;
					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && done.getGlobalBounds().contains(mousePos)) clickState = BYE;
					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && returnToTheGame.getGlobalBounds().contains(mousePos))
					{
						window.clear();
						player.body.setPosition(Vector2f(900.f, 1140.f));
						player.setAnimationRow(2);
						player.direction = DOWN;
						state = SKY;
					}
				}

				//music;
				if (!playStoreMusic)
				{
					menuMusic.stop();
					introMusic.stop();
					gameMusic.pause();
					bossMusic.stop();
					storeMusic.play();
					playMenuMusic = false;
					playIntroMusic = false;
					playGameMusic = false;
					playBossMusic = false;
					playStoreMusic = true;
				}

				//update GUI;
				gui.updateCoin(deltaTime, windowSize, playerPosition);
				gui.updateWandState(deltaTime, windowSize, playerPosition);

				//update entities;
				seller.updateStill(deltaTime);

				//set view;
				view.setCenter(windowSize / 2.f);

				//clear screen;
				window.clear();
				window.setView(view);

				//draw background;
				store.draw(window);

				//update buttons
				welcomeText.update(mousePos);
				healthPotion.update(mousePos);
				manaPotion.update(mousePos);
				wandUpgrade.update(mousePos);
				moreMaxHP.update(mousePos);
				moreMaxMP.update(mousePos);
				done.update(mousePos);
				thxText.update(mousePos);
				byeText.update(mousePos);
				returnToTheGame.update(mousePos);

				//draw entities;
				seller.draw(window);

				//draw platform;
				storeBox.draw(window);

				//draw buttons
				welcomeText.draw(window);
				healthPotion.draw(window);
				manaPotion.draw(window);
				wandUpgrade.draw(window);
				moreMaxHP.draw(window);
				moreMaxMP.draw(window);
				done.draw(window);

				//draw GUI;
				gui.drawCoin(window);
				gui.drawWandState(window);

				if (clickState == BOUGHT) thxText.draw(window);
				if (clickState == BROKE) cheap.draw(window);
				if (clickState == BYE)
				{
					byeText.draw(window);
					returnToTheGame.draw(window);
				}
			}

			//events//
			if (state == HOME || state == OUTDOOR || state == SKY || state == CASTLE)
			{
				//set window event;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed) window.close();

					//buffs;
					if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num1 && hpPotion != 0)
					{
						drink.play();
						hpPotion--;
						playerHP += 200;
					}
					if (event.type == Event::KeyPressed && event.key.code == Keyboard::Num2 && mpPotion != 0)
					{
						drink.play();
						mpPotion--;
						playerMP += 50;
					}
				}

				//update player's stats
				playerHP += 0.2f * deltaTime;
				if (playerHP <= 0)
				{
					playerHP = 0;
					isPlayerDead = true;
				}
				playerMP += 0.5f * deltaTime;
				if (playerMP <= 0) playerMP = 0;
				if (player.run && !unlimitedEnergyCheat) playerEnergy -= 0.5f;
				if (playerEnergy <= 0) playerEnergy = 0;

				//bullet events;
				if (wandLevel > 0) //player's bullets;
				{
					if (Keyboard::isKeyPressed(Keyboard::Space) && playerMP >= 3.f) //release bullet;
					{
						if (elapse[2].asSeconds() >= atkSpd)
						{
							shoot.play();
							clock[2].restart();
							bullet.body.setPosition(playerPosition);
							bullet.direction = player.direction;
							projectileArray.push_back(bullet);
							if (!unlimitedManaCheat) playerMP -= 3.f;
						}
					}
					if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::Space) && playerMP >= 3.f && playerEnergy >= 1000) //special attack;
					{
						if (elapse[10].asSeconds() >= atkSpd)
						{
							shoot.play();
							clock[10].restart();
							for (int i = -1;i <= 1;i++)
							{
								bullet.direction = player.direction;
								if (bullet.direction == UP || bullet.direction == DOWN) bullet.body.setPosition(playerPosition.x + i * 20, playerPosition.y + 100);
								if (bullet.direction == RIGHT || bullet.direction == LEFT) bullet.body.setPosition(playerPosition.x + 100, playerPosition.y + i * 20);
								projectileArray.push_back(bullet);
							}
							for (int i = -2;i <= 1;i++)
							{
								bullet.direction = player.direction;
								if (bullet.direction == UP || bullet.direction == DOWN) bullet.body.setPosition(playerPosition.x + i * 20 + 10, playerPosition.y + 50);
								if (bullet.direction == RIGHT || bullet.direction == LEFT) bullet.body.setPosition(playerPosition.x + 50, playerPosition.y + i * 20 + 10);
								projectileArray.push_back(bullet);
							}
							for (int i = -2;i <= 2;i++)
							{
								bullet.direction = player.direction;
								if (bullet.direction == UP || bullet.direction == DOWN) bullet.body.setPosition(playerPosition.x + i * 20, playerPosition.y);
								if (bullet.direction == RIGHT || bullet.direction == LEFT) bullet.body.setPosition(playerPosition.x, playerPosition.y + i * 20);
								projectileArray.push_back(bullet);
							}
							for (int i = -2;i <= 1;i++)
							{
								bullet.direction = player.direction;
								if (bullet.direction == UP || bullet.direction == DOWN) bullet.body.setPosition(playerPosition.x + i * 20 + 10, playerPosition.y - 50);
								if (bullet.direction == RIGHT || bullet.direction == LEFT) bullet.body.setPosition(playerPosition.x - 50, playerPosition.y + i * 20 + 10);
								projectileArray.push_back(bullet);
							}
							if (!unlimitedManaCheat) playerMP -= 50.f;
							if (!unlimitedEnergyCheat) playerEnergy -= 1000.f;
						}
					}
					bulletCounter = 0; //hit enemies;
					for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
					{
						if (state == HOME && !collisionCheat) for (int i = 0; i < blockH.size(); i++) if (blockH[i].getGlobalBounds().intersects(projectileArray[bulletCounter].body.getGlobalBounds())) projectileArray[bulletCounter].isCollided = true;
						if (state == OUTDOOR)
						{
							gargoyle1Counter = 0; //gargoyle1 got hit;
							for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(gargoyle1Array[gargoyle1Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 3.f);
									playerEnergy += wandLevel * damage / 2500.f + 250.f * deltaTime;
									dmgDp.text.setString("-" + to_string(damage));
									dmgDp.text.setPosition(gargoyle1Array[gargoyle1Counter].body.getPosition());
									dmgArray.push_back(dmgDp);
									gargoyle1Array[gargoyle1Counter].hp -= damage;
									if (gargoyle1Array[gargoyle1Counter].hp <= 0.f) gargoyle1Array[gargoyle1Counter].isDead = true;
									gargoyle1Array[gargoyle1Counter].isAggroed = true;
								}
								gargoyle1Counter++;
							}

							gargoyle2Counter = 0; //gargoyle1 got hit;
							for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(gargoyle2Array[gargoyle2Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 4.f);
									playerEnergy += wandLevel * damage / 2500.f + 250.f * deltaTime;
									dmgDp.text.setString("-" + to_string(damage));
									dmgDp.text.setPosition(gargoyle2Array[gargoyle2Counter].body.getPosition());
									dmgArray.push_back(dmgDp);
									gargoyle2Array[gargoyle2Counter].hp -= damage;
									if (gargoyle2Array[gargoyle2Counter].hp <= 0.f) gargoyle2Array[gargoyle2Counter].isDead = true;
									gargoyle2Array[gargoyle2Counter].isAggroed = true;
								}
								gargoyle2Counter++;
							}
						}
						if (state == SKY)
						{
							titan1Counter = 0; //titan1 got hit;
							for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(titan1Array[titan1Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 5.f);
									playerEnergy += wandLevel * damage / 2500.f + 250.f * deltaTime;
									dmgDp.text.setString("-" + to_string(damage));
									dmgDp.text.setPosition(titan1Array[titan1Counter].body.getPosition());
									dmgArray.push_back(dmgDp);
									titan1Array[titan1Counter].hp -= damage;
									if (titan1Array[titan1Counter].hp <= 0.f) titan1Array[titan1Counter].isDead = true;
									titan1Array[titan1Counter].isAggroed = true;
								}
								titan1Counter++;
							}

							titan2Counter = 0; //titan2 got hit;
							for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(titan2Array[titan2Counter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 6.f);
									playerEnergy += wandLevel * damage / 2500.f + 250.f * deltaTime;
									dmgDp.text.setString("-" + to_string(damage));
									dmgDp.text.setPosition(titan2Array[titan2Counter].body.getPosition());
									dmgArray.push_back(dmgDp);
									titan2Array[titan2Counter].hp -= damage;
									if (titan2Array[titan2Counter].hp <= 0.f) titan2Array[titan2Counter].isDead = true;
									titan2Array[titan2Counter].isAggroed = true;
								}
								titan2Counter++;
							}
						}
						if (state == CASTLE)
						{
							minionCounter = 0; //minion got hit;
							for (minionIter = minionArray.begin();minionIter != minionArray.end();minionIter++)
							{
								if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(minionArray[minionCounter].body.getGlobalBounds()))
								{
									projectileArray[bulletCounter].isCollided = true;
									int damage = projectileArray[bulletCounter].damage * (wandLevel / 7.f);
									playerEnergy += wandLevel * damage / 2500.f + 250.f * deltaTime;
									dmgDp.text.setPosition(minionArray[minionCounter].body.getPosition());
									dmgArray.push_back(dmgDp);
									minionArray[minionCounter].hp -= damage;
									if (minionArray[minionCounter].hp <= 0.f) minionArray[minionCounter].isDead = true;
								}
								minionCounter++;
							}

							if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(boss.body.getGlobalBounds()) && !boss.isDead)
							{
								projectileArray[bulletCounter].isCollided = true;
								int damage = projectileArray[bulletCounter].damage * (wandLevel / 10.f);
								playerEnergy += wandLevel * damage / 2500.f + 250.f * deltaTime;
								dmgDp.text.setString("-" + to_string(damage));
								dmgDp.text.setPosition(boss.body.getPosition().x + 150.f, boss.body.getPosition().y - 300.f);
								dmgArray.push_back(dmgDp);
								boss.hp -= damage;
								if (boss.hp <= 0.f)
								{
									boss.hp = 0;
									boss.isDead = true;
									playerScore += 100000;
								}
								if (boss.hp >= 199400) bossPhase = AGGROVATED;
							}
						}
						if (projectileArray[bulletCounter].isCollided) //delete bullets;
						{
							projectileArray.erase(bulletIter);
							break;
						}
						bulletCounter++;
					}
					bulletCounter = 0; //draw bullets;
					for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
					{
						projectileArray[bulletCounter].update(deltaTime);
						window.draw(projectileArray[bulletCounter].body);
						bulletCounter++;
					}
				}

				//items events;
				coinCounter = 0; //coins pick up;
				for (coinIter = coinArray.begin(); coinIter != coinArray.end();coinIter++)
				{
					if (player.body.getGlobalBounds().intersects(coinArray[coinCounter].body.getGlobalBounds())) coinArray[coinCounter].isPickedUp = true;
					if (coinArray[coinCounter].isPickedUp)
					{
						getcoin.play();
						playerMoney += entityValue;
						moneyDp.text.setString("+$" + to_string(entityValue));
						moneyDp.text.setPosition(coinArray[coinCounter].body.getPosition());
						moneyArray.push_back(moneyDp);
						coinArray[coinCounter].destroy = true;
					}
					if (coinArray[coinCounter].destroy)
					{
						coinArray.erase(coinIter);
						break;
					}
					coinCounter++;
				}
				hppCounter = 0; //hp potions pick up;
				for (hppIter = hppArray.begin(); hppIter != hppArray.end();hppIter++)
				{
					if (player.body.getGlobalBounds().intersects(hppArray[hppCounter].body.getGlobalBounds())) hppArray[hppCounter].isPickedUp = true;
					if (hppArray[hppCounter].isPickedUp)
					{
						hpPotion++;
						hppDp.text.setString("+1 HEALTH POTION");
						hppDp.text.setPosition(hppArray[hppCounter].body.getPosition());
						hppPickUpArray.push_back(hppDp);
						hppArray[hppCounter].destroy = true;
					}
					if (hppArray[hppCounter].destroy)
					{
						hppArray.erase(hppIter);
						break;
					}
					hppCounter++;
				}
				mppCounter = 0; //mp potions pick up;
				for (mppIter = mppArray.begin(); mppIter != mppArray.end();mppIter++)
				{
					if (player.body.getGlobalBounds().intersects(mppArray[mppCounter].body.getGlobalBounds())) mppArray[mppCounter].isPickedUp = true;
					if (mppArray[mppCounter].isPickedUp)
					{
						mpPotion++;
						mppDp.text.setString("+1 MANA POTION");
						mppDp.text.setPosition(mppArray[mppCounter].body.getPosition());
						mppPickUpArray.push_back(mppDp);
						mppArray[mppCounter].destroy = true;
					}
					if (mppArray[mppCounter].destroy)
					{
						mppArray.erase(mppIter);
						break;
					}
					mppCounter++;
				}
				keyCounter = 0; //keys pick up;
				for (keyIter = keyArray.begin(); keyIter != keyArray.end();keyIter++)
				{
					if (player.body.getGlobalBounds().intersects(keyArray[keyCounter].body.getGlobalBounds())) keyArray[keyCounter].isPickedUp = true;
					if (keyArray[keyCounter].isPickedUp)
					{
						key++;
						keyDp.text.setString("+1 KEY");
						keyDp.text.setPosition(keyArray[keyCounter].body.getPosition());
						keyPickUpArray.push_back(keyDp);
						keyArray[keyCounter].destroy = true;
					}
					if (keyArray[keyCounter].destroy)
					{
						keyArray.erase(keyIter);
						break;
					}
					keyCounter++;
				}

				//display stats update;
				moneyCounter = 0;
				for (moneyIter = moneyArray.begin();moneyIter != moneyArray.end();moneyIter++)
				{
					moneyArray[moneyCounter].update(deltaTime);
					window.draw(moneyArray[moneyCounter].text);
					if (moneyArray[moneyCounter].destroy)
					{
						moneyArray.erase(moneyIter);
						break;
					}
					moneyCounter++;
				}
				hppPickUpCounter = 0;
				for (hppPickUpIter = hppPickUpArray.begin();hppPickUpIter != hppPickUpArray.end();hppPickUpIter++)
				{
					hppPickUpArray[hppPickUpCounter].update(deltaTime);
					window.draw(hppPickUpArray[hppPickUpCounter].text);
					if (hppPickUpArray[hppPickUpCounter].destroy)
					{
						hppPickUpArray.erase(hppPickUpIter);
						break;
					}
					hppPickUpCounter++;
				}
				mppPickUpCounter = 0;
				for (mppPickUpIter = mppPickUpArray.begin();mppPickUpIter != mppPickUpArray.end();mppPickUpIter++)
				{
					mppPickUpArray[mppPickUpCounter].update(deltaTime);
					window.draw(mppPickUpArray[mppPickUpCounter].text);
					if (mppPickUpArray[mppPickUpCounter].destroy)
					{
						mppPickUpArray.erase(mppPickUpIter);
						break;
					}
					mppPickUpCounter++;
				}
				keyPickUpCounter = 0;
				for (keyPickUpIter = keyPickUpArray.begin();keyPickUpIter != keyPickUpArray.end();keyPickUpIter++)
				{
					keyPickUpArray[keyPickUpCounter].update(deltaTime);
					window.draw(keyPickUpArray[keyPickUpCounter].text);
					if (keyPickUpArray[keyPickUpCounter].destroy)
					{
						keyPickUpArray.erase(keyPickUpIter);
						break;
					}
					keyPickUpCounter++;
				}
				dmgCounter = 0;
				for (dmgIter = dmgArray.begin();dmgIter != dmgArray.end();dmgIter++)
				{
					dmgArray[dmgCounter].update(deltaTime);
					window.draw(dmgArray[dmgCounter].text);
					if (dmgArray[dmgCounter].destroy)
					{
						dmgArray.erase(dmgIter);
						break;
					}
					dmgCounter++;
				}

				//draw GUI;
				gui.drawStatus(window);
				gui.drawCoin(window);
				gui.drawWandState(window);

				//cheats;
				if (Keyboard::isKeyPressed(Keyboard::Num1) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					collisionCheat = true;
					cout << "collision cheat activated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num1) && Keyboard::isKeyPressed(Keyboard::End))
				{
					collisionCheat = false;
					cout << "collision cheat deactivated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num2) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					gravityCheat = true;
					cout << "flying cheat activated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num2) && Keyboard::isKeyPressed(Keyboard::End))
				{
					gravityCheat = false;
					cout << "flying cheat cheat deactivated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num3) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					unlimitedHealthCheat = true;
					cout << "invincible mode activated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num3) && Keyboard::isKeyPressed(Keyboard::End))
				{
					unlimitedHealthCheat = false;
					cout << "invincible mode deactivated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num4) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					unlimitedManaCheat = true;
					cout << "gatling mode activated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num4) && Keyboard::isKeyPressed(Keyboard::End))
				{
					unlimitedManaCheat = false;
					cout << "gatling mode deactivated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num5) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					unlimitedEnergyCheat = true;
					cout << "fit mode activated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num5) && Keyboard::isKeyPressed(Keyboard::End))
				{
					unlimitedEnergyCheat = false;
					cout << "fit mode deactivated!" << endl;
				}
				if (Keyboard::isKeyPressed(Keyboard::Num6) && Keyboard::isKeyPressed(Keyboard::Home))
				{
					wandLevel = 60;
					cout << "fit mode deactivated!" << endl;
				}

				if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::K)) key = 5;
				if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::K)) key = 0;

				if (Keyboard::isKeyPressed(Keyboard::R) && Keyboard::isKeyPressed(Keyboard::I) && Keyboard::isKeyPressed(Keyboard::P))
				{
					cout << "ur dead" << endl;
					isPlayerDead = true;
				}

				if (isPlayerDead)
				{
					window.clear();
					isRestarted = true;
					state = GAME_OVER;
				}
			}

			//pause//
			if (Keyboard::isKeyPressed(Keyboard::Escape)) isPause = true;
		}

		//pause menu//
		if (isPause)
		{
			//set window event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && resume.getGlobalBounds().contains(mousePos)) isPause = false;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && toMenu.getGlobalBounds().contains(mousePos))
				{
					isPause = false;
					isRestarted = true;
					window.clear();
					state = MENU;
				}
			}

			//music;
			menuMusic.pause();
			introMusic.pause();
			gameMusic.pause();
			bossMusic.pause();
			storeMusic.pause();
			playMenuMusic = false;
			playIntroMusic = false;
			playGameMusic = false;
			playBossMusic = false;
			playStoreMusic = false;

			//update buttons;
			resume.update(mousePos);
			toMenu.update(mousePos);

			//set view;
			view.setCenter(windowSize / 2.f);
			window.clear();
			window.setView(view);

			//draw buttons;
			resume.draw(window);
			toMenu.draw(window);
		}

		//restart;
		if (isRestarted)
		{
			isRestarted = false;
			
			if (!collectHS) 
			{
				highScore.erase(highScore.begin(), highScore.end());
				file = fopen("resources/leaderboard.txt", "r");
				for (int i = 0;i < 5;i++) 
				{
					fscanf(file, "%s", temp);
					nameArr[i] = temp;
					fscanf(file, "%d", &scoreArr[i]);
					highScore.push_back(make_pair(scoreArr[i], nameArr[i]));
				}
				if (name == "") name = "(noname)";
				highScore.push_back(make_pair(playerScore, name));
				sort(highScore.begin(), highScore.end());
				fclose(file);

				file = fopen("resources/leaderboard.txt", "w");
				char temp[26];
				for (int i = 5;i >= 1;i--) 
				{
					strcpy(temp, highScore[i].second.c_str());
					fprintf(file, "%s %d\n", temp, highScore[i].first);
				}
				fclose(file);
				collectHS = true;
			}

			//items
			coinArray.clear();
			hppArray.clear();
			mppArray.clear();
			keyArray.clear();
			projectileArray.clear();
			gargoyle1BulletArray.clear();
			gargoyle2BulletArray.clear();
			titan2BulletArray.clear();
			laserArray.clear();

			//enemies;
			boss.isDead = false;
			boss.hp = 200000;
			normalGargoyle.isSpawned[0] = true;
			advancedGargoyle.isSpawned[0] = true;
			normalTitan.isSpawned[0] = true;
			advancedTitan.isSpawned[0] = true;
			minion.isSpawned[0] = true;
			minion.isSpawned[1] = true;
			minion.isSpawned[2] = true;
			minion.isSpawned[3] = true;
			minion.isSpawned[4] = true;
			minion.isSpawned[5] = true;
			minion.isSpawned[6] = true;
			minion.isSpawned[7] = true;
			minion.isSpawned[8] = true;
			minion.isSpawned[9] = true;
			minion.isSpawned[10] = true;
			minion.isSpawned[11] = true;
			minion.isSpawned[12] = true;
			minion.isSpawned[13] = true;
			minion.isSpawned[14] = true;
			gargoyle1Counter = 0;
			for (gargoyle1Iter = gargoyle1Array.begin();gargoyle1Iter != gargoyle1Array.end();gargoyle1Iter++) gargoyle1Array[gargoyle1Counter].isAggroed = false;
			gargoyle2Counter = 0;
			for (gargoyle2Iter = gargoyle2Array.begin();gargoyle2Iter != gargoyle2Array.end();gargoyle2Iter++) gargoyle2Array[gargoyle2Counter].isAggroed = false;
			titan1Counter = 0;
			for (titan1Iter = titan1Array.begin();titan1Iter != titan1Array.end();titan1Iter++) titan1Array[titan1Counter].isAggroed = false;
			titan2Counter = 0;
			for (titan2Iter = titan2Array.begin();titan2Iter != titan2Array.end();titan2Iter++) titan2Array[titan2Counter].isAggroed = false;
			minionCounter = 0;
			for (minionIter = minionArray.begin();minionIter != minionArray.end();minionIter++) minionArray[minionCounter].isAggroed = false;

			//player stats;
			isPlayerDead = false;
			wandLevel = 0;
			playerScore = 0;
			playerMoney = 0;
			playerHP = maxHP;
			playerMP = maxMP;
			playerEnergy = maxEnergy;
			hpPotion = 0;
			mpPotion = 0;
			key = 0;

			//credits;
			isScrolled = false;

			//input;
			input.setSelected(true);
			input.clear();

			//intro;
			page = 1;
		}

		//game over//
		if (state == GAME_OVER)
		{
			//music;
			if (!playYouDie)
			{
				menuMusic.stop();
				introMusic.stop();
				gameMusic.stop();
				bossMusic.stop();
				storeMusic.stop();
				die.play();
				playMenuMusic = false;
				playIntroMusic = false;
				playGameMusic = false;
				playBossMusic = false;
				playStoreMusic = false;
				playYouDie = true;
			}
			
			//set window event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();

				//see score;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && scoreState.getGlobalBounds().contains(mousePos))
				{
					window.clear();
					state = SCORE;
				}

				//return to menu;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && returnToMenu.getGlobalBounds().contains(mousePos))
				{
					isRestarted = true;
					window.clear();
					state = MENU;
				}
			}

			//set view;
			view.setCenter(windowSize / 2.f);

			//clear screen;
			window.clear();
			window.setView(view);

			//update buttons;
			gameOver.update(mousePos);
			scoreState.update(mousePos);
			returnToMenu.update(mousePos);

			//draw buttons;
			gameOver.draw(window);
			scoreState.draw(window);
			returnToMenu.draw(window);
		}

		//leaderboard;
		if (state == SCORE)
		{
			//set window event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && toMenu.getGlobalBounds().contains(mousePos))
				{ 
					window.clear();
					state = MENU;
				}
			}

			Tomenu.update(mousePos);

			highScore.erase(highScore.begin(), highScore.end());
			file = fopen("resources/leaderboard.txt", "r");
			for (int i = 0;i < 5;i++)
			{
				fscanf(file, "%s", temp);
				nameArr[i] = temp;
				fscanf(file, "%d", &scoreArr[i]);
				highScore.push_back(make_pair(scoreArr[i], nameArr[i]));
			}
			sort(highScore.begin(), highScore.end());
			fclose(file);

			window.clear();
			background.draw(window);
			board.draw(window);
			title.draw(window);
			Tomenu.draw(window);
			showText(Vector2f(windowSize.x / 2.f + 250.0f, 5.f * windowSize.y / 14.f), to_string(highScore[4].first), &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f - 400.0f, 5.f * windowSize.y / 14.f), highScore[4].second, &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f + 250.0f, 6.f * windowSize.y / 14.f), to_string(highScore[3].first), &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f - 400.0f, 6.f * windowSize.y / 14.f), highScore[3].second, &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f + 250.0f, 7.f * windowSize.y / 14.f), to_string(highScore[2].first), &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f - 400.0f, 7.f * windowSize.y / 14.f), highScore[2].second, &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f + 250.0f, 8.f * windowSize.y / 14.f), to_string(highScore[1].first), &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f - 400.0f, 8.f * windowSize.y / 14.f), highScore[1].second, &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f + 250.0f, 9.f * windowSize.y / 14.f), to_string(highScore[0].first), &font, 30, window);
			showText(Vector2f(windowSize.x / 2.f - 400.0f, 9.f * windowSize.y / 14.f), highScore[0].second, &font, 30, window);
		}

		//tutorial//
		if (state == TUTORIAL)
		{
			//set window event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();

				//to menu;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && Tomenu.getGlobalBounds().contains(mousePos))
				{
					isRestarted = true;
					player.setAnimationRow(2);
					window.clear();
					state = MENU;
				}
			}

			//update;
			Tomenu.update(mousePos);
			player.updateTutorial1(deltaTime);
			wandedJack.updateTutorial2(deltaTime);
			player.body.setPosition(windowSize.x / 2.f - 490.f, windowSize.y / 2.f - 110.f);
			wandedJack.body.setPosition(windowSize.x / 2.f + 35.f, windowSize.y / 2.f - 230.f);

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				bullet.body.setPosition(wandedJack.body.getPosition());
				if (elapse[9].asSeconds() >= 0.5f)
				{
					clock[9].restart();
					projectileArray.push_back(bullet);
				}
			}

			bulletCounter = 0;
			for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
			{
				if (projectileArray[bulletCounter].body.getGlobalBounds().intersects(blockade.getGlobalBounds())) projectileArray[bulletCounter].isCollided = true;
				bulletCounter++;
			}

			bulletCounter = 0;
			for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
			{
				if (projectileArray[bulletCounter].isCollided)
				{
					projectileArray.erase(bulletIter);
					break;
				}
				bulletCounter++;
			}

			//set view;
			view.setCenter(windowSize / 2.f);

			//clear screen;
			window.clear();
			window.setView(view);

			bulletCounter = 0;
			for (bulletIter = projectileArray.begin(); bulletIter != projectileArray.end();bulletIter++)
			{
				projectileArray[bulletCounter].direction = RIGHT;
				projectileArray[bulletCounter].update(deltaTime);
				window.draw(projectileArray[bulletCounter].body);
				bulletCounter++;
			}

			//draw;
			background.draw(window);
			Tutorial.draw(window);
			Tomenu.draw(window);
			player.draw(window);
			wandedJack.draw(window);
		}

		//credit//
		if (state == CREDIT)
		{
			//set window event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) window.close();

				//to menu;
				if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && Tomenu.getGlobalBounds().contains(mousePos))
				{
					window.clear();
					state = MENU;
					isRestarted = true;
				}
			}

			//update;
			if (isScrolled)
			{
				if (speech.body.getPosition().y > windowSize.y / 2.f) speech.body.move(0.f, -100.f * deltaTime);
				else isScrolled = false;
			}

			Tomenu.update(mousePos);

			//set view;
			view.setCenter(windowSize / 2.f);

			//clear screen;
			window.clear();
			window.setView(view);

			//draw;
			background.draw(window);
			speech.draw(window);
			Tomenu.draw(window);
		}

		//display window//
		window.display();
	}
	return 0;
}

//resizable view;
void resizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(viewHeight * aspectRatio, viewHeight);
}

//show texts;
void showText(Vector2f position, string word, Font* font, int size, RenderWindow& window)
{
	sf::Text text;
	text.setFont(*font);
	text.setPosition(position);
	text.setString(word);
	text.setCharacterSize(size);
	text.setOutlineColor(Color::White);
	window.draw(text);
}