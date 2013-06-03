// First new GL program
// Just makes a red triangle

#include "include/Angel.h"
#include <math.h>

#define BUFFER_SIZE 100000







//--------------------------------------------------------------------------

void Vertex_Array_Object(void);

	    // Specifiy the vertices for a triangle
vec2 vertices[BUFFER_SIZE] ;
vec4 colors[BUFFER_SIZE] ;
vec2 *ver_pointer;
int NumPoints = 0;


#define PI 3.14159265
#define SHAPE_BUFFER_SIZE 100000
#define VECT_BUFFER_SIZE 100000
vec2 shape_buffer[SHAPE_BUFFER_SIZE];

vec2 *shape_pointer;

int index = 0;
		/*
		float x_offest=1.0;
		float y_offest=-1.0;
		float scale=.51;
		int np=21;
		vec2 temp[21]= {

	       vec2( 0.0, 0.0 ), vec2( -1.0, 0.0 ), vec2( 0.0, -1.0 ),

		vec2(0.0,0.0),vec2(1.0,0.0),vec2(0.0,1.0),

		vec2(1.0,0.0),vec2(1.0,1.0),vec2(0.0,1.0),

		vec2(scale*(0.0+x_offest),scale*(0.0+y_offest)),vec2(scale*(0.0+x_offest),scale*(1.0+y_offest)),

	vec2(scale*(-sin(2*PI/5)+x_offest),scale*(cos(2*PI/5)+y_offest)),
	vec2(scale*(0.0+x_offest),scale*(0.0+y_offest)),

	vec2(scale*(-sin(2*PI/5)+x_offest),scale*(cos(2*PI/5)+y_offest)),vec2(scale*(-sin(4*PI/5)+x_offest),scale*(-cos(PI/5)+y_offest)),
	vec2(scale*(0.0+x_offest),scale*(0.0+y_offest)),

	vec2(scale*(-sin(4*PI/5)+x_offest),scale*(-cos(PI/5)+y_offest)),vec2(scale*(sin(4*PI/5)+x_offest),scale*(-cos(PI/5)+y_offest)),


	vec2(scale*(0.0+x_offest),scale*(0.0+y_offest)),vec2(scale*(sin(4*PI/5)+x_offest),scale*(-cos(PI/5)+y_offest)),vec2(scale*(sin(2*PI/5)+x_offest),scale*(cos(2*PI/5)+y_offest)),


	vec2(scale*(0.0+x_offest),scale*(0.0+y_offest)),vec2(scale*(0.0+x_offest),scale*(1.0+y_offest)),vec2(scale*(sin(2*PI/5)+x_offest),scale*(cos(2*PI/5)+y_offest))
	    };

		for(int i = NumPoints+1 ;i<np;i++){
			vertices[i]=temp[i];
		}
		NumPoints=NumPoints+np;
		*/

//test
void Create_Shapes(void);
void load_data(vec2 *ver_pointer,vec2 *shape_pointer);
void load_triangle(vec2 A, vec2 B, vec2 C);
void Make_Square(float x, float y, float side);
void Make_Equal_Tri(float cx, float cy,float side);
float Degre_To_Rads(float degree);
void load_triangle(vec2 A, vec2 B, vec2 C){

	vec2 temp[3]= {
A,B,C
    };
	
	for(int i=0 ;i<3;i++){
		shape_buffer[index+i]=temp[i];
	}
	index=index+3;

	
}

void load_data(vec2 *ver_pointer,vec2 *shape_pointer){
	NumPoints=index;
	shape_pointer=shape_buffer;
	for(int i=0;i<NumPoints;i++){
		*ver_pointer= *shape_pointer;
		ver_pointer++;
		shape_pointer++;
	}
}
void Make_Ellipse(float a, float b, float r);
void Make_Square(float x, float y, float side){
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
	}
	
}

float Degre_To_Rads(float degree){
	
	return 	M_PI*degree/(180.0);
	
}

void Make_Ellipse(float cx, float cy, float a, float b, float r){
	
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
		load_triangle(temp1,center,temp2);
	}
	
}

void Make_Equal_Tri(float cx, float cy,float side){
	
	int vect_total=3;
	vec2 vect_buffer[vect_total];
	vec2 temp1;
	vec2 temp2;
	vec2 center=vec2(cx,cy);
	
	float hieght = sqrt(pow(side,2.0) - pow(side/2.0,2.0));
	vect_buffer[0] = vec2( cx-side/2.0, cy -hieght/2.0);
	vect_buffer[1] =vec2( cx+side-side/2.0, cy -hieght/2.0);
	vect_buffer[2]  = vec2( cx+side/2.0-side/2.0, cy+ hieght-hieght/2.0);

	
	for(int i=0; i<=vect_total;i++){
		temp1=vect_buffer[i%vect_total];
		temp2=vect_buffer[(i+1)%vect_total];
		load_triangle(temp1,center,temp2);
	}
	
}

void Create_Shapes(void){
	//load_triangle(vec2( 0.0, 0.0 ), vec2( -1.0, 0.0 ), vec2( 0.0, -1.0 ));
	//load_triangle(vec2(0.0,0.0),vec2(1.0,0.0),vec2(0.0,1.0));
	
	Make_Square(0.0,-0.5,.75);
	Make_Ellipse(-0.5,0.5,2.0,1.0,.01);
	Make_Ellipse(0.5,0.5,1.0,1.0,.05);
	Make_Equal_Tri(0.0,0.5,.5);
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
