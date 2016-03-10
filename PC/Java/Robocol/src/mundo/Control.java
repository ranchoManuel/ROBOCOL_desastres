package mundo;

import interfaz.InterfazPrincipal;

import java.io.IOException;
import java.util.Properties;

public class Control
{
	//{"Orugas","Brazos","SensoresADC","Acel_Magn","Acel_Continuo","Acel_end","Acel_ter","Toggle_Luz","Toggle_Buzzer"};
	// "MCA:"  ,"MBR:"	,"SEN;"		  ,"CAD;"	  ,"ZAR;"		  ,"END;"	 ,"TER;"	,"TGL;"		 ,"TGB;"};

	//{"Up","Down","Left","Right","Up_br1","Down_br1","Up_br2","Down_br2","Acel_Continuo","Acel_End","Acel_Ter","Toggle_Luz","Toggle_Buzzer", "Stop", "Next_camera", "Prev_camera"};
	//'w',  's',   'a',   'd',    't',      'g',      'y',     'h',       'z',             'x',      'c',       'n',         'm',             'e',    'k'            'l'    };

	private static final int MAX_PARAMETROS = 6;

	private IComunicacion comunicacionComandos;
	private IComunicacion comunicacionCamaras;	
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

		String hostname=propiedades.getProperty("ipComandos");
		if(comunicacionPorSocket)
		{
			String port_name=propiedades.getProperty("PuertoComandos");
			comunicacionComandos=new Comunicacion_SOCKET(this,hostname,port_name);
		}
		else
		{
			String puerto = propiedades.getProperty("PuertoUART").trim();
			int time_out = Integer.parseInt(propiedades.getProperty("Time_out_UART").trim());
			int data_rate = Integer.parseInt(propiedades.getProperty("Data_rate_UART").trim());

			comunicacionComandos=new Comunicacion_USART(this,puerto,time_out,data_rate);
		}

		String port_camaras=propiedades.getProperty("PuertoCamaras");
		comunicacionCamaras=new Comunicacion_SOCKET(this,hostname,port_camaras);

		thread_CAD_SEN=new Thread_CAD_SEN(this);
		thread_CAD_SEN.start();
	}

	public void cerrar()
	{
		thread_CAD_SEN.parar();
		comunicacionComandos.close();
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
		//'z',             'x',      'c',       'n',         'm',             'e',    'k'            'l'    };

		if(c=='w') {m1=300; m2=-300;}			//Up
		else if(c=='s') {m1=-300; m2=300;}	//Down
		else if(c=='a') {m1=300; m2=300;} 	//Left
		else if(c=='d') {m1=-300; m2=-300;} 	//Rigth

		if(c=='w' || c=='s' || c=='a' || c=='d')
		{
			//MCA:#:#;
			if(!lockMCA) lockMCA=true;
		}

		//Para ajustar el movimiento de los brazos.
		if(c=='t') {b1=300;}		//Up_br1
		else if(c=='g') {b1=-300;}		//Down_br1
		else if(c=='y') {b2=300;}		//Up_br2
		else if(c=='h') {b2=-300;}		//Down_br2

		if(c=='t' || c=='g' || c=='y' || c=='h')
		{
			//MBR:#:#;
			if(!lockMBR) lockMBR=true;
		}

		if(c=='z'); //Acel_Continuo
		else if(c=='x'); //Acel_End
		else if(c=='c'); //Acel_Ter
		else if(c=='n')lockTGL=true;//Toggle_Luz
		else if(c=='m')lockTGB=true; //Toggle_Buzzer
		else if(c=='e') {pararMotores(); pararBrazos(); return;} //Freno para el operario
		else if(c=='k') siguienteCamara(); //Next_camera
		else if(c=='l') anteriorCamara(); //Prev_camera
	}

	private void anteriorCamara()
	{
		comunicacionCamaras.enviarLinea("l");
		interfaz.displayInfoEnviada("Anterior Camara");
	}

	private void siguienteCamara() 
	{
		comunicacionCamaras.enviarLinea("k");
		interfaz.displayInfoEnviada("Siguiente Camara");
	}

	public void pedirCAD()
	{
		comunicacionComandos.enviarLinea("CAD;");
		interfaz.displayInfoEnviada("CAD;");
	}

	public void pedirSEN()
	{
		comunicacionComandos.enviarLinea("SEN;");
		interfaz.displayInfoEnviada("SEN;");
	}

	public void pararMotores()
	{
		m1=m2=0;
		comunicacionComandos.enviarLinea("MCA:0:0;");
		interfaz.displayInfoEnviada("MCA:0:0;");
	}

	public void pararBrazos()
	{
		b1=b2=0;
		comunicacionComandos.enviarLinea("MBR:0:0;");
		interfaz.displayInfoEnviada("MBR:0:0;");
	}

	public void moverCarro()
	{
		comunicacionComandos.enviarLinea("MCA:"+m1+":"+m2+";");
		interfaz.displayInfoEnviada("MCA:"+m1+":"+m2+";");
	}
	public void moverBrazos()
	{
		comunicacionComandos.enviarLinea("MBR:"+b1+":"+b2+";");
		interfaz.displayInfoEnviada("MBR:"+b1+":"+b2+";");
	}
	public void toggleBuzzer()
	{
		comunicacionComandos.enviarLinea("TGB;");
		interfaz.displayInfoEnviada("TGB;");
	}
	public void toggleLuz()
	{
		comunicacionComandos.enviarLinea("TGL;");
		interfaz.displayInfoEnviada("TGL;");
	}
}