package Socket_Chat;

import java.io.BufferedInputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class ServidorChat
{
	private static int port1=1234;
	private static final int BUFFSIZE = 110;

	public static void main(String[] args) throws Exception
	{
		ServerSocket serverSocket = new ServerSocket(port1);
		Socket clientSocket = serverSocket.accept();
		PrintWriter out=new PrintWriter(clientSocket.getOutputStream(), true);
		BufferedInputStream in = new BufferedInputStream(clientSocket.getInputStream());
		
		byte[] buffer = new byte[BUFFSIZE];
		int bytesRead = 0;
		
		while((bytesRead=in.read(buffer)) !=-1) // read up to 110 bytes
		{ 
			String leido = new String(buffer,0,bytesRead); // convert bytes to String using default encoding
			out.print(leido);
			out.flush();
		}

		out.close(); in.close();
        serverSocket.close();
	}
}
