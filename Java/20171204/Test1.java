
public class Test1 extends GameEngine {
	
    /** 
     * �R���X�g���N�^�̒�`�ύX
     * �������p���\�b�h�̃��[�J������h�~
     * �e�Q�[�����Ɉˑ����������o�֐����ł�
     * for���[�v���ɂ���ӂȌĂяo�����o���Ȃ�
     */
    public void init() {
        setTitle( "Test1" );
        setRule( "Hello,World1" );
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
    public boolean judge(){
    	
    	System.out.println(getTitle() + getRule());
    	return true;
    }
    
    // �o�ߕ\�����s�����\�b�h�̒ǉ�
    public void progressDisplay(){}
    
    // ���ʕ\�����s�����\�b�h�̒ǉ�
	public void doneDisplay(){}
}