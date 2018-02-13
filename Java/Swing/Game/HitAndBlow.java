
import java.util.Random;

public class HitAndBlow extends MyGameEngine
{

    /** ヒットの数 */
    private int hit = 0;

    /** ブローの数 */
    private int blow = 0;
    
    private int count = 0;
    
    public HitAndBlow()
    {
    	super(3);
    	
    	SetTitle("ヒット アンド ブローゲーム!!");
    }
    
    public void MakeAnswers() {
    	Random rnd = new Random();
		
		// Create Answer Random
		while( count < GetNumberOfAnswers() )
		{
			SetAnswerNumber(count, rnd.nextInt(9));
			
			count++;
		}
		count = 0;
    }
    
    public boolean Judge() {
    	JudgeHitBlow(GetInputNumber(), GetAnswerNumber());
    	if ( GetHit() >= 3 )
    	{
    		return true;
    	}
    	return false;
    }

    public int GetBlow() {
        return blow;
    }

    public int GetHit() {
        return hit;
    }
    
	// Hit or Blow or No
	private void JudgeHitBlow(int[] ansArgs, int[] userAnsArgs)
	{
		int cnt = 0;
		
		// Initialize
		hit = 0;
		blow = 0;
		
		while( cnt < GetNumberOfAnswers() )
		{
			if( userAnsArgs[cnt] == ansArgs[cnt] )
			{
				hit++;
			}
			else
			{
				if( (cnt - 1 >= 0) &&(userAnsArgs[cnt] == ansArgs[cnt - 1]) )
				{
					blow++;
				}
				else if( (cnt + 1 <= 2) && (userAnsArgs[cnt] == ansArgs[cnt + 1]))
				{
					blow++;
				}
				else if( (cnt - 2 > -1 ) && (userAnsArgs[cnt] == ansArgs[cnt - 2]) )
				{
					blow++;
				}
				else if( (cnt + 2 < 3) && (userAnsArgs[cnt] == ansArgs[cnt + 2]) )
				{
					blow++;
				}
			}
			cnt++;
		}
		cnt = 0;
	}
}