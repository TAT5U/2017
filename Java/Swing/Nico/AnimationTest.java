import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;
import java.awt.Container;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

class AnimationPanel 
	extends JPanel implements ActionListener
{
	Timer pTimer;
	int width, height;
	int x = 0, y = 0;
	int d = 10, dx = 1,dy = 1;
	
	public AnimationPanel(int w, int h)
	{
		width = w;
		height = h;
		pTimer = new Timer(200, this);
		pTimer.setActionCommand("timer");
		pTimer.start();
	}
	
	public void start()
	{
		//pTimer.start();
	}
	
	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.drawArc(x, y, 100, 100, 0, 360);
		g.drawArc(x + 20, y + 40, 10, 10, 0, 360);
		g.drawArc(x + 70, y + 40, 10, 10, 0, 360);
		g.drawArc(x + 25, y + 40, 50, 50, 0, -180);
		
		g.drawLine(0, height - 50, width, height - 50);
	}
	
	@Override
	public void actionPerformed( ActionEvent e )
	{
		if (x < 0 || x + 120 > width)
		{
			dx *= -1;
		}
		if (y < 0 || y + 160 > height)
		{
			dy *= -1;
		}
		
		x += d * dx;
		y += d * dy;
		repaint();
	}

}

class AnimationTest {
	
	public static void main(String args[])
	{
		JFrame f = new JFrame();
		f.setDefaultCloseOperation
				(JFrame.EXIT_ON_CLOSE);
		f.setSize(300, 200);
		f.setTitle("MovingSmiley");
		f.setResizable(false);
		//Container c = f.getContentPane();
		AnimationPanel p  = new AnimationPanel(300,200);
		f.getContentPane().add(p);
		p.start();
		
		f.setVisible(true);
	}
}
