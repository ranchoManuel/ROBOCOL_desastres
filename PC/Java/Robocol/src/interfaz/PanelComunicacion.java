package interfaz;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class PanelComunicacion extends JPanel implements KeyListener, ActionListener
{
	private static final long serialVersionUID=1L;
	private static final String newline=System.getProperty("line.separator");

	private JTextArea displayAreaRecivo;
	private JTextField typingArea;
	private InterfazPrincipal ventana;
	private JTextArea displayAreaEnvio;

	public PanelComunicacion(InterfazPrincipal padre)
	{
		ventana=padre;
		// Set up the content pane.
		JButton button=new JButton("Clear");
		button.addActionListener(this);

		typingArea=new JTextField(30);
		typingArea.addKeyListener(this);

		displayAreaEnvio=new JTextArea();
		displayAreaEnvio.setEditable(false);
		displayAreaEnvio.setBackground(Color.BLACK);
		displayAreaEnvio.setForeground(Color.WHITE);
		JScrollPane scrollPaneenvio=new JScrollPane(displayAreaEnvio);
		scrollPaneenvio.setPreferredSize(new Dimension(425, 200));
		
		displayAreaRecivo=new JTextArea();
		displayAreaRecivo.setEditable(false);
		displayAreaRecivo.setBackground(Color.BLACK);
		displayAreaRecivo.setForeground(Color.GREEN);
		JScrollPane scrollPanerecivo=new JScrollPane(displayAreaRecivo);
		scrollPanerecivo.setPreferredSize(new Dimension(375, 200));

		setLayout(new BorderLayout());
		add(typingArea, BorderLayout.NORTH);
		JPanel contenedor=new JPanel();
		contenedor.setLayout(new GridLayout(2,1));
		contenedor.add(scrollPaneenvio);
		contenedor.add(scrollPanerecivo);
		add(contenedor, BorderLayout.CENTER);
		add(button, BorderLayout.SOUTH);
	}
	
	/** Handle the key typed event from the text field. */
	public void keyTyped(KeyEvent e)
	{
		ventana.enviarCaracterLeido(e.getKeyChar());
		typingArea.setText("");
	}

	//No hace nada
	public void keyPressed(KeyEvent e){}

	//No hace nada
	public void keyReleased(KeyEvent e){}

	/** Handle the button click. */
	public void actionPerformed(ActionEvent e)
	{
		// Clear the text components.
		displayAreaRecivo.setText("");
		displayAreaEnvio.setText("");
		typingArea.setText("");

		// Return the focus to the typing area.
		typingArea.requestFocusInWindow();
	}

	public void displayInfoRecivida(String info)
	{
		displayAreaRecivo.append(info+newline);
		displayAreaRecivo.setCaretPosition(displayAreaRecivo.getDocument().getLength());
	}

	public void displayInfoEnviada(String info)
	{
		displayAreaEnvio.append(info+newline);
		displayAreaEnvio.setCaretPosition(displayAreaEnvio.getDocument().getLength());
	}
}