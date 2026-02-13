#include <iostream>
#include <raylib.h>


int Player_score = 0;
int CPU_score = 0;

	class Ball {
	public:
		float x, y;
		int radius;
		int speed_x, speed_y;


		void Draw() {
			//Ball
			DrawCircle(x, y, radius, WHITE);
		};

		
		void Update_Ball() {
			x += speed_x;
			y += speed_y;

			if (y + radius >= GetScreenHeight() || y - radius <= 0) {
				speed_y *= -1;
			}
			if (x + radius >= GetScreenWidth()) {
				CPU_score++;
				ResetBall();
			}
				
			if(x - radius <= 0){
				Player_score++;
				ResetBall();
			}
		}

		void ResetBall() {
			x = GetScreenWidth() / 2;
			y = GetScreenHeight() / 2;

			int speed_choices[2] = { -1, 1 };
			speed_x *= speed_choices[GetRandomValue(0, 1)];
			speed_y *= speed_choices[GetRandomValue(0, 1)];

		}
	};

	class Paddle {
	protected:
		void LimitedMov() {
			if (y <= 0) {
				y = 0;
			}
			if (y + height >= GetScreenHeight()) {
				y = GetScreenHeight() - height;
			}
		}
	public:
		float x, y;
		float width, height;
		int speed_y;

		void Draw() {
			DrawRectangle(x, y, width, height, WHITE);
		}

		void UpdatePaddle() {
			if (IsKeyDown(KEY_UP)) {
				y = y - speed_y;
			}
			if (IsKeyDown(KEY_DOWN)) {
				y = y + speed_y;
			}
			LimitedMov();
		}
	};

	class PC_Paddle : public Paddle {
	public:
		void Update(int ball_y) {
			if (y + height / 2 > ball_y) {
				y = y - speed_y;
			}
			if (y + height / 2 <= ball_y) {
				y = y + speed_y;
			}
			LimitedMov();
		}
	};

//Create obj
Ball ball;
Paddle Paddle_1;
PC_Paddle Paddle_2;


int main() {
	std::cout << "Starting the Ping Pong Game";
	const int Win_Height = 800;
	const int Win_Width = 1280;
	SetTargetFPS(60); 
	InitWindow(Win_Width, Win_Height, "Ping Pong Game");

	ball.x = Win_Width / 2;
	ball.y = Win_Height / 2;
	ball.radius = 25;
	ball.speed_x = 7;
	ball.speed_y = 7;

	Paddle_1.x = 10;
	Paddle_1.y = Win_Height / 4;
	Paddle_1.width = 25;
	Paddle_1.height = 120; 
	Paddle_1.speed_y = 6;

	Paddle_2.x = 1245;
	Paddle_2.y = Win_Height / 4;
	Paddle_2.width = 25;
	Paddle_2.height = 120;
	Paddle_2.speed_y = 6;


	
	while (WindowShouldClose() == false) {
		BeginDrawing();	

		ball.Update_Ball();
		Paddle_1.UpdatePaddle();
		Paddle_2.Update(ball.y);


		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ Paddle_1.x, Paddle_1.y, Paddle_1.width, Paddle_1.height })) {
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ Paddle_2.x, Paddle_2.y, Paddle_2.width, Paddle_2.height })) {
			ball.speed_x *= -1;
		}

		//Clear
		ClearBackground(BLACK);

		//Line
		DrawLine(Win_Width / 2, Win_Height, Win_Width / 2, 0, WHITE);
		ball.Draw();

		//Paddles
		Paddle_1.Draw();	
		Paddle_2.Draw();

		//Draw text
		DrawText(TextFormat("%i", CPU_score), Win_Width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", Player_score), 3 * Win_Width / 4 - 20, 20, 80, WHITE);
		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}