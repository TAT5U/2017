/*2017-06-08
    狩野 達哉
        Chap5-EX-2*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Guess
{
    class Program
    {
        static void Main(string[] args)
        {
            //答えとなる数を設定
            const int GuessAns = 32;

            //最小値・最大値・入力された値・当てるまでの回数の変数
            int min = 0, max = 100, ans = 0, cnt = 1;

            //当たるまでループ
            while (true)
            {
                //表示
                Console.Write("{0}から{1}の間の数値を当ててください。 >", min, max);

                //入力された値が不正(数字以外・最小値未満や最大値以上)のときはエラー処理
                if (int.TryParse(Console.ReadLine(),out ans)==true&&ans<=max&&ans>=min)
                {
                    //答えの値が小さいとき
                    if (ans < GuessAns)
                    {
                        Console.WriteLine("答はもっと大きいです。");

                        //最小値変更
                        min = ans;
                    }

                    //答えの値が大きいとき
                    else if (ans > GuessAns)
                    {
                        Console.WriteLine("答はもっと小さいです。");

                        //最大値変更
                        max = ans;
                    }

                    //当たったとき
                    else
                    {
                        Console.WriteLine("おめでとう。{0}回目で当たりました。", cnt);
                        break;
                    }

                    //改行
                    Console.WriteLine();

                    //回数カウント
                    cnt++;
                }
                else
                {
                    //例外の発生時の表示
                    Console.WriteLine("入力値が正しくありません。再入力してください。");

                    //ループの先頭に戻る
                    continue;
                }

            }

            //入力待ち状態にして確認する
            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();
        }
    }
}
