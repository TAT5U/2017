import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Container;
import java.awt.Graphics;


class TestPanel extends JPanel
{
	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.drawRect(0, 150, 300, 0);
		g.drawArc(75, 50, 100, 100, 0, 360);
	}
}

class GraphicTest {
	
	public static void main(String args[])
	{
		JFrame f = new JFrame();
		f.setDefaultCloseOperation
				(JFrame.EXIT_ON_CLOSE);
		f.setSize(300, 200);
		Container c = f.getContentPane();
		TestPanel p  = new TestPanel();
		c.add(p);
		AnimationPanel ani = new AnimationPanel(0, 0);
		c.add(ani);
		
		f.setVisible(true);
	}
}


