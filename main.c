// Multitap test for FC
// by Takuya Mastubara
#include "pattern.h"   // 
#include "fcsub.h"     // 

void sp1_remove(char i);
char sp1_append(char x,char y,char tile,char attr);
void sp1_chr(char num,unsigned char tile,unsigned char attr);
void sp1_ofs(char num,unsigned char x,unsigned  char y);

const char colortable[] = {
    C_BLACK ,C_BLUE ,C_RED ,C_WHITE,  // BG palette 0
    C_BLACK ,C_BLUE ,C_RED ,C_WHITE,
    C_BLACK ,C_BLUE ,C_RED ,C_WHITE,
    C_BLACK ,C_BLUE ,C_RED ,C_WHITE,
    C_BLACK ,C_BLUE ,C_RED ,C_WHITE,  // SP palette 0
    C_BLACK ,C_GREEN,C_RED ,C_YELLOW,
    C_BLACK ,C_BLUE ,C_RED ,C_WHITE,
    C_BLACK ,C_BLUE ,C_RED ,C_WHITE
};

const unsigned char btnname[11][13] = {
  "FC MULTITAP",
  "-----------",
  "1 GAMEPAD1:",
  "2 GAMEPAD2:",
  "3 TAP P1:",
  "4 TAP P2:",
  "5 TAP P3:",
  "6 TAP P4:",
  "ID1:",
  "ID2:"
};

unsigned char button[8];
#define JOY_D0 (1<<0)
#define JOY_D1 (1<<1)

#define PLAYER1  0
#define PLAYER2  1
#define PLAYER3  2
#define PLAYER4  3
#define PLAYER5  4
#define PLAYER6  5
#define TAPID1   6
#define TAPID2   7

//---- NES Multitapから入力  *未使用
void multitap_nes(void)
{
    unsigned char tmp1;
    unsigned char tmp2;
    char i;
    JOYPAD1 = 0x01;    // load
    JOYPAD1 = 0x01;    // wait
    JOYPAD1 = 0x00;    // latch
    for(i=0; i<8; i++){
        tmp1 <<= 1;
        if( JOYPAD1 & JOY_D0 ) tmp1 |= 1;  // ボタン
        tmp2 <<= 1;
        if( JOYPAD2 & JOY_D0 ) tmp2 |= 1;  // ボタン
    }
    button[PLAYER1] = tmp1;
    button[PLAYER2] = tmp2;
    for(i=0; i<8; i++){
        tmp1 <<= 1;
        if( JOYPAD1 & JOY_D0 ) tmp1 |= 1;  // ボタン
        tmp2 <<= 1;
        if( JOYPAD2 & JOY_D0 ) tmp2 |= 1;  // ボタン
    }
    button[PLAYER3] = tmp1;
    button[PLAYER4] = tmp2;
    for(i=0; i<8; i++){
        tmp1 <<= 1;
        if( JOYPAD1 & JOY_D0 ) tmp1 |= 1;  // ID
        tmp2 <<= 1;
        if( JOYPAD2 & JOY_D0 ) tmp2 |= 1;  // ID
    }
    button[TAPID1] = tmp1;
    button[TAPID2] = tmp2;
}

//---- ファミコン拡張端子 Multitapから入力
void multitap_fc(void)
{
    unsigned char tmp1;
    unsigned char tmp2;
    unsigned char tmp3;
    unsigned char tmp4;
    unsigned char tempdata;
    char i;
    JOYPAD1 = 0x01;    // load
    JOYPAD1 = 0x01;    // wait
    JOYPAD1 = 0x00;    // latch
    for(i=0; i<8; i++){
        tmp1 <<= 1;
        tmp3 <<= 1;
        tempdata = JOYPAD1;
        if( tempdata & JOY_D0 ) tmp1 |= 1;  // ボタン
        if( tempdata & JOY_D1 ) tmp3 |= 1;  // ボタン
        tmp2 <<= 1;
        tmp4 <<= 1;
        tempdata = JOYPAD2;
        if( tempdata & JOY_D0 ) tmp2 |= 1;  // ボタン
        if( tempdata & JOY_D1 ) tmp4 |= 1;  // ボタン
    }
    button[PLAYER1] = tmp1;
    button[PLAYER2] = tmp2;
    button[PLAYER3] = tmp3;
    button[PLAYER4] = tmp4;
    for(i=0; i<8; i++){
        tmp1 <<= 1;
        if( JOYPAD1 & JOY_D1 ) tmp1 |= 1;  // ボタン
        tmp2 <<= 1;
        if( JOYPAD2 & JOY_D1 ) tmp2 |= 1;  // ボタン
    }
    button[PLAYER5] = tmp1;
    button[PLAYER6] = tmp2;
    for(i=0; i<8; i++){
        tmp1 <<= 1;
        if( JOYPAD1 & JOY_D1 ) tmp1 |= 1;  // ID
        tmp2 <<= 1;
        if( JOYPAD2 & JOY_D1 ) tmp2 |= 1;  // ID
    }
    button[TAPID1] = tmp1;
    button[TAPID2] = tmp2;
}

//---- スプライト1個 消去(スプライト番号0～63)
void sp1_remove(char i)
{
    sp1_ofs(i,OUTSIDE,OUTSIDE);    // スプライトを画面外に
}

//---- スプライト1個 追加(X座標,Y座標,タイル0～255,アトリビュート0～255)
char sp1_append(char x,char y,char tile,char attr)
{
    char i;
    for(i=0; i<64; i++){
        if(sp_gety(i)==OUTSIDE)break;
    }
    if(i==64) return(255);
    sp1_ofs(i, x,y);
    sp1_chr(i, tile,attr);
    return(i);
}

//---- スプライト1個 表示変更(番号0～63,タイル0～255,アトリビュート0～255)
void sp1_chr(char num,unsigned char tile,unsigned char attr)
{
    unsigned char *ptr;
    ptr = (unsigned char *)SPWADDR+(num*4); // スプライトワーク
    ptr[1] = tile;    // スプライト タイル番号
    ptr[2] = attr;    // スプライト アトリビュート
}

//---- スプライト1個 アニメ変更(スプライトnum0～63)
void sp1_anime(char num)
{
    unsigned char *ptr;
    ptr = (unsigned char *)SPWADDR+(num*4); // スプライトワーク
    ptr[1] ^= 1;   // スプライト タイル番号
}

//---- スプライト1個 座標変更(スプライトnum0～63,X座標0～255,Y座標0～255)
void sp1_ofs(char num,unsigned char x,unsigned  char y)
{
    unsigned char *ptr;
    ptr = (unsigned char *)SPWADDR+(num*4); // スプライトワーク
    ptr[0] = y;       // スプライト Y座標
    ptr[3] = x;       // スプライト X座標
}

//---- 移動量
const signed char x1[4] = { 0, 1, 0,-1};
const signed char y1[4] = {-1, 0, 1, 0};

#define VFLIP (1<<7)

//---- メイン関数
char NesMain()
{
    char i,loopcnt,dir;
    char tempstr[3];
    char x,y,tempbtn;

    fc_init(); // 全機能の初期化
    ppu_pattern((unsigned char *)pattern,0,512);   // パターン設定
    ppu_palette((char *)colortable,0,8);           // パレット設定

    for(i=0; ;i++){
        if(btnname[i][0]==0)break;
        bg_printstr(2,2+i,(char *)btnname[i]);
    }

    for(i=0; i<6 ;i++){
        x = (i*24)+64;
        y = 120;
        sp1_ofs(i,x,y);
        sp1_chr(i,128,0);    // human
        sp1_ofs(i+6,x,y-8);
        sp1_chr(i+6,225+i,1);  // number
    }

    ppu_enable(1);  // 画面表示を有効化
    ppu_vsync();    // V blank待ち

    while (1){
        multitap_fc();  // マルチタップ入力
        for(i=0; i<6; i++){
            tempbtn = button[i];
            if((tempbtn==0xff)||(tempbtn==0))continue;
            dir = 255;
            if(tempbtn & BUTTON_UP   ) dir=0;
            if(tempbtn & BUTTON_RIGHT) dir=1;
            if(tempbtn & BUTTON_DOWN ) dir=2;
            if(tempbtn & BUTTON_LEFT ) dir=3;
            if(dir == 255) continue;
            x = sp_getx(i);
            y = sp_gety(i);
            x += x1[dir];
            y += y1[dir];
            sp1_ofs(i,x,y);	 // human
            sp1_chr(i,128+(dir*2)+(loopcnt>>2),0);
            sp1_ofs(i+6,x,y-8);	 // number
        }
        loopcnt = (loopcnt+1) & 7;
        num_to_hex(tempstr,button[loopcnt]); // ボタンの状態

        ppu_vsync();  // V blank
        sp_dmastart();
        bg_printstr(14,4+loopcnt,tempstr);
        bg_scroll(0,0);  // BGスクロール
    }
    return 0;
}
