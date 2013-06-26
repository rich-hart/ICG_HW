/*
Richard Hart
Assignment 3


x Enable double buffering.
x Create a main window with the "black & white" square
Place an ellipse in a SubWindow of the main window. Set the sub-window's display function to draw the background a different color.
Create a menu on the sub window only that allows the user to change the subwindow's background color.
Draw a circle and triangle, which have the same color, in a separate window entitled “window 2”. Allow the user to change the color of these objects by typing a key, 'r' - red, 'g' - green, 'b' - blue, 'y' - yellow, 'o' - orange, 'p' - purple, 'w' - white.
Animate the shapes using the idle function as follows:
Make the squares rotate counter clockwise.
Make the triangle rotate clockwise.
Make the circle increase in size and then decrease in size as though it was “breathing”.
Create a menu for the main window that is right-click activated with the following layout:
Stop Animation
Start Animation
Square Colors ->
     White
     Red
     Green
Where each button does the indicated action.
(Extra Credit) Alter the main window so that if a user clicks on it with the left click button, a new circle with a random color appears where s/he clicked.

*/

#include "include/Angel.h"
#include <math.h>

#define BUFFER_SIZE 100000

#define RED 0
#define RED_SHADED 1
#define WHITE 2
#define BLACK 3
#define MULTI_COLORED 4

#define SHADE_CENTER 0
#define SHADE_OFF_CENTER 1
#define SHADE_VERTEXS 2

//Angel Code:

vec2 vertices[BUFFER_SIZE] ;// Specifiy the vertices for a triangle
vec2 *ver_pointer;

int NumPoints = 0;

void Vertex_Array_Object(void);
void Initialize_Buffer_Object(void);
void Load_Shaders(void);

//---------

// My Code:

//define constants
#define PI 3.14159265
#define SHAPE_BUFFER_SIZE 100000
#define VECT_BUFFER_SIZE 100000

//arrays to hold shape and color data of objects
vec2 shape_buffer[SHAPE_BUFFER_SIZE];
vec2 *shape_pointer;

int index = 0;

vec4 colors[BUFFER_SIZE];
int color_index=0;


//this loads vertex data from my buffer into angel's
void load_data(vec2 *ver_pointer,vec2 *shape_pointer);

//functions that load data needed to generate an object into my buffer
void load_triangle(vec2 A, vec2 B, vec2 C);

void load_color(float r, float g, float b, float a);

void load_multi_color(void);

//functions used to generate shapes

float Degre_To_Rads(float degree);

void Make_Poly(float cx, float cy, float a, float b, float r,float rotate, int sides,int color, int shade_location);

void Make_Square(void);

void Make_Equil_Tri(void);

void Make_Circle(void);

void Make_Ellipse(void);



//load 3 non co-plainer points into the shape buffer render a triangle.
void load_triangle(vec2 A, vec2 B, vec2 C){

	shape_buffer[index]=A;
	index++;
	
	shape_buffer[index]=B;
	index++;
	
	shape_buffer[index]=C;
	index++;

}

// defines the color of a triangle that was just added into the shape buffer. 
//must be called after load_triangle. 

void load_color(float r, float g, float b, float a){
	for(int i=0;i<3;i++){
		colors[color_index]=vec4(r,g,b,a);
		color_index++;
	}

}

// defines a multicolored shading for a triangle that was just added into the shape buffer. 
//must be called after load_triangle.

void load_multi_color(void){
	
	colors[color_index]=vec4(1.0,0.0,0.0,1.0);
	color_index++;	

	colors[color_index]=vec4(0.0,1.0,0.0,1.0);
	color_index++;

	colors[color_index]=vec4(0.0,0.0,1.0,1.0);
	color_index++;
	
}

// loads data from my buffer into angels vertex buffer
void load_data(vec2 *ver_pointer,vec2 *shape_pointer){
	
	NumPoints=index;
	shape_pointer=shape_buffer;
	
	for(int i=0;i<NumPoints;i++){
		
		*ver_pointer= *shape_pointer;
		ver_pointer++;
		shape_pointer++;
		
	}
}

float Degre_To_Rads(float degree){
	
	return (degree / 180.0  )*M_PI;
	
}

//creates an polygon who's vertexes lie on  the ellipse equation (x/a)^2+(y/b)^2=r^2


void Make_Poly(float cx, float cy, float a, float b, float r,float rotate, int sides,int color, int shade_location){

	vec2 vect_buffer[sides];

	vec2 temp1;
	vec2 temp2;
	vec2 temp3;

	vec2 center;
	vec2 off_center;

	float x;
	float y;
	float degree=rotate;
	// calculating the vertex locations of the polygon and storing them temperarily in the vect_buffer array
	for(int i=0; i<=sides;i++){
		x=sqrt(r)*a*cos(Degre_To_Rads(degree))+cx;
		y=sqrt(r)*b*sin(Degre_To_Rads(degree))+cy;
		vect_buffer[i]=vec2(x,y);
		degree=degree+(360.0/(float)sides);
	}
	
	center=vec2(cx,cy);
	off_center=vect_buffer[0];
	
	// deciding how the triangles that create the polygon will be constructed e.g. 
	for(int i=0; i<=sides;i++){
		temp1=vect_buffer[i%sides];
		temp2=vect_buffer[(i+1)%sides];
		
		switch (shade_location){
			// all triangles have a common vertex at the center of the polygon
			case SHADE_CENTER:
			temp3=center;
			break;
			//the first vertex created for the polygon will also be a vertex for every triangle the makes up the polygon.
			case SHADE_OFF_CENTER:
			temp3=off_center;
			break;
			//every three vertex's that are read from the vect_buffer array will form a triangle in the polygon. 
			case SHADE_VERTEXS:
			temp3=vect_buffer[(i+2)%sides];
			break;

		}

		load_triangle(temp1,temp2,temp3);

		switch ( color )
		{	
			//color the triangle red. 
			case RED:
			load_color(1.0,0.0,0.0,1.0);
			break;
			//color the traingle based on some function associated with the current angle
			case RED_SHADED:
			load_color(float(i)/float(sides),0.0,0.0,1.0);
			break;
			//color the tri white
			case WHITE:
			load_color(1.0,1.0,1.0,1.0);
			break;
			//color the tri black
			case BLACK:
			load_color(0.0,0.0,0.0,1.0);
			break;
			//create a multicolored tri
			case MULTI_COLORED:
			load_multi_color();
			break;
			
			default:
			break;    
		}


	}

}

// create an ellispe by making a polygon of many sides.. 
void Make_Ellipse(void){
	
		Make_Poly(-0.5,0.5,2.0,1.0,.01,0.0,360,RED,SHADE_CENTER);
	
}
// create an ellispe by making a polygon of many sides..
void Make_Circle(void){
	
		Make_Poly(0.5,0.5,1.0,1.0,.05,0.0,360,RED_SHADED,SHADE_OFF_CENTER);
	
}
// make an equalateral tri
void Make_Equil_Tri(void){
	
		Make_Poly(0.0,0.5,1.0,1.0,.05,90.0,3,MULTI_COLORED,SHADE_VERTEXS);
	
}
//create a black and white square pattern. 
void Make_Square(void){
	
	float center_to_vertex_length = sqrt(pow(.5,2)+pow(.5,2));
	int color;
	for(int i = 0 ; i <= 8;i++){


		if (i%2){
			color=BLACK;

		} else {
			color=WHITE;
		}
		Make_Poly(0.0,-0.5,1.0,1.0,center_to_vertex_length*pow(2.0,-1.0*i),45.0,4,color,SHADE_CENTER);

	}
	
}




void
	init_1( void )
{
	ver_pointer=vertices;
	
	Make_Square();

	load_data(ver_pointer,shape_pointer);

	Vertex_Array_Object();

	Initialize_Buffer_Object();

	Load_Shaders();

}

void
	init_2( void )
{
	ver_pointer=vertices;

	Make_Ellipse();

	load_data(ver_pointer,shape_pointer);

	Vertex_Array_Object();

	Initialize_Buffer_Object();

	Load_Shaders();

}

//----------------------------------------------------------------------------

void
	display( void )
{
	glClear( GL_COLOR_BUFFER_BIT );     // clear the window
	glDrawArrays( GL_TRIANGLES, 0, NumPoints );    // draw the points
	glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
	keyboard( unsigned char key, int x, int y )
{
	switch ( key ) {
		case 033:
		exit( EXIT_SUCCESS );
		break;
	}
}

//----------------------------------------------------------------------------

int
	main( int argc, char **argv )
{
	puts("Testing Textmate Editing");
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize( 512, 512 );

	//main window
	uint main_id = glutCreateWindow( "Assignment 3: Main window" );
	glutSetWindow(main_id);
	glewExperimental=GL_TRUE; 
	glewInit();    
	init_1();

	glutDisplayFunc( display );
	
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize( 512, 512 );

	//subwindow
	uint sub_id = glutCreateWindow( "Assignment 3: Subwindow" );
	glutSetWindow(sub_id);
	glewExperimental=GL_TRUE; 
	glewInit();    
	init_2();

	glutDisplayFunc( display );
	
	glutKeyboardFunc( keyboard );

	glutMainLoop();

	return 0;
}



void Vertex_Array_Object(void){
	// Create a vertex array object
	GLuint vao[1];
	glGenVertexArrays( 1, vao );
	glBindVertexArray( vao[0] );
	
}

void Initialize_Buffer_Object(void){



	// Create and init_1ialize a buffer object
	GLuint buffer;
	glGenBuffers( 1, &buffer );
	glBindBuffer( GL_ARRAY_BUFFER, buffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(colors), NULL, GL_STATIC_DRAW );
	glBufferSubData( GL_ARRAY_BUFFER,0, sizeof(vertices), vertices );
	glBufferSubData( GL_ARRAY_BUFFER,sizeof(vertices), sizeof(colors), colors );

}

void Load_Shaders(void){
	// Load shaders and use the resulting shader program
	GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
	glUseProgram( program );

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( loc );
	glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );


	//Initialize the vertex position attribute from the vertex shader
	GLuint loc2 = glGetAttribLocation( program, "vColor" );
	glEnableVertexAttribArray( loc2 );
	glVertexAttribPointer( loc2, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)) );

	glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
}

