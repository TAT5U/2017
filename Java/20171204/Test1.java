
public class Test1 extends GameEngine {
	
    /** 
     * コンストラクタの定義変更
     * 初期化用メソッドのローカル化を防止
     * 各ゲーム名に依存したメンバ関数名では
     * forループ等による一意な呼び出しが出来ない
     */
    public void init() {
        setTitle( "Test1" );
        setRule( "Hello,World1" );
    }

    /**
     * 答えを入力する
     * 入力内容についてはゲームに依存する可能性が
     * 高いので枠組みだけを用意しておくイメージ
     */
    public void inputAnswer() {
    
    }

    /**
     * ゲームの結果判定を行う
     * 
     * @return ゲームクリアならtrue、それ以外はfalse。
     */
    public boolean judge(){
    	
    	System.out.println(getTitle() + getRule());
    	return true;
    }
    
    // 経過表示を行うメソッドの追加
    public void progressDisplay(){}
    
    // 結果表示を行うメソッドの追加
	public void doneDisplay(){}
}