import java.util.Random;

public class GameEngine {
	
    /** タイトル */
    private String title = "";
	
    /** ルール説明 */
    private String rule ="";

    /** 解答を格納する配列 */
    private int[] answer;

    /** 入力した内容を保持する配列 */
    private int[] input;

    /** 答えの数字の数。将来的に拡張する事を考慮して作成 */
    private int numberOfAnswers = 3;

    /** 乱数の幅。この場合、1から6までとなる */
    private int widthOfRandom = 10;

    /** ヒットの数 */
    private int hit = 0;

    /** ブローの数 */
    private int blow = 0;
    
    //Tatsuya Add
    private int count = 0;
    
    /** 
     * デフォルトコンストラクタ。
     * numberOfAnswersがデフォルト値の3のまま運用する場合 
     */
    public GameEngine() 
    {
    
    }

    /** 
     * numberOfAnswersを変更し、
     * 解答の数字の数を3以外にしたい場合に使う
     */
    public GameEngine(int numberOfAnswers) {
        this.numberOfAnswers = numberOfAnswers;
        answer = new int[numberOfAnswers];
        input = new int[numberOfAnswers];
        makeAnswers();
    }

    /**
     * 答えを作成する。
     * 答えの数が変更されることも考え、numberOfAnswersと照合する。
     */
    public void makeAnswers() {
    	Random rnd = new Random();
		
		// Create Answer Random
		while( count < 3 )
		{
			answer[count] = rnd.nextInt(9);
			
			count++;
		}
		count = 0;
    }

    /**
     * inputとanswerを突き合わせる。
     * すべてhitならtrue、それ以外はfalse。
     *
     * @return すべてhitならtrue、それ以外はfalse。
     */
    public boolean judge() {
    	JudgeHitBlow(getInput(), getAnswer());
    	if ( getHit() >= 3 )
    	{
    		return true;
    	}
    	return false;
    }

    public int getNumberOfAnswers() {
        return numberOfAnswers;
    }

    public int getWidthOfRandom() {
        return widthOfRandom;
    }

    public int[] getAnswer() {
        return answer;
    }

    public int getBlow() {
        return blow;
    }

    public int getHit() {
        return hit;
    }

    public int[] getInput() {
        return input;
    }

    public String getRule() {
        return rule;
    }
    public void setRule(String rule) {
        this.rule = rule;
    }
    public String getTitle() {
        return title;
    }
    public void setTitle(String title) {
        this.title = title;
    }
    
	// Hit or Blow or No
	private void JudgeHitBlow(int[] ansArgs, int[] userAnsArgs)
	{
		int cnt = 0;
		
		// Initialize
		hit = 0;
		blow = 0;
		
		while( cnt < 3 )
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