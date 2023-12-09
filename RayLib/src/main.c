#include <raylib.h>
#include <raymath.h>

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1200
#define WINDOW_NAME "Raylib Window"
#define FRAMERATE 90
#define PLAYERSPEED 5
#define PADDLEHEIGHT 250
#define PADDLEWIDTH 50
#define BALLHEIGHT 50
#define BALLWIDTH 50

typedef struct {
	float x;
	float y;
	float MoveSpeed;
} Player;


int main(void){
	InitWindow(SCREENWIDTH,SCREENHEIGHT,WINDOW_NAME);
	SetTargetFPS(FRAMERATE);

	Player playerA = {100,100,10.0f};
	Player Enemy = {SCREENWIDTH - 100, SCREENHEIGHT - PADDLEHEIGHT - 100, 5.0f};
	Player Ball = {SCREENWIDTH/2,SCREENHEIGHT/2,5.0f};
	float Xspeed = (float)GetRandomValue(-20,20);
	float Yspeed = (float)GetRandomValue(-20,20);
	bool JustStarted = true;
	bool AfterGame = false;
	while(!WindowShouldClose()){
//=============================Update=======================================//
		while (JustStarted)
		{
			BeginDrawing();
			DrawText("Press Enter To Start",100,100, 100,WHITE);
			if (IsKeyDown(KEY_ENTER)){
				JustStarted = false;
			}
			EndDrawing();
		}

		while (AfterGame)
		{
			BeginDrawing();
			ClearBackground(BLACK);
			DrawText("Press Enter to play Again",100,100, 100,WHITE);
			if (IsKeyDown(KEY_ENTER)){
				Ball.x = SCREENWIDTH/2;
				Ball.y = SCREENHEIGHT/2;
 				AfterGame = false;
			}
			EndDrawing();
		}

		Enemy.y = Enemy.y + Enemy.MoveSpeed;
		Ball.x = Ball.x + Xspeed;
		Ball.y = Ball.y + Yspeed;

		if(Ball.y + BALLHEIGHT > playerA.y && Ball.y < playerA.y + PADDLEHEIGHT){
			if(Ball.x < playerA.x + PADDLEWIDTH){
				Xspeed = GetRandomValue(1,20);
				Yspeed = GetRandomValue(1,20);
			}
		}

		if(Ball.y + BALLHEIGHT > Enemy.y && Ball.y < Enemy.y + PADDLEHEIGHT){
			if(Ball.x + BALLWIDTH > Enemy.x){
				Xspeed = GetRandomValue(-20,-1);
				Yspeed = GetRandomValue(-20,-1);
			}
		}

		if(Ball.x < 0){
			AfterGame = true;
		}
		if(Ball.x + BALLWIDTH > SCREENWIDTH){
			AfterGame = true;
		}

		if(Ball.y < 0){
			Yspeed = GetRandomValue(1,20);
		}
		if(Ball.y + BALLHEIGHT > SCREENHEIGHT){
			Yspeed = GetRandomValue(-20,-1);
		}
		
		if(playerA.y < 0){
			playerA.y = 0;
		}
		if(playerA.y + PADDLEHEIGHT > SCREENHEIGHT){
			playerA.y = SCREENHEIGHT - PADDLEHEIGHT;
		}
		if(Enemy.y < 0){
			Enemy.MoveSpeed = GetRandomValue(5, 15);
		}
		if(Enemy.y + PADDLEHEIGHT > SCREENHEIGHT){
			Enemy.MoveSpeed = GetRandomValue(-15,-5);
		}

		if (IsKeyDown(KEY_DOWN)){
			playerA.y += playerA.MoveSpeed;
		}
		if(IsKeyDown(KEY_UP)){
			playerA.y -= playerA.MoveSpeed;
		}

//------------------------------Draw---------------------------------------//
		BeginDrawing();
		ClearBackground(BLACK);
		//DrawText("Hello World",100,100,25,WHITE);
		
	
		DrawRectangle(playerA.x,playerA.y,PADDLEWIDTH,PADDLEHEIGHT,WHITE);
		DrawRectangle(Enemy.x,Enemy.y,PADDLEWIDTH,PADDLEHEIGHT,WHITE);
		DrawRectangle(Ball.x ,Ball.y,BALLWIDTH,BALLHEIGHT,RED);
		//WaitTime(1);	
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
