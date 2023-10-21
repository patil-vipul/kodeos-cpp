#include <tmvga.h>
#include <stdfun.h>

using namespace standard;
using namespace kodeos::common;
using namespace GUI;


GUI::Box::Box(char ip_lbl[], int w, int h, int x, int y)
{
    XPOS = x;
    YPOS = y;
    OBJ_WIDTH = w;
    OBJ_HEIGHT = h;
    BOLD = false;
    LABEL = ip_lbl;
    LEN = length(LABEL);
   
}

GUI::Box::Box(char ip_lbl[], int w, int h, int x, int y, bool flag)
{
    XPOS = x;
    YPOS = y;
    BOLD = flag;
    OBJ_WIDTH = w;
    OBJ_HEIGHT = h;
    LABEL = ip_lbl;
    LEN = length(LABEL);
   
}

void GUI::clickedOn(int x,int y){
    int i;
    for(i=0;i<nb;i++){
   if(x>= buttons[i]->getXPOS() && x<(buttons[i]->getXPOS() + buttons[i]->getXDimension())){
                        if(y>=buttons[i]->getYPOS() && y<(buttons[i]->getYPOS() + buttons[i]->getYDimension())){
                            buttons[i]->al->actionPerformed(buttons[i]->ID);
                        }
}
    }
}

void GUI::Button::addMouseListener(ActionListener *i_al){
        al = i_al;
		buttons[nb]=this;
		nb++;
	
}

void GUI::Box::draw()
{
    int i, j,POS=0;

    if(BOLD){
        printch(201, XPOS, YPOS);
    for (i = 1; i < OBJ_WIDTH; i++)
    {
        printch(205, XPOS + i, YPOS);
    }
    printch(187, XPOS + i, YPOS);

    for (j = 1; j < OBJ_HEIGHT; j++)
    {
        printch(186, XPOS, YPOS + j);
        printch(186, XPOS + OBJ_WIDTH, YPOS + j);
    }

    printch(200, XPOS, YPOS + j);
    for (i = 1; i < OBJ_WIDTH; i++)
    {
        printch(205, XPOS + i, YPOS + j);
    }
    printch(188, XPOS + i, YPOS + j);

    }else{
        printch(218, XPOS, YPOS);
    for (i = 1; i < OBJ_WIDTH; i++)
    {
        printch(196, XPOS + i, YPOS);
    }
    printch(191, XPOS + i, YPOS);

    for (j = 1; j < OBJ_HEIGHT; j++)
    {
        printch(179, XPOS, YPOS + j);
        printch(179, XPOS + OBJ_WIDTH, YPOS + j);
    }

    printch(192, XPOS, YPOS + j);
    for (i = 1; i < OBJ_WIDTH; i++)
    {
        printch(196, XPOS + i, YPOS + j);
    }
    printch(217, XPOS + i, YPOS + j);
    }

    i = 1;
    if(OBJ_WIDTH>LEN)
        POS = ((OBJ_WIDTH - LEN) / 2);
    else
    {
       POS = 1;
       LABEL[OBJ_WIDTH-3] = '\0';
    }

    printf(LABEL,XPOS + i + POS,YPOS + (OBJ_HEIGHT / 2));    
}

GUI::Desktop::Desktop(char title[70])
{

    int i = 0;
    SET_AC(0x8F);

    while (i < 80)
        fillBlock(i++, 0);
    
    SET_SC(0x8F);
    printf(title, ((80 - length(title)) / 2) , 0);
    SET_SC(0xF0);
}

GUI::Icon::Icon(String ip_label,int x,int y){
    LABEL = ip_label;
    XPOS = x;
    YPOS = y;
    this->drawIcon();
    if(SELVIEW==0)
        SELVIEW=1;
    icons[ni] = this;
    ni++;
}

void GUI::Icon::drawIcon(){
    
    GUI::Box border("",8,7,XPOS,YPOS);
    border.draw();

    printch(177,XPOS+3,YPOS+1);
    printch(177,XPOS+4,YPOS+1);
    printch(177,XPOS+5,YPOS+1);

    printch(179,XPOS+2,YPOS+1);
    printch(179,XPOS+6,YPOS+1);

    printch(192,XPOS+2,YPOS+2);
    printch(196,XPOS+3,YPOS+2);
    printch(194,XPOS+4,YPOS+2);
    printch(196,XPOS+5,YPOS+2);
    printch(217,XPOS+6,YPOS+2);

    printch(196,XPOS+3,YPOS+3);
    printch(193,XPOS+4,YPOS+3);
    printch(196,XPOS+5,YPOS+3);
    
  
    if(length(LABEL)>7){
        String temp;
        for(int i =7;((i<length(LABEL)+1) && (i<13));i++){
            temp[i-7]=LABEL[i];
        }
        LABEL[7]='\0';
        printf(LABEL,XPOS+1,YPOS+4);
        printf(temp,XPOS+1,YPOS+5);
      
    }
    else{
         printf(LABEL,XPOS+2,YPOS+4);
    }

}

void GUI::Icon::select(){
    SET_AC(0xEF);
    for(int i=XPOS+1;i<XPOS+8;i++){
        fillBlock(i,YPOS+6);
    }
    selection = this;
}

void GUI::Icon::deselect(){
    SET_AC(0xF0);
    for(int i=XPOS+1;i<XPOS+8;i++){
        fillBlock(i,YPOS+6);
    }
}

void GUI::Icon::bindApplication(TextApp *t){
    app = t;
}

void GUI::fillBlock(int xoffset, int yoffset)
{
    static uint16_t *VideoMemory = (uint16_t *)0xb8000;
    VideoMemory[80 * yoffset + xoffset] = ' ' | GET_AC() << 8;
}

void GUI::screen_init()
{
    int i, j;
    for (i = 0; i < 25; i++)
        for (j = 0; j < 80; j++)
            fillBlock(j, i);
}

GUI::Button::Button(String ip_lbl, String ip_id, int w, int h, int x, int y)
{
    XPOS = x;
    YPOS = y;
    OBJ_WIDTH = w;
    LABEL = ip_lbl;
    ID = ip_id;
    LEN = length(LABEL);
    OBJ_HEIGHT = h;
}

void GUI::Button::draw()
{
    SET_AC(0xE0);
    SET_SC(0xE0);
    int i, j,POS;

    for (i = 0; i < OBJ_HEIGHT; i++)
    int xstatus = 0;
        for (j = 0; j < OBJ_WIDTH; j++)
            fillBlock(XPOS + j, YPOS + i);
    i = 0;
    if(OBJ_WIDTH>LEN)
        POS = ((OBJ_WIDTH - LEN) / 2);
    else
    {
       POS = 1;
       LABEL[OBJ_WIDTH-2] = '\0';
    }
    
    printf(LABEL,XPOS + i + POS,YPOS);
}

	int GUI::Button::getXPOS(){
        return XPOS;
    }

	int GUI::Button::getYPOS(){
        return YPOS;
    }
	int GUI::Button::getXDimension(){
        return OBJ_WIDTH;
    }
	int GUI::Button::getYDimension(){
        return OBJ_HEIGHT;
    }
    String GUI::Button::getLabel(){
        return LABEL;
    }

void GUI::SET_SC(kodeos::common::uint8_t c)
{
    SC_COLOR = c;
}
void GUI::SET_AC(kodeos::common::uint8_t c)
{
    AC_COLOR = c;
}
uint8_t GUI::GET_SC()
{
    return SC_COLOR;
}
uint8_t GUI::GET_AC()
{
    return AC_COLOR;
}

int GUI::GET_SIndex(){
    return ni;
}

int GUI::GET_SELVIEW(){
    return SELVIEW;
}

void GUI::SET_SELVIEW(int i){
    SELVIEW=i;
}

void GUI::enterSelection(){
    int i,j;
    SET_AC(0x70);
    for(j=1;j<25;j++)
    for(i=0;i<80;i++)
        fillBlock(i,j);
    SET_SC(0x7F);
    printf("Press ESC to close applicattion",44,22);
    icons[ISSELECT]->app->Start();
    SET_SELVIEW(0);
    AppLoaded = true;
}

void GUI::changeSelection(uint8_t val){
    icons[ISSELECT]->deselect();
    if(val == 0x4B){
        if(ISSELECT==0)
            ISSELECT=ni;
        ISSELECT--;
    }
    else if(val == 0x4D){
        if(ISSELECT==ni-1)
            ISSELECT=-1;
        ISSELECT++;
    }
    icons[ISSELECT]->select();

}

GUI::Frame::Frame(char label[40]){
    SET_AC(0xEE);
    int i,j;
    printch(218,4,3);
    for(i = 5;i<75;i++){
        fillBlock(i,3);
    }
    printch(191,75,3);
    SET_AC(0xF0);
    for(j=4;j<21;j++){
    for(i = 5;i<75;i++)
        fillBlock(i,j);
    }
    for(i=4;i<21;i++){
        printch(179,4,i);
        printch(179,75,i);
    }
    printch(192,4,21);
    for(i = 5;i<75;i++){
        printch(196,i,21);
    }
    printch(217,75,21);
    SET_SC(0xE0);
    printf(label,( ( 80 - length(label) ) / 2 ),3);
}
void GUI::RedrawIcons(){
    int i;
    for(i=0;i<ni;i++){
        icons[i]->drawIcon();
    }

}

void GUI::endApplication(){
    AppLoaded = false;
    updatePrintScale(0,1);
    SET_AC(0xF0);
    int i,j;
    for(j=1;j<25;j++)
    {
        for(i=0;i<80;i++){
            fillBlock(i,j);
        }
    }
    SET_SC(0xF0);
    RedrawIcons();
    SET_SELVIEW(1);
    setShowKey(false);
}


bool GUI::getAppLoaded(){
    return AppLoaded;
}