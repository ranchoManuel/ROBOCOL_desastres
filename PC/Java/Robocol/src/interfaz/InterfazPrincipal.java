package interfaz;

import java.awt.BorderLayout;
import java.awt.Cursor;
import java.awt.Graphics2D;
import java.awt.SplashScreen;
import java.io.FileInputStream;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.Properties;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.UIManager;

import mundo.Control;

public class InterfazPrincipal extends JFrame
{
	private static final long serialVersionUID=1L;

	private static final String FOLDER="./data/", ARCHIVO="configGeneral.properties";
	private static final String TITULO = "Robocol Desastres";
	private static final String LOGO = "logo.png";

	private PanelVideo pvi;
	private PanelComunicacion pc;
	private Panel3D p3D;

	private Properties propiedades;
	private static Control mundo;

	public static void main(String[] args)
	{
		try 
		{
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		}
		catch(Exception e){/*No hacer nada*/}

		try
		{
			new InterfazPrincipal();
		}
		catch(IOException e)
		{
			JOptionPane.showMessageDialog(null, "El archivo de configuracion no existe en la carpeta data","Error al desplegar la aplicacion", JOptionPane.ERROR_MESSAGE);
		}
		catch(IllegalAccessException e)
		{
			JOptionPane.showMessageDialog(null, "La aplicacion no cuenta con los permisos necesarios","Error al desplegar la aplicacion", JOptionPane.ERROR_MESSAGE);
		}
		catch(NoSuchFieldException e){/*No hacer nada*/}
	}

	public InterfazPrincipal() throws IOException, IllegalAccessException, NoSuchFieldException 
	{
		final SplashScreen splash = SplashScreen.getSplashScreen();
		if(splash == null) System.err.println("SplashScreen.getSplashScreen() returned null");
		else 
		{
			Graphics2D g = splash.createGraphics();
			if(g == null)
			{
				System.err.println("g is null");
				return;
			}
		}
		setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

		//--------------------------------------------------
		propiedades = new Properties();
		propiedades.load(new FileInputStream(FOLDER+ARCHIVO));

		//1) saber con que me voy a comunicar
		String texto=propiedades.getProperty("ComunicacionPorSocket");
		boolean comSocket = texto.equals("true");
		System.out.println("paso 1");

		//2) saber donde quedan los jars; Manejo de extensiones de aplicacion, hay mas de esto en panelVideo
		//----------------------------------------------
		String path = propiedades.getProperty("SERIAL_PATH");
		System.setProperty("java.library.path", path);
		Field fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
		fieldSysPath.setAccessible( true );
		fieldSysPath.set( null, null );
		//----------------------------------------------
		System.out.println("paso 2");

		mundo=new Control(this, comSocket, propiedades);
		System.out.println("paso 3");

		setTitle(TITULO);
		setSize(1000, 800);
		setIconImage(new ImageIcon(FOLDER+LOGO).getImage());
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new BorderLayout());
		System.out.println("paso 4");

		String ipVideo=propiedades.getProperty("ipVideo");
		int portVideo=Integer.parseInt(propiedades.getProperty("puertoVideo"));
		String vlcPath=propiedades.getProperty("VLC_PATH");
		pvi=new PanelVideo(ipVideo, portVideo, vlcPath);
		add(pvi, BorderLayout.CENTER);
		System.out.println("paso 5");

		pc=new PanelComunicacion();
		add(pc, BorderLayout.SOUTH);
		System.out.println("paso 6");

		p3D=new Panel3D();
		add(p3D, BorderLayout.WEST);
		p3D.init();
		System.out.println("paso 7");

		setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
		if(splash!=null) splash.close();
		setVisible(true);
	}

	public Control getMundo() {return mundo;}

	public void enviarCaracterLeido(char c)
	{mundo.enviarOrden(c);}

	public void displayInfoRecibida(String mensajeDelOtro)
	{pc.displayInfoRecibida(mensajeDelOtro);}

	public void displayInfoEnviada(String orden)
	{if(pc!=null) pc.displayInfoEnviada(orden);}

	public void Graficar_CAD(double[] valores)
	{p3D.graficar_CAD(valores[0], valores[1], valores[2],valores[3], valores[4], valores[5]);}

	public void Graficar_ACE(double[] valores)
	{p3D.graficar_ACE(valores[0], valores[1], valores[2]);}

	public void Graficar_SEN(double[] valores)
	{p3D.graficar_SEN(valores[0], valores[1], valores[2]);}
}