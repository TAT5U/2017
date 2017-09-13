/*2017-06-01
    狩野 達哉
        Chap-5-2*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Division
{
    class Program
    {
        //List5-16
        //例題のソースコード
        static void Main(string[] args)
        {
            //割られる数と割る数の変数宣言
            int n1, n2;

            //続けるかどうかの文字を取得する変数
            string yn;
            do
            {
                //例外処理
                //割られる数・割る数が不正な値のときにメッセージを表示
                try
                {
                    //文字を表示
                    Console.Write("割られる数> ");

                    //入力された数をint型に変換して格納
                    n1 = int.Parse(Console.ReadLine());
                    do
                    {
                        //文字を表示
                        Console.Write("割る数> ");

                        //入力された数をint型に変換して格納
                        n2 = int.Parse(Console.ReadLine());

                        //割る数が0の場合エラー表示
                        if (n2==0)
                        {
                            //文字を表示
                            Console.WriteLine("0では割り切れません。再入力してください。");
                            continue;
                        }
                        //文字を表示 式を表示
                        Console.Write("{0} / {1} = ", n1, n2);

                        //どちらかが負数の場合の処理
                        if (n1<0&&n2>0)
                        {
                            Console.Write("-");
                            n1 = -n1;
                        }
                        else if (n1>0&&n2<0)
                        {
                            Console.Write("-");
                            n2 = -n2;
                        }

                        //割った結果を表示(整数部分)
                        Console.Write(n1 / n2);
                    } while (n2==0);
                }
                catch (FormatException ex)
                {

                    Console.WriteLine(ex.Message);
                    break;
                }

                //余りを格納する変数
                int remainder;

                //カウンタ
                int i = 1;

                //表示する最大桁数分ループさせる
                while (i<=50)
                {
                    //余りを格納
                    remainder = n1 % n2;

                    //余りが0なら終了
                    if (remainder==0)
                    {
                        break;
                    }
                    //余り*10を割られる数に格納
                    n1 = remainder * 10;

                    //最初なら小数点を表示
                    if (i==1)
                    {
                        Console.Write(".");
                    }

                    //割った結果を表示(小数部分)
                    Console.Write(n1 / n2);

                    //カウント
                    i++;
                }
                //文字を表示
                Console.Write("\n");

                //文字を表示
                Console.WriteLine("処理を続けますか? \'y\' / \'n\'");

                //文字を取得
                yn = Console.ReadLine();

            //「y」または「Y」ならループ、それ以外なら終了
            } while (yn=="y"||yn=="Y");

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
