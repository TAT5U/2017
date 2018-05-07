using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;


public class ScoreScript : MonoBehaviour 
{
	private List<int> data;
	private StreamReader readScore;
	public int myScore;

	//const string key = "0x474C5332303137";
	public void WriteScore(int score)
	{
		myScore = score;

        // Tatsuya changed
        if (Application.platform == RuntimePlatform.IPhonePlayer)
        {
#if UNITY_IOS
        	UnityEngine.iOS.Device.SetNoBackupFlag(UnityEngine.Application.persistentDataPath + "/score.dat");
#endif
	    	File.AppendAllText(UnityEngine.Application.persistentDataPath + "/score.dat", score.ToString() + "\n");
        }
        else if (Application.platform == RuntimePlatform.Android)
		{
			if (!Directory.Exists(Application.persistentDataPath))
			{
				Directory.CreateDirectory(Application.persistentDataPath);
			}
			File.AppendAllText(UnityEngine.Application.persistentDataPath + "/score.dat", score.ToString() + "\n");
		}

		// Just in case
		else
		{
			if (!Directory.Exists("Documents"))
			{
				Directory.CreateDirectory("Documents");
			}
			File.AppendAllText("Documents/score.dat", score.ToString() + "\n");
		}
	}

	public List<int> ReadScore()
	{
		data = new List<int>();

		// Tatsuya changed
		if ((Application.platform == RuntimePlatform.Android) || (Application.platform == RuntimePlatform.IPhonePlayer))
		{
			readScore = new StreamReader(UnityEngine.Application.persistentDataPath + "/score.dat");
		}

		// Just in case
		else
		{
			if (!Directory.Exists("Documents"))
			{
				Directory.CreateDirectory("Documents");
			}
			readScore = new StreamReader("Documents/score.dat");
		}

		while (readScore.Peek() >= 0)
		{
			data.Add(int.Parse(readScore.ReadLine()));
		}
		readScore.Close();
		SortScore(data.Count);
		data.Reverse();

		return data;
	}

	private void SortScore(int scoreCount)
	{
		int i = 0, k = 0, work = 0;
		bool sortFlg = false;

		// Bubble
		do
		{
			sortFlg = false;
			while (i < scoreCount - 1 - k)
			{
				if (data[i] > data [i + 1])
				{
					sortFlg = true;
					work = data[i];
					data[i] = data[i + 1];
					data[i + 1] = work;
				}
				i++;
			}
			i = 0;
			k++;
		} while (sortFlg == true);
	}
}
