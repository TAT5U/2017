using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Player : MonoBehaviour 
{
	public TimeManager time_;

	private Move moveScript_;
	private int enemyStrikeCount_ = 0;


	private const int kEnemyCount = 5;


	void Start()
	{
		moveScript_ = gameObject.AddComponent<Move>();
		time_.GameStart();
	}
	
	// Update is called once per frame
	void Update () 
	{
		if (Input.GetMouseButtonDown(0))
		{
			moveScript_.TargetClick();
		}
		if (Input.GetMouseButtonUp(0))
		{
			moveScript_.TargetRelease();
		}
	}

	void OnCollisionEnter2D(Collision2D col)
	{
		if (col.gameObject.tag == "Enemy")
		{
			col.gameObject.GetComponent<Enemy>().EnemyDestrory();
			enemyStrikeCount_++;
		}
		StrikeJudge();
	}

	void StrikeJudge()
	{
		if (enemyStrikeCount_ == kEnemyCount)
		{
			time_.SetTime();
			SceneManager.LoadScene(2);
		}
	}
}
