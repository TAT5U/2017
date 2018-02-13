import java.util.Random;

public class Hit_Blow
{	
	public static void main(String[] args)
	{
		int[] ans = new int[3];
		int[] userAns = new int[3];
		int count = 0;
		Random rnd = new Random();
		
		// 乱数で答え生成
		while( count < 3 )
		{
			ans[count] = rnd.nextInt(9);
			
			// デバッグ表示
			//System.out.print(ans[count] + "\n");
			count++;
		}
		count = 0;
		
		// 表示
		System.out.print("Hit And Blow!!\n");
		System.out.print("ゲームスタート!!\n");
		System.out.print("\n3桁の数字を入力してください!!\n");
	
		while ( true )
		{
			int inputWork = Input.getInt();
			// 入力された値を取得
			while( count < 3 )
			{
				if((Integer.toString(inputWork).length() > 3) || (Integer.toString(inputWork).length() < 3))
				{
					System.out.print("値が不正です!!\n");
					break;
				}
				else
				{
					userAns[count] = Integer.parseInt(Integer.toString(inputWork).substring(count, count + 1));
				}
				count++;
			}
			count = 0;
			
				if(Integer.toString(inputWork).length() == 3)
				{
					String result = Judge(ans, userAns);
					System.out.print(result + "\n\n");
					if( Integer.valueOf(result.substring(4, 5)).intValue() == 3 )
					{
						break;
					}
				}
		}
		// 正解で終了
	}
	
	// 判定
	// Hit or Blow or No
	public static String Judge(int[] ansArgs, int[] userAnsArgs)
	{
		int cnt = 0;
		int hit = 0, blow = 0;
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
		
		String judgeResult = "Hit " + Integer.toString(hit) + "  Blow " + Integer.toString(blow);
		return judgeResult;
	}
}