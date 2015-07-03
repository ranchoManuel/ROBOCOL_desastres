package mundo;

import interfaz.InterfazPrincipal;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Observable;
import java.util.Properties;

public class Control extends Observable
{
	public static final String FOLDER="./data/", USART_FILE="usart.wtf", SOCKET_FILE="socket.wtf", GENERAL="configGeneral.wtf";

	private IComunicacion comunicacion;
	private InterfazPrincipal ventana;
	private int ejeY,ejeX;
	private static char[] letras;
	private static String[] encabezados;
	//private ThreadCAD threadCAD;

	public Control(InterfazPrincipal keyEventDemo, boolean comunicacionPorSocket, char[] letrasP, String[] encabezadosP) throws IOException
	{
		ejeX=ejeY=0; //
		letras=letrasP;
		encabezados=encabezadosP;
		ventana=keyEventDemo;

		Properties p = new Properties();

		if(comunicacionPorSocket)
		{
			p.load(new FileInputStream(FOLDER+SOCKET_FILE));

			String hostname=p.getProperty("hostname");
			String port_name=p.getProperty("Puerto");
			comunicacion=new Comunicacion_SOCKET(this,hostname,port_name);
		}
		else
		{
			p.load(new FileInputStream(FOLDER+USART_FILE));

			String puerto = p.getProperty("Puerto").trim();
			int time_out = Integer.parseInt(p.getProperty("Time_out").trim());
			int data_rate = Integer.parseInt(p.getProperty("Data_rate").trim());
			comunicacion=new Comunicacion_USART(this,puerto,time_out,data_rate);
		}
	}

//	public void cerrar()
//	{
//		threadCAD.parar();
//		comunicacion.close();
//	}

	public void tomarDato(String mensajeDelOtro)
	{
		//Le presento al usuario lo que estoy reciviendo
		ventana.displayInfoRecivida(mensajeDelOtro);

		//ahora interpreto el mensaje y hago lo que me toca con esto
		
	}

	public void enviarOrden(char c)
	{
		String orden="";
		if(c==letras[0] && ejeY<255) ejeY++;
		else if(c==letras[1] && ejeX>0) ejeX--;
		else if(c==letras[2] && ejeY>0) ejeY--;
		else if(c==letras[3] && ejeX<255) ejeX++;
		else if(c==letras[4]);
		else if(c==letras[5]);
		else if(c==letras[6]);
		else if(c==letras[7]);

		for(int i=0; i < letras.length; i++)
		{
			if(c==letras[i] && i>=0 && i<4)
			{
				orden=encabezados[0]+ejeY+":"+ejeX+";";
				break;
			}
			else if(c==letras[i] && i>=4 && i<6)
			{
				orden="";
				break;
			}
			else if(c==letras[i] && i>=6 && i<8)
			{
				orden="";
				break;
			}
			else if(c==letras[i] && i==8)
			{
				orden=encabezados[2];
				break;
			}
			else if(c==letras[i] && i==9)
			{
				orden=encabezados[3];
				break;
			}
			else if(c==letras[i] && i==10)
			{
				orden=encabezados[4];
				break;
			}
			else if(c==letras[i] && i==11)
			{
				orden=encabezados[5];
				break;
			}
			else if(c==letras[i] && i==12)
			{
				orden=encabezados[6];
				break;
			}
			else if(c==letras[i] && i==13)
			{
				orden=encabezados[7];
				break;
			}
			else if(c==letras[i] && i==14)
			{
				orden=encabezados[8];
				break;
			}
		}

		//System.out.println(c+"=> "+orden);
		if(orden.length()>0) 
		{
			ventana.displayInfoEnviada(orden);
		}
	}

//	public void prenderThread()
//	{
//		System.out.println("Prende Thread");
//		threadCAD=new ThreadCAD(this);
//		threadCAD.start();
//	}
//	
//	public void pedirCAD()
//	{
//		comunicacion.enviarLinea("CAD;");		
//	}
}