/***********************************************************
 * �Q�[���G���W�����g�p����O��ł�HitAndBlow�{��
 *
 * ���L�̂悤�Ƀ��W�b�N�͒S���̃N���X�ɋ@�\���Ϗ�����
 * ���C���͑S�̗̂���݂̂��L�q����
 ***********************************************************/

public class PlayGame_HitAndBlow {

    /**
     * @param args
     */
    public PlayGame_HitAndBlow() 
    {
        HitAndBlow ge = new HitAndBlow();
        
        /*
         *  count�̓`�������W��
         */
        int count = 0;

        System.out.println(ge.GetTitle());
        System.out.println(ge.GetRule());
        
        //�����_���ȓ������쐬����
        ge.MakeAnswers();
        
        while (true) {
            count++;
            System.out.println("*** "+count + "��� ***");
            //�C���v�b�g
            for (int i = 0; i < ge.GetNumberOfAnswers(); i++) {
                System.out.print( (i + 1) + "�� : ");
                ge.SetInputNumber(i);
            }
            //�������f
            boolean end=ge.Judge();
            //�I�����f
            System.out.println("�q�b�g:" + ge.GetHit()
                            + " �u���[:" + ge.GetBlow());
            if (end) {
                System.out.println("������I");
                break;
            }else{
                System.out.println();
            }
        }
    }
}