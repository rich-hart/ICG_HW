attribute vec4 vPosition;
varying vec4 vColor;

void
main()
{
    gl_Position = vPosition;
	vColor = vec4( 1.0, 0.0, 1.0, 1.0 );
}
