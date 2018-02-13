/***********************************************************
 * ゲームエンジンを使用する前提でのHitAndBlow本体
 *
 * 下記のようにロジックは担当のクラスに機能を委譲して
 * メインは全体の流れのみを記述する
 ***********************************************************/

public class HitAndBlow2 {

    /**
     * @param args
     */
    public static void main(String[] args) {
        GameEngine ge = new GameEngine(3);
        /*
         *  countはチャレンジ数
         */
        int count = 0;

        System.out.println(ge.getTitle());
        System.out.println(ge.getRule());
        
        //ランダムな答えを作成する
        ge.makeAnswers();
        
        while (true) {
            count++;
            System.out.println("*** "+count + "回目 ***");
            //インプット
            for (int i = 0; i < ge.getNumberOfAnswers(); i++) {
                System.out.print( (i + 1) + "個目 : ");
                ge.inputAnswer(i);
            }
            //答え判断
            boolean end=ge.judge();
            //終了判断
            System.out.println("ヒット:" + ge.getHit()
                            + " ブロー:" + ge.getBlow());
            if (end) {
                System.out.println("あがり！");
                break;
            }else{
                System.out.println();
            }
        }
    }
}