/*Program.cs*/

/*2017-08-01
    狩野 達哉
        Chap-5*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GotoSample
{
    class Program
    {
        //List5-15
        //多重ループをgotoで一気に脱出する例
        //構造がぐちゃぐちゃになるので使用は避ける
        static void Main(string[] args)
        {
            //カウントとそれぞれのカウントの合計値を格納する変数
            int i = 0, j = 0, k = 0, no =1;

            //多重ループ
            for (i = 1; i <= 10; i++)
            {
                for (j = 1; j <= 10; j++)
                {
                    for (k = 1; k <= 10; k++)
                    {
                        //それぞれのカウントの合計値を格納
                        no += (i + j + k);

                        //合計値が2000以上になったらgotoで脱出
                        if (no >= 2000)
                        {
                            goto OUT;
                        }
                    }
                }
            }

            //脱出先
            OUT:

            //それぞれのカウントと合計値を表示
            Console.WriteLine("i:{0} j:{1} k:{2} no:{3}", i, j, k, no);

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
