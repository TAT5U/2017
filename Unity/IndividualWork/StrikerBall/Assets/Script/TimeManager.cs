using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimeManager : MonoBehaviour 
{
	private bool isStart_ = false;
	private float timeCount_ = 0.0f;

	private string time_ = "Time";
	private string bestTime_ = "BestTime";

	void Start()
	{
		if (!PlayerPrefs.HasKey(bestTime_))
		{
			PlayerPrefs.SetFloat(bestTime_, 9999.0f);
		}
	}

	public void GameStart()
	{
		isStart_ = true;
	}
	
	// Update is called once per frame
	void Update () 
	{
		if (isStart_)
		{
			timeCount_ += Time.deltaTime;
		}
	}

	public float GetTime()
	{
		return timeCount_;
	}

	public void SetTime()
	{
		PlayerPrefs.SetFloat(time_, timeCount_);
		SetBestTime();
	}


	void SetBestTime()
	{
		if (timeCount_ > PlayerPrefs.GetFloat(bestTime_)) return;

		PlayerPrefs.SetFloat(bestTime_, timeCount_);
	}
}
