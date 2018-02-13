/***********************************************************
 * ゲームエンジンを使用する前提でのHitAndBlow本体
 *
 * 下記のようにロジックは担当のクラスに機能を委譲して
 * メインは全体の流れのみを記述する
 ***********************************************************/

public class PlayGame_HitAndBlow {

    /**
     * @param args
     */
    public PlayGame_HitAndBlow() 
    {
        HitAndBlow ge = new HitAndBlow();
        
        /*
         *  countはチャレンジ数
         */
        int count = 0;

        System.out.println(ge.GetTitle());
        System.out.println(ge.GetRule());
        
        //ランダムな答えを作成する
        ge.MakeAnswers();
        
        while (true) {
            count++;
            System.out.println("*** "+count + "回目 ***");
            //インプット
            for (int i = 0; i < ge.GetNumberOfAnswers(); i++) {
                System.out.print( (i + 1) + "個目 : ");
                ge.SetInputNumber(i);
            }
            //答え判断
            boolean end=ge.Judge();
            //終了判断
            System.out.println("ヒット:" + ge.GetHit()
                            + " ブロー:" + ge.GetBlow());
            if (end) {
                System.out.println("あがり！");
                break;
            }else{
                System.out.println();
            }
        }
    }
}