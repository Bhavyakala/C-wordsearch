#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<iomanip.h>
union REGS in,out;
struct mouse
{
	int x,y,button;
};
mouse getcoordinates()  //function to get coordinates on mouse click
{
	in.x.ax=3;
	int86(51,&in,&out);
	mouse a;
	a.button=out.x.bx;
	a.x=out.x.cx;
	a.y=out.x.dx;
	return a;
}
void callmouse()   //function to call mouse
{
	in.x.ax=1;
	int86(51,&in,&out);
}
void restrictmouse(int x1, int y1, int x2, int y2)
{
	in.x.ax=7;
	in.x.cx=x1;
	in.x.dx=x2;
	int86(51,&in,&out);
	in.x.ax=8;
	in.x.cx=y1;
	in.x.dx=y2;
	int86(51,&in,&out);

}
void hidemouse()  //function to hide mouse
{
	in.x.ax=2;
	int86(51,&in,&out);
}
void frontpage() //function to display first screen
{
  cleardevice();
  setbkcolor(BLACK);
  setcolor(RED);
  rectangle(8,10,618,455);
  setcolor(WHITE);
  settextstyle(1,0,5);
  outtextxy(61,75, "WELCOME TO THE GAME ") ;
  settextstyle(1,0,9);
  setcolor(LIGHTGREEN);
  outtextxy(22,155,"WORDSEARCH");
  setcolor(WHITE);
  settextstyle(6,0,1);
  outtextxy(210,430,"Press Enter To Continue");
  getch();
}

void lastpage() //function to display last screen
{
  cleardevice();
  setbkcolor(BLACK);
  setcolor(RED);
  rectangle(8,10,618,455);
  setcolor(WHITE);
  settextstyle(1,0,5);
  outtextxy(200,145, "THANK YOU") ;
  outtextxy(61,220, "FOR PLAYING THIS GAME") ;
  getch();
}
class project
{
     char s[20][20],b[30];   //declaration of class data members
     int temp[8][8];
     int score,c,z;
 public:
     project();           //declaration of member functions
     void mainmenu();
     void playmenu();
     void help();
     void check(int,int,int,int);
     void qinput(char []);
     void convert(int,int,int &,int &);
     void color(int ,int,int,int);
     int retscore()
      { return score; }
};
project::project()     //constructor definition
{  score=0;  z=0;
   for(int i=0;i<8;i++)
   {
      for(int j=0;j<8;j++)
	  temp[i][j]=0;
   }

}
//function to check answer
void project::check(int r1, int r2,int c1 , int c2 )
{
    int i;
    char ch[20],ans[20]={NULL};
    if (r1==r2&&c1==c2)     //forming the selected string
     {
     }
    else if(r1==r2)
     {
       for(i=0;i<=(c2-c1);i++)
	{
	 ans[i]=s[r1][i+c1];
	}
     }
    else if(c1==c2)
     {
       for(i=0;i<=(r2-r1);i++)
	{
	 ans[i]=s[r1+i][c1];
	}
     }
    else if((r2-r1)==(c2-c1) && (r2-r1)>0)
     {
       for(i=0;i<=(r2-r1);i++)
	{
	 ans[i]=s[r1+i][c1+i];
	}
     }
    else if((r2-r1)==(c1-c2)&& (r1-r2)>0)
     {
       for(i=0;i<=(r1-r2);i++)
	{
	 ans[i]=s[r1-i][c1+i];
	}
     }
   c=0;
   fstream f(b,ios::in); //checking answer from file by comparing with string
   while(!f.eof())
     {
       f.getline ( ch , 20 ,'\n');
       if (strcmpi(ans,ch)==0)
	{
	  score++;
	  c=1;
	}
     }
   f.close();  //closing file
   if(c==1)
   {
      if(r1==r2)
      {
       for(i=0;i<=(c2-c1);i++)
	{
	 temp[r1][i]=1;
	}
      }
      else if(c1==c2)
      {
	for(i=0;i<=(r2-r1);i++)
	{
	   temp[i][c1]=1;
	}
      }
      else if((r2-r1)==(c2-c1) && (r2-r1)>0)
      {
       for(i=0;i<=(r2-r1);i++)
	{
	    temp[r1+i][c1+i]=1;
	}
      }
      else if((r2-r1)==(c1-c2)&& (r1-r2)>0)
      {
       for(i=0;i<=(r1-r2);i++)
	{
	    temp[r1-i][c1+i]=1;
	}
      }
   }
}
//function to highlight correct answer
void project::color(int r1,int r2, int c1,int c2)
{
   int i,j;
   char x[20]={NULL};
   if (c==1)       // condition for correct answers
   {
      setfillstyle(1,WHITE);
      floodfill(525,95+z*30,RED);
      z++;
      if (r1==r2&&c1==c2)
      {
	setfillstyle(1,BLUE);
	floodfill(205 + (c1)*31 , 105 + (r1)*31,RED);
      }
      else if(r1==r2)
      {
       for(i=0;i<=(c2-c1);i++)
	{
	  setfillstyle(1,BLUE);
	  floodfill(205 + (c1+i)*31 , 105 + (r1)*31,RED);
	  setcolor(LIGHTGREEN);
	  x[0]=s[r1][i+c1];
	  x[1]='\0';
	  outtextxy(210 + (c1+i)*(31.25), 105+ r1*(31.25),x);
	}
     }
    else if(c1==c2)
     {
       for(i=0;i<=(r2-r1);i++)
	{
	  setfillstyle(1,BLUE);
	  floodfill(205 + (c1)*31 , 105 + (r1+i)*31,RED);
	  setcolor(LIGHTGREEN);
	  x[0]=s[r1+i][c1];
	  x[1]='\0';
	  outtextxy(210 + (c1)*(31.25), 105+ (r1+i)*(31.25),x);

	}
     }
    else if((r2-r1)==(c2-c1) && (r2-r1)>0)
     {
       for(i=0;i<=(r2-r1);i++)
	{
	  setfillstyle(1,BLUE);
	  floodfill(205 + (c1+i)*31 , 105 + (r1+i)*31,RED);
	  setcolor(LIGHTGREEN);
	  x[0]=s[r1+i][c1+i];
	  x[1]='\0';
	  outtextxy(210 + (c1+i)*(31.25), 105+ (r1+i)*(31.25),x);
	}
     }
    else if((r2-r1)==(c1-c2)&& (r1-r2)>0)
     {
       for(i=0;i<=(r1-r2);i++)
	{
	  setfillstyle(1,BLUE);
	  floodfill(205 + (c1+i)*31 , 105 + (r1-i)*31,RED);
	  setcolor(LIGHTGREEN);
	  x[0]=s[r1-i][c1+i];
	  x[1]='\0';
	  outtextxy(210 + (c1+i)*(31.25), 105+ (r1-i)*(31.25),x);
	}
     }
   }
   else    //condition for wrong answer
   {
    if (r1==r2&&c1==c2)
      {
	setfillstyle(1,BLACK);
	floodfill(205 + (c1)*31 , 105 + (r1)*31,RED);
      }
    else if(r1==r2)
     {
       for(i=0;i<=(c2-c1);i++)
	{
	  int k=temp[r1][c1+i];
	  setfillstyle(1,k);
	  floodfill(205 + (c1+i)*31 , 105 + (r1)*31,RED);
	  setcolor(LIGHTGREEN);
	  x[0]=s[r1][i+c1];
	  x[1]='\0';
	  outtextxy(210 + (c1+i)*(31.25), 105+ r1*(31.25),x);

	}
     }
    else if(c1==c2)
     {
       for(i=0;i<=(r2-r1);i++)
	{
	  int k=temp[r1+i][c1];
	  setfillstyle(1,k);
	  floodfill(205 + (c1)*31 , 105 + (r1+i)*31,RED);
	  setcolor(LIGHTGREEN);
	  x[0]=s[r1+i][c1];
	  x[1]='\0';
	  outtextxy(210 + (c1)*(31.25), 105+ (r1+i)*(31.25),x);

	}
     }
    else if((r2-r1)==(c2-c1) && (r2-r1)>0)
     {
       for(i=0;i<=(r2-r1);i++)
	{
	  int k=temp[r1+i][c1+i];
	  setfillstyle(1,k);
	  floodfill(205 + (c1+i)*31 , 105 + (r1+i)*31,RED);
	  setcolor(LIGHTGREEN);
	  x[0]=s[r1+i][c1+i];
	  x[1]='\0';
	  outtextxy(210 + (c1+i)*(31.25), 105+ (r1+i)*(31.25),x);
	}
     }
    else if((r2-r1)==(c1-c2)&& (r1-r2)>0)
     {
       for(i=0;i<=(r1-r2);i++)
	{
	  int k=temp[r1-i][c1+i];
	  setfillstyle(1,k);
	  floodfill(205 + (c1+i)*31 , 105 + (r1-i)*31,RED);
	  setcolor(LIGHTGREEN);
	  x[0]=s[r1-i][c1+i];
	  x[1]='\0';
	  outtextxy(210 + (c1+i)*(31.25), 105+ (r1-i)*(31.25),x);
	}
     }
   }
}
//function to convert click into coordinates of 2-d array
void  project::convert(int x,int y, int &r,int &c)
{
   int i;
   for(i=0; i<9; i++)
    {
      if( x >= (200+i*31.5 ) && x <= (200+30.5+i*31.5) )
       c=i;
      if( y >= (95+i*31.5 ) && y <= (95+30.5+i*31.5) )
       r=i;
    }
}
//function to read and display grid
void project::qinput(char a[])
{
   cleardevice();
   setcolor(RED) ;
   setbkcolor(BLACK);
   int  i=0,j ;
   char ch[20],x[20];
   fstream f(a,ios::in);
   while(!f.eof())           //reading from file
    {
      f.getline ( ch , 20 ,'\n');
      strcpy(s[i],ch);
      i++;
    }
   for(i=0; i<=250 ; i=i+(31.25))  //loop to from grid
    {
      line(200,95+i,450,95 + i);
      line(200 + i,95, 200 +i,345);
    }
   for(i=0;i<7;i++)
    {
      circle(525,95+i*30,6);
    }
   setcolor(LIGHTGREEN);
   for (i=0; i<9; i++)     //loop to display question
    {
       for (j=0;j<9; j++)
	{
	  x[0]=s[i][j];
	  x[1]='\0';
	  outtextxy(210 + j*(31.25), 105+ i*(31.25), x);
	}
    }
   setcolor(WHITE);
   outtextxy(525,370,"EXIT");
   if(strcmp(a,"csproj//qcolors.txt")==0)
     {   outtextxy(270,30,"COLORS"); }
   else if(strcmp(a,"csproj//qanim.txt")==0)
     {   outtextxy(270,30,"ANIMALS"); }
   else if(strcmp(a,"csproj//qcount.txt")==0)
     {   outtextxy(270,30,"COUNTRIES"); }
   else if(strcmp(a,"csproj//qprof.txt")==0)
     {   outtextxy(270,30,"PROFFESIONS"); }
   else if(strcmp(a,"csproj//qcomp.txt")==0)
     {   outtextxy(270,30,"COMPANIES"); }
}
//function to display instructions
void project::help()
{
   cleardevice();
   setbkcolor(BLACK);
   outtextxy(50,50, "INSTRUCTIONS");
   outtextxy(50,100, " HOW TO PLAY: ");
   setcolor(WHITE);
   outtextxy(50,150, "1.This is a wordsearch, you have to find words related to the category");
   outtextxy(50,200, "2.After each mouse click you have to press enter key\n ");
   setcolor(LIGHTRED);
   outtextxy(50,250, "3.select the category you want to play here " );
   setcolor(GREEN);
   outtextxy(50,300, "click here to go to main menu");
   l: callmouse();
   mouse a;
   a.button=0;
   while(!kbhit())
    {
      a.button=0;
      a=getcoordinates();
      if(a.button==1)   //conditions to call different functions
       {
	  hidemouse();
	  getch();
	  if (a.x>=50 && a.x<=400 && a.y>=225 && a.y<=260)
	    {
	       playmenu();   break;
	    }
	  else if (a.x>=50 && a.x<=400 && a.y>=280 && a.y<=320)
	    {
	      mainmenu();  break;
	    }
	  else
	    {
	      goto l;
	    }
	  break;
       }
    }
}
//program to display mainmenu
void project::mainmenu()
{
   cleardevice();
   setcolor(WHITE);
   setbkcolor(BLACK);
   outtextxy(270,30,"WORD SEARCH");
   setcolor(RED);
   outtextxy(100,75,  "1.PLAY MENU");
   outtextxy(100,125, "2.INSTRUCTIONS ");
   outtextxy(100,175, "3.EXIT" );
   l: callmouse();
   mouse a;
   a.button=0;
   while(!kbhit())
    {
      a=getcoordinates();
      if(a.button==1)      //conditions to call different functions
       {
	 hidemouse();
	 getch();
	 if (a.x>=100 && a.x<=400 && a.y>=50 && a.y<=100)
	   {
	     playmenu();  break;
	   }
	 else if (a.x>=100 && a.x<=400 && a.y>=101 && a.y<=150)
	   {
	     help();  break;
	   }
	 else if (a.x>=100 && a.x<=400 && a.y>=151 && a.y<=200)
	   {
	     exit(0);
	   }
	 else
	   {
	      goto l;
	   }
	 break;
       }
    }
}
//function to display mainmenu
void project::playmenu()
{
   char file_name[100];
   cleardevice();
   setcolor(WHITE);
   setbkcolor(BLACK);
   outtextxy(270,30,"PLAYMENU");
   setcolor(RED);
   outtextxy(100,50,  "1.colors");
   outtextxy(100,100, "2.animals");
   outtextxy(100,150, "3.countries" );
   outtextxy(100,200, "4.professions");
   outtextxy(100,250, "5.companies");
   setcolor(GREEN);
   outtextxy(100,300, "Go Back");
   l: callmouse();
   mouse a;
   a.button=0;
   while(!kbhit())
    {
      a=getcoordinates();
      if(a.button==1)      //conditions to call different functions
      {
	hidemouse();
	getch();
	if (a.x>=100 && a.x<=400 && a.y>=25 && a.y<=75)
	 {
	   strcpy(file_name,"csproj//qcolors.txt");
	   strcpy(b,"csproj//acolors.txt");
	   qinput(file_name);//call to qinput function and passing file name
	 }
	else if (a.x>=100 && a.x<=400 && a.y>=76 && a.y<=125)
	 {
	   strcpy(file_name,"csproj//qanim.txt");
	   strcpy(b,"csproj//aanim.txt");
	   qinput(file_name);//call to qinput function and passing file name
	 }
	else if (a.x>=100 && a.x<=400 && a.y>=126 && a.y<=175)
	 {
	   strcpy(file_name,"csproj//qcount.txt");
	   strcpy(b,"csproj//acount.txt");
	   qinput(file_name);//call to qinput function and passing file name
	 }
	else if (a.x>=100 && a.x<=400 && a.y>=176 && a.y<=225)
	 {
	   strcpy(file_name,"csproj//qprof.txt");
	   strcpy(b,"csproj//aprof.txt");
	   qinput(file_name);//call to qinput function and passing file name
	 }
	else if (a.x>=100 && a.x<=400 && a.y>=226 && a.y<=275)
	 {
	   strcpy(file_name,"csproj//qcomp.txt");
	   strcpy(b,"csproj//acomp.txt");
	   qinput(file_name);//call to qinput function and passing file name
	 }
	else if (a.x>=100 && a.x<=400 && a.y>=276 && a.y<=325)
	 {
	   mainmenu();
	 }
	else
	 {
	   goto l;
	 }
	break;
      }
    }
}
//main function
void main()
{
   project p1;    //declaration of class object
   int r1,r2,c1,c2,score=0;
   int gd=DETECT,gm,i;
   initgraph(&gd,&gm,"x:\\bgi");
   cleardevice();
   setbkcolor(BLACK);
   char m='k';
   char temp[3];
   temp[0]=m;
   temp[1]='\0';
   frontpage();
   settextstyle(0,0,1);
   p1.mainmenu();
   do                 //loop on mouse click
   {
    l: callmouse();
    mouse a;
    a.button=0;
    while(!kbhit())
     {
       a=getcoordinates();
       if(a.button==1)
	 {
	   if (a.x>=525 && a.x<=540 && a.y>=370 && a.y<=380)
	    {
	      exit(0);   break;
	    }
	    else if (a.x<=190 || a.x>=495 || a.y<=95 || a.y>=340)
	    {
	       getch();
	       hidemouse();
	       goto l;
	    }
	   getch();
	   break;
	 }
     }
    hidemouse();
    setfillstyle(1,YELLOW);   //changing color of selected box
    floodfill(a.x,a.y,RED);
    p1.convert(a.x,a.y,r1,c1); //call to convert function
    callmouse();
    while(!kbhit())
     {
       a=getcoordinates();
       if(a.button==1)
	{
	  if (a.x>=525 && a.x<=540 && a.y>=370 && a.y<=380)
	    {
	      exit(0);   break;
	    }
	  getch();
	  break;
	}
     }
    hidemouse();
    p1.convert(a.x,a.y,r2,c2); //call to convert function
    setfillstyle(1,YELLOW); //changing color of selected box
    floodfill(a.x,a.y,RED);
    char score1[7] ;
    itoa(score,score1,10);
    setcolor(BLACK);
    outtextxy(300,400,"score");
    outtextxy(350,400,score1);
    p1.check(r1,r2,c1,c2); //call to check function
    p1.color(r1,r2,c1,c2); //call to color function
    score=p1.retscore();  //call to retscore function
    itoa(score,score1,10);
    setcolor(RED);
    outtextxy(300,400,"score");
    outtextxy(350,400,score1);
   }while(score!=7);
   getch();
   lastpage();
   closegraph();
}
