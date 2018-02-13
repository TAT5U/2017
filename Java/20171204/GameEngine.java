
abstract public class GameEngine {
	
    // title��rule���uprotected�v�ɕύX
    /** �^�C�g�� */
    protected String title = "";
	
    /** ���[������ */
    protected String rule ="";

    /** 
     * �R���X�g���N�^�̒�`�ύX
     * �������p���\�b�h�̃��[�J������h�~
     * �e�Q�[�����Ɉˑ����������o�֐����ł�
     * for���[�v���ɂ���ӂȌĂяo�����o���Ȃ�
     */
    public void init() {
        
    }

    /**
     * ��������͂���
     * ���͓��e�ɂ��Ă̓Q�[���Ɉˑ�����\����
     * �����̂Řg�g�݂�����p�ӂ��Ă����C���[�W
     */
    public void inputAnswer() {
    
    }

    /**
     * �Q�[���̌��ʔ�����s��
     * 
     * @return �Q�[���N���A�Ȃ�true�A����ȊO��false�B
     */
    abstract public boolean judge();
    
    // ���ʕ\�����s�����\�b�h�̒ǉ�
    abstract public void progressDisplay();
    
    // ���ʕ\�����s�����\�b�h�̒ǉ�
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