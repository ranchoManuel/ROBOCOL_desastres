package clienteVideo;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.UIManager;
import uk.co.caprica.vlcj.component.EmbeddedMediaPlayerComponent;

public class InterfazCliente extends JFrame implements ActionListener
{
	private static final long serialVersionUID=1L;
	private static final String VLC_PATH = "./libs/video/";

	private final static String PLAY = "Play";
	private final static String STOP = "Stop";

	private static final String IP="10.5.5.9";
	private static final int PORT=8080;

	private JButton play;
	private JButton stop;

	private EmbeddedMediaPlayerComponent mediaPlayer;

	public static void main(String args[]) throws Exception
	{
		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		new InterfazCliente();
	}

	public InterfazCliente( ) throws Exception
	{
		//Logger logger = LoggerFactory.getLogger(getClass());
		System.setProperty("jna.library.path", VLC_PATH);
		// Inicializa el media component

		setLayout(new BorderLayout());
		mediaPlayer = new EmbeddedMediaPlayerComponent();
		add(mediaPlayer, BorderLayout.CENTER);
		setSize(900, 600);
		setTitle("Streaming de video");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocationRelativeTo(null);
		
		play = new JButton("Play");
		play.addActionListener(this);
		play.setActionCommand(PLAY);

		stop = new JButton("Stop");
		stop.addActionListener(this);
		stop.setActionCommand(STOP);

		JPanel opciones=new JPanel();
		opciones.setLayout(new GridLayout(1, 3));

		opciones.add(play);
		opciones.add(stop);

		// Se agrega el panel de botones a la interfaz
		add(opciones, BorderLayout.SOUTH);
		setVisible(true);
	}

	public void actionPerformed( ActionEvent e )
	{
		String comando=e.getActionCommand();

		if(comando.equals(PLAY)) conectarStreaming( IP, PORT);
		else if(comando.equals(STOP)) mediaPlayer.getMediaPlayer().stop();
	}

	public void conectarStreaming( String nIp, int nPuerto )
	{
		//mediaPlayer.getMediaPlayer().playMedia("rtp://@" + nIp + ":" + nPuerto );
		//mediaPlayer.getMediaPlayer().playMedia("http://" + nIp + ":" + nPuerto );
		//mediaPlayer.getMediaPlayer().playMedia("http://10.5.5.9:8080/live/amba.m3u8");
		mediaPlayer.getMediaPlayer().playMedia("udp://@:10000");
	}
}