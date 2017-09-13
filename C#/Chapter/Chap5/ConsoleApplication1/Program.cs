/*2017-05-11
    狩野 達哉
        Chap-5*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        //List5-1
        //文字の表示
        //static void Main(string[] args)
        //{
        //    //文字を表示
        //    Console.WriteLine("これがコンソールアプリケーションです。");

        //    //入力待ち状態にして確認する
        //    Console.WriteLine("終了するには何かキーを押してください。");
        //    Console.Read();
        //}

        //List5-2
        //値の表示
        //static void Main(string[] args)
        //{
        //    //変数に値を格納
        //    int a = 10;
        //    string s = "こんにちは";

        //    //変数aの値を改行しないで表示
        //    Console.Write(a);

        //    //変数sの値を改行して表示
        //    Console.WriteLine(s);

        //    //sとaを表示
        //    Console.WriteLine(s + "、aの値は" + a + "です。");

        //    //入力待ち状態にして確認する
        //    Console.WriteLine("終了するには何かキーを押してください。");
        //    Console.Read();
        //}

        //List5-3
        //引数で指定して値を表示する
        //static void Main(string[] args)
        //{
        //    //変数に値を格納
        //    int a = 10;
        //    string s = "こんにちは";

        //    //引数を使って表示する{}を使う
        //    Console.WriteLine("{0}、aの値は{1}です。", s, a);

        //    //入力待ち状態にして確認する
        //    Console.WriteLine("終了するには何かキーを押してください。");
        //    Console.Read();
        //}

        //List5-4
        //書式を指定して値を表示する
        //static void Main(string[] args)
        //{
        //    //通貨表示
        //    Console.WriteLine("{0:C}", 1000);

        //    //16進数表示
        //    Console.WriteLine("{0:X}", 250);

        //    //数値表示
        //    Console.WriteLine("{0:N}", 2500000);

        //    //小数点以下の桁数指定
        //    Console.WriteLine("{0:F3}", 123.45678);

        //    //%表示
        //    Console.WriteLine("{0:P}", 2.0 / 3.0);

        //    //入力待ち状態にして確認する
        //    Console.WriteLine("終了するには何かキーを押してください。");
        //    Console.Read();
        //}

        //List5-5
        //キーボードから入力する
        static void Main(string[] args)
        {
            //科目を入力させて格納
            Console.Write("科目> ");
            string subject = Console.ReadLine();

            //入力された点数をint型で変換して格納
            Console.Write("点数> ");
            int score = int.Parse(Console.ReadLine());

            //入力された平均点をdouble型で変換して格納
            Console.Write("平均点> ");
            double average = double.Parse(Console.ReadLine());

            //格納された科目・点数・平均点を表示
            Console.WriteLine("{0}は{1}点(平均{2}点)", subject, score, average);

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
