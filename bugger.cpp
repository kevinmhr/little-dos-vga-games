// dragchase by keyvan mehrbakhsh 2022
// try too shoot before the red stick below gets to the yellow sign.


#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NUM_COLORS 256

#define SET_MODE 0x00
#define VIDEO_INT 0x10
#define VGA_256_COLOR_MODE 0x13
#define TEXT_MODE 0x03
int xscroll;
int yscroll;
int height= 320;
int width= 200;
int ff();
#define PALETTE_INDEX 0x3C8
#define PALETTE_DATA 0x3C9

typedef unsigned char byte;

byte far *VGA=(byte far *)0xA0000000L;
int x=150;
int  y=150;
#define SETPIX(x,y,c) *(VGA+(x)+(y)+height)=c
#define GETPIX(x,y,c) *(VGA+(x)+(y)*height)=c
#define TARGPIX(targx,targy,c) *(VGA+(targx)+(targy)*320)=c
#define BULLETPIX(targx,targy,c) *(VGA+(targx)+(targy)*320)=c

//#define MAX(x,y) ((x) > (y) ? (x) : (y))
//#define MIN(x,y) ((x) < (y) ? (x) : (y))
  int i,k,l,c,o,z,p,s,move;
  int xtrig[]={2,4,6,8};
  int ytrig[]={2,4,6,8};
  int r,flat;
  int ol=0;
int sc=1;

int targx,bullx;
int targy,bully,tempy;
int null=100;
int key,cari,carp;
int re=-10;
int co=1;
int tri=0;
void set_mode(byte mode)
{
   union REGS regs;
  regs.h.ah = SET_MODE;
  regs.h.al = mode;
  int86( VIDEO_INT, &regs, &regs );
}

int ballx[]={1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6,7,7,7,7,7,8,8,8,8,8};
int bally[]={1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5.1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5};
//int charax[]={1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4};
//int charay[]={2,3,3,4,5,5,6,4,9,9,1,1,1,4,5,6,7,7,7,7,1,1,1,4,5,6,7,7,7,7,2,3,3,5,5,6,4,4,9,9,};
int car[]={1,3,1,4,1,5,1,6,2,3,2,4,2,5,2,6,2,7,3,3
	   ,3,6,3,7,4,3,4,6,4,7,5,3,5,6,5,7,6,3,6,6,
	   6,7,7,3,7,4,7,5,7,6,8,3,8,4,8,5,8,6,9,3,
	    9,4,9,5,9,6,10,3,10,4,10,5,10,6,11,3,11,4,11,5};


int charax[]={1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,

	     4,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,
	     1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,

	     4,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,


	      1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
	       1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
		1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
	       1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};





	     int charay[]={1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,

	     4,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,
	     1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,

	     4,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,


	      1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
	       1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
		1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,
	       1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};


int chaax[]={1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6,7,7,7,7,7,8,8,8,8,8};
int chaay[]={1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5.1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5};




int chix[]={1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4};
int chiy[]={1,2,3,3,3,3,5,5,9,9,1,1,3,4,5,6,7,7,9,9,1,1,3,4,5,6,7,7,9,9,1,2,3,3,3,3,5,5,9,9,};

int location[]={10,90,30,60,20,70};



int iconx[]={1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4
	     , 1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};

int icony[]={4,4,4,4,4,1,1,1,1,1,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,1,1,1,1,1,4,4,4,4,4
	      ,	1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};









int charac[]={3,3,3,3,3,3,3,3,3,3,4,2,2,2,2,2,2,2,2,4,4,2,2,2,2,2,2,2,2,4,3,3,3,3,3,3,3,3,3,3};
void put_pixels(){

 union REGS regs;
  regs.h.ah = 0x0c;
  regs.h.al = 4;
  regs.x.cx = x;
  regs.x.dx = y;
  int86( VIDEO_INT, &regs, &regs );



}



void snd()
{
  int snu;
   for (snu=5000;snu<5000+sc*100;snu++){

   sound(snu);
   // delay(1);
   co=co+1;
 }

}
void default_scene_bg()
		       {
	     for (int cari=0;cari<80;cari++){
	   for (int t=0;t<640;t++){


	     // GETPIX(car[(t+x)/30]+icony[(t+x)/30]+100,car[(t+y)/30]+icony[(t+y)/30]+100,iconx[1+t]);


	      GETPIX(charax[(t+x)/3]+charay[(t+x)/3]+10,charax[(t+y)/3]+charay[(t+y)/3]+10,charax[1+t]);

			      }
				   }

}


void default_scene()
		       {

	   for (int t=0;t<80;t++){




	      GETPIX(bally[(t/2)+x]+x,ballx[(t/2)+y]+y,bally[1+tri]);

			      }

}
void caar(){



	 for (int carp=0;carp<80;carp++){
	 for (int cari=0;cari<2;cari++){
		    for (int t=0;t<30;t++){


	    //  GETPIX(ballx[cari]+xscroll, bally[carp+l+l+abs(sc)]+y,car[3+x] );
	      // GETPIX(ballx[cari]+xscroll, bally[carp+l+sc]+1,car[2+x] );

			      GETPIX(yscroll+carp*5,yscroll+cari*5,8);
	      GETPIX(xscroll+carp*10+x,yscroll+cari*5,4);
		   GETPIX(xscroll*cari,yscroll*carp*tri,4+tri);
	      GETPIX(xscroll+carp*10+x,yscroll+cari*10+y,1);
		      GETPIX(xscroll*carp,yscroll*carp*tri,4+tri);
	      GETPIX(xscroll+cari*10+x,yscroll+cari*10+y,1);




			} }
}}

void chara(tri)
		       {

	    for (int carp=0;carp<40;carp++){
	    for (int t=0;t<10;t++){
		    // if (  x == car[cari]+xscroll && y == car[carp]+xscroll ){

			// snd();

		     //  GETPIX( ballx[carp]+xtrig[tri]^tri, bally[carp]+ytrig[tri]^tri, tri );
		      // GETPIX( iconx[carp]+xtrig[tri]^tri, icony[carp]+ytrig[tri]^tri, tri );




		       GETPIX( chix[carp]+xtrig[tri]^tri, chiy[carp]+ytrig[tri]^tri, tri );
		       GETPIX( iconx[carp]+xtrig[tri]^tri, icony[carp]+ytrig[tri]^tri, tri );
			GETPIX( chix[carp]+xtrig[tri+1], chiy[carp]+ytrig[tri+1], tri );
		       GETPIX( iconx[carp]+xtrig[tri+1], icony[carp]+ytrig[tri+1], tri );

		       GETPIX( chix[carp]+xtrig[tri+1]^tri, chiy[carp]+ytrig[tri-1]^tri+1, tri );
		       GETPIX( iconx[carp]+xtrig[tri+1]^tri, icony[carp]+ytrig[tri-1]^tri+1, tri );
			GETPIX( chix[carp]+xtrig[tri], chiy[carp]+ytrig[tri]-1, tri );
		       GETPIX( iconx[carp]+xtrig[tri], icony[carp]+ytrig[tri]-1, tri );

				 }

			       }




	     // car[l]=charac[l+key]+2;




}



void icon(){

	       for (int carp=0;carp<40;carp++){
     //	GETPIX( iconx[carp]+xtrig+8, icony[carp]+ytrig+8, xtrig );
		     //  GETPIX( icony[carp]+xtrig-8, iconx[carp]+ytrig-8, ytrig );

		       }


}
void clsc(int opaq){


       for(l=0;l<200;l++){



  for(c=0;c<320;c++){


    GETPIX (c,l,opaq
    );

  //  GETPIX (c,l,0);
//     GETPIX (c,l,0);

       //	charac[l]=charac[l+1*y];
      }}



 }


void colli(){





}
void scoreboard(){

if (null == 200){
	     sc=sc-20;
	//   ytrig=ytrig-(tan(key)/4);xtrig=xtrig-tan(key);



		 for (l=0;l<40;l++){





	     // charac[l]=charac[l+key]+1;



			   }

	    null=0;
}
		  }


void moving(){
	 x=x+o;
y=y+r;
	 y=y+k;
k=k*z;






}


void bullet()    {



		 if (ol ==     3)
			    {

			       //	bullx=x;
			 //   bully=y;

			     for(l=0;l<200;l++){
			     // xscroll--;
			       co=co+1;


			    sound(l+2000);





			BULLETPIX(bullx+l, bully,3  );

			//   colli();


			BULLETPIX((bullx+l)-2, bully,0  );


			} }
	ol=0;

}

int main(){






  char kc = 0;
  char s[255];
  byte *pal;

  set_mode( VGA_256_COLOR_MODE );



  /* printf("Hello, world!\n"); */


  /* loop until ESC pressed */
  while( kc!=0X1b )


  {

moving();


if (y>=175){r=-(r);} if (y>=190){y=190;}
if (k>1){k=1;}
if (x>=310){o=-(o);} if (x>=320){x=320;}
//if (x>10){xtrig--;}
if (tri>=4 ){tri--;}

if(y<=10){r=-(r); }  if(y<=0){y=o; }
 if (x<=10){o=-(o);}  if (x<=0){x=0;}
//if (z>0){z=0;}
if (ytrig[tri]>180){ytrig[tri]=0;xtrig[tri]=xtrig[x]*30; sc=sc-10;}
if (co>10){co=1;}
yscroll++;
if( sc<=1){sc=1;}
//if (xtrig<0){xtrig=0; }
if (yscroll>=190){yscroll==0;}

if (xscroll>=310){xscroll==10; }
if (re>=310){re==10; }

if (xtrig[tri]>310){xtrig[tri]=xtrig[tri]; }
if (xtrig[tri]<10){xtrig[tri]=10; }
if (ytrig[tri]<10){ytrig[tri]=10; }

if (sc==400){ clsc(3);}
//if (y == ytrig && x == xtrig){ snd(); co=co+1;null=200;  }
//x++;


ytrig[tri]++;

//clsc(0);

scoreboard();
chara(tri);

caar();




    GETPIX(50+sc,190,3);
    GETPIX(50+sc,191,3);
    GETPIX(50+sc,192,3);
     GETPIX(50+sc,190,4);
    GETPIX(50+sc,191,4);
    GETPIX(50+sc,192,4);


	     //	sc=sc+5;
	  //  xtrig=320;


//null=0;

    GETPIX(150,190,6);
    GETPIX(150,191,6);
    GETPIX(150,192,6);

//      }
chara(tri);
  default_scene();
    default_scene_bg();
bullet();
//ytrig[tri]++;
//icon();


tri++;

clsc(0);


//default_scene();




if(

 x==xtrig[tri] & y==ytrig[tri]|
 x==xtrig[tri]-1 & y==ytrig[tri]|
 x==xtrig[tri]+1 & y==ytrig[tri]|
  x==xtrig[tri]+3 & y==ytrig[tri]|
 x==xtrig[tri]-2 & y==ytrig[tri]|
 x==xtrig[tri]+2 & y==ytrig[tri]|
  x==xtrig[tri] & y==ytrig[tri]|
 x==xtrig[tri]-3 & y==ytrig[tri]|
 x==xtrig[tri]+3 & y==ytrig[tri] |
  x==xtrig[tri] & y==ytrig[tri]+1|
 x==xtrig[tri] & y==ytrig[tri]-1|
 x==xtrig[tri]+1 & y==ytrig[tri]+1|
  x==xtrig[tri] & y==ytrig[tri]-1|
 x==xtrig[tri]-2 & y==ytrig[tri]+1|
 x==xtrig[tri]-2 & y==ytrig[tri]-1|
  x==xtrig[tri]+3 & y==ytrig[tri]+1|
 x==xtrig[tri]-3 & y==ytrig[tri]-1|
 x==xtrig[tri]-1 & y==ytrig[tri]+1







)


{co++; snd();delay(4);sc=sc+10;clsc(4);ytrig[tri]=0; xtrig[tri]=x+y*2;  }

//tri=tri+1;
  chara(tri);
//  default_sc
// ytrig[tri]++;
 nosound();
if (tri>=3){tri=1;}




    if(kbhit()) {




//ytrig=y+tri;	       //	printf(s, "r",s);
       tri=tri+1;
       kc=getch();
      if( kc == (char)0 ) {
	kc=getch();
	/* special key handling */
	switch( kc )
	{
	case 0x48: /* up arrow */
	     r=r-1;
	 //  y=y-5;
	 // k--;
	   z=z-1;
	  // o=0;
	  //strcpy(s, "up arrow");
	break;
	case 0x4d:

	       //left

      //	x=x+5;
	     // r=0;
	      o=1;



	 break;
	case 0x4b:

	       //	 r=0;
       //	x=x-5;
		o=-1;

	  break;

	case 0x50: /* down arrow */
		   o=0;
	      //	k=k++;
	      //	z=z++;
		  r=1;
       //	  y=y+5;
	  //strcpy(s, "down arrow");

	   break;

		case 0x52:
		     //	 for (l=0;l<100;l++){

		     ol=3;

		      // charac[l]=0;
		       //		 }
				 break;
	default: /* other special keys */

	//    r=0;
	  //  o=0;
	 //
	  sprintf(s, "00 %02x", kc);

	}
      }


      else {

   r=0;o=0;
;

      }
//     printf("Key pressed: %s\n", s);



  }


}
//default_scene();
	 set_mode( TEXT_MODE );

  return 0;
	}