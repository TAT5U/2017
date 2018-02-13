
abstract public class GameEngine {
	
    // titleとruleを「protected」に変更
    /** タイトル */
    protected String title = "";
	
    /** ルール説明 */
    protected String rule ="";

    /** 
     * コンストラクタの定義変更
     * 初期化用メソッドのローカル化を防止
     * 各ゲーム名に依存したメンバ関数名では
     * forループ等による一意な呼び出しが出来ない
     */
    public void init() {
        
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
    abstract public boolean judge();
    
    // 結果表示を行うメソッドの追加
    abstract public void progressDisplay();
    
    // 結果表示を行うメソッドの追加
    abstract public void doneDisplay();

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
}