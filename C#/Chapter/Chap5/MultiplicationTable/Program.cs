/*2017-06-08
    狩野 達哉
        Chap5-EX*/
        
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiplicationTable
{
    class Program
    {
        static void Main(string[] args)
        {
            //九九の数値と結果を格納する変数
            int x = 1, y = 1, ans = 0;

            //表示
            Console.WriteLine("   *  *  *   九九の表   *  *  *");
            Console.WriteLine("   |   1   2   3   4   5   6   7   8   9");
            Console.WriteLine("-----------------------------------------");

            //九九を表示するループ  縦
            while (y<10)
            {
                //表示
                Console.Write(y+"  |");

                //九九を表示するループ  横
                while (x<10)
                {
                    //計算した結果が10以下の場合に桁を合わせるために空白を1つ表示する
                    if ((ans=x*y)<10)
                    {
                        Console.Write(" ");
                    }

                    //結果を表示
                    Console.Write("  "+ans);

                    //カウント
                    x++;
                }
                //改行
                Console.Write("\n");

                //横のカウントを初期化
                x = 1;

                //カウント
                y++;
            }

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
