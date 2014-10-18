//由用户设置的色彩值
uniform vec4  u_ShapeColor;
//入口函数
void main()
{
	//返回像素化时的色彩值。
//	gl_FragColor   =  u_ShapeColor;
    gl_FragColor=vec4((u_ShapeColor.r*CC_SinTime.w+1.0)*0.5,u_ShapeColor.g,u_ShapeColor.b,u_ShapeColor.a);
//    gl_FragColor=vec4(0,0,255,0);
}