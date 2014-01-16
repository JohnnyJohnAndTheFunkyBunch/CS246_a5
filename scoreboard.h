#ifndef SCOREBOARD_H
#define SCOREBOARD_H

const int maxScore = 9999;

class ScoreBoard
{
			int highscore;
			int score;
			
    public:
				static ScoreBoard *instance;
				static ScoreBoard *getInstance();
        ScoreBoard();
        
				int getHighscore() const;
				int getScore() const;
				void addScore(int amt);
				void resetScore();        // reset the Score, but keep the High Score
				
				static void cleanup();
    protected:
    private:
};

#endif // SCOREBOARD_H
