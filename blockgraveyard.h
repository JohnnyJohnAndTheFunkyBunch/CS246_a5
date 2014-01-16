#ifndef BLOCKGRAVEYARD_H
#define BLOCKGRAVEYARD_H


#include <vector>
#include <iostream>

struct BlockGhost{
	int level;         // Level it was born in
	int yBot;          // bottom y-coordinate 
	int yTop;          // top y-coordinate
};


class BlockGraveyard 
{
			std::vector<BlockGhost> lst;
		public:
			BlockGraveyard();
			void addGhost(BlockGhost b);    // Add a block to the vector (blocks that were set)
			int notifyGhosts(int n);        // Notify which line has been cleared, outputs score
			~BlockGraveyard();
			friend std::ostream& operator<< (std::ostream& os,  BlockGraveyard &g);
		private:
};



#endif 
