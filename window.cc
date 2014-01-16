#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"
#include "block.h"
#include "textdisplay.h"
#include "scoreboard.h"
#include "level.h"

using namespace std;

/////////////// Static ////////////////////
//////////// Singleton //////////////

Xwindow *Xwindow::instance = 0;

Xwindow *Xwindow::getInstance() {
	if (!instance) {
		instance = new Xwindow;
		atexit(cleanup);
	}
	return instance;
}

void Xwindow::cleanup() {
	delete instance;
}

/////////////// Stuff I didn't write////////////////////

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 10; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
  XSetForeground(d, gc, colours[Black]);
}

///////////////////// Stuff I wrote ///////////////////////////


//////// Non-Grid Drawing //////////


void Xwindow::init(){
	fillRectangle(5,5,5,385, Xwindow::Black);// border down
	fillRectangle(5,5,260,5, Xwindow::Black);// border up right down
	fillRectangle(260,5,5,385, Xwindow::Black);// border down
	fillRectangle(5,385,260,5, Xwindow::Black);// border up right down
	fillRectangle(295, 30, 125, 75, Xwindow::White); // erase next
	fillRectangle(295, 145, 125, 75, Xwindow::White); // erase Hold
	
	fillRectangle(10,10, 250, 375, Xwindow::White); // erase board
	
	drawString(275, 250, "Level");
	drawString(275, 300, "Score");
	drawString(275, 350, "Hi Score");
	drawString(347, 20, "Next");
	drawString(347, 125, "Hold");
}


void Xwindow::drawLevel() {
	fillRectangle(270, 260, 50, 25, Xwindow::White); // eraser
	drawString(275, 275, itos(Level::getLevel()));
}

void Xwindow::drawScore() {
	ScoreBoard *s = ScoreBoard::getInstance();
	fillRectangle(270, 310, 50, 25, Xwindow::White);
	fillRectangle(270, 360, 50, 25, Xwindow::White);
	drawString(275, 325, itos(s->getScore()));
	drawString(275, 375, itos(s->getHighscore()));
}

//////////// Grid Drawings ////////////

void Xwindow::place(Block &b, int x, int y) {
	Point *p = b.getBody();
	char c = b.getChar();
	int color = getColor(c);	
	for(int i = 0 ; i < 4 ; i++) {
		place(color, p[i].x + x, p[i].y + y);
	}
	if (b.getSkip()) {
		for(int i = 0 ; i < 4 ; i++) {
			if ((p[i].x + x) < 10 && (p[i].y + y)< 15) {
				fillRectangle((p[i].x + x) * 25 + 10 + 7, 367 - (p[i].y + y) * 25 + 1, 10, 10, Xwindow::White);
			}
		}
	}
}

void Xwindow::place(int colour, int x, int y) {
	if (x < 10 && y < 15) {
		fillRectangle(x * 25 + 10 + 1, 360 - y * 25 + 1, 23, 23, colour);
	}
}

void Xwindow::refresh(){
	TextDisplay *t = TextDisplay::getInstance();
	for(int i = 0 ; i < 15 ; i++) {
		for(int j = 0 ; j < 10 ; j++) {
			place(getColor(t->grid[i][j]), j, i);
			if(t->grid[i][j] >= 'a' && t->grid[i][j] <= 'z') { // if skippable
				fillRectangle(j * 25 + 10 + 7, 367 - i * 25 + 1, 10, 10, Xwindow::White);
			}
		}
	}
}


void Xwindow::unplace(int x, int y) {
	if (x < 10 && y < 15) {
		fillRectangle(x * 25 + 10, 360 - y * 25, 25, 25, Xwindow::White);
	}
}

void Xwindow::unplace(Block &b, int x, int y) {
	Point *p = b.getBody();
	for(int i = 0 ; i < 4 ; i++) {
		unplace(p[i].x + x, p[i].y + y);
	}
}


	
//////////// Next Drawings/ //////

void Xwindow::drawNext(Block &b) {
	Point *p = b.getBody();
	char c = b.getChar();
	int color = getColor(c);
	if (c == 'I') {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle( p[i].x * 25 + 310, 340 - (11 + p[i].y) * 25 , 23, 23, color);
		}
		// if skip
		if (b.getSkip()) {
			for(int i = 0 ; i < 4 ; i++) {
				fillRectangle( p[i].x * 25 + 316, 347 - (11 + p[i].y) * 25 , 10, 10, Xwindow::White);
			}
		}
	}
	else if (c == 'O') {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle( p[i].x * 25 + 335, 340 - (11 + p[i].y) * 25 , 23, 23, color);
		}
		if (b.getSkip()) {
			for(int i = 0 ; i < 4 ; i++) {
				fillRectangle( p[i].x * 25 + 341, 347 - (11 + p[i].y) * 25 , 23, 23, color);
			}
		}
	}
	else {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle((13 + p[i].x) * 25 , 340 - (11 + p[i].y) * 25 , 23, 23, color);
		}
		if (b.getSkip()) {
			for(int i = 0 ; i < 4 ; i++) {
				fillRectangle((13 + p[i].x) * 25 + 6 , 347 - (11 + p[i].y) * 25 , 10, 10, Xwindow::White);
			}
		}
	}
}

void Xwindow::undrawNext(Block &b) {
	Point *p = b.getBody();
	char c = b.getChar();
	if (c == 'I') {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle( p[i].x * 25 + 310, 340 - (11 + p[i].y) * 25 , 23, 23, Xwindow::White);
		}
	}
	else if (c == 'O') {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle( p[i].x * 25 + 335, 340 - (11 + p[i].y) * 25 , 23, 23, Xwindow::White);
		}
	}
	else {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle((13 + p[i].x) * 25 , 340 - (11 + p[i].y) * 25 , 23, 23, Xwindow::White);
		}
	}
}

//////////// Hold Drawing //////////////

void Xwindow::drawHold(Block &b) {
	Point *p = b.getBody();
	char c = b.getChar();
	int color = getColor(c);
	if (c == 'I') {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle( p[i].x * 25 + 310, 450 - (11 + p[i].y) * 25 , 23, 23, color);
		}
		if (b.getSkip()) {
			for(int i = 0 ; i < 4 ; i++) {
				fillRectangle( p[i].x * 25 + 316, 457 - (11 + p[i].y) * 25 , 10, 10, Xwindow::White);
			}
		}
	}
	else if (c == 'O') {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle( p[i].x * 25 + 335, 450 - (11 + p[i].y) * 25 , 23, 23, color);
		}
		if (b.getSkip()) {
			for(int i = 0 ; i < 4 ; i++) {
				fillRectangle( p[i].x * 25 + 341, 457 - (11 + p[i].y) * 25 , 10, 10, Xwindow::White);
			}
		}
	}
	else {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle((13 + p[i].x) * 25 , 450 - (11 + p[i].y) * 25 , 23, 23, color);
		}
		if (b.getSkip()) {
			for(int i = 0 ; i < 4 ; i++) {
				fillRectangle((13 + p[i].x) * 25 + 6, 457 - (11 + p[i].y) * 25 , 10, 10, Xwindow::White);
			}
		}
	}
}

void Xwindow::undrawHold(Block &b) {
	Point *p = b.getBody();
	char c = b.getChar();
	if (c == 'I') {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle( p[i].x * 25 + 310, 450 - (11 + p[i].y) * 25 , 23, 23, Xwindow::White);
		}
	}
	else if (c == 'O') {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle( p[i].x * 25 + 335, 450 - (11 + p[i].y) * 25 , 23, 23, Xwindow::White);
		}
	}
	else {
		for(int i = 0 ; i < 4 ; i++) {
			fillRectangle((13 + p[i].x) * 25 , 450 - (11 + p[i].y) * 25 , 23, 23, Xwindow::White);
		}
	}
}

/////////// You LOST drawing //////

void Xwindow::drawDead() {
	fillRectangle(50, 120, 160, 80, Xwindow::Black);
	drawString(115, 160, "DEAD", Xwindow::White);
}

////////////////////////// Private //////////////


int Xwindow::getColor(char c) {
		switch(c) {
		case ' ':
			return Xwindow::White;
			break;
		case 'I': case 'i':
			return Xwindow::Cyan;
			break;
		case 'J': case 'j':
			return Xwindow::Blue;
			break;
		case 'L': case 'l':
			return Xwindow::Orange;
			break;
		case 'S': case 's':
			return Xwindow::Green;
			break;
		case 'Z': case 'z':
			return Xwindow::Red;
			break;
		case 'O': case 'o':
			return Xwindow::Yellow;
			break;
		case 'T': case 't':
			return Xwindow::Magenta;
			break;
		case 'X': case 'x':
			return Xwindow::Brown;
			break;
	}
}



std::string Xwindow::itos(int n) {
	std::string s = "";
	if (n == 0) {
		return "0";
	}
	while(n != 0) {
		char c = n % 10 + 48;
		s = c + s;
		n = n / 10;
	}
	return s;
}
	
	
	
	
	
	
	
	
	
	




