package experimento3D;
import java.awt.BorderLayout;
import javax.swing.JFrame;

public class InterfazPrincipal extends JFrame
{
	private static final long serialVersionUID=1L;
	private PanelComunicacion pc;
	private Panel3D pg;

	public static void main(String[] args)
	{
		new InterfazPrincipal();
	}
	
	public InterfazPrincipal()
	{
		setTitle("Juegos Geometria");
		setSize(600, 600);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new BorderLayout());

		pg=new Panel3D();
		pg.main();
		
		pc=new PanelComunicacion(this);
		add(pc, BorderLayout.CENTER);
		// Display the window.
		setVisible(true);
	}
	
	public void enviarCaracterLeido(char keyChar)
	{
		pg.procesarComando(keyChar);
	}
	
}