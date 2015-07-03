package interfaz;

import java.io.Serializable;
import processing.core.PApplet;

public class Panel3D extends PApplet implements Serializable
{
	private static final long serialVersionUID = 1L;
	private int SIZE = 800, SIZEX = 800;
	private static float proty=0, protx=0, x, y;

	public void main()
	{
		PApplet.main(new String[] { "--present", "interfaz.Panel3D" });
	}

	public void setup()
	{
		size(SIZEX, SIZE, P3D);
	}

	public void draw()
	{
		translate(SIZEX/2, SIZE/2, -400);
		background(255);
		buildShape(proty, protx);
		
		if(abs(proty - y) < 0.05) y = proty;
		if(abs(protx - x) < 0.05) x = protx;

		buildShape(y, x);

		proty = y;     
		protx = x;
	}

	public void buildShape(float roty, float rotx)
	{
		pushMatrix();
		scale(6,6,14);
		rotateY(roty);
		rotateX(rotx);
		
		fill(255);
		stroke(0);
		box(60, 10, 10);
		fill(0, 255, 0);
		box(10, 9, 40);
		translate(0, -10, 20);
		fill(255, 0, 0);
		box(5, 12, 10);  
		popMatrix();
	}

	public void procesarComando(char key)
	{
		if (key=='w') x+=0.1;
		else if(key=='s') x-=0.1;

		if(key=='a') y-=0.1;
		else if(key=='d') y+=0.1;
	}
}