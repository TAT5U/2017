/***********************************************************
 * �Q�[���G���W�����g�p����O��ł�HitAndBlow�{��
 *
 * ���L�̂悤�Ƀ��W�b�N�͒S���̃N���X�ɋ@�\���Ϗ�����
 * ���C���͑S�̗̂���݂̂��L�q����
 ***********************************************************/

public class HitAndBlow2 {

    /**
     * @param args
     */
    public static void main(String[] args) {
        GameEngine ge = new GameEngine(3);
        /*
         *  count�̓`�������W��
         */
        int count = 0;

        System.out.println(ge.getTitle());
        System.out.println(ge.getRule());
        
        //�����_���ȓ������쐬����
        ge.makeAnswers();
        
        while (true) {
            count++;
            System.out.println("*** "+count + "��� ***");
            //�C���v�b�g
            for (int i = 0; i < ge.getNumberOfAnswers(); i++) {
                System.out.print( (i + 1) + "�� : ");
                ge.inputAnswer(i);
            }
            //�������f
            boolean end=ge.judge();
            //�I�����f
            System.out.println("�q�b�g:" + ge.getHit()
                            + " �u���[:" + ge.getBlow());
            if (end) {
                System.out.println("������I");
                break;
            }else{
                System.out.println();
            }
        }
    }
}