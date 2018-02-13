
import java.util.Random;
public class MultiplicationGame extends MyGameEngine
{
    private int[] ans = new int[4];
    private int count = 0;
    
    public MultiplicationGame()
    {
    	super(4);
    	
    	SetTitle("Š|‚¯ZƒQ[ƒ€!!");
    }
    
    public void MakeAnswers() 
    {
    	Random rnd = new Random();
		
		// Create Answer Random
		while( count < GetNumberOfAnswers() )
		{
			SetAnswerNumber(count, rnd.nextInt(9));
			
			count++;
		}
		count = 0;
    }
	public String DispQuestion()
	{
		ans = GetAnswerNumber();
		return (String.valueOf(ans[0]) + " ~ " + String.valueOf(ans[1]) + " ~ " + String.valueOf(ans[2]) + " ~ " + String.valueOf(ans[3]));
	}

	public int Answer()
	{
		int x = ans[0] * ans[1] * ans[2] * ans[3];
		return x;
	}
    
	public String Judge()
	{
		int [] inputAnswer = new int[4];
		inputAnswer = GetInputNumber();
		return (String.valueOf(inputAnswer[0]) + String.valueOf(inputAnswer[1]) + String.valueOf(inputAnswer[2]) + String.valueOf(inputAnswer[3]));
	}
}