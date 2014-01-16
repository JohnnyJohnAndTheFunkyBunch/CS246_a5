#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Block;


class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=450, int height=395);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour=Black);
  
 	///////////// My methods//////////////
  
	// implement singleton
	static Xwindow *instance;
	static Xwindow *getInstance();
	static void cleanup();
  
  // Initialize the graphics
  void init();
  void drawLevel();
  void drawScore();
  
  void place(Block &b, int x, int y);       // Draw a block
  void place(int colour, int x, int y);     // Draw a Square
  void unplace(int x, int y);               // Erase a Square
  void unplace(Block &b, int x, int y);     // Erase a Block
  
  void refresh();                           // Refresh when clear rows
  
  void drawNext(Block &b);                  // Draw the Next Block
  void undrawNext(Block &b);                // Erase the Next Block
  
  void drawHold(Block &b);                  // Draw the Hold Block
  void undrawHold(Block &b);                // Erase the Hold Block
  
  void drawDead();                          // Draw dead notification
 private:
 	int getColor(char c);
 	// int to string
  std::string itos(int n);
  
};

#endif
