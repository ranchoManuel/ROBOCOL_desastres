package mundo;

import interfaz.InterfazPrincipal;

import java.io.IOException;
import java.util.Properties;

public class Control
{
	//{"Mensaje.Orugas","Mensaje.Brazos","Mensaje.SensoresADC","Mensaje.Acel_Magn","Mensaje.Acel_Continuo","Mensaje.Acel_end","Mensaje.Acel_ter","Mensaje.Toggle_Luz","Mensaje.Toggle_Buzzer"};
	private static final String[] COMANDOS={"MCA:","MBR:","SEN;","CAD;","ZAR;","END;","TER;","TGL;","TGB;"};

	//{"Tecla.Up","Tecla.Down","Tecla.Left","Tecla.Rigth","Tecla.Up_b1","Tecla.Down_b1","Tecla.Up_b2","Tecla.Down_b2","Tecla.SensoresADC","Tecla.Acel_Magn","Tecla.Acel_Continuo","Tecla.Acel_End","Tecla.Acel_Ter","Tecla.Toggle_Luz","Tecla.Toggle_Buzzer"};
	private static final char[] letras={'w','s','a','d','t','g','y','h','o','p','z','x','c','n','m'};

	private static final int MAX_PARAMETROS = 6;

	private IComunicacion comunicacion;
	private InterfazPrincipal interfaz;
	private Thread_CAD_SEN thread_CAD_SEN;

	private int m1,m2;
	private StringBuilder sb;
	private char[] cadena;
	private double[] parametros=new double[MAX_PARAMETROS];

	public Control(InterfazPrincipal ventana, boolean comunicacionPorSocket, Properties propiedades) throws IOException
	{
		m2=m1=0;//
		interfaz=ventana;
		sb=new StringBuilder();

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
		if(cadena[0]=='O' && cadena[1]=='K' && cadena[2]==';') //OK;
			mostrar=true;
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
			agarrarParamerosEnMensaje(6);
			interfaz.Graficar_CAD(parametros);
		}
		else if(cadena[0]=='A' && cadena[1]=='C' && cadena[2]=='E') //ACE
		{
			mostrar=true;
			agarrarParamerosEnMensaje(3);
			interfaz.Graficar_ACE(parametros);
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

	private void agarrarParamerosEnMensaje(int numParametros)
	{
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
				parametros[j--]=num;
				num=0;
				pot=1;
			}
			//Ignora los espacios y el ';' del final
		}		
	}

	public void enviarOrden(char c)
	{
		//Resetear el buffer del string
		sb.setLength(0);
		//Para ajustar el movimiento del carros.
		if(c==letras[0] && m1<255) m1++;
		else if(c==letras[1] && m2>0) m2--;
		else if(c==letras[2] && m1>0) m1--;
		else if(c==letras[3] && m2<255) m2++;

		//Para ajustar el movimiento de los brazos.
		else if(c==letras[4]);
		else if(c==letras[5]);
		else if(c==letras[6]);
		else if(c==letras[7]);

		//Para preparar el mensaje
		for(int i=0; i<letras.length; i++)
		{
			if(c==letras[i] && i>=0 && i<4)
			{
				//MCA:#:#;
				sb.append(COMANDOS[0]+m1+":"+m2+";");
				break;
			}
			else if(c==letras[i] && i>=4 && i<8)
			{
				//MBR:#:#;
				sb.append(COMANDOS[1]+":"+0+":"+0+";");
				break;
			}
			else if(c==letras[i] && i>=8)
			{
				//SEN;  CAD;  ZAR;  END;  TER;  TGL;  TGB;
				sb.append(COMANDOS[i-6]);
				break;
			}
		}

		//Para enviar
		if(sb.length()>0) 
		{
			comunicacion.enviarLinea(sb.toString());
			interfaz.displayInfoEnviada(sb.toString());
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
}