using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ResultScript : MonoBehaviour 
{
	public ScoreScript score;

	// Use this for initialization
	void Start () 
	{
		gameObject.transform.Find("Score").GetComponent<Text>().text += score.ScoreLoad().ToString();
		gameObject.transform.Find("BestScore").GetComponent<Text>().text += score.BestScoreLoad().ToString();
	}
}
