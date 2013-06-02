// First new GL program
// Just makes a red triangle

#include "include/Angel.h"
#include <math.h>

#define BUFFER_SIZE 100000







//--------------------------------------------------------------------------



	    // Specifiy the vertices for a triangle
vec2 vertices[BUFFER_SIZE] ;
int NumPoints = 0;


#define PI 3.14159265
#define SHAPE_BUFFER_SIZE 100000
vec2 shape_buffer[SHAPE_BUFFER_SIZE];
int index = 0;


//test
void load_data(void);
void load_triangle(vec2 A, vec2 B, vec2 C);

void load_triangle(vec2 A, vec2 B, vec2 C){

	vec2 temp[3]= {
A,B,C
    };
	
	for(int i=0 ;i<3;i++){
		shape_buffer[index+i]=temp[i];
	}
	index=index+3;

	
}

void load_data(void){
	float x_offest=1.0;
	float y_offest=-1.0;
	float scale=.51;
	int np=21;
	/*
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
	NumPoints=index;
	
	for(int i=0;i<NumPoints;i++){
		vertices[i]=shape_buffer[i];
	}
}

void
init( void )
{
	
	load_triangle(vec2( 0.0, 0.0 ), vec2( -1.0, 0.0 ), vec2( 0.0, -1.0 ));
	load_triangle(vec2(0.0,0.0),vec2(1.0,0.0),vec2(0.0,1.0));
	load_data();


	
    // Create a vertex array object
    GLuint vao[1];
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
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
