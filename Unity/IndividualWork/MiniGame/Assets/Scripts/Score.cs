using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//GUI (Text いじるときなど)に必要
using UnityEngine.UI;

public class Score : MonoBehaviour {

	public Text score;
	public Wall wall;
	// Use this for initialization
	void Start () {
		int x = 0;
		//x = wall.GetScore();

		score.text = "Your Score " + wall.GetScore().ToString();
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
