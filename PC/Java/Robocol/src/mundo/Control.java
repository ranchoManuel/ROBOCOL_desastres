package mundo;

import interfaz.InterfazPrincipal;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;
import java.util.regex.Pattern;

public class Control
{
	public static final String FOLDER="./data/", USART_FILE="usart.wtf", SOCKET_FILE="socket.wtf", GENERAL="configGeneral.wtf";

	private static final String REGEX = "(OK;)|(ERR;)|(SEN:.*:.*:.*;)|(CAD:.*:.*:.*:.*:.*:.*;)|(ACE:.*:.*:.*;)|(-{9}ON-{9})";

	private IComunicacion comunicacion;
	private InterfazPrincipal ventana;
	private ThreadCAD threadCAD;
	private static char[] letras;
	private static String[] encabezados;

	private int ejeY,ejeX;
	private StringBuilder sb;
	private Pattern pattern = Pattern.compile(REGEX);

	public Control(InterfazPrincipal keyEventDemo, boolean comunicacionPorSocket, char[] letrasP, String[] encabezadosP) throws IOException
	{
		ejeX=ejeY=0;//
		letras=letrasP;
		encabezados=encabezadosP;
		ventana=keyEventDemo;
		sb=new StringBuilder();

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

		threadCAD=new ThreadCAD(this);
		threadCAD.start();
	}

	public void cerrar()
	{
		threadCAD.parar();
		comunicacion.close();
	}

	public void tomarDato(String mensajeDelOtro)
	{
		//Una expresion regular para saber que los mensajes que llegan esta bien.
		if(pattern.matcher(mensajeDelOtro).matches())
		{
			//Le presento al usuario lo que estoy reciviendo
			ventana.displayInfoRecibida(mensajeDelOtro);
			
			//Ahora se interpreta el mensaje y se procesa
		}
	}

	public void enviarOrden(char c)
	{
		//Resetear el buffer del string
		sb.setLength(0);
		//Para ajustar el movimiento del carros.
		if(c==letras[0] && ejeY<255) ejeY++;
		else if(c==letras[1] && ejeX>0) ejeX--;
		else if(c==letras[2] && ejeY>0) ejeY--;
		else if(c==letras[3] && ejeX<255) ejeX++;

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
				sb.append(encabezados[0]+ejeY+":"+ejeX+";");
				break;
			}
			else if(c==letras[i] && i>=4 && i<8)
			{
				//MBR:#:#;
				sb.append(encabezados[1]+":"+0+":"+0+";");
				break;
			}
			else if(c==letras[i] && i>=8)
			{
				//SEN;  CAD;  ZAR;  END;  TER;  TGL;  TGB;
				sb.append(encabezados[i-6]);
				break;
			}
		}

		//Para enviar
		if(sb.length()>0) 
		{
			comunicacion.enviarLinea(sb.toString());
			ventana.displayInfoEnviada(sb.toString());
		}
	}

	public void pedirCAD()
	{comunicacion.enviarLinea("CAD;");}
}