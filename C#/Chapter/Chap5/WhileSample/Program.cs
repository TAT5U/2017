/*Program.cs*/

/*2017-08-01
    狩野 達哉
        Chap-5*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WhileSample
{
    class Program
    {
        //List5-10
        //while文の例
        static void Main(string[] args)
        {
            //入力された値と合計値を格納する変数
            int n = 0, sum = 0;

            //整数値を入力させて格納
            Console.Write("整数値> ");
            n = int.Parse(Console.ReadLine());

            //入力された値が0以下だったら終了
            while (n > 0)
            {
                //合計値を格納
                sum += n;

                //整数値を入力させて格納
                Console.Write("整数値> ");
                n = int.Parse(Console.ReadLine());
            }

            //合計値を表示
            Console.WriteLine("合計値は{0}です。", sum);

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
