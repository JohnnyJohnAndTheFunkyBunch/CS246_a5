#include "scoreboard.h"
#include <cstdlib>

/////////////// Static ////////////////////

ScoreBoard *ScoreBoard::instance = 0;

ScoreBoard *ScoreBoard::getInstance() {
	if (!instance) {
		instance = new ScoreBoard;
		atexit(cleanup);
	}
	return instance;
}

//////////////// Member ///////////////

ScoreBoard::ScoreBoard() : highscore(0), score(0) {}

int ScoreBoard::getHighscore() const { return highscore; }

int ScoreBoard::getScore() const { return score; }


void ScoreBoard::addScore(int amt) { 
	score += amt;
	if (score >= maxScore) {
		score = maxScore;
	}
	if (score > highscore) {
		highscore = score;
	}
}

void ScoreBoard::resetScore() { score = 0; }

void ScoreBoard::cleanup() {
	
	delete instance;
}
