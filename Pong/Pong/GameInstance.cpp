#include "GameInstance.h"

GameInstance::GameInstance(Player* leftPlayer, Player* rightPlayer, Ball* ball)
{
	GameInstance::leftPlayer = leftPlayer;
	GameInstance::rightPlayer = rightPlayer;
	GameInstance::ball = ball;
	srand(static_cast <unsigned> (time(0)));
}

void GameInstance::StartRound()
{
	ball->pos = glm::vec2(gameBoard.width / 2.0f, gameBoard.height / 2.0f);
	ball->currentSpeed = gameBoard.initialBallSpeed;
	
	float r = static_cast <float> (rand()) / static_cast <float>(RAND_MAX);
	
	if(leftScoredLast)
	{
		glm::vec2 newBallDir = glm::vec2(0.2 + 1 * r, 2 * r - 1);
		newBallDir = glm::normalize(newBallDir);
		ball->forceDir = newBallDir;
	}
	else
	{
		glm::vec2 newBallDir = glm::vec2(-0.2 -1 * r, 2 * r - 1);
		newBallDir = glm::normalize(newBallDir);
		ball->forceDir = newBallDir;
	}

	playing = true;
}

void GameInstance::gameStep(float deltaTime)
{
	if(playing)
	{
		ball->pos = ball->pos + ball->forceDir * ball->currentSpeed;

		//ball hits right player
		if (ball->pos.x + ballWidth / 2 > rightPlayer->pos.x - playerWidth / 2 && ball->pos.x + ballWidth < rightPlayer->pos.x + playerWidth / 2)
		{
			if (ball->pos.y + ballHeight / 2 > rightPlayer->pos.y - playerHeight / 2 && ball->pos.y - ballHeight / 2 < rightPlayer->pos.y + playerHeight / 2)
			{
				float deltaY = ball->pos.y - rightPlayer->pos.y;
				glm::vec2 newBallDir = glm::vec2(-1, deltaY / playerHeight);
				newBallDir = glm::normalize(newBallDir);
				ball->forceDir = newBallDir;
				ball->currentSpeed = ball->currentSpeed * gameBoard.ballSpeedIncrease;
			}
		}
		//ball hits left player
		if (ball->pos.x - ballWidth / 2 < leftPlayer->pos.x + playerWidth / 2 && ball->pos.x - ballWidth > leftPlayer->pos.x - playerWidth / 2)
		{
			if (ball->pos.y + ballHeight / 2 > leftPlayer->pos.y - playerHeight / 2 && ball->pos.y - ballHeight / 2 < leftPlayer->pos.y + playerHeight / 2)
			{
				float deltaY = ball->pos.y - leftPlayer->pos.y;
				glm::vec2 newBallDir = glm::vec2(1, deltaY / playerHeight);
				newBallDir = glm::normalize(newBallDir);
				ball->forceDir = newBallDir;
				ball->currentSpeed = ball->currentSpeed * gameBoard.ballSpeedIncrease;
			}
		}

		//ball hits top
		if (ball->pos.y + ballHeight / 2 > gameBoard.height)
		{
			ball->forceDir.y = ball->forceDir.y * -1;
		}
		//ball hits bottom
		if (ball->pos.y - ballHeight / 2 < 0)
		{
			ball->forceDir.y = ball->forceDir.y * -1;
		}
		//ball hits right goal
		if (ball->pos.x + ballWidth / 2 > gameBoard.width)
		{
			scoreLeft++;
			leftScoredLast = true;
			if (autoRestart)
				StartRound();
			else
				playing = false;
		}
		//ball hits left goal
		if (ball->pos.x - ballWidth / 2 < 0)
		{
			scoreRight++;
			leftScoredLast = false;

			if (autoRestart)
				StartRound();
			else
				playing = false;
		}
		
	}

	
	

}