using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ResultSclipt : MonoBehaviour 
{
	public ConfigScript config;

	public string scoreName;

	// Tatsuya add
	public ScoreScript score;

	List<int> scoreNumber = new List<int>();
	private Vector2 localPos;

	// Fade flg
	private bool fadeJudgeFlg;

	public FadeAnimationScript fadeIn;
	private List<GameObject> dispObject;

	private bool isFade = false;

	// Use this for initialization
	void Start () 
	{
		localPos = transform.localPosition;

		//GUIでfalseにすると必ずtrueになるのでここでもfalseに設定
		gameObject.SetActive(false);
	}
	void Update()
	{
		if (!fadeJudgeFlg)
		{
			fadeJudgeFlg = fadeIn.FadeJudge();
		}


		if (gameObject.activeInHierarchy && !isFade)
		{
			Text scoreText;

			scoreText = GetComponent<Text>();
			scoreText.text = score.myScore.ToString() + " ly";

			scoreText.rectTransform.sizeDelta = new Vector2(scoreText.preferredWidth, scoreText.rectTransform.sizeDelta.y);

			fadeIn.FadeInStart(scoreText);
			isFade = true;
		}
	}
	public bool GetFadeJudge()
	{
		return fadeJudgeFlg;
	}


}
