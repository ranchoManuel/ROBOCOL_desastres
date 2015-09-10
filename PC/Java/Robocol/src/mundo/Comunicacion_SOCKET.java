package mundo;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class Comunicacion_SOCKET implements IComunicacion
{
	private static final int BUFFSIZE = 110;
	
	private Socket echoSocket;
	private PrintWriter out;
	private BufferedInputStream in;
	
	byte[] buffer = new byte[BUFFSIZE]; // 10 bytes buffer
	int bytesRead = 0;
	
	private Control mundo;
	private AuxThread aux;

	public Comunicacion_SOCKET(Control control, String hostname, String port_number)
	{
		mundo=control;
		try
		{
			echoSocket = new Socket(hostname.trim(), Integer.parseInt(port_number.trim()));
			out = new PrintWriter(echoSocket.getOutputStream(), true);
			in = new BufferedInputStream(echoSocket.getInputStream());
			
			aux=new AuxThread(mundo, in);
			aux.start();
		}
		catch(NumberFormatException | IOException e)
		{
			System.err.println("ROBOCOL:: No se logra conectar con el server");
			e.printStackTrace();
		}
	}

	@Override
	public void enviarLinea(String linea)
	{
		out.print(linea);
		out.flush();
	}
	
	@Override
	public void close()
	{
		aux.parar();
		try
		{
			in.close();
			out.close();
			echoSocket.close();
		}
		catch(IOException e)
		{e.printStackTrace();}
	}
	
	private class AuxThread extends Thread
	{
		private static final int BUFFSIZE = 110;
		
		private BufferedInputStream in;
		private boolean continuar;
		private Control padre;

		public AuxThread(Control padreP, BufferedInputStream inP)
		{
			padre=padreP;
			in=inP;
			continuar=true;
		}

		public void parar(){continuar=false;}

		public void run()
		{
			byte[] buffer = new byte[BUFFSIZE]; // 10 bytes buffer
			int bytesRead = 0;
			
			while(continuar)
			{
				try
				{
					while((bytesRead=in.read(buffer)) !=-1) // read up to 10 bytes
					{ 
						String leido = new String(buffer,0,bytesRead); // convert bytes to String using default encoding
						padre.tomarDato(leido);
					}

				}
				catch (IOException e) {}
			}
		}
	}
}