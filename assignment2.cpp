// First new GL program
// Just makes a red triangle

#include "include/Angel.h"
#include <math.h>

#define BUFFER_SIZE 100000

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
vec4 colors[BUFFER_SIZE] ;
int color_index=0;


//this loads vertex data from my buffer into angel's
void load_data(vec2 *ver_pointer,vec2 *shape_pointer);

//functions that load data needed to generate an object into my buffer
void load_triangle(vec2 A, vec2 B, vec2 C);

void load_color(float r, float g, float b, float a);

void load_multi_color(void);

//functions used to generate shapes
void Make_Square(float x, float y, float side,int type);

void Make_Equal_Tri(float cx, float cy,float side);

float Degre_To_Rads(float degree);

void Make_Ellipse(float a, float b, float r,int type);

void Create_Shapes(void);



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

// create a square of cented at (x,y)
void Make_Square(float x, float y, float side,int type){
	int vect_total=4;
	vec2 vect_buffer[vect_total];
	vec2 temp1;
	vec2 temp2;
	vec2 center=vec2(x,y);
	vect_buffer[0] = vec2( x+side/2.0, y+side/2.0 );
	vect_buffer[1] =vec2( x+side/2.0, y-side/2.0 );
	vect_buffer[2]  = vec2( x-side/2.0, y-side/2.0 );
	vect_buffer[3] =vec2( x-side/2.0, y+side/2.0 );
	
	for(int i=0; i<=vect_total;i++){
		temp1=vect_buffer[i%vect_total];
		temp2=vect_buffer[(i+1)%vect_total];
		load_triangle(temp1,center,temp2);
		if(type){
			load_color(1.0,1.0,1.0,1.0);
		}else{
			load_color(0.0,0.0,0.0,1.0);
		}
	}
	
}

float Degre_To_Rads(float degree){
	
	return 	M_PI*degree/(180.0);
	
}

//creates an ellipse based on the equation (x/a)^2+(y/b)^2=r^2
void Make_Ellipse(float cx, float cy, float a, float b, float r,int type){
	
	int vect_total=360;
	vec2 vect_buffer[vect_total];
	vec2 temp1;
	vec2 temp2;
	vec2 center=vec2(cx,cy);
	float x;
	float y;
	for(int i=0; i<=vect_total;i++){
		x=sqrt(r)*a*cos(Degre_To_Rads(float(i)))+cx;
			y=sqrt(r)*b*sin(Degre_To_Rads(float(i)))+cy;
			vect_buffer[i]=vec2(x,y);
	
	}
	
	for(int i=0; i<=vect_total;i++){
		temp1=vect_buffer[i%vect_total];
		temp2=vect_buffer[(i+1)%vect_total];
		if(type){
			vec2 off_center=vec2(sqrt(r)*a+cx,cy);
		load_triangle(temp1,off_center,temp2);
		load_color(float(i)/float(vect_total),0.0,0.0,1.0);
		} else{
				load_triangle(temp1,center,temp2);
				load_color(1.0,0.0,0.0,1.0);
		}
	}
	
}

//creates an equalateral triangle centered at (x,y)
void Make_Equal_Tri(float cx, float cy,float side){
	
	int vect_total=3;
	vec2 vect_buffer[vect_total];
	vec2 temp1;
	vec2 temp2;
	vec2 center=vec2(cx,cy);
	
	float hieght = sqrt(pow(side,2.0) - pow(side/2.0,2.0));
	vec2 A = vec2( cx-side/2.0, cy -hieght/2.0);
	vec2 B =vec2( cx+side-side/2.0, cy -hieght/2.0);
	vec2 C   = vec2( cx+side/2.0-side/2.0, cy+ hieght-hieght/2.0);

	load_triangle(A,B,C);
	load_multi_color();

	
}

// the function that defines that shaped to be displays
void Create_Shapes(void){

	Make_Square(0.0,-0.5,1.0,1);
	Make_Square(0.0,-0.5,.75,0);
	Make_Square(0.0,-0.5,.5,1);
	Make_Square(0.0,-0.5,.25,0);
	Make_Square(0.0,-0.5,.123,1);
	Make_Ellipse(-0.5,0.5,2.0,1.0,.01,0);
	Make_Ellipse(0.5,0.5,1.0,1.0,.05,1);
	Make_Equal_Tri(0.0,0.5,.5);
}



void
init( void )
{
	ver_pointer=vertices;
	
	Create_Shapes();
	
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
    glFlush();
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
    glutInitDisplayMode( GLUT_RGBA );
    glutInitWindowSize( 512, 512 );

    glutCreateWindow( "Assignment 2" );
    glewExperimental=GL_TRUE; 
    glewInit();    
    init();

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
	

	
	// Create and initialize a buffer object
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
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
	
	
	//Initialize the vertex position attribute from the vertex shader
    GLuint loc2 = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( loc2 );
    glVertexAttribPointer( loc2, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(sizeof(vertices)) );
	
	glClearColor( 0.0, 0.0, 0.0, 1.0 ); // black background
}

