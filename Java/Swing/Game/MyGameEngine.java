abstract class MyGameEngine {
	
    // Title Name
    private String title = "";
	
    // Rule Text
    private String rule ="";

    // Answer
    private String[] answer;

    // Input Answer
    private String[] input;

    /** “š‚¦‚Ì”š‚Ì”B«—ˆ“I‚ÉŠg’£‚·‚é–‚ğl—¶‚µ‚Äì¬ */
    private int numberOfAnswers = 1;
    
    private int count = 0;
    
    public MyGameEngine() 
    {
    	answer = new String[numberOfAnswers];
    	input = new String[numberOfAnswers];
    }
    
    public MyGameEngine(int value) 
    {
        numberOfAnswers = value;
        answer = new String[numberOfAnswers];
        input = new String[numberOfAnswers];
    }
    
    public int GetNumberOfAnswers() 
    {
        return numberOfAnswers;
    }
    
    public String[] GetAnswer() 
    {
        return answer;
    }
    
    public String[] GetInput() 
    {
        return input;
    }
    
    
	public int[] GetAnswerNumber() 
    {
    	int[] ansNum = new int[numberOfAnswers];
    	
    	while ( count <  numberOfAnswers)
    	{
    		ansNum[count] = Integer.parseInt(answer[count]);
    		count++;
    	}
    	count = 0;
    	
        return ansNum;
    }
    
    public int[] GetInputNumber() 
    {
    	int[] inputNum = new int[numberOfAnswers];
    	
    	while ( count <  numberOfAnswers)
    	{
    		inputNum[count] = Integer.parseInt(input[count]);
    		count++;
    	}
    	count = 0;
    	
        return inputNum;
    }

    public String GetRule() 
    {
        return rule;
    }
    public void SetRule(String rule)
     {
        this.rule = rule;
    }
    public String GetTitle() 
    {
        return title;
    }
    public void SetTitle(String title) 
    {
        this.title = title;
    }
    
    
	public void SetAnswerNumber(int cnt, int value) 
    {
    	answer[cnt] = String.valueOf(value);
    }
    
    
    public void SetInputNumber(int cnt) 
    {
    	input[cnt] = String.valueOf(Input.getInt());
    }
}