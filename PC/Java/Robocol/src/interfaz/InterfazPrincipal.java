package interfaz;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.io.FileInputStream;
import java.lang.reflect.Field;
import java.util.MissingFormatArgumentException;
import java.util.Properties;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.UIManager;

import mundo.Control;

public class InterfazPrincipal extends JFrame 
{
	private static final long serialVersionUID=1L;

	private static final String MODO_DE_COMINICACION="ComunicacionPorSocket";
	private static final String[] TECLAS={"Tecla.Up","Tecla.Down","Tecla.Left","Tecla.Rigth","Tecla.Up_b1","Tecla.Down_b1","Tecla.Up_b2","Tecla.Down_b2","Tecla.SensoresADC","Tecla.Acel_Magn","Tecla.Acel_Continuo","Tecla.Acel_End","Tecla.Acel_Ter","Tecla.Toggle_Luz","Tecla.Toggle_Buzzer"};
	private static final String[] MENSAJES={"Mensaje.Orugas","Mensaje.Brazos","Mensaje.SensoresADC","Mensaje.Acel_Magn","Mensaje.Acel_Continuo","Mensaje.Acel_end","Mensaje.Acel_ter","Mensaje.Toggle_Luz","Mensaje.Toggle_Buzzer"};
	private static final String SERIAL_PATH="SERIAL_PATH";
	
	private static Control mundo;
	private PanelComunicacion pc;
	private Panel3D p3D;
	private PanelGraphic p2D;
	private PanelVideo pvi;

	public static void main(String[] args) throws Exception
	{
		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		new InterfazPrincipal();
	}

	public InterfazPrincipal() throws Exception
	{
		Properties p = new Properties();
		p.load(new FileInputStream(Control.FOLDER+Control.GENERAL));

		//1) saber con que me voy a comunicar
		String texto=p.getProperty(MODO_DE_COMINICACION);
		if(texto==null) throw new MissingFormatArgumentException("Debe existir la propiedad \""+MODO_DE_COMINICACION+"\"");

		boolean comSocket = texto.equals("true");
		if(!comSocket && !texto.equals("false")) throw new IllegalArgumentException("La propiedad ComunicacionPorSocket debe ser \"true\" o \"false\"");

		//2) saber donde quedan los jars; Manejo de extensiones de aplicacion
		//----------------------------------------------
		String path = p.getProperty(SERIAL_PATH);
		System.setProperty("java.library.path", path);
		Field fieldSysPath = ClassLoader.class.getDeclaredField( "sys_paths" );
		fieldSysPath.setAccessible( true );
		fieldSysPath.set( null, null );
		//----------------------------------------------

		//3) saber cuales son las teclas
		char[] letras=new char[TECLAS.length];
		for(int i=0; i < TECLAS.length; i++)
		{
			texto=p.getProperty(TECLAS[i]);
			if(texto==null) throw new MissingFormatArgumentException("Debe existir la propiedad \""+TECLAS[i]+"\"");

			if(texto.length()>1 || !Character.isLetter(texto.charAt(0))) throw new IllegalArgumentException("La propiedad "+TECLAS[i]+" debe ser una sola letra");
			letras[i]=texto.charAt(0);
		}

		//4) saber cuales son los encabezados de los mensajes
		String[] encabezados=new String[MENSAJES.length];
		for(int i=0; i < encabezados.length; i++)
		{
			texto=p.getProperty(MENSAJES[i]);
			if(texto==null) throw new MissingFormatArgumentException("Debe existir la propiedad \""+MENSAJES[i]+"\"");

			encabezados[i]=texto;
		}

		mundo=new Control(this, comSocket, letras, encabezados);
		// Create and set up the window.
		setTitle("Robocol");
		setSize(1000, 800);
		setIconImage(new ImageIcon(Control.FOLDER+"logo.png").getImage());
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new BorderLayout());

		JPanel aux=new JPanel();
		aux.setLayout(new GridLayout(2,1));

		pvi=new PanelVideo();
		add(pvi, BorderLayout.CENTER);

		p2D=new PanelGraphic(this);
		aux.add(p2D);

		pc=new PanelComunicacion(this);
		aux.add(pc);
		add(aux, BorderLayout.EAST);

		p3D=new Panel3D();
		p3D.main();
		// Display the window.
		setVisible(true);
	}

	public void enviarCaracterLeido(char c)
	{mundo.enviarOrden(c);}

	public Control getMundo() {return mundo;}

	public void Graficar_3D(char key)
	{p3D.procesarComando(key);}

	public void Graficar_2D(char key)
	{p2D.procesarComando(key);}

	public void displayInfoRecibida(String mensajeDelOtro)
	{pc.displayInfoRecibida(mensajeDelOtro);}

	public void displayInfoEnviada(String orden)
	{pc.displayInfoEnviada(orden);}
}