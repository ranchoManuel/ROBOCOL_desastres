package serverSocket_Juguete;

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
		System.out.println("Hola 1");
		ServerSocket serverSocket = new ServerSocket(PUERTO);
		Socket clientSocket = serverSocket.accept();
		System.out.println("Lo llamaron");
		PrintWriter out=new PrintWriter(clientSocket.getOutputStream(), true);
		BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
		System.out.println("Hola 2");

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
