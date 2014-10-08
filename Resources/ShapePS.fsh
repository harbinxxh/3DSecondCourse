//由用户设置的色彩值
uniform vec4  u_ShapeColor;
//入口函数
void main()
{
	//返回像素化时的色彩值。
	gl_FragColor   =  u_ShapeColor ;
}