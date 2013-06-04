attribute vec4 vPosition;

attribute vec4 vColor;

varying vec4 fColor;


float Distance(float x1,float y1, float x2, float y2){

	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

void
main()
{
    gl_Position = vPosition;
	
	fColor = vColor;

}
