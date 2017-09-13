/*Program.cs*/

/*2017-07-01
    狩野 達哉
        DateTime構造体の仕組み*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DateTimeSample
{
    class Program
    {
        static void Main(string[] args)
        {
            //List6-10呼び出し
            dateTimePropertyExample();

            //改行
            Console.WriteLine();

            //List6-11呼び出し
            dateTimeAddExample();

            //改行
            Console.WriteLine();

            //List6-12呼び出し
            dateTimeToXxxxXxxxStringExample();

            //改行
            Console.WriteLine();

            //List6-13呼び出し
            dateTimeToStringExample();
        }

        //List6-10
        //DateTimeのプロパティ
        static void dateTimePropertyExample()
        {
            //日付表示(時間はすべて0で表示)
            Console.WriteLine("今日の日付 : " + DateTime.Today);

            //日付と時間を表示
            Console.WriteLine("現在の日付と日時 : " + DateTime.Now);

            //現在の日時と時間を取得
            DateTime now = DateTime.Now;

            //１つずつ表示
            Console.WriteLine("年 = " + now.Year);
            Console.WriteLine("月 = " + now.Month);
            Console.WriteLine("日 = " + now.Day);
            Console.WriteLine("時 = " + now.Hour);
            Console.WriteLine("分 = " + now.Minute);
            Console.WriteLine("秒 = " + now.Second);
            Console.WriteLine("曜日 = " + now.DayOfWeek);
        }

        //List6-11
        //Addメソッド
        //TimeSpanで指定した時間間隔を加算する
        static void dateTimeAddExample()
        {
            //現在の日時を取得
            DateTime now = DateTime.Now;

            //現在の日時の表示
            Console.WriteLine(now);

            //TimeSpan設定(時,分,秒)
            TimeSpan addSpan = new TimeSpan(10, 10, 10);

            //TimeSpanを加算
            DateTime answer = now.Add(addSpan);

            //加算した日時の表示
            Console.WriteLine(answer);

            //TimeSpan設定(日,時,分,秒)
            addSpan = new TimeSpan(1, 1, 1, 1);

            //TimeSpanの加算
            answer = now.Add(addSpan);

            //加算した日時を表示
            Console.WriteLine(answer);
        }

        //List6-12
        //ToXxxxXxxxStringメソッド
        static void dateTimeToXxxxXxxxStringExample()
        {
            //現在の日時を取得
            DateTime now = DateTime.Now;

            ////現在の日時の表示
            Console.WriteLine(now);

            //長い文字列形式の日付に変換して表示
            Console.WriteLine(now.ToLongDateString());

            //長い文字列形式の時刻に変換して表示
            Console.WriteLine(now.ToLongTimeString());

            //短い文字列形式の日付に変換して表示
            Console.WriteLine(now.ToShortDateString());

            //短い文字列形式の時刻に変換して表示
            Console.WriteLine(now.ToShortTimeString());
        }

        //List6-13
        //ToStringメソッド
        static void dateTimeToStringExample()
        {
            //現在の日時を取得
            DateTime now = DateTime.Now;

            //現在の日時を表示
            Console.WriteLine(now.ToString());

            //長い文字列形式の日付表示
            Console.WriteLine("D = " + now.ToString("D"));

            //長い文字列形式の時刻表示
            Console.WriteLine("T = " + now.ToString("T"));

            //短い文字列形式の日付表示
            Console.WriteLine("d = " + now.ToString("d"));

            //短い文字列形式の時刻表示
            Console.WriteLine("t = " + now.ToString("t"));

            //長い文字列形式の月と日だけ表示
            Console.WriteLine("m = " + now.ToString("m"));
        }
    }
}