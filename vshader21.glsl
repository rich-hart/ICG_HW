attribute vec4 vPosition;
//attribute vec4 vColor;
varying vec4 fColor;

void
main()
{
    gl_Position = vPosition;
	
	fColor=vec4(0.0,1.0,0.0,1.0);
gl_FragColor =vec4(0.0,1.0,0.0,1.0);
//	fColor = vColor;
}
