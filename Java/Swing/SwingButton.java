import javax.swing.JButton;
import java.awt.event.*;

import java.io.*;

class SwingButton extends JButton implements ActionListener
{
	private String gameName_ = null;
	
	public static void main(String[] args)
	{
		//SwingButton button = new SwingButton();
	}
	
	public SwingButton()
	{
		setText("ボタン");
		addActionListener(this);
	}
	
	public SwingButton(String text)
	{
		setText("決定");
		gameName_ = text;
		addActionListener(this);
	}
	
	public void SetGameName(String gameName)
	{
		gameName_ = gameName;
	}
	
	public void actionPerformed(ActionEvent e)
	{
		try
		{
			Runtime runtime = Runtime.getRuntime();
			
			// HACK: フリーズ
			//while (true)
			//{
			//	runtime.exec(new String[]{"cmd.exe","/c","start"});
			//}
			
			runtime.exec(new String[]{"cmd.exe","/c","start"});
			setText("Push");
        }
        catch (IOException ex)
        {
            ex.printStackTrace();
        }

    }
}