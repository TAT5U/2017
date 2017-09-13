/*Television.cs*/

/*2017-08-29
    Tatsuya Kano
        Chap-7*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassSample
{
    // List7-1
    // Television class
    //public class Television
    //{
    //    // Television power
    //    public bool power;

    //    // Current channel
    //    public int channel;

    //    // Current volume
    //    public int volume;

    //    // Channel lower limit
    //    public const int channelMin = 1;

    //    // Channel upper limit
    //    public const int channelMax = 12;

    //    // Volume lower limit
    //    public const int volumeMin = 0;

    //    // Volume upper limit
    //    public const int volumeMax = 40;

    //    // Television Power Supply Switch
    //    public void OnOff()
    //    {
    //        if (power == true)
    //        {
    //            // Off
    //            power = false;
    //        }
    //        else
    //        {
    //            // On
    //            power = true;
    //        }
    //    }

    //    // Channel Settings
    //    public void SetChannel(int c)
    //    {
    //        if (c >= channelMin && c <= channelMax)
    //        {
    //            // Set channel
    //            channel = c;
    //        }
    //    }

    //    // Channel+1
    //    public void ChannelUP()
    //    {
    //        if (channel < channelMax)
    //        {
    //            channel++;
    //        }
    //    }

    //    // Channel-1
    //    public void ChannelDown()
    //    {
    //        if (channel > channelMin)
    //        {
    //            channel--;
    //        }
    //    }

    //    // Volume+1
    //    public void VolumeUP()
    //    {
    //        if (volume < volumeMax)
    //        {
    //            volume++;
    //        }
    //    }

    //    // Volume-1
    //    public void VolumeDown()
    //    {
    //        if (volume > volumeMin)
    //        {
    //            volume--;
    //        }
    //    }
    //}

    // List7-4
    // Fix to private
    //public class Television
    //{
    //    private bool power;
    //    private int channel;
    //    private int volume;
    //    private const int channelMin = 1;
    //    private const int channelMax = 12;
    //    private const int volumeMin = 0;
    //    private const int volumeMax = 40;

    //    // Television Power Supply Switch
    //    public void OnOff()
    //    {
    //        if (power == true)
    //        {
    //            power = false;
    //        }
    //        else
    //        {
    //            power = true;
    //        }
    //    }

    //    public void SetChannel(int c)
    //    {
    //        if (c >= channelMin && c <= channelMax)
    //        {
    //            channel = c;
    //        }
    //    }

    //    // Channel+1
    //    public void ChannelUP()
    //    {
    //        if (channel < channelMax)
    //        {
    //            channel++;
    //        }
    //    }

    //    public void ChannelDown()
    //    {
    //        if (channel > channelMin)
    //        {
    //            channel--;
    //        }
    //    }

    //    public void VolumeUP()
    //    {
    //        if (volume < volumeMax)
    //        {
    //            volume++;
    //        }
    //    }

    //    public void VolumeDown()
    //    {
    //        if (volume > volumeMin)
    //        {
    //            volume--;
    //        }
    //    }
    //}

    // List7-5
    // Add property
    //public class Television
    //{
    //    private bool power;
    //    private int channel;
    //    private int volume;
    //    private const int channelMin = 1;
    //    private const int channelMax = 12;
    //    private const int volumeMin = 0;
    //    private const int volumeMax = 40;

    //    // Power property
    //    public bool Power
    //    {
    //        get
    //        {
    //            return power;
    //        }
    //        set
    //        {
    //            power = value;
    //        }
    //    }

    //    // Channel property
    //    public int Channel
    //    {
    //        get
    //        {
    //            return channel;
    //        }
    //        set
    //        {
    //            if (value >= channelMin && value <= channelMax)
    //            {
    //                channel = value;
    //            }
    //        }

    //    }

    //    // Volume property
    //    public int Volume
    //    {
    //        get
    //        {
    //            return volume;
    //        }
    //        set
    //        {
    //            if (value >= volumeMin && value <= volumeMax)
    //            {
    //                volume = value;
    //            }
    //        }
    //    }

    //    // Television Power Supply Switch
    //    public void OnOff()
    //    {
    //        if (power == true)
    //        {
    //            power = false;
    //        }
    //        else
    //        {
    //            power = true;
    //        }
    //    }

    //    // Channel+1
    //    public void ChannelUP()
    //    {
    //        if (channel < channelMax)
    //        {
    //            channel++;
    //        }
    //    }

    //    public void ChannelDown()
    //    {
    //        if (channel > channelMin)
    //        {
    //            channel--;
    //        }
    //    }

    //    public void VolumeUP()
    //    {
    //        if (volume < volumeMax)
    //        {
    //            volume++;
    //        }
    //    }

    //    public void VolumeDown()
    //    {
    //        if (volume > volumeMin)
    //        {
    //            volume--;
    //        }
    //    }
    //}

    // List7-7
    // Change read only property
    //public class Television
    //{
    //    private bool power;
    //    private int channel;
    //    private int volume;
    //    private const int channelMin = 1;
    //    private const int channelMax = 12;
    //    private const int volumeMin = 0;
    //    private const int volumeMax = 40;

    //    // Power property
    //    public bool Power
    //    {
    //        get
    //        {
    //            return power;
    //        }
    //    }

    //    public int Channel
    //    {
    //        get
    //        {
    //            return channel;
    //        }
    //        set
    //        {
    //            if (value >= channelMin && value <= channelMax)
    //            {
    //                channel = value;
    //            }
    //        }
    //    }

    //    // Volume property
    //    public int Volume
    //    {
    //        get
    //        {
    //            return volume;
    //        }
    //    }

    //    public void OnOff()
    //    {
    //        if (power == true)
    //        {
    //            power = false;
    //        }
    //        else
    //        {
    //            power = true;
    //        }
    //    }

    //    public void ChannelUP()
    //    {
    //        if (channel < channelMax)
    //        {
    //            channel++;
    //        }
    //    }

    //    public void ChannelDown()
    //    {
    //        if (channel > channelMin)
    //        {
    //            channel--;
    //        }
    //    }

    //    public void VolumeUP()
    //    {
    //        if (volume < volumeMax)
    //        {
    //            volume++;
    //        }
    //    }

    //    public void VolumeDown()
    //    {
    //        if (volume > volumeMin)
    //        {
    //            volume--;
    //        }
    //    }
    //}

    // List7-8
    // Automatic property
    //public class Television
    //{
    //    private int channel;
    //    private const int channelMin = 1;
    //    private const int channelMax = 12;
    //    private const int volumeMin = 0;
    //    private const int volumeMax = 40;

    //    // Power property
    //    public bool Power
    //    {
    //        get;
    //        private set;
    //    }

    //    public int Channel
    //    {
    //        get
    //        {
    //            return channel;
    //        }
    //        set
    //        {
    //            if (value >= channelMin && value <= channelMax)
    //            {
    //                channel = value;
    //            }
    //        }
    //    }

    //    // Volume property
    //    public int Volume
    //    {
    //        get;
    //        private set;
    //    }

    //    // Television Power Supply Switch
    //    public void OnOff()
    //    {
    //        if (Power == true)
    //        {
    //            Power = false;
    //        }
    //        else
    //        {
    //            Power = true;
    //        }
    //    }

    //    public void ChannelUP()
    //    {
    //        if (channel < channelMax)
    //        {
    //            channel++;
    //        }
    //    }

    //    public void ChannelDown()
    //    {
    //        if (channel > channelMin)
    //        {
    //            channel--;
    //        }
    //    }

    //    // Volume+1
    //    public void VolumeUP()
    //    {
    //        if (Volume < volumeMax)
    //        {
    //            Volume++;
    //        }
    //    }

    //    // Volume-1
    //    public void VolumeDown()
    //    {
    //        if (Volume > volumeMin)
    //        {
    //            Volume--;
    //        }
    //    }
    //}

    // List7-9
    // Add constructor
    public class Television
    {
        private int channel;
        private const int channelMin = 1;
        private const int channelMax = 12;
        private const int volumeMin = 0;
        private const int volumeMax = 40;

        // No argument constructor
        public Television()
        {
            Console.WriteLine("引数のないコンストラクターの呼び出し");
            Power = false;
            Channel = 1;
            Volume = 20;
        }

        // Two arguments constructor
        public Television(int channel, int volume)
        {
            Console.WriteLine("引数が2個のコンストラクターの呼び出し");
            Power = false;
            Channel = channel;
            Volume = volume;
        }

        // Three arguments constructor
        public Television(bool power, int channel, int volume)
        {
            Console.WriteLine("引数が3個のコンストラクターの呼び出し");
            Power = power;
            Channel = channel;
            Volume = volume;
        }

        // Power property
        public bool Power
        {
            get;
            private set;
        }

        public int Channel
        {
            get
            {
                return channel;
            }
            set
            {
                if (value >= channelMin && value <= channelMax)
                {
                    channel = value;
                }
            }
        }

        // Volume property
        public int Volume
        {
            get;
            private set;
        }

        // Television Power Supply Switch
        public void OnOff()
        {
            if (Power == true)
            {
                Power = false;
            }
            else
            {
                Power = true;
            }
        }

        public void ChannelUP()
        {
            if (channel < channelMax)
            {
                channel++;
            }
        }

        public void ChannelDown()
        {
            if (channel > channelMin)
            {
                channel--;
            }
        }

        // Volume+1
        public void VolumeUP()
        {
            if (Volume < volumeMax)
            {
                Volume++;
            }
        }

        // Volume-1
        public void VolumeDown()
        {
            if (Volume > volumeMin)
            {
                Volume--;
            }
        }
    }
}
