using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreConvert : MonoBehaviour 
{
	private int numberMaxLength = 0;

	private List<int> scoreNum = new List<int>();
	private int scoreDigit = 0;

	private string numberSum;


	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public List<int> ConvertToScoreNumImage(int num, bool flg, bool rankFlg)
	{

		//objectName = gameObject.transform.parent.gameObject.name + name;
		scoreNum = new List<int>();

		scoreNum.Add(11);

		scoreDigit = num;
		while (scoreDigit != 0)
		{
			// 分割
			num = scoreDigit % 10;
			scoreDigit = scoreDigit / 10;
			scoreNum.Add(num);
		}
		if (flg)
		{
			numberMaxLength = scoreNum.Count;
		}
		while (scoreNum.Count < numberMaxLength)
		{
			scoreNum.Add(12);
		}
		if (rankFlg)
		{
			scoreNum.Add(10);

			//scoreNum.Add(i);
		}

		return scoreNum;
	}
}
