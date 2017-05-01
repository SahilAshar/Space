#define menu_screen 0
#define diff_screen 1
#define highscore_screen 2
#define play_screen 3


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
extern long buttonPress;

extern int testC;

extern void init_All(void);

extern int hori;
extern int verti;

extern void startEngine(void);
