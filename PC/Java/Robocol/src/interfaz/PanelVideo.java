package interfaz;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;

import uk.co.caprica.vlcj.component.EmbeddedMediaPlayerComponent;

public class PanelVideo extends JPanel implements ActionListener
{
	private static final long serialVersionUID=1L;

	private final static String PLAY_STOP = "Play_Stop";
	private static final String PLAY = "Play";
	private static final String STOP = "Stop";

	private JButton play_stop;

	private String ip;
	private int port;

	private EmbeddedMediaPlayerComponent mediaPlayer;

	public PanelVideo(String ipP, int portP, String vlcPath)
	{
		ip=ipP;
		port=portP;
		System.setProperty("jna.library.path", vlcPath);

		setLayout(new BorderLayout());
		mediaPlayer = new EmbeddedMediaPlayerComponent();
		add(mediaPlayer, BorderLayout.CENTER);

		play_stop = new JButton(PLAY);
		play_stop.addActionListener(this);
		play_stop.setActionCommand(PLAY_STOP);

		add(play_stop, BorderLayout.SOUTH);
		setVisible(true);
	}

	public void actionPerformed( ActionEvent e )
	{
		String comando=e.getActionCommand();

		if(comando.equals(PLAY_STOP)) 
		{
			if(play_stop.getText().equals(PLAY))
			{
				conectarStreaming();
				play_stop.setText(STOP);
			}
			else
			{
				mediaPlayer.getMediaPlayer().stop();
				play_stop.setText(PLAY);				
			}
		}
	}

	public void conectarStreaming()
	{
		//rtsp://@192.168.0.145:1234/
		//mediaPlayer.getMediaPlayer().playMedia("rtp://@" + nIp + ":" + nPuerto );
		//mediaPlayer.getMediaPlayer().playMedia("http://" + nIp + ":" + nPuerto );
		//mediaPlayer.getMediaPlayer().playMedia("http://10.5.5.9:8080/live/amba.m3u8");
		//mediaPlayer.getMediaPlayer().playMedia("./data/video.mp4");
		mediaPlayer.getMediaPlayer().playMedia("udp://@:"+port);
	}
}