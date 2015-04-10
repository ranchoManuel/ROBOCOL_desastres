package experimento2D;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

public class PanelGraphic extends JPanel
{
	private static final long serialVersionUID = 1L;

	private Graphics2D pantalla;

	private int ang;
	private Image image;

	public PanelGraphic(InterfazPrincipal padre)
	{
		setBorder(new TitledBorder(""));
		image=new ImageIcon("./data/plane.png").getImage();
	}

	public void paintComponent( Graphics g ) 
	{
		super.paintComponent(g);
		pantalla=(Graphics2D)g;
		pantalla.setRenderingHint( RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON );
		pantalla.setColor(Color.WHITE);
		pantalla.fillRect(0, 0, getWidth(), getHeight());

		dibujar();
	}

	private void dibujar()
	{
		pantalla.setColor(Color.RED);
		pantalla.drawString("NORTE",getWidth()/2-15, 10);
		pantalla.setColor(Color.BLACK);
		
		pantalla.translate(this.getWidth() / 2, this.getHeight() / 2);
		pantalla.rotate(Math.toRadians(ang));
//		pantalla.translate(-image.getWidth(null) / 2, -image.getHeight(null) / 2);
		pantalla.drawRect(-25, -50, 50, 100);
		pantalla.drawImage(image,-image.getHeight(null)/2,-image.getWidth(null)/2,null);
		//pantalla.drawString(""+Math.toDegrees(Math.toRadians(ang)),0, 0);
	}

	public void reset()
	{}

	public void procesarComando(char key)
	{
		if(key=='w')
		{
			ang++;
		}
		else if(key=='s')
		{
			ang--;			
		}
		
		repaint();
	}

}