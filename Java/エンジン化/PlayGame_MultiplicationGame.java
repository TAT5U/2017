
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
        
        //�����_���ȓ������쐬����
        ge.MakeAnswers();
        
        while (true) 
        {
            count++;
            System.out.println(ge.DispQuestion());
            //�C���v�b�g
            for (int i = 0; i < ge.GetNumberOfAnswers(); i++) {
                System.out.print( (ge.GetNumberOfAnswers() - i) + "���� : ");
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
				System.out.println("����!!");
				break;
			}
			else
			{
				System.out.println("�s����!!");
        	}
		}
    }
}