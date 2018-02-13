import java.util.Random;

public class GameEngine {
	
    /** �^�C�g�� */
    private String title = "";
	
    /** ���[������ */
    private String rule ="";

    /** �𓚂��i�[����z�� */
    private int[] answer;

    /** ���͂������e��ێ�����z�� */
    private int[] input;

    /** �����̐����̐��B�����I�Ɋg�����鎖���l�����č쐬 */
    private int numberOfAnswers = 3;

    /** �����̕��B���̏ꍇ�A1����6�܂łƂȂ� */
    private int widthOfRandom = 10;

    /** �q�b�g�̐� */
    private int hit = 0;

    /** �u���[�̐� */
    private int blow = 0;
    
    //Tatsuya Add
    private int count = 0;
    
    /** 
     * �f�t�H���g�R���X�g���N�^�B
     * numberOfAnswers���f�t�H���g�l��3�̂܂܉^�p����ꍇ 
     */
    public GameEngine() 
    {
    
    }

    /** 
     * numberOfAnswers��ύX���A
     * �𓚂̐����̐���3�ȊO�ɂ������ꍇ�Ɏg��
     */
    public GameEngine(int numberOfAnswers) {
        this.numberOfAnswers = numberOfAnswers;
        answer = new int[numberOfAnswers];
        input = new int[numberOfAnswers];
        makeAnswers();
    }

    /**
     * �������쐬����B
     * �����̐����ύX����邱�Ƃ��l���AnumberOfAnswers�Əƍ�����B
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
     * input��answer��˂����킹��B
     * ���ׂ�hit�Ȃ�true�A����ȊO��false�B
     *
     * @return ���ׂ�hit�Ȃ�true�A����ȊO��false�B
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