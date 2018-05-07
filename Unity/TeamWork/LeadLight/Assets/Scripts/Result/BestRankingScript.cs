using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BestRankingScript : MonoBehaviour 
{
	// Tatsuya add
	public ScoreScript score;
	public string bestRankingName;
	public FadeAnimationScript fadeIn;
	public ResultSclipt resultFade;

	private int BestScore;
	private List<int> bestScoreNumber = new List<int>();
	private int i = 0;
	private Vector2 localPos;
	private bool isFade = false;

	// Use this for initialization
	void Start () 
	{
		localPos = transform.localPosition;
		gameObject.SetActive(false);
	}

	void Update()
	{
		if (gameObject.activeInHierarchy && !isFade && resultFade.GetFadeJudge())
		{
			BestScore = score.ReadScore()[0];
			Text scoreText;
			scoreText = GetComponent<Text>();
			scoreText.text = BestScore.ToString() + " ly";
			scoreText.rectTransform.sizeDelta = new Vector2(scoreText.preferredWidth, scoreText.rectTransform.sizeDelta.y);
			fadeIn.FadeInStart(scoreText);
			isFade = true;
		}
	}
}
