/*Program.cs*/

/*2017-08-01
    狩野 達哉
        Chap-5*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BreakSample
{
    class Program
    {
        //List5-12
        //break文の例
        static void Main(string[] args)
        {
            //入力された値と合計値を格納する変数
            int n = 0, sum = 0;

            //表示
            Console.WriteLine("整数値を10回入力してください。");
            Console.WriteLine("途中で負数を入力したら終了します。");

            //ループ
            for (int i = 1; i <= 10; i++)
            {
                //整数値を入力させて格納
                Console.Write("> ");
                n = int.Parse(Console.ReadLine());

                //負数が入力されたらbreak
                if (n < 0)
                {
                    break;
                }

                //合計値を格納
                sum += n;
            }

            //合計値を表示
            Console.WriteLine("合計値は{0}です。", sum);

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
