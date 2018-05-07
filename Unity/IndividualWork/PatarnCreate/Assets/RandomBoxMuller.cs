using System.Collections;
using System.Collections.Generic;
using System;
using System.Linq;
using System.Text;

namespace RandomBoxMuller
{

    /// <summary>
    /// ボックス＝ミュラー法
    /// 公式： z1 = Math.sqrt(-2.0 * Math.Log(X)) * Math.Cos(2.0 * Math.PI * Y)
    /// 公式： z2 = Math.sqrt(-2.0 * Math.Log(X)) * Math.Sin(2.0 * Math.PI * Y)
    /// 
    /// また平均値 mu,分散 sigma2乗に従う正規分布は,
    /// 公式： z1 = sigma * Math.sqrt(-2.0 * Math.Log(X)) * Math.Cos(2.0 * Math.PI* Y) + mu
    /// 公式： z2 = sigma * Math.sqrt(-2.0 * Math.Log(X)) * Math.Sin(2.0 * Math.PI * Y) + mu   で求められる
    /// 
    /// XとYは一様分布に従う数。一様分布に従う数は線形合同法を用いることで求める。(randやRandomなどの乱数生成はこれにあたる。)
    /// 上のXとYからガウス分布(正規分布）に従うz1,z2を与えるこの変換をボックス=ミュラー変換と呼ぶ。
    /// これのガウス分布に従う確率変数を生成させる方法のことをボックス=ミュラー法という。
    /// 
    /// z1,z2は,平均0,分散1の標準ガウス分布N(0,1)に従う互いに独立な確率変数となる。
    /// 
    /// </summary>
    public class RandomBoxMuller
    {

        private Random random;


        /// <summary>
        /// コンストラクタ(シード値はシステム起動後の経過時間とする)
        /// </summary>
        public RandomBoxMuller()
        {
            //using SystemにEvironmentは入っている
            //引数はTickCountはシステム起動後のミリ秒単位の経過時間を取得している
            random = new Random(Environment.TickCount);
        }


        /// <summary>
        /// コンストラクタ(シード値 設定可能)
        /// </summary>
        /// <param name="seed"> シード値 </param>
        public RandomBoxMuller(int seed)
        {
            random = new Random(seed);
        }

        public double next(double mu = 0.0,double sigma = 1.0,bool getCos = true)
        {
            if(getCos)
            {
                double rand = 0.0;
                while ((rand = random.NextDouble()) == 0.0) ;
                double rand2 = random.NextDouble();

                //ここで公式を使用
                double normrand = Math.Sqrt(-2.0 * Math.Log(rand)) * Math.Cos(2.0 * Math.PI * rand2);

                //分散値を乗算して,最後に平均を足す。
                normrand = normrand * sigma + mu;
                return normrand;
            }
            else
            {
                double rand = 0.0;
                while ((rand = random.NextDouble()) == 0.0) ;
                double rand2 = random.NextDouble();
                double normrand = Math.Sqrt(-2.0 * Math.Log(rand)) * Math.Sin(2.0 * Math.PI * rand2);
                normrand = normrand * sigma + mu;
                return normrand;
            }
        }

        public double[] nextPair(double mu = 0.0,double sigma = 1.0)
        {
            double[] normrand = new double[2];
            double rand = 0.0;
            while ((rand = random.NextDouble()) == 0.0) ;
            double rand2 = random.NextDouble();
            normrand[0] = Math.Sqrt(-2.0 * Math.Log(rand)) * Math.Cos(2.0 * Math.PI * rand2);
            normrand[0] = normrand[0] * sigma + mu;
            normrand[1] = Math.Sqrt(-2.0 * Math.Log(rand)) * Math.Sin(2.0 * Math.PI * rand2);
            normrand[1] = normrand[1] * sigma + mu;

            return normrand;
        }
       


    }
}
