/*Program.cs*/

/*2017-08-01
    狩野 達哉
        Chap-5*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ContinueSample
{
    class Program
    {
        //List5-13
        //forループの中でcontinueする例
        //static void Main(string[] args)
        //{
        //    //入力された値と割られる値を格納する変数
        //    int n = 0, div = 1000;

        //    //表示
        //    Console.WriteLine("整数値を5回入力してください。");

        //    //ループ
        //    for (int i = 1; i <= 5; i++)
        //    {
        //        //整数値を入力させて格納
        //        Console.Write("> ");
        //        n = int.Parse(Console.ReadLine());

        //        //0が入力されたらcontinue
        //        if (n == 0)
        //        {
        //            Console.WriteLine("0では割れません。再入力してください。");
        //            continue;
        //        }

        //        //表示
        //        Console.Write("{0} / {1} = ", div, n);

        //        //入力された値で割って格納
        //        div /= n;

        //        //割った値を表示
        //        Console.WriteLine(div);
        //    }

        //    //入力待ち状態にして確認する
        //    Console.WriteLine("終了するには何かキーを押してください。");
        //    Console.Read();
        //}

        //List5-14
        //whileループの中でcontinueする例
        //whileでcontinueに入るとそこはカウントされない
        static void Main(string[] args)
        {
            //カウントと入力された値と割られる値を格納する変数
            int i = 1, n = 0, div = 1000;

            //表示
            Console.WriteLine("整数値を5回入力してください。");

            //カウントが5を超えたら終了
            while (i <= 5)
            {
                //整数値を入力させて格納
                Console.Write("> ");
                n = int.Parse(Console.ReadLine());

                //0が入力されたらcontinue
                if (n == 0)
                {
                    Console.WriteLine("0では割れません。再入力してください。");
                    continue;
                }

                //表示
                Console.Write("{0} / {1} = ", div, n);

                //入力された値で割って格納
                div /= n;

                //割った値を表示
                Console.WriteLine(div);

                //カウント
                i++;
            }

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
