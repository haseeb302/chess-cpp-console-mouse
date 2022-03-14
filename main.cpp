#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <math.h>
//#include<stdio.h>
//#include<graphics.h>

using namespace std;
int black=0,white=1;

//HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
void getRowColbyLeftClick(int &rpos,int &cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if(InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = (InputRecord.Event.MouseEvent.dwMousePosition.X)/10;
            rpos = (InputRecord.Event.MouseEvent.dwMousePosition.Y)/10;
            break;
        }
    }
    while(true);
}
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
void gotoRowCol(int rpos, int cpos)
{
    int xpos=cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}
void copyy(char c[][8],char b[][8])
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            c[i][j]=b[i][j];
        }
    }
}
void printboxes(int sc,int se,int rdim,int cdim,char s)
{
    for(int ri=0; ri<rdim; ri++)
    {
        for(int ci=0; ci<cdim; ci++)
        {
            if(ri==0 || ri==rdim-1 || ci==0 || ci==cdim-1)
            {
//                 bar(150, 200, 400, 350);
                gotoRowCol(se+ci,sc+ri);
                cout<<s;
            }
        }
    }
}
void init(char b[][8],int & turn)
{
    turn=0;
    b[0][0]=b[0][7]='R';
    b[0][1]=b[0][6]='H';
    b[0][2]=b[0][5]='B';
    b[0][3]='Q';
    b[0][4]='K';
    b[7][0]=b[7][7]='r';
    b[7][1]=b[7][6]='h';
    b[7][2]=b[7][5]='b';
    b[7][3]='q';
    b[7][4]='k';
    for(int i=0; i<8; i++)
    {
        b[1][i]='P';
        b[6][i]='p';
    }
    for(int r=2; r<6; r++)
    {
        for(int c=0; c<8; c++)
        {
            b[r][c]='-';
        }
    }
}
bool Isblack(char s)
{
    if(s>='A' && s<='Z')
        return true;

    else
        return false;
}
bool Iswhite(char s)
{
    if(s>='a' && s<='z')
        return true;

    else
        return false;
}
void nofbox(int BN,int rdim,int cdim,char s)
{
    int ri=(BN-1)/8 * rdim;
    int ci=(BN-1)%8 * cdim;

    printboxes(ri,ci,rdim,cdim,s);
}
void rookprint(int ri,int ci,int rdim,int cdim)
{
    ri=ri*rdim+rdim/2;
    ci=ci*cdim+cdim/2-1;

    gotoRowCol(ri-2,ci);
    cout<<"#**#";
    gotoRowCol(ri-1,ci);
    cout<<" ** ";
    gotoRowCol(ri,ci);
    cout<<" ** ";
    gotoRowCol(ri+1,ci);
    cout<<"****";
}
void horseprint(int ri,int ci,int rdim,int cdim)
{
    ri=ri*rdim+rdim/2;
    ci=ci*cdim+cdim/2-1;
//    gotoRowCol(ri,ci);
    gotoRowCol(ri-2,ci-1);
    cout<<" ** ";
    gotoRowCol(ri-1,ci-3);
    cout<<" *****";
    gotoRowCol(ri,ci-2);
    cout<<" ****";
    gotoRowCol(ri+1,ci-1);
    cout<<" ***";
    gotoRowCol(ri+2,ci-1);
    cout<<"****";

}
void bishopprint(int ri,int ci,int rdim,int cdim)
{
    ri=ri*rdim+rdim/2;
    ci=ci*cdim+cdim/2-1;

    gotoRowCol(ri-3,ci-1);
    cout<<"  O";
    gotoRowCol(ri-2,ci-1);
    cout<<"/___\\";
    gotoRowCol(ri-1,ci-1);
    cout<<"(___)";
    gotoRowCol(ri,ci-1);
    cout<<" (_)";
    gotoRowCol(ri+1,ci-1);
    cout<<" (_)";
}
void queenprint(int ri,int ci,int rdim,int cdim)
{
    ri=ri* rdim+rdim/2;
    ci=ci* cdim+cdim/2-1;

    gotoRowCol(ri-3,ci);
    cout<<"^^";
    gotoRowCol(ri-2,ci-1);
    cout<<"<__>";
    gotoRowCol(ri-1,ci-1);
    cout<<"<__>";
    gotoRowCol(ri,ci-1);
    cout<<"<__>";
    gotoRowCol(ri+1,ci-1);
    cout<<"{  }";
    gotoRowCol(ri+2,ci-2);
    cout<<"{____}";

}
void kingprint(int ri,int ci,int rdim,int cdim)
{
    ri=ri* rdim+rdim/2;
    ci=ci* cdim+cdim/2-1;

    gotoRowCol(ri-3,ci);
    cout<<"**";
    gotoRowCol(ri-2,ci-2);
    cout<<" {__}";
    gotoRowCol(ri-1,ci-2);
    cout<<"{____}";
    gotoRowCol(ri,ci-2);
    cout<<" {__}";
    gotoRowCol(ri+1,ci-1);
    cout<<"{__}";
    gotoRowCol(ri+2,ci-2);
    cout<<"{____}";
}
void pawnsprint(int ri,int ci,int rdim,int cdim)
{
    ri=ri* rdim+rdim/2;
    ci=ci* cdim+cdim/2-1;

    gotoRowCol(ri-2,ci);
    cout<<" O";
    gotoRowCol(ri-1,ci);
    cout<<"( )";
    gotoRowCol(ri,ci);
    cout<<"( )";
    gotoRowCol(ri+1,ci-1);
    cout<<"(___)";
}
void rookremove(int ri,int ci,int rdim,int cdim)
{
    ri=ri*rdim+rdim/2;
    ci=ci*cdim+cdim/2-1;

    gotoRowCol(ri-2,ci);
    cout<<"    ";
    gotoRowCol(ri-1,ci);
    cout<<"    ";
    gotoRowCol(ri,ci);
    cout<<"    ";
    gotoRowCol(ri+1,ci);
    cout<<"    ";
}
void horseremove(int ri,int ci,int rdim,int cdim)
{
    ri=ri*rdim+rdim/2;
    ci=ci*cdim+cdim/2-1;
//    gotoRowCol(ri,ci);
    gotoRowCol(ri-2,ci-1);
    cout<<"    ";
    gotoRowCol(ri-1,ci-3);
    cout<<"      ";
    gotoRowCol(ri,ci-2);
    cout<<"     ";
    gotoRowCol(ri+1,ci-1);
    cout<<"    ";
    gotoRowCol(ri+2,ci-1);
    cout<<"    ";

}
void bishopremove(int ri,int ci,int rdim,int cdim)
{
    ri=ri*rdim+rdim/2;
    ci=ci*cdim+cdim/2-1;

    gotoRowCol(ri-3,ci-1);
    cout<<"   ";
    gotoRowCol(ri-2,ci-1);
    cout<<"      ";
    gotoRowCol(ri-1,ci-1);
    cout<<"     ";
    gotoRowCol(ri,ci-1);
    cout<<"    ";
    gotoRowCol(ri+1,ci-1);
    cout<<"    ";
}
void queenremove(int ri,int ci,int rdim,int cdim)
{
    ri=ri* rdim+rdim/2;
    ci=ci* cdim+cdim/2-1;

    gotoRowCol(ri-3,ci);
    cout<<"  ";
    gotoRowCol(ri-2,ci-1);
    cout<<"    ";
    gotoRowCol(ri-1,ci-1);
    cout<<"    ";
    gotoRowCol(ri,ci-1);
    cout<<"    ";
    gotoRowCol(ri+1,ci-1);
    cout<<"    ";
    gotoRowCol(ri+2,ci-2);
    cout<<"      ";

}
void kingremove(int ri,int ci,int rdim,int cdim)
{
    ri=ri* rdim+rdim/2;
    ci=ci* cdim+cdim/2-1;

    gotoRowCol(ri-3,ci);
    cout<<"  ";
    gotoRowCol(ri-2,ci-2);
    cout<<"     ";
    gotoRowCol(ri-1,ci-2);
    cout<<"      ";
    gotoRowCol(ri,ci-2);
    cout<<"     ";
    gotoRowCol(ri+1,ci-1);
    cout<<"    ";
    gotoRowCol(ri+2,ci-2);
    cout<<"      ";
}
void pawnsremove(int ri,int ci,int rdim,int cdim)
{
    ri=ri* rdim+rdim/2;
    ci=ci* cdim+cdim/2-1;

    gotoRowCol(ri-2,ci);
    cout<<"  ";
    gotoRowCol(ri-1,ci);
    cout<<"   ";
    gotoRowCol(ri,ci);
    cout<<"   ";
    gotoRowCol(ri+1,ci-1);
    cout<<"     ";
}
void print(char b[][8],int rdim,int cdim)
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(b[i][j]=='R')
            {
                SetConsoleTextAttribute(h,15);
                rookprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='H')
            {
                SetConsoleTextAttribute(h,15);
                horseprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='B')
            {
                SetConsoleTextAttribute(h,15);
                bishopprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='Q')
            {
                SetConsoleTextAttribute(h,15);
                queenprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='K')
            {
                SetConsoleTextAttribute(h,15);
                kingprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='P')
            {
                SetConsoleTextAttribute(h,15);
                pawnsprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='r')
            {
                SetConsoleTextAttribute(h,3);
                rookprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='h')
            {
                SetConsoleTextAttribute(h,3);
                horseprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='b')
            {
                SetConsoleTextAttribute(h,3);
                bishopprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='q')
            {
                SetConsoleTextAttribute(h,3);
                queenprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='k')
            {
                SetConsoleTextAttribute(h,3);
                kingprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='p')
            {
                SetConsoleTextAttribute(h,3);
                pawnsprint(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
        }
    }
}

void removee(char b[][8],int rdim,int cdim)
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(b[i][j]=='R')
            {
                SetConsoleTextAttribute(h,15);
                rookremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='H')
            {
                SetConsoleTextAttribute(h,15);
                horseremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='B')
            {
                SetConsoleTextAttribute(h,15);
                bishopremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='Q')
            {
                SetConsoleTextAttribute(h,15);
                queenremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='K')
            {
                SetConsoleTextAttribute(h,15);
                kingremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='P')
            {
                SetConsoleTextAttribute(h,15);
                pawnsremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,15);
            }
            if(b[i][j]=='r')
            {
                SetConsoleTextAttribute(h,3);
                rookremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='h')
            {
                SetConsoleTextAttribute(h,3);
                horseremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='b')
            {
                SetConsoleTextAttribute(h,3);
                bishopremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='q')
            {
                SetConsoleTextAttribute(h,3);
                queenremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='k')
            {
                SetConsoleTextAttribute(h,3);
                kingremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
            if(b[i][j]=='p')
            {
                SetConsoleTextAttribute(h,3);
                pawnsremove(i,j,rdim,cdim);
                SetConsoleTextAttribute(h,3);
            }
        }
    }
}
void printbox(char b[][8],int rdim,int cdim,char s)
{
    for(int i=1; i<=64; i++)
    {
        SetConsoleTextAttribute(h,15);
        nofbox(i,rdim,cdim,s);
    }
}
void askforselection(int & sri,int & sci,int & turn)
{
    gotoRowCol(5,82);
    SetConsoleTextAttribute(h,15);
    cout<<"Player "<<turn+1<<" SELECT YOUR POSITION ";
    getRowColbyLeftClick(sri,sci);
//    cin>>sri>>sci;
//    sri--;
//    sci--;
}
void askfordest(int & dri,int & dci)
{
    gotoRowCol(7,82);
    SetConsoleTextAttribute(h,15);
    cout<<"SELECT DESTINATION POSITION ";
    getRowColbyLeftClick(dri,dci);
//    cin>>dri>>dci;
//    dri--;
//    dci--;
}
void makemove(char b[][8],int sri,int sci,int eri,int eci)
{
    b[eri][eci]=b[sri][sci];
    b[sri][sci]='-';
}
int turnchange(int & turn)
{
    turn=(turn+1)%2;
}
bool islegalselec(char b[][8],int & sri,int & sci,int & turn)
{
    if(sri<0 || sri>7 || sci<0 || sci>7)
    {
        return false;
    }
    char s=b[sri][sci];

    if(turn==black)
        return Isblack(s);

    if(turn==white)
        return Iswhite(s);
}
bool islegaldest(char b[][8],int & eri,int & eci,int & turn)
{
    if(eri<0 || eri>7 || eci<0 || eci>7)
    {
        return false;
    }
    char s=b[eri][eci];

    if(turn==black)
        return !(Isblack(s));
    if(turn==white)
        return !(Iswhite(s));
}
bool IsN2S(int sri,int sci,int eri,int eci)
{
    if(sci==eci)
        return true;

    else
        return false;
}
bool IsE2W(int sri,int sci,int eri,int eci)
{
    if(sri==eri)
        return true;

    else
        return false;
}
bool Islopy(int sri,int sci,int eri,int eci)
{
    int r=eri-sri;
    int c=eci-sci;

    if(r==c || r==-c)
        return true;

    else
        return false;
}
bool IsN2Sclear(char b[][8],int sri,int sci,int eri,int eci)
{
    int rs,re;
    if(sri<eri)
    {
        rs=sri+1;
        re=eri;
        for(int i=rs; i<re; i++)
        {
            if(b[i][sci]!='-')
            {
            return false;
            }
        }
        return true;
    }
    if(sri>eri)
    {

        rs=eri+1;
        re=sri;
        for(int i=rs; i<re; i++)
        {
            if(b[i][sci]!='-')
            {
            return false;
            }
        }
        return true;
    }

}
bool IsE2Wclear(char b[][8],int sri,int sci,int eri,int eci)
{
    int cs,ce;
    if(sci<eci)
    {
        cs=sci+1;
        ce=eci-1;
    }
    if(sci>eci)
    {
        cs=eci+1;
        ce=sci-1;
    }
    for(int i=cs; i<=ce; i++)
    {
        if(b[sri][i]!='-')
            return false;
    }
    return true;
}
bool IsSlopesclear(char b[][8],int sri,int sci,int eri,int eci)
{
    int r=eri-sri-1;
    int c=eci-sci-1;


        for(int i=1; i<=r; i++)
        {
            if(r>=0 && c>=0)
            {
                if(b[sri+i][sci+i]!='-')
                {
                    return false;
                }
            }
            if(r>=0 && c<=0)
            {
                if(b[sri+i][sci-i]!='-')
                {
                    return false;
                }
            }
            if(r<=0 && c<=0)
            {
                if(b[sri-i][sci-i]!='-')
                {
                    return false;
                }
            }
            if(r<=0 && c>=0)
            {
                if(b[sri-i][sci+i]!='-')
                {
                    return false;
                }
            }
        }
        return true;
}
bool Iskingmove(char b[][8],int sri,int sci,int eri,int eci)
{
    int r=eri-sri;
    int c=eci-sci;

    if(abs(r)==1 && abs(c)==0)
    {
        return true;
    }
    if(abs(r)==0 && abs(c)==1)
    {
        return true;
    }
    if(abs(r)==1 && abs(c)==1)
    {
        return true;
    }
    return false;
}
bool ispawnmove(char b[][8],int sri,int sci,int eri,int eci,int turn)
{
    if(turn==black)
    {
        if((sri==1 || sri==6) && sri<eri)
        {
            int r=abs(eri-sri);
            int c=abs(eci-sci);
            if((r==1 || r==2) && c==0)
            {
                return true;
            }
        }
        if((sri!=1 || sri!=6) && sri<eri)
        {
            int r=abs(eri-sri);
            int c=abs(eci-sci);
            if(r==1  && c==0)
            {
                return true;
            }
        }
    }

    if(turn==white)
    {
        if((sri==1 || sri==6) && sri>eri)
        {
            int r=abs(eri-sri);
            int c=abs(eci-sci);
            if((r==1 || r==2) && c==0)
            {
                return true;
            }
        }
        if((sri!=1 || sri!=6) && sri>eri)
        {
            int r=abs(eri-sri);
            int c=abs(eci-sci);
            if(r==1  && c==0)
            {
                return true;
            }
        }
    }
    return false;
}
bool ishorsemove(char b[][8],int sri,int sci,int eri,int eci)
{
    int r,c;
    r=abs(eri-sri);
    c=abs(eci-sci);
    return (r==1 && c==2) || (r==2 && c==1);
}
bool Isrookmove(char b[][8],int sri,int sci,int eri,int eci)
{
    if((IsN2S(sri,sci,eri,eci) && IsN2Sclear(b,sri,sci,eri,eci)) ||
            (IsE2W(sri,sci,eri,eci) && IsE2Wclear(b,sri,sci,eri,eci)))
    {
        return true;
    }
    return false;
}
bool Isbishopmove(char b[][8],int sri,int sci,int eri,int eci)
{
    if((Islopy(sri,sci,eri,eci) && IsSlopesclear(b,sri,sci,eri,eci)))
    {
        return true;
    }
    return false;
}
bool Isqueenmove(char b[][8],int sri,int sci,int eri,int eci)
{
    if((Isrookmove(b,sri,sci,eri,eci)) || (Isbishopmove(b,sri,sci,eri,eci)))
    {
        return true;
    }
    return false;
}
bool Islegalplay(char b[][8],int sri,int sci,int eri,int eci,int turn)
{
    switch(b[sri][sci])
    {
    case 'R':
    case 'r':
        Isrookmove(b,sri,sci,eri,eci);
        break;

    case 'B':
    case 'b':
        Isbishopmove(b,sri,sci,eri,eci);
        break;

    case 'Q':
    case 'q':
        Isqueenmove(b,sri,sci,eri,eci);
        break;

    case 'K':
    case 'k':
        Iskingmove(b,sri,sci,eri,eci);
        break;

    case 'H':
    case 'h':
        ishorsemove(b,sri,sci,eri,eci);
        break;

    case 'P':
    case 'p':
        ispawnmove(b,sri,sci,eri,eci,turn);
        break;
    }
}
void highlight(char c[][8],int sri,int sci,int turn,char b[][8])
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(Islegalplay(b,sri,sci,i,j,turn)==true)
            {
                if(islegaldest(b,i,j,turn)==true)
                {
                    c[i][j]='*';
                }
            }
        }
    }
}
void highlightprintandremove(char c[][8],int sri,int sci,int turn,int rdim,int cdim,char s)
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(c[i][j]=='*')
            {
                SetConsoleTextAttribute(h,2);
                printboxes(j*rdim+1,i*cdim+1,8,8,s);
            }
        }
    }
}
void newgame(char b[][8],int & turn)
{
    ifstream start("new.txt");
    start>>turn;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            start>>b[i][j];
        }
    }
}
void Savegame(char b[][8],int & turn,int sri,int sci)
{
    ofstream save("saveload.txt");
    save<<turn;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            save<<b[i][j];
        }
    }
}
void loadgame(char b[][8],int & turn,int sri,int sci)
{
    ifstream save("saveload.txt");
    save>>turn;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            save>>b[i][j];
        }
    }
}
void prinmenu()
{
    printboxes(100,40,15,15,'*');
    gotoRowCol(46,103);
    cout<<"NEW GAME";
    printboxes(115,40,15,15,'*');
    gotoRowCol(46,118);
    cout<<"SAVE GAME";
    printboxes(130,40,15,15,'*');
    gotoRowCol(46,133);
    cout<<"LOAD GAME";
    printboxes(145,40,15,15,'*');
    gotoRowCol(46,148);
    cout<<"UNDO MOVE";
}
void undo(char b[][8],int sri,int sci,int eri,int eci)
{
    b[sri][sci]=b[eri][eci];
    b[eri][eci]='-';
}
void NSL(char b[][8],int & turn,int sri,int sci,int eri,int eci)
{

    if((sri>=4 && sri<14) && sci==10)
    {
        system("cls");
        newgame(b,turn);
        printbox(b,10,10,'-');
        print(b,10,10);
        prinmenu();
    }
    if((sri>=4 && sri<14) && sci==11)
    {
        system("cls");
        gotoRowCol(12,85);
        cout<<"YOUR GAME IS SAVED SUCCESFULY";
        Savegame(b,turn,sri,sci);
        printbox(b,10,10,'-');
        print(b,10,10);
        prinmenu();
    }
    if((sri>=4 && sri<14) && sci==13)
    {
        system("cls");
        gotoRowCol(12,85);
        cout<<"YOUR GAME IS LOADED    ";
        loadgame(b,turn,sri,sci);
        printbox(b,10,10,'-');
        print(b,10,10);
        prinmenu();
    }
}
bool kingfind(char b[][8])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(b[i][j]=='k' || b[i][j]=='K')
                return true;
        }
    }
    return false;
}
bool check(char b[][8],int sri,int sci,int eri,int eci,int & turn)
{
     if(Iskingmove(b,sri,sci,eri,eci)==true)
     {

     }
}
int main()
{
//    getch();
//    int gd = DETECT,gm;
//    initgraph(&gd, &gm, "");
    int rows=100,cols=100,BN;
    int rdim=10,cdim=10,turn,sri,sci,eri,eci,i=0,j=0;
    char b[8][8],s,c[8][8];

    init(b,turn);
    printbox(b,rdim,cdim,'-');
    print(b,rdim,cdim);
    prinmenu();
    do
    {
        do
        {
            i=sri;
            j=sci;
            askforselection(sri,sci,turn);
            copyy(c,b);
            if(islegalselec(c,sri,sci,turn)==true)
            {
            highlight(c,sri,sci,turn,b);
            highlightprintandremove(c,sri,sci,turn,rdim,cdim,'*');
            gotoRowCol(12,85);
            cout<<"                             ";
            }
            if(islegalselec(c,sri,sci,turn)==false)
            {
                gotoRowCol(12,85);
                cout<<"INVALID SELECTION OF PLAYER       ";
            }
            NSL(b,turn,sri,sci,eri,eci);
            if((sri>=4 && sri<14) && sci==14)
            {
            system("cls");
            removee(b,rdim,cdim);
            undo(b,i,j,eri,eci);
            printbox(b,10,10,'-');
            print(b,10,10);
            prinmenu();
            turnchange(turn);
            }
        }
        while(islegalselec(b,sri,sci,turn)==false);
        do
        {
            askfordest(eri,eci);
            if(islegaldest(b,eri,eci,turn)==true)
            {
            highlightprintandremove(c,sri,sci,turn,rdim,cdim,' ');
            }
        }
        while(islegaldest(b,eri,eci,turn)==false);
        if(Islegalplay(b,sri,sci,eri,eci,turn)==true)
        {
            removee(b,rdim,cdim);
            makemove(b,sri,sci,eri,eci);
            print(b,rdim,cdim);
            turnchange(turn);
        }
        else
        {
            gotoRowCol(12,85);
            cout<<"                                      ";
            gotoRowCol(12,85);
            cout<<"INVALID MOVE OF PLAYER    ";
        }
}

    while(true);
//   closegraph();
    getch();
}

