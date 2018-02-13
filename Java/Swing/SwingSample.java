import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Container;
import java.awt.BorderLayout;




class SwingSample extends JFrame
{
	public static void main(String[] args)
	{
		SwingSample frame = new SwingSample();
		frame.setVisible(true);
	}
	
	private SwingSample()
	{
		setTitle("タイトル");
		setSize(300, 200);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		CreateComponent();
	}
	
	private void CreateComponent()
	{
		JPanel panel = new JPanel();
		
		SwingLabel label = new SwingLabel();
		panel.add(label);
		
		SwingButton button = new SwingButton(label.getText());
		panel.add(button);
		
		Container content = getContentPane();
		content.add(panel, BorderLayout.CENTER);
	}
}