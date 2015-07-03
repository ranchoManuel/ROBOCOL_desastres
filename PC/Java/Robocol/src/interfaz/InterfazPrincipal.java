package interfaz;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.io.FileInputStream;
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
	private static final String modoDeComunicacion="ComunicacionPorSocket";
	private static final String[] teclas={"Tecla.Up","Tecla.Down","Tecla.Left","Tecla.Rigth","Tecla.Up_b1","Tecla.Down_b1","Tecla.Up_b2","Tecla.Down_b2","Tecla.SensoresADC","Tecla.Acel_Magn","Tecla.Acel_Continuo","Tecla.Acel_End","Tecla.Acel_Ter","Tecla.Toggle_Luz","Tecla.Toggle_Buzzer"};
	private static final String[] mensajes={"Mensaje.Orugas","Mensaje.Brazos","Mensaje.SensoresADC","Mensaje.Acel_Magn","Mensaje.Acel_Continuo","Mensaje.Acel_end","Mensaje.Acel_ter","Mensaje.Toggle_Luz","Mensaje.Toggle_Buzzer"};

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
		String texto=p.getProperty(modoDeComunicacion);
		if(texto==null) throw new MissingFormatArgumentException("Debe existir la propiedad \""+modoDeComunicacion+"\"");

		boolean comSocket = texto.equals("true");
		if(!comSocket && !texto.equals("false")) throw new IllegalArgumentException("La propiedad ComunicacionPorSocket debe ser \"true\" o \"false\"");

		//1) saber cuales son las teclas
		char[] letras=new char[teclas.length];
		for(int i=0; i < teclas.length; i++)
		{
			texto=p.getProperty(teclas[i]);
			if(texto==null) throw new MissingFormatArgumentException("Debe existir la propiedad \""+teclas[i]+"\"");

			if(texto.length()>1 || !Character.isLetter(texto.charAt(0))) throw new IllegalArgumentException("La propiedad "+teclas[i]+" debe ser una sola letra");
			letras[i]=texto.charAt(0);
		}

		//2) saber cuales son los encabezados de los mensajes
		String[] encabezados=new String[mensajes.length];
		for(int i=0; i < encabezados.length; i++)
		{
			texto=p.getProperty(mensajes[i]);
			if(texto==null) throw new MissingFormatArgumentException("Debe existir la propiedad \""+mensajes[i]+"\"");

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
//		
//		long t0=System.currentTimeMillis();
//		while(System.currentTimeMillis()-t0<7000);
//		mundo.prenderThread();
	}

	public void enviarCaracterLeido(char c)
	{
		mundo.enviarOrden(c);		
	}

	public Control getMundo() {return mundo;}

	public void Graficar_3D(char key)
	{
		p3D.procesarComando(key);
	}

	public void Graficar_2D(char key)
	{
		p2D.procesarComando(key);
	}

	public void displayInfoRecivida(String mensajeDelOtro)
	{
		pc.displayInfoRecivida(mensajeDelOtro);
	}

	public void displayInfoEnviada(String orden)
	{
		pc.displayInfoEnviada(orden);
	}
}