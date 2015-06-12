package mundo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Comunicacion_SOCKET extends Thread implements IComunicacion
{
	private Socket echoSocket;
	private PrintWriter out;
	private BufferedReader in;
	private Control mundo;
	private boolean continuar;

	public Comunicacion_SOCKET(Control control, String hostname, String port_number)
	{
		continuar=true;
		mundo=control;
		try
		{
			echoSocket = new Socket(hostname, Integer.parseInt(port_number));
			out = new PrintWriter(echoSocket.getOutputStream(), true);
			in = new BufferedReader(new InputStreamReader(echoSocket.getInputStream()));
		}
		catch(NumberFormatException | IOException e)
		{
			System.err.println("No se logra conectar con el server");
			e.printStackTrace();
		}
	}

	@Override
	public void enviarLinea(String linea)
	{
		out.println(linea);
	}
	
	@Override
	public void run()
	{
		while(continuar)
		{
			try
			{
				String leido=in.readLine();
				mundo.tomarDato(leido);
			}
			catch(IOException e)
			{
				System.err.println("Problemas al leer lo que llega");
				e.printStackTrace();
			}
		}
	}

	@Override
	public void close()
	{
		continuar=false;
		try
		{
			in.close();
			out.close();
			echoSocket.close();
		}
		catch(IOException e)
		{e.printStackTrace();}
	}
}