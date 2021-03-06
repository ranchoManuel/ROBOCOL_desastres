package interfaz;

import java.io.Serializable;

import extra.Algoritmos;
import processing.core.PApplet;

public class Panel3D extends PApplet implements Serializable
{
	private static final long serialVersionUID = 1L;
	private int SIZEY = 600, SIZEX = 600;
	private static final double GRAV_TO_RAD = Math.PI/(1000*2);
	private static final double TO_ANG  = 180.0/Math.PI;

	private static float angleX, angleY, angleZ, sensT, sensH, sensD;
	private static double heading;

	public void setup()
	{
		size(SIZEX, SIZEY, P3D);
	}

	public void draw()
	{
		translate(SIZEX/2, SIZEY/2, -400);
//		background(0,128,255);
		background(0);
		buildShape();
	}

	public void buildShape()
	{
		//Para escribir Textos en pantalla
		fill(255);
		textAlign(CENTER);
		textSize(26);
		String text1=String.format("Angulo X: %3.3f\n Angulo Y: %3.3f\n Angulo Z: %3.3f\n Brujula: %3.3f", angleX*TO_ANG, angleY*TO_ANG, angleZ*TO_ANG, heading*TO_ANG);
		text(text1,0,200);
		String text2=String.format("Temperatura: %3.3f\n Humedad: %3.3f\n Distancia: %3.3f\n", sensT, sensH, sensD);
		text(text2,0,400);
		
		//Para Rotar Correctamente la Figura
		pushMatrix();
		scale(6,6,14);
		rotateX(angleX);
		rotateY(angleY);
		rotateZ(angleZ);

		//directionalLight(255, 255, 255, -1, -1, 1);
		//------Arma Fig-------
		stroke(0);
		fill(255);
		box(60, 10, 10);
		fill(0, 255, 0);
		box(10, 9, 40);
		translate(0, -10, 20);
		fill(255, 0, 0);
		box(5, 12, 10);  
		//---------------------
		
		popMatrix();
	}

	public void graficar_ACE(double accelX, double accelY, double accelZ)
	{
		angleX  = (float) (accelY*GRAV_TO_RAD);
		//angleY= 0;
		angleZ = (float) (accelX*GRAV_TO_RAD);
	}

	public void graficar_CAD(double accelX, double accelY, double accelZ, double magX, double magY, double magZ)
	{
		angleX  = (float) (accelY*GRAV_TO_RAD);
		//angleY= 0;
		angleZ = (float) (accelX*GRAV_TO_RAD);
		
		double[] ref={0,0,1};
		double[] mag={accelX, accelY, accelZ};
		heading=Algoritmos.anguloEntreVectores3D(ref, mag)*2;
	}

	public void graficar_SEN(double senT, double senH, double senD)
	{
		sensT = (float) (-71.4286*(3.3*senT/255)+189.28);
		sensH = (float) (31.25*(3.3*senH/255)-25);
		sensD = (float) (2.54*1000*(3.3*senD/255)/9.8);
	}
}
