package Socket_Echo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class Cliente
{
	private static final int PORT = 1234;
	private static final String HOST = "127.0.0.1";

	public static void main(String[] args) throws UnknownHostException, IOException
	{
		 Socket echoSocket = new Socket(HOST, PORT);
         PrintWriter out = new PrintWriter(echoSocket.getOutputStream(), true);
         BufferedReader in = new BufferedReader(new InputStreamReader(echoSocket.getInputStream()));
         BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

         String userInput;
         while ((userInput = stdIn.readLine()) != null)
         {
             out.println(userInput);
             System.out.println("echo: " + in.readLine());
         }
         echoSocket.close();
	}
}
