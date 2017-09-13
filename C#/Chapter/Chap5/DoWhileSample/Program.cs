/*Program.cs*/

/*2017-08-01
    狩野 達哉
        Chap-5*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DoWhileSample
{
    class Program
    {
        //List5-11
        //do～whileの例
        //List5-10をdo～whileに書き直したもの
        static void Main(string[] args)
        {
            //入力された値と合計値を格納する変数
            int n = 0, sum = 0;


            //入力された値が0以下だったら終了
            //必ず1回は実行
            do
            {
                //整数値を入力させて格納
                Console.Write("整数値> ");
                n = int.Parse(Console.ReadLine());

                //合計値を格納
                sum += n;
            } while (n > 0);

            //合計値を表示
            Console.WriteLine("合計値は{0}です。", sum);

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
