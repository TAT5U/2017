
public class PlayGame_MultiplicationGame {

    /**
     * @param args
     */
    public PlayGame_MultiplicationGame()
    {
        MultiplicationGame ge = new MultiplicationGame();
        
        int count = 0;

        System.out.println(ge.GetTitle());
        System.out.println(ge.GetRule());
        
        //ランダムな答えを作成する
        ge.MakeAnswers();
        
        while (true) 
        {
            count++;
            System.out.println(ge.DispQuestion());
            //インプット
            for (int i = 0; i < ge.GetNumberOfAnswers(); i++) {
                System.out.print( (ge.GetNumberOfAnswers() - i) + "桁目 : ");
                ge.SetInputNumber(i);
            }

			int ans = ge.Answer();
			int maxCount = 4;
			maxCount = maxCount - String.valueOf(ans).length();
			int cnt = 0;
			
			String inputAns = "";
			
			while ( cnt < maxCount )
			{
				inputAns += "0";
				cnt++;
			}
			cnt = 0;
			
			if ( (inputAns + String.valueOf(ans)).equals(ge.Judge()) )
			{
				System.out.println("正解!!");
				break;
			}
			else
			{
				System.out.println("不正解!!");
        	}
		}
    }
}