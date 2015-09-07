package Socket_Chat;

import java.io.BufferedInputStream;
import java.io.IOException;

public class AuxThread extends Thread
{
	private static final int BUFFSIZE = 110;
	
	private BufferedInputStream in;
	private boolean continuar;
	private ClienteChat padre;

	public AuxThread(ClienteChat padreP, BufferedInputStream inP)
	{
		padre=padreP;
		in=inP;
		continuar=true;
	}

	public void parar(){continuar=false;}

	public void run()
	{
		byte[] buffer = new byte[BUFFSIZE];
		int bytesRead = 0;
		
		while(continuar)
		{
			try
			{
				while((bytesRead=in.read(buffer)) !=-1)
				{
					String leido = new String(buffer,0,bytesRead);
					padre.imprimirCadena(leido);
				}

			}
			catch (IOException e) {}
		}
	}
}