package Socket_Echo;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Servidor
{
	private static final int PUERTO=1234;

	public static void main(String[] args) throws Exception
	{
		ServerSocket serverSocket = new ServerSocket(PUERTO);
		Socket clientSocket = serverSocket.accept();
		PrintWriter out=new PrintWriter(clientSocket.getOutputStream(), true);
		BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

		// Initiate conversation with client
        for(String inputLine; (inputLine = in.readLine()) != null;)
        {
        	System.out.println(inputLine);
            out.println(inputLine);
        }
        
        out.close(); in.close();
        serverSocket.close();
	}
}
