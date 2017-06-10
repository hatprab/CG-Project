#include<stdlib.h>
#include<gl/glut.h>
#include "SOIL.h"
#include<math.h>
#include<stdio.h>
#define PI 3.1415926
static int radius = 2;
float move = 0;
double matrix[16];
int flag=0;
bool fullscreen= false;
/*Base With Grass and Ground*/
GLfloat vertices[][3]={ {-4.0, -1.0, 4.0},{-4.0, 0.0, 4.0},
						{4.0, 0.0, 4.0},{4.0, -1.0, 4.0},
						{-4.0, -1.0, -4.0},{-4.0, 0.0, -4.0},
						{4.0, 0.0, -4.0},{4.0, -1.0, -4.0} } ;
/*Was color cube to lazy to remove*/
GLfloat colors[][3]= { {1.0, 0.7, 0.0},{1.0, 0.4667, 0.0},
						{1.0, 0.2833, 0.0},{1.0, 0.1833, 0.0},
						{1.0, 0.7, 0.0},{1.0, 0.4667, 0.0},
						{1.0, 0.2833, 0.0},{1.0, 0.1833, 0.0},
						{1.0, 0.7, 0.0},{1.0, 0.4667, 0.0},
						{1.0, 0.2833, 0.0},{1.0, 0.1833, 0.0}
					};
/*Color fo rthe trees*/
GLfloat treecolors[][3]= { {0.75, 1.0, 0.0},{0.5667, 1.0, 0.0},
						{0.7833, 1.0, 0.0},{0.6833,1.0, 0.0},
						{0.75, 1.0, 0.0},{0.5667, 1.0, 0.0},
						{0.7833, 1.0, 0.0},{0.6833,1.0, 0.0},
						{0.75, 1.0, 0.0},{0.5667, 1.0, 0.0},
						{0.7833, 1.0, 0.0},{0.6833,1.0, 0.0}
					};

/*Who know what are these*/
		GLuint textureId;
		GLfloat theta[]={28.0,4.0,0.0};
		GLint axis=1;
		GLdouble viewer[]={0.0,0.0,5.0}; 
/*Who know what are these*/

/*Simple function to load img for texture.....i have study this*/
GLuint LoadTexture( const char * filename )
{

  GLuint texture;
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
// Actual RGB data
  unsigned char * data;
  FILE * file;
  file = fopen( filename, "rb" );
				  if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
					printf("Not a correct BMP file\n");
					return 0;
				}
	width  = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	data   = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
	fread( data, width * height * 3, 1, file );
	fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];
   data[index] = R;
   data[index+2] = B;

}
glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
gluBuild2DMipmaps( GL_TEXTURE_2D, 1, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
free( data );
return texture;
}

/*Was to create polygon but change to create quard from color cube program*/

void polygon(int a, int b, int c, int d){
	glBegin(GL_QUADS);
		glColor3fv(colors[a]);glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);glVertex3fv(vertices[d]);
	glEnd();
}

/*Was to create polygon but change to create quard from color cube program also if you notice it have texture mapping*/
void polygon2(int a, int b, int c, int d){
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);glVertex3fv(vertices[a]);
		glTexCoord2f(1.0,0.0);glVertex3fv(vertices[b]);
		glTexCoord2f(1.0,1.0);glVertex3fv(vertices[c]);
		glTexCoord2f(0.0,1.0);glVertex3fv(vertices[d]);
	glEnd();
	glDisable(GL_TEXTURE_2D);//for color correction
}


/*Was to color cube But worked for my need too lazy to change name*/
void base(){ 
	textureId = LoadTexture("img/ground.bmp");
	glBindTexture(GL_TEXTURE_2D, textureId);
	glColor3f(0.69f, 0.5428f, 0.138f);
		polygon2(0,3,2,1);
		polygon2(2,3,7,6);
		polygon(0,3,7,4);
	textureId = LoadTexture("img/grass.bmp");
	glBindTexture(GL_TEXTURE_2D, textureId);
	glColor3f(0.4876f, 0.69f, 0.1380f);
		polygon2(1,2,6,5);
	textureId = LoadTexture("img/ground.bmp");
	glBindTexture(GL_TEXTURE_2D, textureId);
	glColor3f(0.69f, 0.5428f, 0.05f);
		polygon2(4,5,6,7);
		polygon2(0,1,5,4);
	} 

void mountain(){
	glNewList(3, GL_COMPILE_AND_EXECUTE);
	glPushMatrix();

			//Draw Mountain 
			glEnable(GL_TEXTURE_2D);
			textureId = LoadTexture("img/tile.bmp");
			glBindTexture(GL_TEXTURE_2D, textureId);
			glColor3f(0.478,0.435,0.254);

			glBegin(GL_QUADS);
				glTexCoord2f(0.0,0.0);
				glVertex3f(0.0,3.0, 0.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(1.0,3.0, 0.0);
				glTexCoord2f(1.0,1.0);
				glVertex3f(1.0,0.0, -1.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(0.0,0.0, -1.0);

				glTexCoord2f(0.0,0.0);
				glVertex3f(1.0,3.0, 1.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(0.0,3.0, 1.0);
				glTexCoord2f(1.0,1.0);
				glVertex3f(0.0,0.0, 2.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(1.0,0.0, 2.0);

				glTexCoord2f(0.0,0.0);
				glVertex3f(1.0,3.0, 0.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(1.0,3.0, 1.0);
				glTexCoord2f(1.0,1.0);
				glVertex3f(2.0,0.0, 1.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(2.0,0.0, 0.0);

				glTexCoord2f(0.0,0.0);
				glVertex3f(0.0,3.0, 0.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(0.0,3.0, 1.0);
				glTexCoord2f(1.0,1.0);
				glVertex3f(-1.0,0.0, 1.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(-1.0,0.0, 0.0);
			glEnd();

			textureId = LoadTexture("img/tile.bmp");
			glBindTexture(GL_TEXTURE_2D, textureId);

			glBegin(GL_TRIANGLES);
				glTexCoord2f(0, 0);
				glVertex3f(0.0,3.0, 1.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(0.0,0.0, 2.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(-1.0,0.0, 1.0);

				glTexCoord2f(0, 0);
				glVertex3f(1.0,3.0, 1.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(2.0,0.0, 1.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(1.0,0.0, 2.0);

				glTexCoord2f(0, 0);
				glVertex3f(1.0,3.0, 0.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(1.0,0.0, -1.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(2.0,0.0, 0.0);

				glTexCoord2f(0, 0);
				glVertex3f(0.0,3.0, 0.0);
				glTexCoord2f(1.0,0.0);
				glVertex3f(0.0,0.0, -1.0);
				glTexCoord2f(0.0,1.0);
				glVertex3f(-1.0,0.0, 0.0);
			glEnd();
			

			glBegin(GL_POLYGON);
				glTexCoord2f(0.0,0.0);
				glColor3f(1.0,0.0,0.0);
				glVertex3f(0.0,0.0, 0.0);

				glTexCoord2f(0.5,0.0);
				glColor3f(0.5,0.0,0.0);
				glVertex3f(0.0,3.0, 0.0);

				glTexCoord2f(1.0,0.0);
				glColor3f(0.5,0.7,0.0);
				glVertex3f(1.0,3.0, 0.0);

				glTexCoord2f(1.0,1.0);
				glColor3f(0.5,0.0,0.0);
				glVertex3f(1.0,3.0, 1.0);

				glTexCoord2f(0.0,1.0);
				glColor3f(0.5,0.0,0.0);
				glVertex3f(0.0,3.0, 1.0);

				glTexCoord2f(0.5,0.0);
				glColor3f(0.5,0.0,0.0);
				glVertex3f(0.0,3.0, 0.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);

			glLineWidth(2.5); 
			glColor3f(1.0, 0.0, 0.0);

			/*glBegin(GL_LINES);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(15, 0, 0);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(0, 15.0, 0);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(0, 0, 15.0);
			glEnd(); */
		glPopMatrix();
		glEndList();
 
	}

void flames(){
		int ACC=10;
	float r = rand() % 3+3;
    float static a,p,q;
    int static  i;
	float static z=0.2167;
		glColor3f(1,z,0);
		z+=0.009;
		if(z>0.6667)
			z=0.2167;
	glNewList(2, GL_COMPILE);
 	glPushMatrix();
		glTranslatef(-0.1,0.0,-0.1);
			glBegin(GL_QUAD_STRIP);
			for (i=0;i<=ACC;i++)
				{
					a = i*PI*2/ACC;
					p = cos(a);
					q = sin(a);
						glVertex3f(0.6*q, 0.0, 0.6*p);
						glVertex3f(0.1*q, 2.0, 0.1*p);
				}
			glEnd();
			glPushMatrix();
			glTranslatef(1.1,0.0,-0.1);
				glBegin(GL_QUAD_STRIP);
					for (i=0;i<=ACC;i++)
						{
							a = i*PI*2/ACC;
							p = cos(a);
							q = sin(a);
								glVertex3f(0.6*q, 0.0, 0.6*p);
								glVertex3f(0.1*q, 2.0, 0.1*p);
						}
				glEnd();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(1.1,0.0,1.3);
				glBegin(GL_QUAD_STRIP);
					for (i=0;i<=ACC;i++)
						{
							a = i*PI*2/ACC;
							p = cos(a);
							q = sin(a);
								glVertex3f(0.6*q, 0.0, 0.6*p);
								glVertex3f(0.1*q, 2.0, 0.1*p);
						}
				glEnd();
			glPopMatrix();

		glTranslatef(0.6,0.0,0.6);
			glBegin(GL_QUAD_STRIP);
			for (i=0;i<=10;i++)
				{
					a = i*PI*2/ACC;
					p = cos(a);
					q = sin(a);
						glVertex3f(0.1*q, 0.0 , 0.4*p);
						glVertex3f(0.3*q, 2.0 , 0.6*p);

						glVertex3f(0.1*q, 0.0 , 0.6*p);
						glVertex3f(0.4*q, r   , 0.3*p);
				}
			glEnd();
	glPopMatrix();
	glEndList();
}

void trees()
{
		
	int ACC=10;
    float a,p,q;
    int i;
	static int factor= 0;//rand() % 3+3;
	glNewList(1, GL_COMPILE);
	glPushMatrix();
			glTranslatef(2,0.0,2);
			glEnable(GL_TEXTURE_2D);
			textureId = LoadTexture("img/tile.bmp");
			glBindTexture(GL_TEXTURE_2D, textureId);
			glColor3f(0.478,0.435,0.254);
 
					glBegin(GL_QUAD_STRIP);
					for (i=0;i<=ACC;i++)
					{
					a = i*PI*2/ACC;
					p = cos(a);
					q = sin(a);
									glTexCoord2f(0.0,0.0);
					glVertex3f(0.1*q, 0.0, 0.1*p);
									glTexCoord2f(1.0,0.0);
					glVertex3f(0.1*q, 1.0, 0.1*p);
									glTexCoord2f(1.0,1.0);
					glVertex3f(0.1*q, 0.0, 0.1*p);
									glTexCoord2f(0.0,1.0);
					glVertex3f(0.1*q, 1.0, 0.1*p);
					}
					glEnd();
					glDisable(GL_TEXTURE_2D);

					/*if(factor>4){factor=0;}
					factor>4?factor=0:factor++;*/ 

					glTranslatef(-0.1,1.0,-0.1);
					glColor3fv(treecolors[factor]);
					glutSolidSphere(0.27,20.0,20.0);

					glTranslatef(0,0.0,0.2);
					glColor3fv(treecolors[factor+1]);
					glutSolidSphere(0.24,20.0,20.0);

					glTranslatef(0.2,0.0,0);
					glColor3fv(treecolors[factor+2]);
					glutSolidSphere(0.22,20.0,20.0);

					glTranslatef(-0.2,0.0,-0.2);
					glColor3fv(treecolors[factor+3]);
					glutSolidSphere(0.23,20.0,20.0);

					glTranslatef(0.2,0.0,0);
					glColor3fv(treecolors[factor+4]);
					glutSolidSphere(0.30,20.0,20.0);

					glTranslatef(0.0,0.3,0);
					glColor3fv(treecolors[factor+4]);
					glutSolidSphere(0.30,20.0,20.0);
		glPopMatrix();
		glEndList();
	
}

//lava
	void lava(){					
		/*local static variable for lava particle*/
		float random = rand() % 4+6;
		float r = rand() % 4-2;
		static int factor=0;
		static GLfloat midY = 4.5;
		static GLfloat midX = 2.0;
		static GLfloat y = 0;
		static GLfloat x = -2;
		/*local static variable for lava particle*/
		glNewList(4, GL_COMPILE);
		glPointSize(random); // size of errupt praticles
	
	glPushMatrix();	
			if(x>2)
				{x=-2;}
			if(factor>4){factor=0;}
			 factor>4?factor=0:factor++; 
				y = -x*x;
					glBegin(GL_POINTS);
							glColor3fv(colors[factor+1]);/* side (positive) z axis*/
							glVertex3f(0.2 , midY + y + move +r, midX + x );

							glColor3fv(colors[factor+4]);
							glVertex3f(0.6 , midY + y + move-r , midX + x );

							glColor3fv(colors[factor+1]);/* side (negative) -z axis*/
							glVertex3f(0.2 , midY + y + move+r , -(midX + x) );

							glColor3fv(colors[factor+3]);
							glVertex3f(0.6 , midY + y + move-r , -(midX + x) );

							glColor3fv(colors[factor+2]);	/*side (positive) x axis*/
							glVertex3f(midX + x, midY + y+move+r,0.2);

							glColor3fv(colors[factor]);
							glVertex3f(midX + x, midY + y+move-r,0.8);

							glColor3fv(colors[factor+2]);		/* side (negative) -x axis*/
							glVertex3f(-(midX + x), midY + y+move+r,0.2);

							glColor3fv(colors[factor+1]);
							glVertex3f(-(midX + x), midY + y+move-r,0.8);
					glEnd();
			x+=0.2;

	glPopMatrix();
	glEndList();
	}


/*You know i need this */
void display(void) { 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	gluLookAt(viewer[0],viewer[1],viewer[2],0.0,0.0,0.0,0.0,1.0,0.0); //fixed viewer
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	glRotatef(theta[2],0.0,0.0,1.0);
		base();
		glCallList(3);mountain();
		if(flag)
		{	glCallList(4);lava();
		   glPushMatrix();
				glRotatef(10,0.0,1.0,0.0);				
			glCallList(4);lava();
				glRotatef(10,0.0,1.0,0.0);
			glCallList(4);lava();
		   glPopMatrix();
		   	glCallList(2);
		   flames();
		}

		glPushMatrix();
			glCallList(1);
			glTranslatef(0.0,0.0,0.5);
			glCallList(1);
			glTranslatef(0.25,0.0,0.5);
			glCallList(1);
			glTranslatef(0.35,0.0,0.5);
			glCallList(1);
			glTranslatef(0.11,0.0,0.5);
			glCallList(1);
			glTranslatef(0.0,0.0,-5.0);
			glCallList(1);
			glTranslatef(0.25,0.0,0.5);
			glCallList(1);
			glTranslatef(0.35,0.0,0.5);
			glCallList(1);
			glTranslatef(0.11,0.0,0.5);
			trees();
		glPopMatrix();
		

	glFlush();
	glLoadIdentity();
	 glutSwapBuffers();
} 


/*Mouse i hope you get this*/
void mouse(int btn, int state, int x, int y) {
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP) flag=!flag;
    if(btn==GLUT_MIDDLE_BUTTON&&state==GLUT_DOWN) axis=1;
    if(btn==GLUT_RIGHT_BUTTON&&state==GLUT_DOWN) axis=2;
    theta[axis]-=8.0;
    if(theta[axis]<-360.0) theta[axis]=0;
    display();
}

/*Keyboard i m not a keyboard player but a coder hahahah*/
void keys(unsigned char key, int x, int y) {
	if(key == 'x') axis=0;
    if(key == 'y') axis=1;
	if(key == 'z') axis=2;
	/*Reset*/
	if(key == 'r') { theta[0] = 28.0;theta[1] = 4.0;theta[2] = 0.0;}

	if (key == 'f'){
			fullscreen = !fullscreen;
				if(fullscreen){
					glutFullScreen();
			} else {
					glutReshapeWindow(1000,1000);
					glutPositionWindow(0,0);
					fullscreen = false;
				}
		 }
	if(key == 27 ){ exit(0);}
	//theta[axis]+=0.75; //fine tuned
	theta[axis]+=8.0; //fast for testing
    if(theta[axis]>360.0) theta[axis]-=360.0;
    display();
}

/*Just pesudo fuction outside the main even it could be inside main hahhahaha*/
void myinit() {
	//glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6.0,6.0,-8.0,8.0,-2.0,50.0);
    glMatrixMode(GL_MODELVIEW);
}

void myReshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-6.0,6.0,-8.0*(GLfloat)h/(GLfloat)w, 
                  8.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
		glOrtho(-6.0*(GLfloat)w/(GLfloat)h,
                  6.0*(GLfloat)w/(GLfloat)h, -8.0,8.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
}


void idel(void)
{	
theta[axis]+=0.6; //fast for testing
    if(theta[axis]>360.0) theta[axis]-=360.0;
move+=0.08;
if(move>2)
	move=0;
glutPostRedisplay();
}


/*Start reading from here ignore all the comment */
void main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Colorcube Viewer");
	glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
	//glutFullScreen();
    glutMouseFunc(mouse);
	glutIdleFunc(idel);
    glutKeyboardFunc(keys);
    glEnable(GL_DEPTH_TEST);
    myinit();
    glutMainLoop();
}