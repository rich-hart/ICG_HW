attribute vec4 vPosition;

attribute vec4 vColor;

varying vec4 fColor;

void
main()
{
    gl_Position = vPosition;

	float type= vColor.x;
	
	if(type==0.0){
	
	fColor=vec4(0.0,0.0,0.0,1.0);
	
	}
	
	if(type==1.0){
	
	fColor=vec4(1.0,1.0,1.0,1.0);
	
	}
	
	if(type<1.0){
	
	fColor=vec4(1.0,0.0,0.0,.5);
	
	}

	

}
