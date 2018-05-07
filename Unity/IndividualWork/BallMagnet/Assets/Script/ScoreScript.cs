using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreScript : MonoBehaviour 
{
	private int score = 0;

	void Start()
	{
		if (!PlayerPrefs.HasKey("BestScore"))
		{
			BestScoreWrite(0);
		}
	}
	
	// Update is called once per frame
	void Update () 
	{
		gameObject.GetComponent<Text>().text = "Score " + score.ToString();
	}

	public void SetScore(int value)
	{
		score += value;
	}

	public void BestScoreWrite(int value)
	{
		PlayerPrefs.SetInt("BestScore", value);
	}

	public void ScoreWrite()
	{
		PlayerPrefs.SetInt("Score", score);
		if (score > BestScoreLoad())
		{
			BestScoreWrite(score);
		}
	}
	public int ScoreLoad()
	{
		return PlayerPrefs.GetInt("Score");
	}

	public int BestScoreLoad()
	{
		return PlayerPrefs.GetInt("BestScore");
	}
}
