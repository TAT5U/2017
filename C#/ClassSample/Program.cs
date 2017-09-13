using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassSample
{
    class Program
    {
        // List7-2
        // Television class instantiation
        //static void Main(string[] args)
        //{
        //    Television tv = new Television();
        //}

        // List7-3
        // Access class members
        //static void Main(string[] args)
        //{
        //    Television tv = new Television();
        //    Console.WriteLine("10チャンネルを設定します。");

        //    // Instance method
        //    tv.SetChannel(10);

        //    Console.WriteLine("TVは{0}チャンネルです。", tv.channel);
        //    Console.WriteLine("チャンネルを+2します。");

        //    // Instance method
        //    tv.ChannelUP();
        //    tv.ChannelUP();

        //    Console.WriteLine("TVは{0}チャンネルです。", tv.channel);

        //    Console.WriteLine("チャンネルを-1します。");

        //    // Instance method
        //    tv.ChannelDown();

        //    Console.WriteLine("TVは{0}チャンネルです。", tv.channel);

        //    Console.WriteLine("終了するには何かキーを押してください。");
        //    Console.Read();

        //}

        // List7-6
        // Correction class members
        //static void Main(string[] args)
        //{
        //    Television tv = new Television();
        //    Console.WriteLine("10チャンネルを設定します。");

        //    // Instance method
        //    tv.Channel = 10;

        //    Console.WriteLine("TVは{0}チャンネルです。", tv.Channel);
        //    Console.WriteLine("チャンネルを+2します。");

        //    // Instance method
        //    tv.ChannelUP();
        //    tv.ChannelUP();

        //    Console.WriteLine("TVは{0}チャンネルです。", tv.Channel);

        //    Console.WriteLine("チャンネルを-1します。");

        //    // Instance method
        //    tv.ChannelDown();

        //    Console.WriteLine("TVは{0}チャンネルです。", tv.Channel);

        //    Console.WriteLine("終了するには何かキーを押してください。");
        //    Console.Read();

        //}

        // List7-10
        // Calling the constructor
        static void Main(string[] args)
        {
            Television tv = new Television();

            Console.WriteLine("TV1  電源 : {0}    チャンネル : {1} 音量 : {2}", tv.Power ? "ON" : "OFF", tv.Channel, tv.Volume);
            Console.WriteLine("チャンネルを+2します。");
            tv.ChannelUP();
            tv.ChannelUP();
            Console.WriteLine("TV1は{0}チャンネルです。", tv.Channel);

            Console.WriteLine("音量を-2します。");
            tv.VolumeDown();
            tv.VolumeDown();
            Console.WriteLine("TV1の音量は{0}です。", tv.Volume);

            Television tv2 = new Television(8, 25);

            Console.WriteLine("TV2  電源 : {0}    チャンネル : {1} 音量 {2}", tv2.Power ? "ON" : "OFF", tv2.Channel, tv2.Volume);
            Console.WriteLine("チャンネルを+2します。");
            tv2.ChannelUP();
            tv2.ChannelUP();
            Console.WriteLine("TV2は{0}チャンネルです。", tv2.Channel);

            Console.WriteLine("音量を-2します。");
            tv2.VolumeDown();
            tv2.VolumeDown();
            Console.WriteLine("TV2の音量は{0}です。", tv2.Volume);

            Console.WriteLine("終了するには何かキーを押してください。");
            Console.Read();

        }
    }
}
