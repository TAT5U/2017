using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreManager : MonoBehaviour 
{
	public Player player_;

	private int score_;
	private int scoreWriteCount_;
	private float timeDistance_;
	
	// Update is called once per frame
	void Update () 
	{
		timeDistance_ += Time.deltaTime;

		if (player_.IsRunning() && timeDistance_ >= 0.5)
		{
			score_ += 1;
			GetComponent<Text>().text = score_.ToString() + "m";
			timeDistance_ = 0;
			scoreWriteCount_ = 0;
		}
		else if (scoreWriteCount_ <= 0)
		{
			PlayerPrefs.SetInt("Score", score_);
			scoreWriteCount_++;
		}
	}
}
