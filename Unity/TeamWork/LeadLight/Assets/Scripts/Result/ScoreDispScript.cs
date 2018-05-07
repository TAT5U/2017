using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreDispScript : MonoBehaviour 
{
	// 番号の画像
	public Sprite[] numberImage = new Sprite[13];
	private GameObject numberObject;
	private RectTransform numberImageRect;
	private int numCount = 0;
	private Color rankImageColor;

	private List<GameObject> dispObject;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
	}

	public List<GameObject> ScoreDisp(List<int> number, string name, Vector2 pos, bool flg)
	{
		dispObject = new List<GameObject>();

		while (numCount < number.Count)
		{
			numberObject = Instantiate(GameObject.Find(name));
			rankImageColor = numberObject.GetComponent<Image>().color;
			numberImageRect = numberObject.GetComponent<RectTransform>();
			numberImageRect.SetParent(transform, false);
			//numberImageRect.localPosition = new Vector2(numberImageRect.localPosition.x - (numberImageRect.sizeDelta.x * numCount) * 0.30f, localPos.y);
			numberImageRect.localPosition = new Vector2(numberImageRect.localPosition.x - (numberImageRect.sizeDelta.x * numCount) * 0.30f, pos.y);
			numberImageRect.GetComponent<Image>().sprite = numberImage[number[numCount]];
			dispObject.Add(numberObject);
			if (flg)
			{
				rankImageColor = numberImageRect.GetComponent<Image>().color;
				rankImageColor.a = 1.0f;
				numberImageRect.GetComponent<Image>().color = rankImageColor;
			}

			numCount++;
		}
		numCount = 0;
		return dispObject;
	}
}
