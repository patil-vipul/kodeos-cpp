#ifndef __KODEOS__TMVGA_H
#define __KODEOS__TMVGA_H

#include <common/types.h>
#include <stdfun.h>

using namespace standard;
using namespace kodeos::common;

static uint8_t SC_COLOR = 0xF0;
static uint8_t AC_COLOR = 0xF0;

namespace GUI
{

class Button;
class Icon;
class TextApp;

static Button *buttons[128];
static Icon *icons[64];
static Icon *selection;
static int nb=0,ni=0,ISSELECT=0,SELVIEW=0;
static bool AppLoaded = false;


void SET_SC(kodeos::common::uint8_t);
void SET_AC(kodeos::common::uint8_t);
kodeos::common::uint8_t GET_SC();
kodeos::common::uint8_t GET_AC();
int GET_SIndex();
int GET_SELVIEW();
void SET_SELVIEW(int);

void clickedOn(int,int);
void changeSelection(kodeos::common::uint8_t);
void enterSelection();
void endApplication();
void RedrawIcons();
bool getAppLoaded();

class TextApp{
	public:
		virtual void Start();
};

class Box{
private:
	int XPOS, YPOS, OBJ_WIDTH, OBJ_HEIGHT, LEN;
	bool BOLD;
	kodeos::common::String LABEL;

public:
	Box(kodeos::common::String, int, int, int, int);
	Box(kodeos::common::String, int, int, int, int ,bool);
	virtual void draw();
};

class ActionListener{
	public:
	virtual void actionPerformed(kodeos::common::String);
};

class Button {
private:
	int XPOS, YPOS, OBJ_WIDTH, OBJ_HEIGHT, LEN;
	kodeos::common::String LABEL;

public:
	kodeos::common::String ID;
	ActionListener *al;
	Button(kodeos::common::String,kodeos::common::String, int, int, int, int);
	virtual void draw();
	int getXPOS();
	int getYPOS();
	int getXDimension();
	int getYDimension();
	kodeos::common::String getLabel();
	void addMouseListener(ActionListener*);
};

class Desktop
{
public:
	Desktop(char[]);

	template <typename Component>
	void addComponent(Component component){
		component.draw();
	}

};

class Frame{
	public:
	Frame(char[]);
};

class Icon{
	private:
	int XPOS, YPOS;
	kodeos::common::String LABEL;
	public:
		TextApp *app;
		Icon(kodeos::common::String,int,int);
		void select();
		void deselect();
		void drawIcon();
		void bindApplication(TextApp*);
};

void fillBlock(int, int);
void screen_init();

} // namespace GUI

#endif