#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <SDL2/SDL_mixer.h>
#pragma comment(lib, "Winmm.lib")
using namespace std;
int LEVEL,SCORE,LIVE,DAMAGE;
int Wid = 960;
int High = Wid*2/3;
double PI=3.141592653589793238463;
struct Square
{
    int no_sqrt,x=((no_sqrt%8)*(Wid/10))+50,y=(no_sqrt/8)*High/12+20,L=Wid/10,W=L/2,strength;
    bool bomb=false;
};
struct Play
{
    int background,ball,corse,level,score,live,damage,d_level;
    Square square[72];
};
struct Players
{
     string name,Q;
     int no_player;// shomareh bazikon
     int co_play;// teded bazi haei ke anjam dadeh.
     Play play[6];// moshakhase haye har bazi
};

int wid_co=Wid/35,v=wid_co/1.5;
void print_one_digit(int X,int Y,int R,SDL_Renderer *renderer){
    if (R==0) {
        thickLineRGBA(renderer, X+5, Y+10, X+20, Y+10,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+40, X+20, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+20, Y+10, X+20, Y+40,wid_co/8,0,0,255,255);
    }
    if (R==1) {
        thickLineRGBA(renderer, X+17, Y+40, X+17, Y+10,wid_co/8,0,0,255,255);
    }
    if (R==2) {
        thickLineRGBA(renderer, X+5, Y+10, X+20, Y+10,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+40, X+20, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+25, X+20, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+20, Y+10, X+20, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+25, X+5, Y+40,wid_co/8,0,0,255,255);
    }
    if (R==3) {
        thickLineRGBA(renderer, X+5, Y+10, X+v, Y+10,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+40, X+v, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+25, X+v, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+v, Y+10, X+v, Y+40,wid_co/8,0,0,255,255);
    }
    if (R==4) {
        thickLineRGBA(renderer, X+v, Y+10, X+v, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+20,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+20, X+v, Y+20,wid_co/8,0,0,255,255);
    }
    if (R==5) {
        thickLineRGBA(renderer, X+5, Y+10, X+v, Y+10,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+25, X+v, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+40, X+v, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+v, Y+25, X+v, Y+40,wid_co/8,0,0,255,255);
    }
    if (R==6) {
        thickLineRGBA(renderer, X+5, Y+10, X+v, Y+10,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+25, X+v, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+40, X+v, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+v, Y+25, X+v, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+40,wid_co/8,0,0,255,255);
    }
    if (R==7) {
        thickLineRGBA(renderer, X, Y+10, X+v, Y+10,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+v, Y+10, X, Y+40,wid_co/8,0,0,255,255);
    }
    if (R==8) {
        thickLineRGBA(renderer, X+5, Y+10, X+v, Y+10,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+25, X+v, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+40, X+v, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+v, Y+10, X+v, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+40,wid_co/8,0,0,255,255);
    }
    if (R==9) {
        thickLineRGBA(renderer, X+5, Y+10, X+v, Y+10,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+25, X+v, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+40, X+v, Y+40,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+5, Y+10, X+5, Y+25,wid_co/8,0,0,255,255);
        thickLineRGBA(renderer, X+v, Y+10, X+v, Y+40,wid_co/8,0,0,255,255);

    }
}

print_(int X,int Y,int R,SDL_Renderer *renderer,int i)
{
    for(i;i>0;i--)
   {
       print_one_digit(X+i*wid_co,Y,R%10,renderer);R/=10;
   }
}
void rect(SDL_Renderer *m_renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );

int main( int argc, char * argv[] )
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Chunk *backM =Mix_LoadWAV("music\\backM.wav");
    Mix_Chunk *bomb =Mix_LoadWAV("music\\02.wav");
    Mix_Chunk *hit =Mix_LoadWAV("music\\hit2.wav");
    Mix_Chunk *levelupM =Mix_LoadWAV("music\\levelup.wav");
    Mix_Chunk *claps =Mix_LoadWAV("music\\claps.wav");
    Mix_Chunk *loss =Mix_LoadWAV("music\\-.wav");
    Mix_Chunk *end =Mix_LoadWAV("music\\end.wav");
    Mix_Chunk *fireM =Mix_LoadWAV("music\\fire.wav");

    int d_level=9;
    char char_[]="123456789";
    const char * IMG_address_ba[6];
    IMG_address_ba[0]="assets\\bowling8.png";
    IMG_address_ba[1]="assets\\ball1.png";
    IMG_address_ba[2]="assets\\ball2.png";
    IMG_address_ba[3]="assets\\ball3.png";
    IMG_address_ba[4]="assets\\Fireball.png";

    const char * IMG_address_b[8];
      IMG_address_b[0]="assets\\b0.png";
      IMG_address_b[3]="assets\\b1.png";
      IMG_address_b[1]="assets\\b2.png";
      IMG_address_b[2]="assets\\b3.png";
      IMG_address_b[5]="assets\\b4.png";
      IMG_address_b[6]="assets\\bg1.png";
      IMG_address_b[4]="assets\\bg5.png";
    const char * IMG_address_t1="assets\\t1.png";
    const char * IMG_address_t2="assets\\t2.png";
    const char * IMG_address_bo="assets\\bomb3.png";
    const char * IMG_address_bl1="assets\\blow1.png";
    const char * IMG_address_bl2="assets\\blow2.png";
    const char * IMG_address_bb1="assets\\bb2.png";
    const char * IMG_address_bb22="assets\\bb22.png";
    const char * IMG_address_bel="assets\\bel2.jpg";
    const char * IMG_address_bel1="assets\\bel1.jpg";
    const char * IMG_address_pau="assets\\pause.png";
    const char * IMG_address_con="assets\\continue.png";
    const char * IMG_address_hom="assets\\home3.png";
    const char * IMG_address_quit="assets\\quit.png";
    const char * IMG_address_menu="assets\\menu.jpg";
    const char * IMG_address_save="assets\\save.png";
    const char * IMG_address_heart="assets\\h.png";
    const char * IMG_address_bitfire="assets\\bitfire.png";
    const char * IMG_address_brick1="assets\\brick1.jpg";
    const char * IMG_address_brick2="assets\\brick2.png";
    const char * IMG_address_brick3="assets\\brick3.png";
    const char * IMG_address_3ball="assets\\3ball.png";
    const char * IMG_address_bomb="assets\\bomb03.png";
    const char * IMG_address_levelup="assets\\levelup.png";
    const char * IMG_address_levelup10="assets\\10LU.jpg";
    const char * IMG_address_playA="assets\\playA.png";
    const char * IMG_address_mutedA="assets\\mutedA.png";
    const char * IMG_address_back="assets\\go_back.png";

    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    Mix_PlayChannel(-1,backM,-1);
    bool save=false,start=true,there=false,roof,playA=true;
    srand((unsigned) time(NULL));
    string player_name;
    char* splay,*slevel,*sscor,*slive;
    int co_p,player_number,play_number,pler,pl;//,no_player=0;
  base:   ifstream co_players("count of players.txt");
    co_players>>co_p;// tedad bazikon ha ro migire
    bool fire=false;
    fstream playerf("player.txt");
    Players player[co_p+1];
    for(int p=0 ;p<co_p;p++)
        {
             getline(playerf,player[p].name);
             playerf>>player[p].no_player>>player[p].co_play;
             for(int i=0;i<6;i++)
             {
                playerf>>player[p].play[i].corse>>player[p].play[i].level>>player[p].play[i].score>>player[p].play[i].live>>player[p].play[i].damage>>player[p].play[i].background>>player[p].play[i].ball>>player[p].play[i].d_level;
                for(int j=0; j<64;j++)
                {
                    playerf>>player[p].play[i].square[j].strength;
                    player[p].play[i].square[j].no_sqrt=j;
                    player[p].play[i].square[j].x=((player[p].play[i].square[j].no_sqrt%8)*(Wid/8))+Wid/48;
                    player[p].play[i].square[j].y=((player[p].play[i].square[j].no_sqrt/8)*High/10+Wid/30);
                }
             }
        }
    if(start)
{
    cout<<"please inter your name : "<<endl;
    getline(cin,player_name);
    cout<<"co_p="<<co_p<<endl;
    for(int i=0;i<co_p&& !there;i++)
    {
        if(player[i].name==player_name)
        {
             there=true;
             player_number=player[i].no_player;
             cout<<"yes"<<endl;
        }
    }
}
    if(!there)
    {
        fstream playerfn("new player.txt");
        if(start)cout<<"not"<<endl;
        player_number=co_p;
        player[co_p].name=player_name;
        player[co_p].no_player=co_p;
        player[co_p].co_play=0;
    int p=co_p;
        for(int i=0;i<6;i++){
            playerfn>>player[p].play[i].corse>>player[p].play[i].level>>player[p].play[i].score>>player[p].play[i].live>>player[p].play[i].damage;
            int s=0;
            for(int j=0; j<64;j++){
            if(j<8)
            {if(j-s>1)player[p].play[i].square[j].strength=1;
                else player[p].play[i].square[j].strength=rand()%2;
        if(player[p].play[i].square[j].strength>0)s++;
            }
             else
            playerfn>>player[p].play[i].square[j].strength;
            player[p].play[i].square[j].no_sqrt=j;
            player[p].play[i].square[j].x=((player[p].play[i].square[j].no_sqrt%8)*(Wid/8))+Wid/48;
            player[p].play[i].square[j].y=((player[p].play[i].square[j].no_sqrt/8)*High/10+Wid/30);
             }
    }
        co_p++;
    }
    there=true;
    pler=player_number;
    pl=0;
    if(start)
{
    Uint32 WND_flags = SDL_WINDOW_SHOWN ;
    SDL_CreateWindowAndRenderer( Wid,High, WND_flags, &m_window, &m_renderer );

    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = DM.w;
    int H = DM.h;
    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );
}
    start=false;

    SDL_Rect img_3ball;
    SDL_Texture* ball3_img = NULL;
    ball3_img = IMG_LoadTexture(m_renderer, IMG_address_3ball);
    img_3ball.w = Wid/15 ;
    img_3ball.h = img_3ball.w;

    SDL_Rect img_levelup;
    SDL_Texture* levelup_img = NULL;
    levelup_img = IMG_LoadTexture(m_renderer, IMG_address_levelup);
    img_levelup.x =Wid/4;
    img_levelup.y =High/4;
    img_levelup.w = Wid/2 ;
    img_levelup.h = High/2;

    SDL_Rect img_brick1;
    SDL_Texture* brick1_img = NULL;
    brick1_img = IMG_LoadTexture(m_renderer, IMG_address_brick1);
    img_brick1.w = Wid/12 ;
    img_brick1.h = High/15 ;

    SDL_Rect img_brick2;
    SDL_Texture* brick2_img = NULL;
    brick2_img = IMG_LoadTexture(m_renderer, IMG_address_brick2);
    img_brick2.w = Wid/12 ;
    img_brick2.h = High/15 ;

    SDL_Rect img_brick3;
    SDL_Texture* brick3_img = NULL;
    brick3_img = IMG_LoadTexture(m_renderer, IMG_address_brick3);
    img_brick3.w = Wid/12 ;
    img_brick3.h = High/15 ;


    SDL_Rect img_heart;
    SDL_Texture* heart_img = NULL;
    heart_img = IMG_LoadTexture(m_renderer, IMG_address_heart);
    img_heart.y = High*0.92;
    img_heart.w = wid_co ;
    img_heart.h = wid_co ;

    SDL_Rect img_backg;
    SDL_Texture* backg_img = NULL;
    backg_img = IMG_LoadTexture(m_renderer, IMG_address_b[4]);
    img_backg.x = 0;
    img_backg.y = 0;
    img_backg.w = Wid ;
    img_backg.h = High ;

    SDL_Rect img_10lu;
    SDL_Texture* lu10_img = NULL;
    lu10_img = IMG_LoadTexture(m_renderer, IMG_address_levelup10);
    img_10lu.x = 0;
    img_10lu.y = 0;
    img_10lu.w = Wid ;
    img_10lu.h = High ;

    SDL_Rect img_bel;
    SDL_Texture* bel_img = NULL;
    bel_img=IMG_LoadTexture(m_renderer, IMG_address_bel);
    img_bel.x=0;
    img_bel.y=0.9*High;
    img_bel.w=Wid;
    img_bel.h=High*0.1;

    SDL_Rect img_bel1;
    SDL_Texture* bel1_img = NULL;
    bel1_img=IMG_LoadTexture(m_renderer, IMG_address_bel1);
    img_bel1.x=Wid/16;
    img_bel1.y=High/15+(High/8);
    img_bel1.w=Wid*0.9;
    img_bel1.h=High*0.1;

    SDL_Rect img_pau;
    SDL_Texture* pau_img = NULL;
    pau_img=IMG_LoadTexture(m_renderer, IMG_address_pau);
    img_pau.x=28*Wid/30;
    img_pau.y=0.9*High;
    img_pau.w=High*0.1;
    img_pau.h=High*0.1;

    SDL_Rect img_back;
    SDL_Texture* back_img = NULL;
    back_img=IMG_LoadTexture(m_renderer, IMG_address_back);
    img_back.w=High*0.1;
    img_back.h=High*0.1;

    SDL_Rect img_con;
    SDL_Texture* con_img = NULL;
    con_img=IMG_LoadTexture(m_renderer, IMG_address_con);
    img_con.x=28*Wid/30;
    img_con.y=0.9*High;
    img_con.w=High*0.1;
    img_con.h=High*0.1;

    SDL_Rect img_menu;
    SDL_Texture* menu_img = NULL;
    menu_img=IMG_LoadTexture(m_renderer, IMG_address_menu);
    img_menu.x=Wid/4;
    img_menu.y=0.1*High;
    img_menu.w=Wid/2;
    img_menu.h=High*0.8;

    SDL_Rect img_PA;
    SDL_Texture* PA_img = NULL;
    PA_img=IMG_LoadTexture(m_renderer, IMG_address_playA);
    img_PA.w=High*0.1;
    img_PA.h=High*0.1;
    img_PA.x=(3*Wid/4)-1.5*img_PA.w;
    img_PA.y=0.9*High-1.5*img_PA.h;

    SDL_Rect img_MA;
    SDL_Texture* MA_img = NULL;
    MA_img=IMG_LoadTexture(m_renderer, IMG_address_mutedA);
    img_MA.x=img_PA.x;
    img_MA.y=img_PA.y;
    img_MA.w=High*0.1;
    img_MA.h=High*0.1;


    SDL_Rect img_hom;
    SDL_Texture* hom_img = NULL;
    hom_img=IMG_LoadTexture(m_renderer, IMG_address_hom);
    img_hom.x=9*Wid/20;
    img_hom.y=0.2*High;
    img_hom.w=Wid/10;
    img_hom.h=Wid/10;

    SDL_Rect img_save;
    SDL_Texture* save_img = NULL;
    save_img=IMG_LoadTexture(m_renderer, IMG_address_save);
    img_save.x=9*Wid/20;
    img_save.y=0.45*High;
    img_save.w=Wid/10;
    img_save.h=Wid/10;

    SDL_Rect img_quit;
    SDL_Texture* quit_img = NULL;
    quit_img=IMG_LoadTexture(m_renderer, IMG_address_quit);
    img_quit.x=9*Wid/20;
    img_quit.y=0.7*High;
    img_quit.w=Wid/10;
    img_quit.h=Wid/10;

    int bomb_w=Wid/15, bomb_h=High/14;
    SDL_Rect img_bomb;
    SDL_Texture* bomb_img = NULL;
    bomb_img = IMG_LoadTexture(m_renderer, IMG_address_bo);
    img_bomb.w = bomb_w ;
    img_bomb.h = bomb_h ;

    int blow_w=Wid/15, blow_h=High/14;
    SDL_Rect img_blow;
    SDL_Texture* blow_img = NULL;
    blow_img = IMG_LoadTexture(m_renderer, IMG_address_bl2);

    int boa_w=Wid/10, boa_h=High/5;
    SDL_Rect img_board;
    SDL_Texture* board_img = NULL;
    board_img = IMG_LoadTexture(m_renderer, IMG_address_t1);
    img_board.x = 9*Wid/20;
    img_board.y = High*0.70;
    img_board.w = boa_w ;
    img_board.h = boa_h ;

    int img_w=Wid/30, img_h=img_w;
    SDL_Rect img_rect;
    SDL_Texture* m_img = NULL;
    m_img = IMG_LoadTexture(m_renderer, IMG_address_01);
    img_rect.x = Wid/2-img_w/2;
    img_rect.y = 10*High/11;
    img_rect.w = img_w ;
    img_rect.h = img_h ;

  SDL_Event *event = new SDL_Event();
    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );
    SDL_RenderClear( m_renderer );
    backg_img = IMG_LoadTexture(m_renderer,IMG_address_bb1);
    SDL_RenderCopy(m_renderer, backg_img, NULL, &img_backg);
    SDL_RenderPresent( m_renderer );
bool quit=false,chose=false,newg=false;
    SDL_RenderCopy(m_renderer, bel1_img, NULL, &img_bel1);

    int i;
for(int c=0;c<player[player_number].co_play;c++)
{
    int leve=player[player_number].play[c+1].level;
    int scor=player[player_number].play[c+1].score;
    int liv=player[player_number].play[c+1].live;
    int c1=c+2;
    img_bel1.y=High/15+(c1)*(High/8);
    SDL_RenderCopy(m_renderer, bel1_img, NULL, &img_bel1);
    print_(Wid/12,High/15+c1*(High/8),char_[c1],m_renderer,1);
    print_(Wid/12+1*(Wid/4.8),High/15+c1*(High/8),leve,m_renderer,2);
    print_(Wid/12+2*(Wid/4.8),High/15+c1*(High/8),scor,m_renderer,4);
  for(int i=0;i<liv;i++)
  {
        img_heart.y =High/12+c1*(High/8);
        img_heart.x =Wid/8+3*(Wid/4.8)+i*Wid/30;
        SDL_RenderCopy(m_renderer, heart_img, NULL, &img_heart);
  }

}
     textRGBA(m_renderer,Wid/11,High/15+(High/8),"new",2 ,Wid/20,0,255,0,255);
    print_(Wid/12+1*(Wid/4.8),High/15+(High/8),1,m_renderer,2);
    print_(Wid/12+2*(Wid/4.8),High/15+(High/8),0,m_renderer,4);
for(int i=0;i<3;i++)
  {
        img_heart.y =High/12+(High/8);
        img_heart.x =Wid/8+3*(Wid/4.8)+i*Wid/30;
        SDL_RenderCopy(m_renderer, heart_img, NULL, &img_heart);
  }
    img_quit.x=0;
    img_quit.y=0;
    SDL_RenderCopy(m_renderer, quit_img, NULL, &img_quit);

    img_heart.y = High*0.92;
    SDL_RenderPresent( m_renderer );
while (!chose)
        {
        if( SDL_PollEvent( event ) )
        {
            if( event->type ==SDL_MOUSEBUTTONDOWN)
            {
                int x=event->button.x,y=event->button.y;
                if(x>img_quit.x&&y>img_quit.y&x<img_quit.x+img_quit.w&&y<img_quit.y+img_quit.h)
                {
                    SDL_DestroyRenderer( m_renderer );
                    IMG_Quit();
                    SDL_Quit();
                    return 0;
                }

                for(int i=2;i<player[player_number].co_play+3;i++)
                if( x>Wid/11&&x<Wid/11+(Wid/4.8)&&y>High/15+(i-1)*(High/8)&&y<High/15+i*(High/8))
                {

                    SDL_RenderPresent( m_renderer );
                    chose=true;
                    pl=i-2;//play_number
                    LEVEL=player[pler].play[pl].level;
                    SCORE=player[pler].play[pl].score;
                    LIVE=player[pler].play[pl].live;
                    DAMAGE=player[pler].play[pl].damage;
                    if(i==2)newg=true;
                }
            }
        }
        }
base3:
if(newg){
    backg_img = IMG_LoadTexture(m_renderer,IMG_address_bb22);
    img_backg.w=Wid;
    img_backg.h=High;

    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );
    SDL_RenderClear( m_renderer );
    SDL_RenderCopy(m_renderer, backg_img, NULL, &img_backg);
{
    backg_img = IMG_LoadTexture(m_renderer,IMG_address_bb22);
    img_backg.w=Wid/4;
    img_backg.h=High/3;
for(int j=0;j<2;j++)
    for(int i=0;i<3;i++)
{
    img_backg.x=Wid/30+i*Wid/3;
    img_backg.y=High/20+j*High/2;
    backg_img = IMG_LoadTexture(m_renderer,IMG_address_b[j*3+i]);
    SDL_RenderCopy(m_renderer, backg_img, NULL, &img_backg);}
    img_back.x=0;
    img_back.y=0.9*High;
    SDL_RenderCopy(m_renderer, back_img, NULL, &img_back);

    SDL_RenderPresent( m_renderer );

}chose=false;
while (!chose)
        {
        if( SDL_PollEvent( event ) )
        {
            if( event->type ==SDL_MOUSEBUTTONDOWN)
            {
                int x=event->button.x,y=event->button.y;
                if(x>img_back.x&&y>img_back.y&x<img_back.x+img_back.w&&y<img_back.y+img_back.h)
                    goto base;
            for(int j=0;j<2;j++)
            for(int i=0;i<3;i++)
                if(x>Wid/30+i*Wid/3&&x<Wid/30+i*Wid/3+Wid/4&&y>High/20+j*High/2&&y<High/20+j*High/2+High/3)
                    {
                        backg_img = IMG_LoadTexture(m_renderer,IMG_address_b[j*3+i]);
                        chose=true;
                        player[pler].play[pl].background=j*3+i;
                        player[pler].play[pl].d_level=5+i*4;
                    }
            }
        }
        }
    img_backg.x = 0;
    img_backg.y = 0;
    img_backg.w = Wid ;
    img_backg.h = High ;

    SDL_SetRenderDrawColor( m_renderer, 255, 255, 255, 255 );
    SDL_RenderClear( m_renderer );
    SDL_RenderCopy(m_renderer, backg_img, NULL, &img_backg);
    SDL_RenderCopy(m_renderer, back_img, NULL, &img_back);
    SDL_RenderPresent( m_renderer );
{
    img_rect.w=Wid/4;
    img_rect.h=High/3;
for(int j=0;j<1;j++)
    for(int i=0;i<3;i++)
{
    img_rect.x=Wid/30+i*Wid/3;
    img_rect.y=High/20+j*High/2;
    m_img = IMG_LoadTexture(m_renderer,IMG_address_ba[j*2+i]);
    SDL_RenderCopy(m_renderer, m_img, NULL, &img_rect);}
                SDL_RenderPresent( m_renderer );
}
chose=false;
while (!chose)
        {
        if( SDL_PollEvent( event ) )
        {
            if( event->type ==SDL_MOUSEBUTTONDOWN)
            {
                int x=event->button.x,y=event->button.y;
                if(x>img_back.x&&y>img_back.y&x<img_back.x+img_back.w&&y<img_back.y+img_back.h)
                    goto base3;
            for(int j=0;j<1;j++)
            for(int i=0;i<3;i++)
                if(x>Wid/30+i*Wid/3&&x<Wid/30+i*Wid/3+Wid/4&&y>High/20+j*High/2&&y<High/20+j*High/2+High/3)
                        {m_img = IMG_LoadTexture(m_renderer,IMG_address_ba[j*2+i]);
                        chose=true;
                        player[pler].play[pl].ball=j*2+i;}
            }
        }
        }
    img_rect.w = img_w ;
    img_rect.h = img_h ;
}
else{
    backg_img=IMG_LoadTexture(m_renderer,IMG_address_b[player[pler].play[pl].background]);
    m_img=IMG_LoadTexture(m_renderer,IMG_address_ba[player[pler].play[pl].ball]);
}
d_level=player[pler].play[pl].d_level;
    img_backg.h = 0.9*High ;
    textRGBA(m_renderer,Wid/3,High/2,"Loading...",2,Wid/12,150,155,100,255);
    SDL_RenderCopy(m_renderer, bel_img, NULL, &img_bel);
    SDL_RenderCopy(m_renderer, pau_img, NULL, &img_pau);
    img_quit.x=9*Wid/20;
    img_quit.y=0.7*High;
    img_hom.x=9*Wid/20;
    img_hom.y=0.2*High;
   SDL_Delay(800);

/**************************************************************************************************************************************/
/**************************************************************************************************************************************/
/**************************************************************************************************************************************/
/**************************************************************************************************************************************/
int t=70,tt=1,xx1=1000,yy1=1000,XX=Wid/12,YY=High/15,zar=0,lev,lev_co,sco,sco_co,sum_whole_sqr_stre;
int X[3],Y[3],step[3],tedad=1,damag[3];
bool ball3=false,bombp=false,bomby=false,levelup=false;
double tetha[3];
step[0]=5;
step[1]=0;
step[2]=0;
X[1]=Wid;
X[2]=Wid;
Y[1]=0;
Y[2]=0;
board_img = IMG_LoadTexture(m_renderer, IMG_address_t1);
bool shoot=false,pause=false,gameover=false,gameovers=false,lively=false,ch_t=false;
while (!quit)
{
if(LIVE>0)lively=true;
if(LEVEL>10&&!ch_t)
{
    board_img = IMG_LoadTexture(m_renderer, IMG_address_t2);
    ch_t=true;
}

    SDL_RenderCopy(m_renderer, bel_img, NULL, &img_bel);
    SDL_RenderCopy(m_renderer, pau_img, NULL, &img_pau);
    print_(Wid/20+(Wid/10),0.9*High,LEVEL,m_renderer,2);
    print_(Wid/20+7*(Wid/10),High*0.9,SCORE,m_renderer,4);
  for(int i=0;i<LIVE;i++)
  {
        img_heart.x =Wid/4.5+(4+i)*(Wid/25);
        SDL_RenderCopy(m_renderer, heart_img, NULL, &img_heart);
  }
        if( SDL_PollEvent( event ) )
        {
            if(event->type ==SDL_MOUSEBUTTONDOWN)
            {
            if(event->button.x>img_pau.x&&event->button.y>img_pau.y)
               {
            base2:  pause=true;
                    SDL_RenderCopy(m_renderer, bel_img, NULL, &img_bel);
                    print_(Wid/20+(Wid/10),0.9*High,LEVEL,m_renderer,2);
                    print_(Wid/20+7*(Wid/10),High*0.9,SCORE,m_renderer,4);
                    for(int i=0;i<LIVE;i++)
                    {
                        img_heart.x =Wid/4.5+(4+i)*(Wid/25);
                        SDL_RenderCopy(m_renderer, heart_img, NULL, &img_heart);
                    }
                        SDL_RenderCopy(m_renderer, menu_img, NULL, &img_menu);
                        SDL_RenderCopy(m_renderer, hom_img, NULL, &img_hom);
                        SDL_RenderCopy(m_renderer, save_img, NULL, &img_save);
                        SDL_RenderCopy(m_renderer, quit_img, NULL, &img_quit);
                        if(playA)SDL_RenderCopy(m_renderer, PA_img, NULL, &img_PA);
                        else SDL_RenderCopy(m_renderer, MA_img, NULL, &img_MA);
                        SDL_RenderCopy(m_renderer, con_img, NULL, &img_con);
                        SDL_RenderPresent( m_renderer );SDL_Delay(800);
                   while(pause)
                    {
                        if( SDL_PollEvent( event ) )
                            if(event->type ==SDL_MOUSEBUTTONDOWN)
                            {
                                int x=event->button.x,y=event->button.y;
                                if(x>img_PA.x&&x<(img_PA.x+img_PA.w)&&y>img_PA.y&&y<(img_PA.y+img_PA.h))
                                {
                                    if(playA)
                                        {
                                            playA=false;
                                            Mix_Pause(-1);
                                            Mix_Pause(1);
                                        }
                                    else
                                    {
                                        playA=true;
                                        Mix_PlayChannel(-1,backM,-1);
                                        if(fire)
                                        Mix_PlayChannel(1,fireM,-1);
                                    }
                                    SDL_RenderCopy(m_renderer, menu_img, NULL, &img_menu);
                                    SDL_RenderCopy(m_renderer, hom_img, NULL, &img_hom);
                                    SDL_RenderCopy(m_renderer, save_img, NULL, &img_save);
                                    SDL_RenderCopy(m_renderer, quit_img, NULL, &img_quit);
                                    if(playA)SDL_RenderCopy(m_renderer, PA_img, NULL, &img_PA);
                                    else SDL_RenderCopy(m_renderer, MA_img, NULL, &img_MA);
                                    SDL_RenderCopy(m_renderer, con_img, NULL, &img_con);
                                    SDL_RenderPresent( m_renderer );SDL_Delay(800);
                                }
                                if(x>img_pau.x&&y>img_pau.y&&!gameover)
                                    pause=false;
                                if(x>img_hom.x&&y>img_hom.y&x<img_hom.x+img_hom.w&&y<img_hom.y+img_hom.h)
                                    goto base;
                                if(x>img_quit.x&&y>img_quit.y&x<img_quit.x+img_quit.w&&y<img_quit.y+img_quit.h){
                                    quit=true;
                                    break;}
                                if(x>img_save.x&&y>img_save.y&x<img_save.x+img_save.w&&y<img_save.y+img_save.h)
                                {
textRGBA(m_renderer,Wid/3,High/2,"saving...",2,Wid/12,100,155,100,255);
player[pler].play[pl].level=LEVEL;
player[pler].play[pl].live=LIVE;
player[pler].play[pl].damage=DAMAGE;
player[pler].play[pl].score=SCORE;
if(newg)
{
    ofstream co_players("count of players.txt");
    co_players<<co_p;

    fstream playerfn("new player.txt");
    playerfn>>player[pler].play[5].corse>>player[pler].play[5].level>>player[pler].play[5].score>>player[pler].play[5].live>>player[pler].play[5].damage;
    int s=0;
    for(int j=0; j<64;j++){
        if(j<8)
            {
                if(j-s>1)player[pler].play[5].square[j].strength=1;
                else player[pler].play[5].square[j].strength=rand()%2;
        if(player[pler].play[5].square[j].strength>0)s++;
            }
        else
            playerfn>>player[pler].play[5].square[j].strength;
            player[pler].play[5].square[j].no_sqrt=j;
            player[pler].play[5].square[j].x=((player[pler].play[5].square[j].no_sqrt%8)*(Wid/8))+Wid/48;
            player[pler].play[5].square[j].y=((player[pler].play[5].square[j].no_sqrt/8)*High/10+Wid/30);
             }
    for(int i=5;i>0;i--)
        swap(player[pler].play[i],player[pler].play[i-1]);
        player[pler].co_play++;
}
if(player[pler].co_play>5)player[pler].co_play=5;
fstream playerfn("player.txt");
playerfn.seekp(0);
    for(int p=0 ;p<co_p;p++)
    {
        playerfn<<player[p].name<<endl;
        playerfn<<player[p].no_player<<" "<<player[p].co_play<<endl;
            for(int i=0;i<6;i++)
            {
                playerfn<<player[p].play[i].corse<<" "<<player[p].play[i].level<<" "<<player[p].play[i].score<<" "<<player[p].play[i].live<<" "<<player[p].play[i].damage<<" "<<player[p].play[i].background<<" "<<player[p].play[i].ball<<" "<<player[p].play[i].d_level<<endl;
                for(int j=0; j<64;j++)
                {
                    playerfn<<player[p].play[i].square[j].strength<<" ";
                    if((j+1)%8==0)playerfn<<endl;
                }
            }
            playerfn.seekp(-3,ios_base::cur);
    }
    SDL_Delay(800);
                        SDL_RenderCopy(m_renderer, menu_img, NULL, &img_menu);
                        SDL_RenderCopy(m_renderer, hom_img, NULL, &img_hom);
                        SDL_RenderCopy(m_renderer, save_img, NULL, &img_save);
                        SDL_RenderCopy(m_renderer, quit_img, NULL, &img_quit);
                        if(playA)SDL_RenderCopy(m_renderer, PA_img, NULL, &img_PA);
                        else SDL_RenderCopy(m_renderer, MA_img, NULL, &img_MA);
                        SDL_RenderPresent( m_renderer );
                        newg=false;
                        gameovers=false;
                                }
                            }
                    }
               }
                    SDL_RenderCopy(m_renderer, bel_img, NULL, &img_bel);
                    SDL_RenderCopy(m_renderer, pau_img, NULL, &img_pau);
            }
            if(event->type == SDL_KEYUP)
            {
            switch( event->key.keysym.sym )
            {
                case SDLK_LEFT:
                    zar=0;
                    break;
                case SDLK_RIGHT:
                    zar=0;
                    break;
            }
            }
            if( event->type == SDL_KEYDOWN )
            {
                switch( event->key.keysym.sym )
                {
                case SDLK_ESCAPE:
                    quit=true; break;
                case SDLK_f:
                    if(bomby)
                    {
                        Mix_PlayChannel(-1,bomb,0);
                        for(double i=0;i<10;i+=0.1)
                            {
                                img_blow.x=img_rect.x-i*Wid/64;
                                img_blow.y=img_rect.y-i*High/80;
                                img_blow.w=Wid/8+i*(Wid/32);
                                img_blow.h=High/10+i*(High/40);
                                SDL_RenderCopy(m_renderer, blow_img, NULL, &img_blow);
                                SDL_RenderPresent( m_renderer );
                            }
                        for(int i=0;i<64;i++)
                            {
                                if(abs(player[pler].play[pl].square[i].x-img_rect.x)<Wid/5&&abs(player[pler].play[pl].square[i].y-img_rect.y)<High/6)
                                {
                                    SCORE+=player[pler].play[pl].square[i].strength;
                                    player[pler].play[pl].square[i].strength=0;
                                }
                            }
                               damag[0]=0;
                                for(double i=10;i>-2;i-=0.1)
                                    {
                                        img_blow.x=img_rect.x-i*Wid/64;
                                        img_blow.y=img_rect.y-i*High/80;
                                        img_blow.w=Wid/8+i*(Wid/32);
                                        img_blow.h=High/10+i*(High/40);
                                        SDL_RenderCopy(m_renderer, blow_img, NULL, &img_blow);
                                        SDL_RenderPresent( m_renderer );
                                    }
                        bomby=false;
                    }
                    if(!gameover)shoot=true;break;
                case SDLK_LEFT:
                    zar=-1;
                    break;
                case SDLK_RIGHT:
                    zar=1;
                    break;
                case SDLK_UP:
                    for(int i=rand()%8,j=0;j<8;j++)
                        player[pler].play[pl].square[8*i+j].strength=0;
                }
            }
        }
   if(shoot) img_board.x+=zar*Wid/100+zar*tedad*5;
   else img_board.x+=zar*Wid/50;
    if(!shoot)
    {
    if(LEVEL>7&&!gameover){
        for(int sq=56;sq<64;sq++)
            if(player[pler].play[pl].square[sq].strength>0)
            {
            LIVE=0;
            Mix_PlayChannel(-1,end,0);
            textRGBA(m_renderer,Wid/3,High/2,"Game over!",2,Wid/12,255,155,100,255);
            SDL_Delay(800);
            gameover=true;
            gameovers=true;
            shoot=false;
            levelup=false;
            if(lively)goto base2;
            break;
            }
    }

        if(LEVEL%10==0&&levelup)
        {
            Mix_PlayChannel(-1,claps,0);
            for(int i=0;i<Wid;i+=10)
            {
                img_10lu.w=i;
                img_10lu.h=2*img_10lu.w/3;
                img_10lu.x=Wid/2-img_10lu.w/2;
                img_10lu.y=High/2-img_10lu.h/2;
                SDL_RenderCopy(m_renderer, lu10_img, NULL, &img_10lu);
                SDL_RenderPresent( m_renderer );
                SDL_Delay(5);
            }
            SDL_Delay(1000);
            if(LEVEL==10)SDL_Delay(1000);
            levelup=false;
        }
        if(levelup)
        {
            Mix_PlayChannel(-1,levelupM,0);
            levelup=false;
            for(int i=0;i<High/2;i+=5)
            {
            img_levelup.w=3*i/2;
            img_levelup.h=i;
            img_levelup.x=Wid/2-img_levelup.w/2;
            img_levelup.y=High/2-img_levelup.h/2;
            SDL_RenderCopy(m_renderer, levelup_img, NULL, &img_levelup);
            SDL_RenderPresent( m_renderer );
            SDL_Delay(5);
            }
            SDL_Delay(500);
        }
        if(fire)
        {
        img_rect.h=img_w;
        img_rect.w=img_rect.h;
        Y[0]=img_board.y+boa_h/2-(img_w);
        }
        else{
        img_rect.h=img_w+img_w*damag[0]/LEVEL;
        img_rect.w=img_rect.h;
        Y[0]=img_board.y+boa_h/2-(img_w+img_w*damag[0]/LEVEL);
        }
        t+=tt*7;
        X[0]=(img_board.x+boa_w/2);
    img_rect.x = X[0]-img_rect.w/2;
     X[0]=img_rect.x ;
    img_rect.y = Y[0];
    if(t>170||t<14)tt*=-1;
    tetha[0]=(t%180)*PI/180;
    damag[0]=DAMAGE;
    tedad=1;
    step[0]=5;
    step[1]=0;
    step[2]=0;
    X[1]=Wid;
    X[2]=Wid;
    Y[1]=0;
    Y[2]=0;
    img_3ball.y=2*High;
    ball3=false;
    bombp=false;
    bomby=false;
        SDL_RenderCopy(m_renderer, backg_img, NULL, &img_backg);
        SDL_RenderCopy(m_renderer, board_img, NULL, &img_board);
        SDL_RenderCopy(m_renderer, m_img, NULL, &img_rect);
        for(int sq=0;sq<8*min(8,LEVEL);sq++)
            {
                int stre=player[pler].play[pl].square[sq].strength;
                if(stre>0)
                {
                    int l3=LEVEL/3;
                    if(stre<=l3){
                        img_brick1.x=player[pler].play[pl].square[sq].x;
                        img_brick1.y=player[pler].play[pl].square[sq].y;
                        SDL_RenderCopy(m_renderer, brick1_img, NULL, &img_brick1);
                    }
                    if(stre>l3&&stre<=2*l3){
                        img_brick2.x=player[pler].play[pl].square[sq].x;
                        img_brick2.y=player[pler].play[pl].square[sq].y;
                        SDL_RenderCopy(m_renderer, brick2_img, NULL, &img_brick2);
                    }
                    if(stre>2*l3){
                        img_brick3.x=player[pler].play[pl].square[sq].x;
                        img_brick3.y=player[pler].play[pl].square[sq].y;
                        SDL_RenderCopy(m_renderer, brick3_img, NULL, &img_brick3);
                    }
                }
            }
        for(int i=0;i<400;i+=40)
            filledCircleRGBA(m_renderer,X[0]+img_rect.w/2+i*cos(tetha[0]),Y[0]+(img_w+img_w*damag[0]/LEVEL)/2-i*sin(tetha[0]),5,255,0,0,255);
            SDL_RenderPresent( m_renderer );SDL_Delay(80);
 }
    else
    {
    img_3ball.y+=1;
    if(img_3ball.x-img_board.x<img_board.w&&img_3ball.x-img_board.x>-1*(img_3ball.w)&&img_3ball.y>(0.8*High-img_3ball.h)&&img_3ball.y<(0.85*High-img_3ball.h)&&ball3)
    {
        if(bombp)
        {
            bomby=true;
            fire=false;
            Mix_Pause(1);
            m_img=IMG_LoadTexture(m_renderer,IMG_address_bomb);
            img_3ball.y=2*High;
        }
        else {
                        damag[1]=damag[0];
                        damag[2]=damag[0];
                        step[1]=5;
                        step[2]=5;
                        tedad=3;
                        X[1]=X[0];
                        X[2]=X[0];
                        Y[1]=Y[0];
                        Y[2]=Y[0];
                        tetha[1]=2.5;
                        tetha[2]=0.8;
                        img_3ball.y=2*High;
        }
            bombp=false;
            ball3=false;
    }
    if(img_3ball.y>0.86*High-(img_3ball.h))
    {
        bombp=false;
        ball3=false;
        img_3ball.y=2*High;
    }

    sum_whole_sqr_stre=0;
    for(int sqr=0;sqr<64;sqr++)
    {
        int stre=player[pler].play[pl].square[sqr].strength;
        if(stre>0)
            {
                sum_whole_sqr_stre++;
                for(int sh=0;sh<tedad;sh++)
                {
                    xx1=X[sh]-player[pler].play[pl].square[sqr].x;
                    yy1=Y[sh]-player[pler].play[pl].square[sqr].y;
                    int www=img_w+img_w*damag[sh]/LEVEL;
                if(xx1<XX&&xx1>-1*www&&yy1<YY&&yy1>-1*www)
                    {
                        if(abs(sqr%d_level-rand()%d_level)<1&&!fire&&tedad==1)
                            {
                                img_bomb.x=player[pler].play[pl].square[sqr].x+Wid/50;
                                img_bomb.y=player[pler].play[pl].square[sqr].y;
                                SDL_RenderCopy(m_renderer, bomb_img, NULL, &img_bomb);
                                SDL_RenderPresent( m_renderer );
                                Mix_PlayChannel(-1,bomb,0);
                                for(double i=0;i<8;i+=0.1)
                                    {
                                        img_blow.x=player[pler].play[pl].square[sqr].x-i*Wid/64;
                                        img_blow.y=player[pler].play[pl].square[sqr].y-i*High/80;
                                        img_blow.w=Wid/8+i*(Wid/32);
                                        img_blow.h=High/10+i*(High/40);
                                        SDL_RenderCopy(m_renderer, blow_img, NULL, &img_blow);
                                        SDL_RenderPresent( m_renderer );
                                    }
                                for(int i=-1;i<2;i++)
                                    for(int j=-1;j<2;j++)
                                        {
                                            if(player[pler].play[pl].square[sqr+i*8+j].strength<100)
                                            SCORE+=player[pler].play[pl].square[sqr+i*8+j].strength;
                                            player[pler].play[pl].square[sqr+i*8+j].strength=0;
                                        }
                               damag[sh]=0;
                                SCORE+=stre;
                                stre=0;
                                for(double i=8;i>-2;i-=0.1)
                                    {
                                        img_blow.x=player[pler].play[pl].square[sqr].x-i*Wid/64;
                                        img_blow.y=player[pler].play[pl].square[sqr].y-i*High/80;
                                        img_blow.w=Wid/8+i*(Wid/32);
                                        img_blow.h=High/10+i*(High/40);
                                        SDL_RenderCopy(m_renderer, blow_img, NULL, &img_blow);
                                        SDL_RenderPresent( m_renderer );//SDL_Delay(1);
                                    }

                            }
                        else
                            Mix_PlayChannel(-1,hit,0);
                        if((xx1>XX-6||xx1<-1*Wid/30+6)&&!fire)tetha[sh]=PI-tetha[sh];
                        if((yy1>YY-6||yy1<-1*Wid/30+6)&&!fire)tetha[sh]*=-1;
                        if(fire){
                                SCORE+=stre;
                                stre=0;
                        }
                        else
                        {
                            if(stre>=damag[sh] )
                            {
                                SCORE+=damag[sh];
                                stre-=damag[sh];
                                damag[sh]=0;
                            }
                            else
                            {
                                SCORE+=stre;
                                damag[sh]-=stre;
                                stre=0;
                            }
                        }
                    player[pler].play[pl].square[sqr].strength=stre;

                if(tedad==1&&abs((rand()%64)-sqr)>4*d_level&&damag[0]!=0&&!ball3&&((!fire)||(fire&&d_level<12)))
                    {
                        if(rand()%2)
                        {
                        ball3_img = IMG_LoadTexture(m_renderer, IMG_address_3ball);
                        }
                        else
                        {
                        ball3_img = IMG_LoadTexture(m_renderer, IMG_address_bomb);
                        bombp=true;
                        }
                        ball3=true;
                        img_3ball.x=player[pler].play[pl].square[sqr].x;
                        img_3ball.y=player[pler].play[pl].square[sqr].y;
                    }
                    }
                }
            }
    }
    if(LEVEL>7){
        for(int sq=56;sq<64;sq++)
            if(player[pler].play[pl].square[sq].strength>0)
            LIVE=0;
    }
if(tedad>1)
    {int tedadd=tedad;
        for(int sh=0;sh<tedadd;sh++)
        {
            if(damag[sh]==0&&(sh<2||(damag[tedad-1]==0))){
            swap(X[tedad-1],X[sh]);
            swap(Y[tedad-1],Y[sh]);
            swap(damag[tedad-1],damag[sh]);
            swap(tetha[tedad-1],tetha[sh]);
            swap(step[tedad-1],step[sh]);
            X[tedad-1]=Wid*2;
            Y[tedad-1]=0;
            step[tedad-1]=0;
            damag[tedad-1]=0;
            tedad--;
            if(tedad<1){tedad=1;shoot=false;}
            }
        }

    }
    for(int sh=0;sh<tedad;sh++)
    if((tetha[sh]>=PI-0.15&&tetha[sh]<=PI+0.15)||(tetha[sh]>=PI/2-0.15&&tetha[sh]<=PI/2+0.15))tetha[sh]+=0.2;

    int tedadd=tedad;
    for(int sh=0;sh<tedadd;sh++)
    {
    if(X[sh]<5){tetha[sh]=PI-tetha[sh];X[sh]=6;}
    if(X[sh]>Wid-(img_w+img_w*damag[sh]/LEVEL)){tetha[sh]=PI-tetha[sh];X[sh]=Wid-(img_w+img_w*damag[sh]/LEVEL)-10;}
    if(Y[sh]<1){tetha[sh]*=-1;Y[sh]+=5;roof=true;}

    if(Y[sh]>0.86*High-(img_w+img_w*damag[sh]/LEVEL)){
        if(tedad<2)
        {
            LIVE--;
            Mix_PlayChannel(-1,loss,0);
            shoot=false;
        }
        else
        {
            swap(X[tedad-1],X[sh]);
            swap(Y[tedad-1],Y[sh]);
            swap(damag[tedad-1],damag[sh]);
            swap(tetha[tedad-1],tetha[sh]);
            swap(step[tedad-1],step[sh]);
            X[tedad-1]=Wid*2;
            Y[tedad-1]=0;
            step[tedad-1]=0;
            damag[tedad-1]=0;
            tedad--;
            if(tedad<1){tedad=1;shoot=false;}

       }
    }
    }
    if(LIVE<1)
    {
        Mix_PlayChannel(-1,end,0);
        textRGBA(m_renderer,Wid/3,High/2,"Game over!",2,Wid/12,255,155,100,255);
        SDL_Delay(800);
        gameover=true;
        gameovers=true;
        shoot=false;
        if(lively)goto base2;

    }
for(int sh=0;sh<tedad;sh++)
{
    if(X[sh]-img_board.x<img_board.w&&X[sh]-img_board.x>-1*(img_w+img_w*damag[sh]/LEVEL)&&Y[sh]>(0.8*High-(img_w+img_w*damag[sh]/LEVEL))&&Y[sh]<(0.85*High-(img_w+img_w*damag[sh]/LEVEL)))
        {
        tetha[sh]*=-1;
        Y[sh]-=5;
        if(fire&&roof)
        {
            LEVEL++;
            m_img=IMG_LoadTexture(m_renderer,IMG_address_ba[player[pler].play[pl].ball]);
            Mix_Pause(1);
            fire=false;
        }
        roof=false;
        }
}
    if(tedad==1)DAMAGE=damag[0];
    if(DAMAGE==0||(sum_whole_sqr_stre==0))
    {
        for(int j=8*(min(LEVEL,8));j>=0;j--)
        {
            player[pler].play[pl].square[j+8].strength=player[pler].play[pl].square[j].strength;
        }
        for(int j=0;j<8;j++)
            if(d_level==5)
            player[pler].play[pl].square[j].strength=abs(min(rand()%(LEVEL+1),rand()%(LEVEL+1))-min(rand()%(LEVEL+1),rand()%(LEVEL+1)));
                else player[pler].play[pl].square[j].strength=(rand()%(LEVEL+1));
        LEVEL++;
        levelup=true;
        if(sum_whole_sqr_stre!=0)DAMAGE=LEVEL;
        damag[0]=DAMAGE;
        shoot=false;
        step[1]=0;
        step[2]=0;
        X[1]=Wid;
        X[2]=Wid;
        Y[1]=0;
        Y[2]=0;
        tedad=1;
        if(LEVEL%d_level==0)
            {
                m_img=IMG_LoadTexture(m_renderer,IMG_address_ba[4]);
                fire=true;
                Mix_PlayChannel(1,fireM,0);
                bomby=false;
                roof=false;
            }
        else
            {
                m_img=IMG_LoadTexture(m_renderer,IMG_address_ba[player[pler].play[pl].ball]);
                Mix_Pause(1);
                fire=false;
                bomby=false;
            }
    }
    SDL_RenderCopy(m_renderer, backg_img, NULL, &img_backg);
        for(int sq=0;sq<8*(min(LEVEL,8));sq++)
            {int stre=player[pler].play[pl].square[sq].strength;
                if(stre>0)
                {int l3=LEVEL/3;
                    if(stre<=l3){
                        img_brick1.x=player[pler].play[pl].square[sq].x;
                        img_brick1.y=player[pler].play[pl].square[sq].y;
                        SDL_RenderCopy(m_renderer, brick1_img, NULL, &img_brick1);
                    }
                    else{ if(stre>l3&&stre<=2*l3){
                        img_brick2.x=player[pler].play[pl].square[sq].x;
                        img_brick2.y=player[pler].play[pl].square[sq].y;
                        SDL_RenderCopy(m_renderer, brick2_img, NULL, &img_brick2);
                    }
                    else if(stre>2*l3){
                        img_brick3.x=player[pler].play[pl].square[sq].x;
                        img_brick3.y=player[pler].play[pl].square[sq].y;
                        SDL_RenderCopy(m_renderer, brick3_img, NULL, &img_brick3);
                    }
                }}
            }
        SDL_RenderCopy(m_renderer, board_img, NULL, &img_board);
    for(int sh=0;sh<tedad;sh++)
    {
        X[sh] +=step[sh]*cos(tetha[sh]);
        Y[sh] -=step[sh]*sin(tetha[sh]);
        img_rect.x=X[sh];
        img_rect.y=Y[sh];
        if(fire)
        {
        img_rect.h=img_w;
        img_rect.w=img_rect.h;
        }
        else{
        img_rect.h=img_w+img_w*damag[sh]/LEVEL;
        img_rect.w=img_rect.h;
        }
        SDL_RenderCopy(m_renderer, ball3_img, NULL, &img_3ball);
        SDL_RenderCopy(m_renderer, m_img, NULL, &img_rect);
    }
        SDL_RenderPresent( m_renderer );SDL_Delay(8);
    }

}
    SDL_Delay(800);
    SDL_DestroyRenderer( m_renderer );
	IMG_Quit();
	SDL_Quit();
    return 0;

}

void rect(SDL_Renderer *m_renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{
    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_SetRenderDrawColor(m_renderer, R, G, B ,255);
    if (fill_boolian==1)
        SDL_RenderFillRect(m_renderer, &rectangle);
    SDL_RenderDrawRect(m_renderer, &rectangle);

}
