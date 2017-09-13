/*Program.cs*/

/*2017-07-20
    狩野 達哉
        Chap-5*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ForSample
{
    class Program
    {
        //List5-6
        //1から10まで表示
        //static void Main(string[] args)
        //{
        //    //ループ
        //    for (int i = 1; i <= 10; i++)
        //    {
        //        Console.Write(i + " ");
        //    }

        //    //改行
        //    Console.WriteLine();
        //}

        //List5-7
        //1から30までの2で割れるものを3おきに降順に表示
        //static void Main(string[] args)
        //{
        //    //ループ
        //    //3ずつ減らしていく
        //    for (int i = 30; i >= 1; i -= 3)
        //    {
        //        //2で割り切れる時に表示
        //        if (i % 2 == 0)
        //        {
        //            Console.Write(i + " ");
        //        }
        //    }

        //    //改行
        //    Console.WriteLine();
        //}

        //List5-8
        //5行7列の＊を表示
        //static void Main(string[] args)
        //{
        //    //ループ
        //    //行
        //    for (int i = 1; i <= 5; i++)
        //    {
        //        //ループ
        //        //列
        //        for (int j = 1; j <= 7; j++)
        //        {
        //            Console.Write("＊");
        //        }


        //        //改行
        //        Console.WriteLine();
        //    }

        //    //改行
        //    Console.WriteLine();
        //}

        //List5-9
        //＊を行の数だけ表示
        static void Main(string[] args)
        {
            //ループ
            //行
            for (int i = 1; i <= 5; i++)
            {
                //ループ
                //列
                for (int j = 1; j <= i; j++)
                {
                    Console.Write("＊");
                }


                //改行
                Console.WriteLine();
            }

            //改行
            Console.WriteLine();
        }
    }
}
