import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;
import java.awt.Container;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

class GamePanel extends JPanel implements ActionListener, KeyListener
{
	Timer timer_;
	int width_, height_;
	int x_ = 30, y_ = 0;
	int d_ = 10, dX_ = 1,dY_ = 1;
	
	int padY_ = 50;
	int pd_ = 0;
	int padWidth_ = 8, padHeight_ = 30;
	
	int ballSize_ = 10;
	
	public GamePanel(int w, int h)
	{
		width_ = w;
		height_ = h;
		
		setBackground(Color.black);
		timer_ = new Timer(200, this);
		
		// KeyEventを有効化するために必要
		addKeyListener(this);
	}
	
	public void start()
	{
		timer_.start();
	}
	
	@Override
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g);
		g.setColor(Color.white);
		g.fillOval(x_ , y_ , ballSize_, ballSize_);
		g.fillRect(20 , padY_, padWidth_, padHeight_);
	}
	
	@Override
	public void actionPerformed( ActionEvent e )
	{
		bound();
		
		x_ += d_ * dX_;
		y_ += d_ * dY_;
		padY_ += pd_;
		repaint();
	}
	
	private void bound()
	{
		if (x_ + ballSize_ >= width_)
		{
			dX_ *= -1;
		}
		if (y_ < 0 || y_ + ballSize_ >= height_)
		{
			dY_ *= -1;
		}
		
		
		if ((x_ <= 20 && x_ >= padWidth_) && (y_ > padY_ && y_ < padY_ + padHeight_))
		{
			dX_ *= -1;
			dY_ *= -1;
		}
	}
	
	private void padAttack()
	{

	}
	
	
/***********************KeyEvent***********************/
	@Override
	public void keyPressed(KeyEvent e)
	{
		if (e.getKeyCode() == KeyEvent.VK_UP)
		{
			pd_ = -10;
		}
		else if (e.getKeyCode() == KeyEvent.VK_DOWN)
		{
			pd_ = 10;
		}
	}
	
	@Override
	public void keyReleased(KeyEvent e)
	{
		pd_ = 0;
	}
	
    @Override
	public void keyTyped(KeyEvent e)
	{
		
	}
	
	@Override
	public boolean isFocusable() 
	{
		return true;
	}
/******************************************************/
}


class GameTest {
	
	public static void main(String args[])
	{
		JFrame f = new JFrame();
		f.setDefaultCloseOperation
				(JFrame.EXIT_ON_CLOSE);
		f.setSize(300, 200);
		f.setTitle("GameTest");
		f.setResizable(false);
		//Container c = f.getContentPane();
		GamePanel p  = new GamePanel(300,200);
		f.getContentPane().add(p);
		p.start();
		
		f.setVisible(true);
	}
}
