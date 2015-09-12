package mundo;

public class Thread_CAD_SEN extends Thread
{
	private static final long MILLISEG_ANTES_ACTIVACION = 10*1000;
	private static final long MILLISEG_ENTRE_CAD = 100;
	
	private Control ventana;
	private boolean seguir;
	
	public Thread_CAD_SEN(Control padre)
	{
		ventana=padre;
		seguir=true;
	}
	
	public void run()
	{
		//Dejar un tiempo, para asegurar que haya canal
		long t1=System.currentTimeMillis();
		while(System.currentTimeMillis()-t1<MILLISEG_ANTES_ACTIVACION);
		
		t1=System.currentTimeMillis();
		int cont=0;
		while(seguir)
		{
			if(System.currentTimeMillis()-t1 >= MILLISEG_ENTRE_CAD)
			{
				cont++;
				if(cont >= 3)
				{
					cont=0;
					ventana.pedirSEN();
				}
				else ventana.pedirCAD();
				
				t1=System.currentTimeMillis();
				while(System.currentTimeMillis()-t1<1);
			}
		}
	}
	
	public void parar()
	{seguir=false;}
}