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
	float type = vColor.t;
	float cx = vColor.x;
	float cy = vColor.y;
	float side = vColor.z;
	
	if(0==1){
	
	float hieght = sqrt(pow(side,2.0) - pow(side/2.0,2.0));
	vec2 A = vec2( cx-side/2.0, cy -hieght/2.0);
	vec2 B =vec2( cx+side-side/2.0, cy -hieght/2.0);
	vec2 C   = vec2( cx+side/2.0-side/2.0, cy+ hieght-hieght/2.0);
	
	float da=Distance(A.x,A.y,vPosition.x,vPosition.y);
	float db=Distance(B.x,B.y,vPosition.x,vPosition.y);
	float dc=Distance(C.x,C.y,vPosition.x,vPosition.y);
	
	
//	fColor=vec4(da/hieght,db/hieght,dc/hieght,1.0);
	fColor=vec4(1.0,0.0,0.0,1.0);	
	} else{
	
	
	fColor = vColor;
	}
}
