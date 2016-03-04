package mundo;

import interfaz.InterfazPrincipal;

import java.io.IOException;
import java.util.Properties;

public class Control
{
	//{"Orugas","Brazos","SensoresADC","Acel_Magn","Acel_Continuo","Acel_end","Acel_ter","Toggle_Luz","Toggle_Buzzer"};
	// "MCA:"  ,"MBR:"	,"SEN;"		  ,"CAD;"	  ,"ZAR;"		  ,"END;"	 ,"TER;"	,"TGL;"		 ,"TGB;"};

	//{"Up","Down","Left","Right","Up_br1","Down_br1","Up_br2","Down_br2","Acel_Continuo","Acel_End","Acel_Ter","Toggle_Luz","Toggle_Buzzer", "Stop"};
	private static final char[] letras={'w','s','a','d','t','g','y','h','z','x','c','n','m','e'};

	private static final int MAX_PARAMETROS = 6;

	private IComunicacion comunicacion;
	private InterfazPrincipal interfaz;
	private Thread_CAD_SEN thread_CAD_SEN;

	protected boolean lockMCA, lockMBR, lockSEN, lockCAD, lockTGL, lockTGB;
	private int m1,m2,b1,b2;
	private char[] cadena;
	private double[] parametros=new double[MAX_PARAMETROS];

	public Control(InterfazPrincipal ventana, boolean comunicacionPorSocket, Properties propiedades) throws IOException
	{
		lockMCA=lockMBR=lockSEN=lockCAD=lockTGL=lockTGB=false;
		m2=m1=b1=b2=0;
		interfaz=ventana;

		if(comunicacionPorSocket)
		{
			String hostname=propiedades.getProperty("ipComandos");
			String port_name=propiedades.getProperty("PuertoComandos");

			comunicacion=new Comunicacion_SOCKET(this,hostname,port_name);
		}
		else
		{
			String puerto = propiedades.getProperty("PuertoUART").trim();
			int time_out = Integer.parseInt(propiedades.getProperty("Time_out_UART").trim());
			int data_rate = Integer.parseInt(propiedades.getProperty("Data_rate_UART").trim());

			comunicacion=new Comunicacion_USART(this,puerto,time_out,data_rate);
		}

		thread_CAD_SEN=new Thread_CAD_SEN(this);
		thread_CAD_SEN.start();
	}

	public void cerrar()
	{
		thread_CAD_SEN.parar();
		comunicacion.close();
	}

	public void tomarDato(String mensajeDelOtro)
	{
		cadena=mensajeDelOtro.toCharArray();
		boolean mostrar=false;
		if(mensajeDelOtro.length()<3) return;
		if(cadena[0]=='O' && cadena[1]=='K' && cadena[2]==';') //OK;
		{
			lockMCA=lockMBR=lockTGB=lockTGL=false;
			mostrar=true;
		}

		if(mensajeDelOtro.length()<4) return;
		else if(cadena[0]=='E' && cadena[1]=='R' && cadena[2]=='R' && cadena[3]==';') //ERR;
			mostrar=true;
		else if(cadena[0]=='S' && cadena[1]=='E' && cadena[2]=='N') //SEN
		{
			mostrar=true;
			agarrarParamerosEnMensaje(3);
			interfaz.Graficar_SEN(parametros);
		}
		else if(cadena[0]=='C' && cadena[1]=='A' && cadena[2]=='D') //CAD
		{
			mostrar=true;
			if(agarrarParamerosEnMensaje(6)) interfaz.Graficar_CAD(parametros);
		}
		else if(cadena[0]=='A' && cadena[1]=='C' && cadena[2]=='E') //ACE
		{
			mostrar=true;
			if(agarrarParamerosEnMensaje(3)) interfaz.Graficar_ACE(parametros);
		}

		//Le presento al usuario lo que estoy reciviendo
		if(mostrar) 
		{
			interfaz.displayInfoRecibida(mensajeDelOtro);
			return;
		}

		//El mensaje de cuando se reinicia la FRDM
		if(mensajeDelOtro.matches("(-*ON-*)"))
			interfaz.displayInfoRecibida(mensajeDelOtro);
	}

	private boolean agarrarParamerosEnMensaje(int numParametros)
	{
		int numLeidos=0;
		int num=0, j=numParametros-1, pot=1;
		//Se usa i>2 por que se quieren ignorar las 3 primeras letras
		for(int i=cadena.length-1; i>2 && j>=0; i--)
		{
			if(cadena[i]=='-') num*=-1;
			else if(Character.isDigit(cadena[i]))
			{
				num+=(cadena[i]-'0')*pot;
				pot*=10;
			}
			else if(cadena[i]==':')
			{
				numLeidos++;
				parametros[j--]=num;
				num=0;
				pot=1;
			}
			//Ignora los espacios y el ';' del final
		}

		return numLeidos==numParametros;
	}

	public void enviarOrden(char c)
	{
		//Para ajustar el movimiento del carros.
		if(c==letras[0]) {m1=300; m2=-300;}			//Up
		else if(c==letras[1]) {m1=-300; m2=300;}	//Down
		else if(c==letras[2]) {m1=300; m2=300;} 	//Left
		else if(c==letras[3]) {m1=-300; m2=-300;} 	//Rigth

		//Para ajustar el movimiento de los brazos.
		else if(c==letras[4]) {b1=300;}		//Up_br1
		else if(c==letras[5]) {b1=-300;}		//Down_br1
		else if(c==letras[6]) {b2=300;}		//Up_br2
		else if(c==letras[7]) {b2=-300;}		//Down_br2

		//Para preparar el mensaje
		ciclo: for(int i=0; i<letras.length; i++)
		{
			if(c==letras[i])
			{
				if(i>=0 && i<4)
				{
					//MCA:#:#;
					if(!lockMCA) lockMCA=true;
					break ciclo;
				}
				else if(i>=4 && i<8)
				{
					//MBR:#:#;
					if(!lockMBR) lockMBR=true;
					break ciclo;
				}
				else if(i>=8)
				{
					//  8;   9;   10;    11;   12;
					//ZAR;  END;  TER;  TGL;  TGB;
					if(i==11 && !lockTGL) lockTGL=true;
					else if(i==12 && !lockTGB) lockTGB=true;
					else if(i==letras.length-1) {pararMotores(); pararBrazos(); return;} //Freno para el operario
					break ciclo;
				}
			}
		}
	}

	public void pedirCAD()
	{
		comunicacion.enviarLinea("CAD;");
		interfaz.displayInfoEnviada("CAD;");
	}

	public void pedirSEN()
	{
		comunicacion.enviarLinea("SEN;");
		interfaz.displayInfoEnviada("SEN;");
	}

	public void pararMotores()
	{
		m1=m2=0;
		comunicacion.enviarLinea("MCA:0:0;");
		interfaz.displayInfoEnviada("MCA:0:0;");
	}

	public void pararBrazos()
	{
		b1=b2=0;
		comunicacion.enviarLinea("MBR:0:0;");
		interfaz.displayInfoEnviada("MBR:0:0;");
	}

	public void moverCarro()
	{
		comunicacion.enviarLinea("MCA:"+m1+":"+m2+";");
		interfaz.displayInfoEnviada("MCA:"+m1+":"+m2+";");
	}
	public void moverBrazos()
	{
		comunicacion.enviarLinea("MBR:"+b1+":"+b2+";");
		interfaz.displayInfoEnviada("MBR:"+b1+":"+b2+";");
	}
	public void toggleBuzzer()
	{
		comunicacion.enviarLinea("TGB;");
		interfaz.displayInfoEnviada("TGB;");
	}
	public void toggleLuz()
	{
		comunicacion.enviarLinea("TGL;");
		interfaz.displayInfoEnviada("TGL;");
	}
}