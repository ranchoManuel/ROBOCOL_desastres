package experimento3D;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
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

	private JTextArea displayArea;
	private JTextField typingArea;
	private InterfazPrincipal ventana;

	public PanelComunicacion(InterfazPrincipal padre)
	{
		ventana=padre;
		// Set up the content pane.
		JButton button=new JButton("Clear");
		button.addActionListener(this);

		typingArea=new JTextField(20);
		typingArea.addKeyListener(this);

		displayArea=new JTextArea();
		displayArea.setEditable(false);
		displayArea.setBackground(Color.BLACK);
		displayArea.setForeground(Color.WHITE);
		JScrollPane scrollPane=new JScrollPane(displayArea);
		scrollPane.setPreferredSize(new Dimension(375, 125));

		setLayout(new BorderLayout());
		add(typingArea, BorderLayout.PAGE_START);
		add(scrollPane, BorderLayout.CENTER);
		add(button, BorderLayout.PAGE_END);
	}
	
	/** Handle the key typed event from the text field. */
	public void keyTyped(KeyEvent e)
	{
		ventana.enviarCaracterLeido(e.getKeyChar());
		typingArea.setText("");
		typingArea.requestFocusInWindow();
	}

	//No hace nada
	/** Handle the key pressed event from the text field. */
	public void keyPressed(KeyEvent e){}

	//No hace nada
	public void keyReleased(KeyEvent e){}

	/** Handle the button click. */
	public void actionPerformed(ActionEvent e)
	{
		// Clear the text components.
		displayArea.setText("");
		typingArea.setText("");

		// Return the focus to the typing area.
		typingArea.requestFocusInWindow();
	}

	public void displayInfo(String info)
	{
		displayArea.append(info+newline);
		displayArea.setCaretPosition(displayArea.getDocument().getLength());
	}
}