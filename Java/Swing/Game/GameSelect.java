import java.lang.reflect.Method;
	
public class GameSelect
{
    private static String[] gameName_ = new String[2];
    private static int gameCount_ = 0;
    
    public static void main(String[] args) 
    {
    	String[] name = {"HitAndBlow", "MultiplicationGame"};
    	SetGame(name);
        System.out.println("プレイしたいゲームの数字を入力してね!\n");
        DispGameName();
        SelectGame(InputNumberCheck());
    }
    
    // HACK: 入力された値を格納した後にチェックを行っているので冗長的
    //		 do-while文を使わずに書くにはこの方法
    private static int InputNumberCheck()
    {
    	int gameNumber = 0;
    	gameNumber = Input.getInt();
    	
    	while ( gameNumber > gameName_.length || gameNumber <= 0 )
    	{
    		System.out.println("入力された番号が不正です。\nもう一度入力してください。\n");
    		gameNumber = Input.getInt();
    	}
    	return gameNumber;
    }
    
    private static void SetGame(String[] game)
    {
    	while ( gameCount_ < gameName_.length )
    	{
    		gameName_[gameCount_] = game[gameCount_];
    		gameCount_++;
    	}
    	gameCount_ = 0;
    }
    
    private static void DispGameName()
    {
    	while ( gameCount_ < gameName_.length )
    	{
    		System.out.println((gameCount_ + 1) + "番 " + gameName_[gameCount_] + "\n");
    		gameCount_++;
    	}
    	gameCount_ = 0;
    }
    
    // 入力された番号からゲームを選んで実行する
    private static void SelectGame(int num)
    {
    	System.out.println(num + "番の" + gameName_[num - 1] + "を開始します!!\n");
    	
    	String playGameName = "PlayGame_" + gameName_[num - 1];
    	
    	// 動的にクラスのインスタンスを作成
    	// try-catch文で必ず例外処理を記述する
    	try
    	{
    		// クラスを生成
    		// <?>でワイルドカードを使用してどの型にでも対応
    		Class<?> gameClassName = Class.forName(playGameName);
    		
    		// インスタンスを生成
    		Object obj = gameClassName.newInstance();
    	}
    	catch(ReflectiveOperationException e)
    	{
    		// printStackTraceを記述することで
    		// 例外時のクラス名などを表示することができる
            e.printStackTrace();
        }
    }
}