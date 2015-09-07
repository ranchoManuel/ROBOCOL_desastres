import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class ClienteChat
{
	private static int port;
	private static String host;

	public static void main(String[] args) throws UnknownHostException, IOException
	{
		host=args[0];
		port=Integer.parseInt(args[1]);
		new ClienteChat();
	}

	public ClienteChat() throws UnknownHostException, IOException
	{
		Socket echoSocket = new Socket(host, port);
		PrintWriter out = new PrintWriter(echoSocket.getOutputStream(), true);
		BufferedInputStream in = new BufferedInputStream(echoSocket.getInputStream());

		BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
		AuxThread thread=new AuxThread(this, in);
		thread.start();

		String userInput;
		while((userInput = stdIn.readLine()) != null)
		{
			if(userInput.equals("FIN"))
			{
				thread.parar();
				break;
			}
			out.print(userInput);
			out.flush();
		}
		echoSocket.close();
	}

	public void imprimirCadena(String leido) {System.out.println("Other: "+leido);}
}
