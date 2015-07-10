package mundo;

public class ThreadCAD extends Thread
{
	private Control ventana;
	private boolean seguir;
	
	public ThreadCAD(Control padre)
	{
		ventana=padre;
		seguir=true;
	}
	
	public void run()
	{
		long t1=System.currentTimeMillis();
		while(seguir)
		{
			if(System.currentTimeMillis()-t1<2000);
			else
			{
				ventana.pedirCAD();
				t1=System.currentTimeMillis();
			}
		}
	}
	
	public void parar()
	{
		seguir=false;
	}
}