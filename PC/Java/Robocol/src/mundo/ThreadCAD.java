package mundo;

public class ThreadCAD extends Thread
{
	private static final long MILLISEG_ANTES_ACTIVACION = 5*1000;
	
	private Control ventana;
	private boolean seguir;
	
	public ThreadCAD(Control padre)
	{
		ventana=padre;
		seguir=true;
		//Dejar un tiempo, para asegurar que haya canal
		long t1=System.currentTimeMillis();
		while(System.currentTimeMillis()-t1<MILLISEG_ANTES_ACTIVACION);
	}
	
	public void run()
	{
		long t1=System.currentTimeMillis();
		while(seguir)
		{
			if(System.currentTimeMillis()-t1<100);
			else
			{
				ventana.pedirCAD();
				t1=System.currentTimeMillis();
			}
		}
	}
	
	public void parar()
	{seguir=false;}
}