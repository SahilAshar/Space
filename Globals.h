#define menu_screen 0
#define diff_screen 1
#define highscore_screen 2
#define play_screen 3
#define gameOver_screen 4


extern int ADCvalue[2];

extern int screen_num;
extern int menu_num;
extern int playerShip_x;

extern void Delay50ms(int count);
extern void Delay75ms(int count);
extern void Delay100ms(int count);


extern void generateMenu(void);
extern void generateDiffi(void);
extern void generateHS(void);
extern void generatePlay(void);
extern void checkSN(void);

extern int up_down;
extern int left_right;
extern long buttonPress;
extern int frameFlag;
extern int diffi;

extern int testC;
extern int gameReady;

extern void init_All(void);

extern int hori;
extern int verti;

extern int shotFired_flag;
extern int shotFired_ticks;

extern int invaderDeaths;
extern int score;
extern int deathFlag;

extern void startEngine(void);
extern void moveBullet(void);
extern void generateBullet(int x, int y);
