package comunicacionSerial;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Field;

public class Control
{
	private static final String SERIAL_PATH = "./libs/serial/";

	public static void main(String[] args) throws Exception
	{
		new Control();
	}
	
	public Control() throws IOException, NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException
	{
		//		Manejo de extensiones de aplicacion
		//----------------------------------------------
		System.setProperty("java.library.path", SERIAL_PATH);
		Field fieldSysPath = ClassLoader.class.getDeclaredField( "sys_paths" );
		fieldSysPath.setAccessible( true );
		fieldSysPath.set( null, null );
		//----------------------------------------------
		
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		Comunicacion_USART comm=new Comunicacion_USART(this, "COM4", 4000, 115200); //Importante! verificar puerto
		for(String linea; (linea=br.readLine())!=null;)
		{
			comm.enviarLinea(linea);
		}
		br.close();
	}

	public void tomarDato(String leido)
	{
		System.out.println(leido);
	}
}